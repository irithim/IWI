#include "IWIApp.h"
#include "DisplayController.h"
#include "CameraController.h"

void IWIApp::prepareSettings(Settings *settings) {
    settings->setResizable(false);
}

void IWIApp::setup() {
    mDisplayWindow = getWindow();
    mDisplayWindow->setUserData(new DisplayController);
    mDisplayWindow->getUserData<DisplayController>()->setup();
    setWindowSize(mDisplayWindow->getUserData<DisplayController>()->getSize());

    mCameraWindow = createWindow(Window::Format().size(400, 400));
    mCameraWindow->setUserData(new CameraController);
    mCameraWindow->getUserData<CameraController>()->setup();
    mCameraWindow->setSize(getWindow()->getUserData<CameraController>()->getSize());

    mEyeWindow = createWindow(Window::Format().size(100, 100));
    mEyeWindow->setUserData(new EyeController);
    mEyeWindow->getUserData<EyeController>()->setup();
    mEyeWindow->setSize(getWindow()->getUserData<EyeController>()->getSize());
}

void IWIApp::mouseDown(MouseEvent event) {
    Controller *controller = getWindow()->getUserData<Controller>();
    controller->mouseDown(event);
}

void IWIApp::mouseMove(MouseEvent event) {
    Controller *controller = getWindow()->getUserData<Controller>();
    controller->mouseMove(event);
}

void IWIApp::update() {
    DisplayController *display_controller = mDisplayWindow->getUserData<DisplayController>();
    CameraController *camera_controller = mCameraWindow->getUserData<CameraController>();
    EyeController *eye_controller = mEyeWindow->getUserData<EyeController>();

    camera_controller->update();

    Surface surface(200, 200, false);
    Rectf eyeL = camera_controller->eyeL;
    Area area(eyeL.x1, eyeL.y1, eyeL.x2, eyeL.y2);
    surface.copyFrom(camera_controller->surface, area, vec2(-eyeL.x1, -eyeL.y1));
    Rectf eyeR = camera_controller->eyeR;
    area = { (int)eyeR.x1, (int)eyeR.y1, (int)eyeR.x2, (int)eyeR.y2 };
    surface.copyFrom(camera_controller->surface, area, vec2(-(eyeR.x1 - (eyeL.x2 - eyeL.x1)), -eyeR.y1));
    eye_controller->setSurface(surface);

    display_controller->setCursor(mCameraWindow->getUserData<CameraController>()->getHeadCursor());

    if (camera_controller->isSmiling()) {
        //display_controller->updateImage();
        display_controller->userDrawing(0, 255, 0);
        camera_controller->resetSmiles();
    }

    eye_controller->update();
    display_controller->update();
}

void IWIApp::draw() {
    Controller *controller = getWindow()->getUserData<Controller>();
    gl::color(Color(1, 1, 1));
    controller->draw();    
}
