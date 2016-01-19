#version 330

layout (std140) uniform Screen
{
	uniform vec2 u_ScreenSize;
	uniform vec2 u_ScreenPosition;
};

in vec2 i_Position;
in vec2 i_TexCoord;


out vec2 TexCoord;

void main()
{

	TexCoord = i_TexCoord;
	vec2 pos = (i_Position + vec2((u_ScreenSize* u_ScreenPosition)  - (u_ScreenSize * 0.5))) / (u_ScreenSize * 0.5);
	gl_Position = vec4(pos, 0, 1);
}