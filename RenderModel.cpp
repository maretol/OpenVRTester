#include "RenderModel.h"

// –{—ˆ OpenGL ‚Å‘‚­‚ñ‚¾‚Á‚Äi‚Ä‚«‚Æ‚¤

RenderModel::RenderModel(const string &renderModelName) {}


RenderModel::~RenderModel() {}

bool RenderModel::BInit(const vr::RenderModel_t & vrModel, const vr::RenderModel_TextureMap_t & vrDiffuseTexture) {
	return false;
}

void RenderModel::Cleanup() {}

void RenderModel::Draw() {}
