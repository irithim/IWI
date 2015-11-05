#include "IWIApp.h"

void invertArea(Surface *surface, Area area) {
    Surface::Iter iter = surface->getIter(area);
    while (iter.line()) {
        while (iter.pixel()) {
            iter.r() = 255 - iter.r();
            iter.g() = 255 - iter.g();
            iter.b() = 255 - iter.b();
        }
    }
}

void IWIApp::prepareSettings( Settings *settings ) {
	settings->setResizable(false);
}

void IWIApp::setup() {
    processedImage_ = Surface(loadImage(loadResource(RES_IMAGE)));
    processedImageTex_ = gl::Texture2d::create(processedImage_);
    setWindowSize(processedImage_.getSize());
}

void IWIApp::mouseDown(MouseEvent event) {
    if (event.isLeftDown()) {
        invertArea(&processedImage_, Area(event.getX() - 2, event.getY() -2, event.getX() + 2, event.getY() + 2));
    } else if (event.isRightDown()) {
        invertArea(&processedImage_, Area(event.getX() - 2, event.getY() -2, event.getX() + 2, event.getY() + 2));
    }
}

void IWIApp::update() {
    processedImageTex_ = gl::Texture2d::create(processedImage_);
}

void IWIApp::draw() {
    gl::clear(Color::black());
    gl::draw(processedImageTex_, processedImage_.getBounds());
}

