#version 330

uniform sampler2D u_Texture;

layout(location = 0) out vec4 Color;

in vec2 TexCoord;

void main()
{
	Color = texture(u_Texture, TexCoord);
}