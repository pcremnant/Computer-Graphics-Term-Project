#pragma once
#include "define.h"

class CModel {
protected:
	vec3Buffer gVertex;
	vec3Buffer gColor;
	vec3Buffer gUv;
	vec3Buffer gNormal;

	std::vector<GLuint> gIndex;

	GLuint nLayoutSize;
	GLuint nDrawType;
	bool bIsDraw;

	int nVerticalRepeat;
	int nHoriziontalRepeat;
public:
	CModel(GLuint drawtype = GL_TRIANGLES, GLuint layout = 3, int horizontalRepeat = 1, int verticalRepeat = 1);
	void SetObjectVertex(const char* ObjectFile);
	vec3Buffer& GetVertex();
	vec3Buffer& GetNormal();
	vec3Buffer& GetUv();
	vec3Buffer& GetColor();
	std::vector<GLuint>& GetIndex();
	GLuint& GetLayoutSize();
	void SetDrawType(GLuint drawtype);
	GLuint& GetDrawType();
	bool& GetIsDraw();
	virtual void SetFrame(int frame, std::pair<int, int> frameNumber) {
		// u = frame % frameNumber.second
		int u = frame % frameNumber.second;
		int v = frame / frameNumber.second;

		float ver = (float)u / (float)frameNumber.second;
		float hor = (float)v / (float)frameNumber.first;

		gUv[0] = (glm::vec3{ (u + 1) * ver,v * hor,0 });
		gUv[1] = (glm::vec3{ (u + 1) * ver,(v + 1) * hor,0 });
		gUv[2] = (glm::vec3{ u * ver, (v + 1) * hor,0 });
		gUv[3] = (glm::vec3{ u * ver, (v + 1) * hor,0 });
		gUv[4] = (glm::vec3{ u * ver,v * hor,0 });
		gUv[5] = (glm::vec3{ (u + 1) * ver,v * hor,0 });


	}
};