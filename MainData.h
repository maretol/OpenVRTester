#pragma once

#include <openvr.h>

#pragma comment(lib, "lib\\win32\\openvr_api.lib")

class vrMain {
private:
	

protected:
	vr::IVRSystem *hmd;


public:
	bool Init();
	void Shutdown();

};