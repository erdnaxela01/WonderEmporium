#ifndef __MESH_H
#define __MESH_H

#include <Windows.h>
#include <gl\GL.h>
#include <vector>

//forward declaration
class ShaderProgram;

//this is your mesh,
//all your vertices are stored here
//it provides a few useful functions and will set up all the attributes that it has
class Mesh
{
public:

	//this will set all the attributes that you would like to set for the mesh
	struct AttributeData
	{
		//set all the attribute data
		AttributeData(const char* tname, unsigned short tcount, unsigned short tstride, unsigned short toffset = 0, bool tnormalized = false, GLenum atribType = GL_FLOAT);
		unsigned short stride;
		unsigned short offset;
		unsigned short count;
		bool normalized;
		const char* name;
        GLenum type;
	};

	Mesh();

	Mesh(Mesh& m) = delete;
	Mesh& operator=(Mesh&) = delete;

	Mesh(Mesh&& m);
	Mesh& operator==(Mesh&&);

	virtual ~Mesh();

	//draw the mesh
	void DrawMesh(ShaderProgram* program);

	//create a mesh passing in the vertex data, number of them, and number of triangles
    void Create(void* data, unsigned int size, unsigned int verticeCount, std::vector<AttributeData>& attributes, GLenum drawMode = GL_TRIANGLES, GLenum drawType = GL_STATIC_DRAW);


	//moves the attributes
    void Create(void* data, unsigned int size, unsigned int verticeCount, std::vector<AttributeData>&& attributes, GLenum drawMode = GL_TRIANGLES, GLenum drawType = GL_STATIC_DRAW);

    //change the data inside the vbo
    void ChangeData(void* data, unsigned int size, unsigned int verticeCount, std::vector<AttributeData>& attributes, GLenum drawMode = GL_TRIANGLES);

    //change the data within the vbo
    void ChangeData(void* data, unsigned int size, unsigned int verticeCount, std::vector<AttributeData>&& attributes, GLenum drawMode = GL_TRIANGLES);
private:
	//generate the vertex buffer
	void GenerateVertexBuffer(void* vertices, unsigned int size, GLenum drawType);

	//the vbo
	unsigned int m_VBO;
	//all the attributes
	std::vector<AttributeData> m_Attributes;
	//the draw mode
	GLenum m_DrawMode;

    GLenum m_DrawType;

    //the size of the previous data
    unsigned int m_Size;

	//the number of triangles
	unsigned int m_Count;
};


#endif //__MESH_H