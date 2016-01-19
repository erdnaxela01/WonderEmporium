#ifndef __MODEL_PARSER_H
#define __MODEL_PARSER_H

#include <fstream>
#include <string>
#include <vector>

#include "Model.h"
#include "ModelPool.h"

struct ParseData
{
    float x;
    float y;
    float z;
    float nX;
    float nY;
    float nZ;
    float tX;
    float tY;
};

struct Paths
{
	Paths(const char* tex, const char* model, const char* file);

	const char* texturePath;
	const char* modelPath;
	const char* fileName;
};

struct Attributes
{
	Attributes(const char* pos, const char* norm, const char* tex);

	const char* position;
	const char* normal;
	const char* texCoord;
};


//this class will parse obj files into models
//this class isnt that great, the parser needs definite work but it works for now
class Parser
{
public:
    static void Parse(Paths paths,Attributes attrib, Model* m, float width = 1.0f, float height = 1.0f, float depth = 1.0f);


private:
    //add a position to a vertex
    static void AddPosition(std::vector<ParseData>* vertices, std::string& line, unsigned int* count);
    //add a normal to a vertex
    static void AddNormal(std::vector<ParseData>* vertices, std::string& line, unsigned int* count);
    //add a texture to a vertex
    static void AddTextureCoord(std::vector<ParseData>* vertices, std::string& line, unsigned int* count);

	static void SetVertices(std::vector<ParseData>* vertices, std::vector<ParseData>* allVertices, std::string& line);

	static void SetMaterial(Material* mat, std::string& line, const char* path, const char* name, const char* texPath);

    //the file
    static std::ifstream s_File;
	static ModelPool s_Pool;
};

#endif //__MODEL_PARSER_H