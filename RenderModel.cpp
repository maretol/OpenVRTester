#include "RenderModel.h"

// �{�� OpenGL �ŏ����񂾂��āi�Ă��Ƃ�

RenderModel::RenderModel(const string &renderModelName) {}


RenderModel::~RenderModel() {}

bool RenderModel::BInit(const vr::RenderModel_t & vrModel, const vr::RenderModel_TextureMap_t & vrDiffuseTexture) {
	return false;
}

void RenderModel::Cleanup() {}

void RenderModel::Draw() {}
