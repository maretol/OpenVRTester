#include "RenderModel.h"

// –{—ˆ OpenGL ‚Å‘‚­‚à‚Ì
// Sample ‚Ì CGLRenderModel‚ÉŠY“–

RenderModel::RenderModel(const string &renderModelName) : m_ModelName(renderModelName) {
	m_IndexBuffer = 0;
	m_VertArray = 0;
	m_VertBuffer = 0;
	m_Texture = 0;
}


RenderModel::~RenderModel() {
	Cleanup();
}

// ‰Šú‰»
// ‚½‚¾‚Ç‚±‚Ü‚ÅÀ‘•‚Å‚«‚é‚©‚í‚©‚ç‚ñ‚Ì‚Å¡‚ÍŒã‰ñ‚µ
bool RenderModel::BInit(const vr::RenderModel_t & vrModel, const vr::RenderModel_TextureMap_t & vrDiffuseTexture) {
	return false;
}

void RenderModel::Cleanup() {
	if (m_VertBuffer) {
		// Buffer, Array‚ÌŠJ•ú
		m_IndexBuffer = 0;
		m_VertArray = 0;
		m_VertBuffer = 0;
	}
}

// •`‰æ
// GL ‚Å‚È‚¢À‘•‚È‚Ì‚ÅŒã‰ñ‚µ
void RenderModel::Draw() {

}
