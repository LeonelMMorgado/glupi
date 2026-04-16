#version 330 core
layout (location = 0) in vec3 aPos;		// Position attribute
layout (location = 1) in vec3 normal;	// normal of vertex
layout (location = 2) in vec2 uv;		// uv of vertex
//layout (location = 1) in vec2 aTexCoord; // Texture coordinate

uniform vec4 uColor;
out vec4 vColor;

uniform mat4 model; // Model matrix
uniform mat4 view;  // View matrix
uniform mat4 projection; // Projection matrix

//out vec2 TexCoord;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	vColor = uColor;
    //TexCoord = aTexCoord;
}

