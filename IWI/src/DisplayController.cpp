#include "DisplayController.h"

void DisplayController::load() {
	processedImage_ = Surface(loadImage(loadResource(RES_IMAGE)));
	processedImageTex_ = gl::Texture2d::create(processedImage_);
}

void DisplayController::mouseDown(MouseEvent event) {
	if (event.isLeftDown()) {
		invertArea(&processedImage_, Area(event.getX() - 2, event.getY() - 2, event.getX() + 2, event.getY() + 2));
	}
	else if (event.isRightDown()) {
		invertArea(&processedImage_, Area(event.getX() - 2, event.getY() - 2, event.getX() + 2, event.getY() + 2));
	}
}

void DisplayController::update() {
	processedImageTex_ = gl::Texture2d::create(processedImage_);
}

void DisplayController::draw() {
	gl::clear(Color::black());
	gl::draw(processedImageTex_, processedImage_.getBounds());
}

void DisplayController::invertArea(Surface *surface, Area area) {
	Surface::Iter iter = surface->getIter(area);
	while (iter.line()) {
		while (iter.pixel()) {
			iter.r() = 255 - iter.r();
			iter.g() = 255 - iter.g();
			iter.b() = 255 - iter.b();
		}
	}
}

ivec2 DisplayController::getSize() {
	return processedImage_.getSize();
}

