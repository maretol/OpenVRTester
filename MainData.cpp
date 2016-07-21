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
	return true;
}

void vrMain::Shutdown() {
	hmd = NULL;
	vr::VR_Shutdown();
}

void vrMain::MainLoop() {
	bool quit = false;

	while (!quit) {
		quit = true;
	}
}

bool vrMain::HandleInput() {

	vr::VREvent_t event;
	while (hmd->PollNextEvent(&event, sizeof(event))) {
		ProcessVREvent(event);
	}

	return false;
}

void vrMain::SetupRenderModelForTrackedDevice(vr::TrackedDeviceIndex_t unTrackeDeviceIndex) {
	if (unTrackeDeviceIndex >= vr::k_unMaxTrackedDeviceCount) {
		return;
	}

	string renderModelName = GetTrackedDeviceString(unTrackeDeviceIndex, vr::Prop_RenderModelName_String);
	// ここで
	RenderModel *renderModel = FindOrLoadRenderModel(renderModelName.c_str());
	// 実装中

}

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

	// もしモデルが見つからないときにモデルをロードする? (Sampleより
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
