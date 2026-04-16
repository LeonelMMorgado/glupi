#version 330 core
in vec4 vColor;
out vec4 FragColor;
//in vec2 TexCoord;

// texture sampler
//uniform sampler2D ourTexture;

void main()
{
	FragColor = vColor;//texture(ourTexture, TexCoord);
}
