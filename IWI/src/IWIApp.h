#ifndef IWIAPP_H
#define IWIAPP_H

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
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
};

#endif