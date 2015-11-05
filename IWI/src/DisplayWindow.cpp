#include "DisplayWindow.h"

void DisplayWindow::load() {
	processedImage_ = Surface(loadImage(loadResource(RES_IMAGE)));
	processedImageTex_ = gl::Texture2d::create(processedImage_);
}

void DisplayWindow::mouseDown(MouseEvent event) {
	if (event.isLeftDown()) {
		invertArea(&processedImage_, Area(event.getX() - 2, event.getY() - 2, event.getX() + 2, event.getY() + 2));
	}
	else if (event.isRightDown()) {
		invertArea(&processedImage_, Area(event.getX() - 2, event.getY() - 2, event.getX() + 2, event.getY() + 2));
	}
}

void DisplayWindow::update() {
	processedImageTex_ = gl::Texture2d::create(processedImage_);
}

void DisplayWindow::draw() {
	gl::clear(Color::black());
	gl::draw(processedImageTex_, processedImage_.getBounds());
}

void DisplayWindow::invertArea(Surface *surface, Area area) {
	Surface::Iter iter = surface->getIter(area);
	while (iter.line()) {
		while (iter.pixel()) {
			iter.r() = 255 - iter.r();
			iter.g() = 255 - iter.g();
			iter.b() = 255 - iter.b();
		}
	}
}

ivec2 DisplayWindow::getSize() {
	return processedImage_.getSize();
}

