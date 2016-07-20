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
	// ‚±‚±‚Å
	// CGLRenderModel *renderModel = FindOrLoadRenderModel(renderModelName.c_str()) ‚ðŒÄ‚Ño‚µ‚Ä‚¢‚é
	// ŽÀ‘•’†

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

string vrMain::GetTrackedDeviceString(vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError *pError = NULL) {
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
