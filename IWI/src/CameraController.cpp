#include "CameraController.h"

void CameraController::load() {
	processedImage_ = Surface(loadImage(loadResource(RES_IMAGE)));
	processedImageTex_ = gl::Texture2d::create(processedImage_);
}

void CameraController::mouseDown(MouseEvent event) {
	Surface::Iter iter = processedImage_.getIter(Area(event.getX() - 20, event.getY() - 20, event.getX() + 20, event.getY() + 20));
	while (iter.line()) {
		while (iter.pixel()) {
			iter.r() = 255 - iter.r();
			iter.g() = 255 - iter.g();
			iter.b() = 255 - iter.b();
		}
	}
}

void CameraController::update() {
	processedImageTex_ = gl::Texture2d::create(processedImage_);
}

void CameraController::draw() {
	gl::clear(Color::black());
	gl::draw(processedImageTex_, processedImage_.getBounds());
}

ivec2 CameraController::getSize() {
	return processedImage_.getSize();
}

