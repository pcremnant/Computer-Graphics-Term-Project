#include "CModel.h"

CModel::CModel(GLuint drawtype, GLuint layout) : nLayoutSize(layout), nDrawType(drawtype) {}
void CModel::SetObjectVertex(const char* ObjectFile)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	vec3Buffer temp_vertices;
	vec2Buffer temp_uvs;
	vec3Buffer temp_normals;

	std::ifstream readFile;
	readFile.open(ObjectFile);

	while (!readFile.eof()) {

		char lineHeader[128];
		readFile >> lineHeader;

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			for (int i = 0; i < 3; ++i) {
				readFile >> vertex[i];
			}
			vertex.y -= 0.25;
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec3 uv;
			for (int i = 0; i < 2; ++i)
				readFile >> uv[i];
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			for (int i = 0; i < 3; ++i)
				readFile >> normal[i];
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex[3];
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

			int i = 0;
			while (i < 9) {
				char temp;
				readFile >> vertexIndex[(int)i++ / 3];
				readFile >> temp;
				readFile >> uvIndex[(int)i++ / 3];
				readFile >> temp;
				readFile >> normalIndex[(int)i++ / 3];
			}
			gIndex.push_back(vertexIndex[0] - 1);
			gIndex.push_back(vertexIndex[1] - 1);
			gIndex.push_back(vertexIndex[2] - 1);
		}
	}
	GLclampf tmpColor = 0.0f;
	for (auto iter = temp_vertices.begin(); iter != temp_vertices.end(); ++iter) {
		gVertex.push_back(*iter);
		tmpColor += 1.f / (float)temp_vertices.size();
		gColor.push_back(glm::vec3{ tmpColor, });
	}

	readFile.close();
}
vec3Buffer& CModel::GetVertex() { return gVertex; }
vec3Buffer& CModel::GetNormal() { return gNormal; }
vec2Buffer& CModel::GetUv() { return gUv; }
vec3Buffer& CModel::GetColor() { return gColor; }
std::vector<GLuint>& CModel::GetIndex() { return gIndex; }
GLuint& CModel::GetLayoutSize() { return nLayoutSize; }
void CModel::SetDrawType(GLuint drawtype) { nDrawType = drawtype; }
GLuint& CModel::GetDrawType() { return nDrawType; }
bool& CModel::GetIsDraw() { return bIsDraw; }