#include "IWIApp.h"
#include "DisplayController.h"
#include "CameraController.h"

void IWIApp::prepareSettings( Settings *settings ) {
	settings->setResizable(false);
}

void IWIApp::setup() {
	getWindow()->setUserData(new DisplayController);
	getWindow()->getUserData<DisplayController>()->load();
	setWindowSize(getWindow()->getUserData<DisplayController>()->getSize());

	app::WindowRef newWindow = createWindow(Window::Format().size(400, 400));
	newWindow->setUserData(new CameraController);
	newWindow->getUserData<CameraController>()->load();
	newWindow->setSize(getWindow()->getUserData<CameraController>()->getSize());
}

void IWIApp::mouseDown(MouseEvent event) {
	Controller *controller = getWindow()->getUserData<Controller>();
	controller->mouseDown(event);
}

void IWIApp::update() {
	Controller *controller = getWindow()->getUserData<Controller>();
	controller->update();
}

void IWIApp::draw() {
	Controller *controller = getWindow()->getUserData<Controller>();
	controller->draw();
}

