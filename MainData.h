#pragma once

#include <openvr.h>

class vrMain {
private:
	

protected:
	vr::IVRSystem *hmd;


public:
	bool Init();
	void Shutdown();

};