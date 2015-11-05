#include "CameraController.h"

void CameraController::load() {
	printDevices();

	try {
		mSize.x = 640;
		mSize.y = 480;
		mCapture = Capture::create(mSize.x, mSize.y);
		mCapture->start();
	}
	catch (ci::Exception &exc) {
		CI_LOG_EXCEPTION("Failed to init capture ", exc);
	}
}

void CameraController::mouseDown(MouseEvent event) {
}

void CameraController::update() {
	if (mCapture && mCapture->checkNewFrame()) {
		if (!mTexture) {
			// Capture images come back as top-down, and it's more efficient to keep them that way
			mTexture = gl::Texture::create(*mCapture->getSurface(), gl::Texture::Format().loadTopDown());
		}
		else {
			mTexture->update(*mCapture->getSurface());
		}
	}
}

void CameraController::draw() {
	gl::clear();

	if (mTexture) {
		gl::ScopedModelMatrix modelScope;
		gl::draw(mTexture);
	}
}

ivec2 CameraController::getSize() {
	return mSize;
}


void CameraController::printDevices()
{
	for (const auto &device : Capture::getDevices()) {
		console() << "Device: " << device->getName() << " " << endl;
	}
}

