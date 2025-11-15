#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <gl_util.h>
#include <input.h>
#include <shader.h>
#include <state.h>
#include <voxel.h>

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

#define WORLD_SIZE_X 64
#define WORLD_SIZE_Y 64
#define WORLD_SIZE_Z 64
#define WORLD_VOLUME WORLD_SIZE_X * WORLD_SIZE_Y * WORLD_SIZE_Z

GLuint compute_program;
float now, last_time;

GLuint output_texture, ssbo_voxels, quadVBO, quadVAO, quadEBO;

typedef enum Voxel_Type {
    VOX_GRASS,
    VOX_WOOD,
    VOX_WATER,
    VOX_GLASS,
    VOX_DIAMOND,
    VOX_JELLY,
} Voxel_Type;

const Voxel voxels[] = {
    {3.0f, 0.0f, 0.0f},
    {3.0f, 0.0f, 0.0f},
    {1.33f, 0.0f, 0.0f},
    {1.5f, 0.0f, 0.0f},
    {2.42f, 0.0f, 0.0f},
    {1.38f, 0.0f, 1.0f},
};

void init(State *state) {
    GLuint compute_shader = make_shader("shaders/compute.glsl", GL_COMPUTE_SHADER);
    compute_program = glCreateProgram();
    glAttachShader(compute_program, compute_shader);
    glLinkProgram(compute_program); //FIXME: check err

    glGenTextures(1, &output_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, output_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindImageTexture(0, output_texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);

    // Room parameters (positioned near the center of the world)
    int roomMinX = 12;
    int roomMaxX = 51;
    int roomMinZ = 12;
    int roomMaxZ = 51;
    int floorY = 1;
    int wallHeight = 10;

    Voxel_Object voxel_data[WORLD_VOLUME];

    // Create a grass floor
    for (int x = roomMinX; x <= roomMaxX; ++x) {
        for (int z = roomMinZ; z <= roomMaxZ; ++z) {
            int index = x + floorY * WORLD_SIZE_X + z * WORLD_SIZE_X * WORLD_SIZE_Y;
            voxel_data[index] = voxel_obj_create(voxels[VOX_GRASS], make_color_rgba(100, 200, 80, 255), ivec3_int(x, floorY, z));
        }
    }

    // Build walls: 3 wood walls and 1 glass wall (glass will be on the +X side)
    for (int y = floorY + 1; y <= floorY + wallHeight; ++y) {
        // North wall (z = roomMinZ) - WOOD
        for (int x = roomMinX; x <= roomMaxX; ++x) {
            int index = x + y * WORLD_SIZE_X + roomMinZ * WORLD_SIZE_X * WORLD_SIZE_Y;
            voxel_data[index] = voxel_obj_create(voxels[VOX_WOOD], make_color_rgba(140, 90, 50, 255), ivec3_int(x, y, roomMinZ));
        }

        // South wall (z = roomMaxZ) - WOOD
        for (int x = roomMinX; x <= roomMaxX; ++x) {
            int index = x + y * WORLD_SIZE_X + roomMaxZ * WORLD_SIZE_X * WORLD_SIZE_Y;
            voxel_data[index] = voxel_obj_create(voxels[VOX_WOOD], make_color_rgba(140, 90, 50, 255), ivec3_int(x, y, roomMaxZ));
        }

        // West wall (x = roomMinX) - WOOD
        for (int z = roomMinZ; z <= roomMaxZ; ++z) {
            int index = roomMinX + y * WORLD_SIZE_X + z * WORLD_SIZE_X * WORLD_SIZE_Y;
            voxel_data[index] = voxel_obj_create(voxels[VOX_WOOD], make_color_rgba(140, 90, 50, 255), ivec3_int(roomMinX, y, z));
        }

        // East wall (x = roomMaxX) - GLASS (slightly transparent)
        for (int z = roomMinZ; z <= roomMaxZ; ++z) {
            int index = roomMaxX + y * WORLD_SIZE_X + z * WORLD_SIZE_X * WORLD_SIZE_Y;
            voxel_data[index] = voxel_obj_create(voxels[VOX_GLASS], make_color_rgba(100, 100, 230, 40), ivec3_int(roomMaxX, y, z));
        }
    }

    // Create a red jelly sphere inside the room
    int cx = (roomMinX + roomMaxX) / 2;
    int cz = (roomMinZ + roomMaxZ) / 2;
    int cy = floorY + 6;
    int radius = 5;
    for (int x = cx - radius; x <= cx + radius; ++x) {
        for (int y = cy - radius; y <= cy + radius; ++y) {
            for (int z = cz - radius; z <= cz + radius; ++z) {
                if (x < 0 || x >= WORLD_SIZE_X || y < 0 || y >= WORLD_SIZE_Y || z < 0 || z >= WORLD_SIZE_Z) continue;
                int dx = x - cx; int dy = y - cy; int dz = z - cz;
                if (dx*dx + dy*dy + dz*dz <= radius*radius) {
                    int index = x + y * WORLD_SIZE_X + z * WORLD_SIZE_X * WORLD_SIZE_Y;
                    voxel_data[index] = voxel_obj_create(voxels[VOX_JELLY], make_color_rgba(240, 100, 200, 100), ivec3_int(x, y, z));
                }
            }
        }
    }

    glGenBuffers(1, &ssbo_voxels);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo_voxels);
    glBufferData(GL_SHADER_STORAGE_BUFFER, WORLD_VOLUME * sizeof(Voxel_Object), voxel_data, GL_STATIC_DRAW);

    // Vincula o buffer ao ponto de ligação 2 (corresponderá ao binding no shader)
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, ssbo_voxels);

    //// UBO para a câmera
    //struct CameraData {
    //    glm::mat4 invProjection;
    //    glm::mat4 invView;
    //    glm::vec3 cameraPos;
    //};

    //GLuint uboCamera;
    //glGenBuffers(1, &uboCamera);
    //glBindBuffer(GL_UNIFORM_BUFFER, uboCamera);
    //glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraData), NULL, GL_DYNAMIC_DRAW);
    //glBindBufferBase(GL_UNIFORM_BUFFER, 1, uboCamera);

    //glBindBuffer(GL_UNIFORM_BUFFER, 0);


    // Configurar o Quad renderizado na tela

    Vector2 quad_vertices[] = {
        {{ 1.0f, 1.0f }},
        {{ 1.0f,-1.0f }},
        {{-1.0f,-1.0f }},
        {{-1.0f, 1.0f }},
    };

    int quad_indices[] = {
        0, 1, 3,
        1, 2, 3,
    };

    glGenVertexArrays(1, &quadVAO);
    glBindVertexArray(quadVAO);

    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &quadEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_indices), quad_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), 0);
    glEnableVertexAttribArray(0); // Ativar o atributo

    glBindVertexArray(0);

    shader_use(state->renderer->shader);
    glUniform1i(glGetUniformLocation(state->renderer->shader->program, "screenTexture"), 0);

    last_time = 0;
}

