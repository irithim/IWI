#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "cinder/Capture.h"
#include "cinder/Log.h"
#include "Resources.h"
#include "Controller.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CameraController : Controller {

public:
	void load();
	void mouseDown(MouseEvent event);
	void update();
	void draw();
	ivec2 getSize();

private:
	void printDevices();

	CaptureRef			mCapture;
	gl::TextureRef		mTexture;
	ivec2				mSize;
};

#endif