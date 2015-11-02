#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

struct CustomCircle {
	vec2 position;
	float radius;
	Color color;
};

class IWIApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

	gl::Texture2dRef processedImageTex_;
	vector<CustomCircle> circles_;

	const float radius_ = 1.0f;
	const Color goodColor_ = Color(0.0f, 0.0f, 1.0f);
	const Color badColor_ = Color(1.0f, 0.0f, 0.0f);
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
	CustomCircle circle;
	circle.position = event.getPos();
	circle.radius = radius_;
	if (event.isLeftDown()) {
		circle.color = goodColor_;
	}
	else if (event.isRightDown()) {
		circle.color = badColor_;
	}
	circles_.push_back(circle);
}

void IWIApp::update()
{
}

void IWIApp::draw()
{
	gl::clear(Color::black());
	gl::draw(processedImageTex_, getWindowBounds());
	for (vector<CustomCircle>::iterator it = circles_.begin(); it != circles_.end(); ++it) {
		gl::color((*it).color);
		gl::drawSolidCircle((*it).position, (*it).radius);
	}
	gl::color(Color::white());
}

CINDER_APP( IWIApp, RendererGl )
