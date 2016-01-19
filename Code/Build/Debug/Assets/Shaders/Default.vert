#version 330

in vec3 i_VertexPos;
in vec2 i_TexCoord;
in vec3 i_Normal;

layout (std140) uniform Matrices
{
	uniform mat4 u_MVMatrix;
	uniform mat4 u_PMatrix;
	uniform mat4 u_NormalMatrix;	
};


uniform vec3 u_Specular;
uniform vec3 u_Diffuse;
uniform float u_Illumination;
uniform vec3 u_AmbientUpper;
uniform vec3 u_AmbientLower;

out vec2 TexCoord;
out float Diffuse;
out vec3 Ambient;
out float Specular;
out float Attenuation;


const vec3 DIRECTION = vec3(0.0, 1.0, 0.0);
const float MAX_DARKNESS = 0.08;

void main()
{
	TexCoord = i_TexCoord;

	//get the normal
	vec3 t = (u_NormalMatrix * vec4(i_Normal, 1)).xyz;

	//get the diffuse coefficient
	Diffuse = max(dot(t,-DIRECTION), MAX_DARKNESS) * u_Illumination;

	//get the ambient coefficient
	Ambient = mix(u_AmbientUpper, u_AmbientLower, (t.y + 1) / 2) * u_Illumination;


	vec3 view = ((u_MVMatrix)*vec4(i_VertexPos,1)).xyz;

	Attenuation = 200 / distance(view, vec3(0.0));

	Specular = 0.0;
	if(Diffuse > MAX_DARKNESS)
	{
		Specular = max(0.0, dot(-normalize(view), reflect(DIRECTION, t)));
		Specular = pow(Specular, 1.0);
	}

	//set the position of the vertex
	vec4 position = (u_PMatrix* u_MVMatrix)*vec4(i_VertexPos,1);
	gl_Position = position;  
}