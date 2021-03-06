#include "RenderModel.h"

// 本来 OpenGL で書くもの
// Sample の CGLRenderModelに該当

RenderModel::RenderModel(const string &renderModelName) : m_ModelName(renderModelName) {
	m_IndexBuffer = 0;
	m_VertArray = 0;
	m_VertBuffer = 0;
	m_Texture = 0;
}


RenderModel::~RenderModel() {
	Cleanup();
}

// 初期化
// ただどこまで実装できるかわからんので今は後回し
bool RenderModel::BInit(const vr::RenderModel_t & vrModel, const vr::RenderModel_TextureMap_t & vrDiffuseTexture) {
	return false;
}

void RenderModel::Cleanup() {
	if (m_VertBuffer) {
		// Buffer, Arrayの開放
		m_IndexBuffer = 0;
		m_VertArray = 0;
		m_VertBuffer = 0;
	}
}

// 描画
// GL でない実装なので後回し
void RenderModel::Draw() {

}
