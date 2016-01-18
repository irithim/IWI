#include "DisplayController.h"

void DisplayController::setup() {
    processedImage_ = Surface(loadImage(loadAsset("cinder_logo.png")));
	processedImageTex_ = gl::Texture2d::create(processedImage_);
}

void DisplayController::mouseDown(MouseEvent event) {
}

void DisplayController::mouseMove(MouseEvent event) {
    mMousePos = event.getPos();
}

void DisplayController::updateImage() {
    invertArea(&processedImage_, Area(mMousePos.x - 2, mMousePos.y - 2, mMousePos.x + 2, mMousePos.y + 2));
}

void DisplayController::update() {
	processedImageTex_ = gl::Texture2d::create(processedImage_);
}

void DisplayController::draw() {
	gl::clear(Color::black());
	gl::draw(processedImageTex_, processedImage_.getBounds());

    gl::color(ColorA(1, 0, 0, 0.35f));
    gl::drawSolidRect(Rectf(Area(mCursorPos, vec2(mCursorPos + 5))), mCursorPos, mCursorPos + 30);
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

void DisplayController::setCursor(vec2 position) {
    mCursorPos = position;
}

void DisplayController::userDrawing(int r, int g, int b) {
    Surface::Iter iter = processedImage_.getIter(Area(mCursorPos, mCursorPos + 30));
    while (iter.line()) {
        while (iter.pixel()) {
            iter.r() = ((int)iter.r() + r) / 2;
            iter.g() = ((int)iter.g() + g) / 2;
            iter.b() = ((int)iter.b() + b) / 2;
        }
    }
}
