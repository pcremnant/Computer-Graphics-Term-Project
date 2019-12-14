#include "define.h"
#include "CModel_plane.h"

// ��ƼŬ ������

#define PARTICLE_EXPLOSION_1 0

class UI_Particle {
private:
	std::vector<const char*> particle;
	std::vector<std::pair<int, int>> imageSize;
	std::vector<std::pair<int, int>> frameNumber;
	CModel_plane* particleModel;
public:
	UI_Particle() {
		// ��ƼŬ 1
		particle.emplace_back("./resource/texture/particle.bmp");
		imageSize.emplace_back(std::make_pair(512, 512));
		frameNumber.emplace_back(std::make_pair(5, 5));
		particleModel = new CModel_plane(LAYOUT_UV);


	}
	// uv���� 512/5 * frame�� �Ǿ�� ��
};