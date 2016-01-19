#version 330

uniform sampler2D u_Texture;

layout (std140) uniform Matrices
{
	uniform mat4 u_MVMatrix;
	uniform mat4 u_PMatrix;
	uniform mat4 u_NormalMatrix;	
};

in vec2 TexCoord;
in float Diffuse;
in vec3 Ambient;
in float Specular;
in float Attenuation;

out vec4 Color;

const float AMBIENT_ATTENUATION = 0.03;
const vec3 GAMMA_CONSTANT = vec3(1.0/1.2);

void main()
{
	
	//pass the color of the texture
	vec4 color = texture(u_Texture, TexCoord);
	color= vec4((color.xyz* min(Attenuation*(Diffuse), 1.0)) + Ambient * Specular * AMBIENT_ATTENUATION ,color.a );
	//do some gamma corection
	Color = vec4(color);
}