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
};