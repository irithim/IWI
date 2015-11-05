#include "IWIApp.h"
#include "DisplayWindow.h"

void IWIApp::prepareSettings( Settings *settings ) {
	settings->setResizable(false);
}

void IWIApp::setup() {
	getWindow()->setUserData(new DisplayWindow);
	getWindow()->getUserData<DisplayWindow>()->load();
	setWindowSize(getWindow()->getUserData<DisplayWindow>()->getSize());
}

void IWIApp::mouseDown(MouseEvent event) {
	DisplayWindow *data = getWindow()->getUserData<DisplayWindow>();
	data->mouseDown(event);
}

void IWIApp::update() {
	DisplayWindow *data = getWindow()->getUserData<DisplayWindow>();
	data->update();
}

void IWIApp::draw() {
	DisplayWindow *data = getWindow()->getUserData<DisplayWindow>();
	data->draw();
}

