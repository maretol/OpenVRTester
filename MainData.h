#pragma once

#include <openvr.h>
#include <string>
#include "RenderModel.h"

using namespace std;

#pragma comment(lib, "lib\\win32\\openvr_api.lib")

class vrMain {
private:
	//------------- ���\�b�h ----------------
	string GetTrackedDeviceString(vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop);
	string GetTrackedDeviceString(vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError *pError);
	
	//-------------- �p�����[�^ -------------


protected:
	//------------- ���\�b�h ----------------

	//-------------- �p�����[�^ -------------
	vr::IVRSystem *hmd;


public:
	//------------- ���\�b�h ----------------
	bool Init();
	void Shutdown();
	void MainLoop();

	bool HandleInput();
	void SetupRenderModelForTrackedDevice(vr::TrackedDeviceIndex_t unTrackeDeviceIndex);
	
	void ProcessVREvent(const vr::VREvent_t &event);

	RenderModel *FindOrLoadRenderModel(const char *pRenderModelName);

	//-------------- �p�����[�^ -------------
};