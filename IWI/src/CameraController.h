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
	void mouseMove(MouseEvent event);
	void update();
	void draw();
	ivec2 getSize();
    bool isSmiling();
    void resetSmiles();

    Rectf eyeL;
    Rectf eyeR;
    Surface surface;
    vec2 getHeadCursor();

private:
    void updateFaces(Surface cameraImage);

    CaptureRef			mCapture;
    gl::TextureRef		mCameraTexture;
    cv::CascadeClassifier	mFaceCascade, mSmileCascade, mEyeLCascade, mEyeRCascade;
    vector<Rectf>			mFaces, mSmiles, mEyes;
    int mSmilingTime;
    int mSmilingTimeThreshold;
    ivec2				mSize;
};

#endif