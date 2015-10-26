#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class IWIApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void IWIApp::setup()
{
}

void IWIApp::mouseDown( MouseEvent event )
{
}

void IWIApp::update()
{
}

void IWIApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( IWIApp, RendererGl )
