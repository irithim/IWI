#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

class Controller {

public:
	virtual void mouseDown(ci::app::MouseEvent event) = 0;
	virtual void mouseMove(ci::app::MouseEvent event) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual ci::ivec2 getSize() = 0;
};

#endif
