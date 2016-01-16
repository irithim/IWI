#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "cinder/Capture.h"
#include "cinder/Log.h"
#include "Resources.h"
#include "Controller.h"
#include "CinderOpenCv.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CameraController : Controller {

public:
    void setup();
	void mouseDown(MouseEvent event);
	void update();
	void draw();
	ivec2 getSize();

private:
    void updateFaces(Surface cameraImage);
	void printDevices();

    CaptureRef			mCapture;
    gl::TextureRef		mCameraTexture;
    cv::CascadeClassifier	mFaceCascade, mSmileCascade;
    vector<Rectf>			mFaces, mSmiles;
    ivec2				mSize;
};

#endif