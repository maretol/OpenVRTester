#pragma once

#include <openvr.h>
#include <DxLib.h>
#include <string>

#include <vector>
#include "RenderModel.h"

using namespace std;

#pragma comment(lib, "lib\\win32\\openvr_api.lib")

class vrMain {
private:
	//------------- ���\�b�h ----------------
	// �G���[�����ȂǂŎg�p
	string GetTrackedDeviceString(vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop);
	string GetTrackedDeviceString(vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError *pError);
	
	//-------------- �p�����[�^ -------------
	bool m_rbShowTrackedDevice[vr::k_unMaxTrackedDeviceCount];

	bool m_Vblank;

	vr::TrackedDevicePose_t m_rTrackedDevicePose[vr::k_unMaxTrackedDeviceCount];

	vector<RenderModel *> m_vecRenderModel;
	RenderModel *m_rTrackedDeviceToRenderModel[vr::k_unMaxTrackedDeviceCount];

	// �O���t�B�b�N�֌W (��XGL->DX�ŏ����������K�v��������Ȃ�
	// ���󂻂̂܂�
	int m_ValidPoseCount;
	string m_PoseClasses;

	struct FramebufferDesc {
		u_int m_DepthBufferId;
		u_int m_RenderTextureId;
		u_int m_RenderFramebufferId;
		u_int m_ResolveTextureId;
		u_int m_ResolveFramebufferId;
	};
	FramebufferDesc leftEyeDesc;
	FramebufferDesc rightEyeDesc;

protected:
	//------------- ���\�b�h ----------------

	//-------------- �p�����[�^ -------------
	vr::IVRSystem *hmd;
	Matrix4 hoge;

public:
	vrMain();

	//------------- ���\�b�h ----------------
	// �������E�I���֌W
	bool Init();
	bool DxInit();
	bool CreateAllShaders();
	void Shutdown();
	void MainLoop();

	// �C�x���g�֌W
	bool HandleInput();
	void SetupRenderModelForTrackedDevice(vr::TrackedDeviceIndex_t unTrackeDeviceIndex);
	void ProcessVREvent(const vr::VREvent_t &event);

	// �����_�����O�֌W
	void RenderFrame();
	void RenderStereoTargets();
	void RenderDistortion();
	void RenderScene(vr::Hmd_Eye eye);
	
	// 
	void UpdateHMDMatrixPose();

	// 
	RenderModel *FindOrLoadRenderModel(const char *pRenderModelName);

	//-------------- �p�����[�^ -------------
};