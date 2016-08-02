#include "MainData.h"
#include <stdio.h>


bool vrMain::Init() {
	vr::EVRInitError eError = vr::VRInitError_None;
	hmd = vr::VR_Init(&eError, vr::VRApplication_Scene);

	if (eError != vr::VRInitError_None) {
		printf("error\n");
		return false;
	}
	printf("success\n");

	if (!DxInit()) {
		printf("%s - Unable to initialize DirectX\n", __FUNCTION__);
		return false;
	}
	return true;
}

// DxLib �̏������B�Ȃɂ��K�v�Ȃ珑������
bool vrMain::DxInit() {
	// �A���`�G�C���A�X��L��������ꍇ�͂����Ő錾���� ( Dxlib�̓s���������O�ɐ錾����

	if (DxLib_Init() == -1) {
		return false;
	}
	
	// �t���X�N���[�����[�h�ɂ��ׂ�?

	// �V�F�[�_�v���O�������s
	if (!CreateAllShaders()) {
		return false;
	}

	return true;
}

void vrMain::Shutdown() {
	hmd = NULL;
	vr::VR_Shutdown();
}

void vrMain::MainLoop() {
	bool quit = false;

	// Sample �ł� SDL �̏����B�e�N�X�`���ǂݍ��݂Ȃ�

	while (!quit) {
		quit = true;

		RenderFrame();
	}
}

bool vrMain::HandleInput() {

	// Sample�͂�����SDL�̃C�x���g�������s���Ă���

	vr::VREvent_t event;
	while (hmd->PollNextEvent(&event, sizeof(event))) {
		ProcessVREvent(event);
	}

	for (vr::TrackedDeviceIndex_t unDevice = 0; unDevice < vr::k_unMaxTrackedDeviceCount; unDevice++) {
		vr::VRControllerState_t state;
		if (hmd->GetControllerState(unDevice, &state)) {
			m_rbShowTrackedDevice[unDevice] = state.ulButtonPressed == 0;
		}
	}

	return false;
}

void vrMain::SetupRenderModelForTrackedDevice(vr::TrackedDeviceIndex_t unTrackeDeviceIndex) {
	if (unTrackeDeviceIndex >= vr::k_unMaxTrackedDeviceCount) {
		return;
	}

	string renderModelName = GetTrackedDeviceString(unTrackeDeviceIndex, vr::Prop_RenderModelName_String);
	RenderModel *renderModel = FindOrLoadRenderModel(renderModelName.c_str());
	
	if (renderModel) {
		string sTrackingSystemName = GetTrackedDeviceString(unTrackeDeviceIndex, vr::Prop_RenderModelName_String);
		printf("Unable to load render model for tracked device %d ( %s.%s )", unTrackeDeviceIndex, sTrackingSystemName.c_str(), renderModelName.c_str());
	} else {
		m_rTrackedDeviceToRenderModel[unTrackeDeviceIndex] = renderModel;
		m_rbShowTrackedDevice[unTrackeDeviceIndex] = true;
	}

}

void vrMain::RenderFrame() {
	if (hmd) {
		// Sample �ł͂����ŃR���g���[���̕\��? �ȉ��̃��\�b�h���s
		// DrawControllers();
		RenderStereoTargets();
		RenderDistortion(); // Distortion : �c�݂Ƃ����Ӗ��B�����Řc�߂�?

		// �����ŕ`��ς݂̉�ʂ��e�N�X�`�������ă����Y�̘c�݂ɍ��킹�����H�����Ă���?
	}
}

void vrMain::RenderStereoTargets() {
	// �w�i�F����
	SetBackgroundColor((int)255*0.15, (int)255*0.15, (int)255*0.15);
	
	// �t���[���o�b�t�@���o�C���h����
	// DxLib(or DirectX API) �ł̎������l����
	// TODO : �����̎���
}

void vrMain::RenderDistortion() {


}