void tick(State *state) {
    //TODO: HERE for input
    process_input(state->window->window);
    return;
}

void update(State *state) {
    now = (float)glfwGetTime();
    printf("FPS: %f\n", 1.0f / (now - last_time));
    last_time = now;
}

void render(State *state) {
    glUseProgram(compute_program);
    //Vincular recursos
    glBindImageTexture(0, output_texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, ssbo_voxels);
    // Dispara as threads do compute shader.
    //  Dividimos o tamanho da tela pelo tamanho do grupo de trabalho definido no shader.
    //  Se o tamanho do grupo for 8x8, por exemplo:
    glDispatchCompute(SCR_WIDTH / 8, SCR_HEIGHT / 8, 1);

    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    // Desenhar o quad na tela
    int width, height;
    glfwGetFramebufferSize(state->window->window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    shader_use(state->renderer->shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, output_texture);

    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    glfwSwapBuffers(state->window->window);
    glfwPollEvents();
}

void destroy(State *state) {
    //deallocate all resources
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadEBO);
    glDeleteBuffers(1, &ssbo_voxels);
    glDeleteTextures(1, &output_texture);
    glDeleteProgram(compute_program);
    state_delete(&state);
    glfwTerminate();
}

int main(void) {
    Window *win = NULL;
    Camera *main_cam = NULL;
    Shader *main_shader = NULL;
    Renderer *renderer = NULL;
    State *state = NULL;
    
    WinSettings settings = (WinSettings){
        .name = "Hello World!",
        .inv_border = false,
        .inv_bg = false,
        .size = vec2_float(SCR_WIDTH, SCR_HEIGHT)
    };
    win = window_create(settings);
    if(!win->window) goto main_clean;
    
    Camera_Args cam_arg;
    cam_arg.p_fov = 90;
    main_cam = camera_create(win, PERSPECTIVE_CAMERA, cam_arg);
    main_shader = shader_create("shaders/vert.glsl", "shaders/frag.glsl");
    if(!main_cam || !main_shader) goto main_clean;
    renderer = renderer_create(main_cam, main_shader, vec4_one());
    if(!renderer) goto main_clean;
    
    state = state_create(win, renderer, &init, &tick, &update, &render, &destroy);
    if(!state) goto main_clean;
    state_loop(state);
    return 0;

main_clean:
    if(win) window_delete(&win);
    if(main_cam) camera_delete(&main_cam);
    if(main_shader) shader_delete(&main_shader);
    if(renderer) renderer_delete(&renderer);
    if(state) state_delete(&state);
    return -1;
}
