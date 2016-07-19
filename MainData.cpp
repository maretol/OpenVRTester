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
}


int main() {
	vrMain *vrmain = new vrMain();
	vrmain->Init();
	return 0;
}
