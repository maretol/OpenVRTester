#pragma once
#include <openvr.h>
#include <string>

using namespace std;

// Sample では OpenGL ベースでやっていたので強引に DirectX に適用してみる
// 現状ところどころ怪しい

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

