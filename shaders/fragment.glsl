#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D ourTexture; // Base texture

void main() {
    FragColor = texture(ourTexture, TexCoord);
}

