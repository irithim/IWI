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
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

	gl::Texture2dRef processedImageTex_;
};

void invertArea(Surface *surface, Area area)
{
	Surface::Iter iter = surface->getIter(area);
	while (iter.line()) {
		while (iter.pixel()) {
			iter.r() = 255 - iter.r();
			iter.g() = 255 - iter.g();
			iter.b() = 255 - iter.b();
		}
	}
}

void IWIApp::setup()
{
	Surface processedImage(loadImage(loadResource(RES_IMAGE)));
	invertArea(&processedImage, Area(0, 0, processedImage.getWidth(), processedImage.getHeight()));
	processedImageTex_ = gl::Texture2d::create(processedImage);
}

void IWIApp::mouseDown( MouseEvent event )
{
}

void IWIApp::update()
{
}

void IWIApp::draw()
{
	gl::draw(processedImageTex_, getWindowBounds());
}

CINDER_APP( IWIApp, RendererGl )
