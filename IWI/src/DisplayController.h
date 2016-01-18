#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include "cinder/ImageIo.h"
#include "Resources.h"
#include "Controller.h"

using namespace ci;
using namespace ci::app;

class DisplayController : Controller {

public:
	void setup();
    void mouseDown(MouseEvent event);
	void mouseMove(MouseEvent event);
	void update();
	void draw();
    void setCursor(vec2 position);
    void userDrawing(int r, int g, int b);

	ivec2 getSize();
    void updateImage();

private:
	void DisplayController::invertArea(Surface *surface, Area area);
	Surface processedImage_;
	gl::Texture2dRef processedImageTex_;
    ivec2 mMousePos;
    ivec2 mCursorPos;
};

#endif