void vrMain::RenderScene(vr::Hmd_Eye eye){}

// Processes a single VR event : VR�Ɋւ���C�x���g����?
void vrMain::ProcessVREvent(const vr::VREvent_t & event) {

	switch (event.eventType) {
		case vr::VREvent_TrackedDeviceActivated:
			SetupRenderModelForTrackedDevice(event.trackedDeviceIndex);
			printf("Device %u attached. Setting up render model.\n", event.trackedDeviceIndex);
			break;
		case vr::VREvent_TrackedDeviceDeactivated:
			printf("Device %u detached.\n", event.trackedDeviceIndex);
			break;
		case vr::VREvent_TrackedDeviceUpdated:
			printf("Device %u updated.\n", event.trackedDeviceIndex);
			break;
	}
}

RenderModel *vrMain::FindOrLoadRenderModel(const char *pRenderModelName) {
	RenderModel *pRenderModel = NULL;
	for (vector<RenderModel *>::iterator i = m_vecRenderModel.begin(); i != m_vecRenderModel.end(); i++) {
		if (!stricmp((*i)->getName().c_str(), pRenderModelName)) {
			pRenderModel = *i;
			break;
		}
	}

	// �������f����������Ȃ��Ƃ��Ƀ��f�������[�h����? (Sample���
	if (!pRenderModel) {
		vr::RenderModel_t *pModel;
		vr::EVRRenderModelError error;
		while (true) {
			error = vr::VRRenderModels()->LoadRenderModel_Async(pRenderModelName, &pModel);
			if (error != vr::VRRenderModelError_Loading) {
				break;
			}

			::_sleep(1);
		}

		if (error != vr::VRRenderModelError_None) {
			printf("Unable to load render model %s - %s\n", pRenderModelName, vr::VRRenderModels()->GetRenderModelErrorNameFromEnum(error));
			return NULL;
		}

		vr::RenderModel_TextureMap_t *pTexture;
		while (true) {
			error = vr::VRRenderModels()->LoadTexture_Async(pModel->diffuseTextureId, &pTexture);
			if (error != vr::VRRenderModelError_Loading) {
				break;
			}

			::_sleep(1);
		}

		if (error != vr::VRRenderModelError_None) {
			printf("Unable to load render texture id : %d for render model %s\n", pModel->diffuseTextureId, pRenderModelName);
			vr::VRRenderModels()->FreeRenderModel(pModel);
			return NULL;
		} else {
			m_vecRenderModel.push_back(pRenderModel);
		}
		vr::VRRenderModels()->FreeRenderModel(pModel);
		vr::VRRenderModels()->FreeTexture(pTexture);
	}
	return pRenderModel;
}

// �V�F�[�_�֐��Ƃ���̊i�[
// TODO : �p�����[�^�̍쐬�Ƃ���ւ̑��
// TODO : DirectX �̃V�F�[�_�̋L�q (HLSL �����肪�����Ǝv����)
bool vrMain::CreateAllShaders() {
	return false;
}

string vrMain::GetTrackedDeviceString(vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop) {
	return GetTrackedDeviceString(unDevice, prop, NULL);
}

string vrMain::GetTrackedDeviceString(vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError *pError) {
	uint32_t unRequiredBufferLen = hmd->GetStringTrackedDeviceProperty(unDevice, prop, NULL, 0, pError);
	if (unRequiredBufferLen == 0) {
		return "";
	}

	char *chBuffer = new char[unRequiredBufferLen];
	unRequiredBufferLen = hmd->GetStringTrackedDeviceProperty(unDevice, prop, chBuffer, unRequiredBufferLen, pError);
	string result = chBuffer;
	delete[] chBuffer;
	return result;
}

int main() {
	vrMain *vrmain = new vrMain();

	if (!vrmain->Init()) {
		vrmain->Shutdown();
		return 1;
	}
	vrmain->MainLoop();

	return 0;
}
