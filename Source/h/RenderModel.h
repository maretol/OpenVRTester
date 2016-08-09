#pragma once
#include <openvr.h>
#include <string>

using namespace std;

// Sample �ł� OpenGL �x�[�X�ł���Ă����̂ŋ����� DirectX �ɓK�p���Ă݂�
// ����Ƃ���ǂ��������

class RenderModel {
private:
	uint32_t m_VertBuffer;
	uint32_t m_IndexBuffer;
	uint32_t m_VertArray;
	uint32_t m_Texture;
	size_t m_unVertexCount;
	string m_ModelName;

public:
	RenderModel(const string &renderModelName);
	~RenderModel();

	bool BInit(const vr::RenderModel_t &vrModel, const vr::RenderModel_TextureMap_t &vrDiffuseTexture);
	void Cleanup();
	void Draw();
	const string &getName() const { return m_ModelName; }
};

