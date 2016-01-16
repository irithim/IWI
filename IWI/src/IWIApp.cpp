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

    if (camera_controller->isSmiling()) {
        display_controller->updateImage();
        camera_controller->resetSmiles();
    }

    Controller *controller = getWindow()->getUserData<Controller>();
    controller->update();
}

void IWIApp::draw() {
    Controller *controller = getWindow()->getUserData<Controller>();
    controller->draw();
}

