#include "CModel.h"

CModel::CModel(GLuint drawtype, GLuint layout) : nLayoutSize(layout), nDrawType(drawtype) { }
void CModel::SetObjectVertex(const char* ObjectFile)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

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
			temp_vertices.emplace_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			for (int i = 0; i < 2; ++i)
				readFile >> uv[i];
			temp_uvs.emplace_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			for (int i = 0; i < 3; ++i)
				readFile >> normal[i];
			temp_normals.emplace_back(normal);
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
			gIndex.emplace_back(vertexIndex[0] - 1);
			gIndex.emplace_back(vertexIndex[1] - 1);
			gIndex.emplace_back(vertexIndex[2] - 1);
		}
	}

	for (auto iter : temp_vertices)
		gVertex.emplace_back(iter);
	for (auto iter : temp_normals)
		gNormal.emplace_back(iter);
	for (auto iter : temp_uvs)
		gUv.emplace_back(iter);

	readFile.close();
}
std::vector<glm::vec3>& CModel::GetVertex() { return gVertex; }
std::vector<glm::vec3>& CModel::GetNormal() { return gNormal; }
vec2Buffer& CModel::GetUv() { return gUv; }
std::vector<glm::vec3>& CModel::GetColor() { return gColor; }
std::vector<GLuint>& CModel::GetIndex() { return gIndex; }

GLuint& CModel::GetLayoutSize() { return nLayoutSize; }
void CModel::SetDrawType(GLuint drawtype) { nDrawType = drawtype; }
GLuint& CModel::GetDrawType() { return nDrawType; }
bool& CModel::GetIsDraw() { return bIsDraw; }