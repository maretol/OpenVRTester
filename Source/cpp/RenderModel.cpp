#include "RenderModel.h"

// �{�� OpenGL �ŏ�������
// Sample �� CGLRenderModel�ɊY��

RenderModel::RenderModel(const string &renderModelName) : m_ModelName(renderModelName) {
	m_IndexBuffer = 0;
	m_VertArray = 0;
	m_VertBuffer = 0;
	m_Texture = 0;
}


RenderModel::~RenderModel() {
	Cleanup();
}

// ������
// �����ǂ��܂Ŏ����ł��邩�킩���̂ō��͌��
bool RenderModel::BInit(const vr::RenderModel_t & vrModel, const vr::RenderModel_TextureMap_t & vrDiffuseTexture) {
	return false;
}

void RenderModel::Cleanup() {
	if (m_VertBuffer) {
		// Buffer, Array�̊J��
		m_IndexBuffer = 0;
		m_VertArray = 0;
		m_VertBuffer = 0;
	}
}

// �`��
// GL �łȂ������Ȃ̂Ō��
void RenderModel::Draw() {

}
