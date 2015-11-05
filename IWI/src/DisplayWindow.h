#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

#include "cinder/app/App.h"
#include "cinder/ImageIo.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;

class DisplayWindow {

public:
	void load();
	void mouseDown(MouseEvent event);
	void update();
	void draw();

	ivec2 getSize();

private:
	void DisplayWindow::invertArea(Surface *surface, Area area);

	Surface processedImage_;
	gl::Texture2dRef processedImageTex_;
};

#endif
