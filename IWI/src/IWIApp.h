#ifndef IWIAPP_H
#define IWIAPP_H

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "Resources.h"
#include "EyeController.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class IWIApp : public App {
public:
    static void prepareSettings(Settings *settings);

    void setup() override;
    void mouseDown(MouseEvent event) override;
    void mouseMove(MouseEvent event) override;
    void update() override;
    void draw() override;

private:
    app::WindowRef mDisplayWindow;
    app::WindowRef mCameraWindow;
    app::WindowRef mEyeWindow;
};

#endif
