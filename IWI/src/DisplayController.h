#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include "cinder/ImageIo.h"
#include "Resources.h"
#include "Controller.h"

using namespace ci;
using namespace ci::app;

class DisplayController : Controller {

public:
	void load();
	void mouseDown(MouseEvent event);
	void update();
	void draw();

	ivec2 getSize();

private:
	void DisplayController::invertArea(Surface *surface, Area area);

	Surface processedImage_;
	gl::Texture2dRef processedImageTex_;
};

#endif
