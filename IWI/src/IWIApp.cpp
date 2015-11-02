#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class IWIApp : public App {
    public:
    static void prepareSettings(Settings *settings);

    void setup() override;
    void mouseDown(MouseEvent event) override;
    void update() override;
    void draw() override;

    Surface processedImage_;
    gl::Texture2dRef processedImageTex_;
};

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

CINDER_APP(IWIApp, RendererGl, IWIApp::prepareSettings)
