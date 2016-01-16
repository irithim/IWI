#include "CameraController.h"

void CameraController::setup()
{
    mFaceCascade.load(getAssetPath("haarcascade_frontalface_alt.xml").string());
    mSmileCascade.load(getAssetPath("haarcascade_smile.xml").string());

    mSmilingTime = 0;
    mSmilingTimeThreshold = 10;

    mSize.x = 640;
    mSize.y = 480;
    mCapture = Capture::create(mSize.x, mSize.y);
    mCapture->start();
}

void CameraController::updateFaces(Surface cameraImage)
{
    const int calcScale = 2; // calculate the image at half scale

    // create a grayscale copy of the input image
    cv::Mat grayCameraImage(toOcv(cameraImage, CV_8UC1));

    // scale it to half size, as dictated by the calcScale constant
    int scaledWidth = cameraImage.getWidth() / calcScale;
    int scaledHeight = cameraImage.getHeight() / calcScale;
    cv::Mat smallImg(scaledHeight, scaledWidth, CV_8UC1);
    cv::resize(grayCameraImage, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR);

    // equalize the histogram
    cv::equalizeHist(smallImg, smallImg);

    // clear out the previously deteced faces & smiles
    mFaces.clear();
    mSmiles.clear();

    // detect the faces and iterate them, appending them to mFaces
    vector<cv::Rect> faces;
    mFaceCascade.detectMultiScale(smallImg, faces);
    for (vector<cv::Rect>::const_iterator faceIter = faces.begin(); faceIter != faces.end(); ++faceIter) {
        Rectf faceRect(fromOcv(*faceIter));
        faceRect *= calcScale;
        mFaces.push_back(faceRect);

        // detect smiles within this face and iterate them, appending them to mSmiles
        vector<cv::Rect> smiles;
        mSmileCascade.detectMultiScale(smallImg(*faceIter), smiles);
        for (vector<cv::Rect>::const_iterator smileIter = smiles.begin(); smileIter != smiles.end(); ++smileIter) {
            Rectf smileRect(fromOcv(*smileIter));
            smileRect = smileRect * calcScale + faceRect.getUpperLeft();
            mSmiles.push_back(smileRect);
        }
    }

    if (mSmiles.size() == 0) {
        resetSmiles();
    }
    else {
        mSmilingTime++;
        if (mSmilingTime > mSmilingTimeThreshold) {
            // Prevent overflow
            mSmilingTime = mSmilingTimeThreshold + 1;
        }
    }
}

bool CameraController::isSmiling() {
    return mSmilingTime > mSmilingTimeThreshold;
}

void CameraController::resetSmiles() {
    mSmilingTime = 0;
}

void CameraController::update()
{
    if (mCapture && mCapture->checkNewFrame()) {
        Surface surface = *mCapture->getSurface();
        if (!mCameraTexture) {
            mCameraTexture = gl::Texture::create(surface);
        }
        else {
            mCameraTexture->update(surface);
        }
        updateFaces(surface);
    }
}

void CameraController::draw()
{
    if (!mCameraTexture)
        return;

    gl::setMatricesWindow(getWindowSize());
    gl::enableAlphaBlending();

    // draw the webcam image
    gl::color(Color(1, 1, 1));
    gl::draw(mCameraTexture);

    // draw the faces as transparent yellow rectangles
    gl::color(ColorA(1, 1, 0, 0.45f));
    for (vector<Rectf>::const_iterator faceIter = mFaces.begin(); faceIter != mFaces.end(); ++faceIter)
        gl::drawSolidRect(*faceIter);

    // draw the smiles as transparent blue ellipses or green if smiling is approved
    if (isSmiling()) {
        gl::color(ColorA(0, 1, 0, 0.35f));
    }
    else {
        gl::color(ColorA(0, 0, 1, 0.35f));
    }
    for (vector<Rectf>::const_iterator smileIter = mSmiles.begin(); smileIter != mSmiles.end(); ++smileIter)
        gl::drawSolidCircle(smileIter->getCenter(), smileIter->getWidth() / 2);
}

void CameraController::mouseDown(MouseEvent event) {
}

void CameraController::mouseMove(MouseEvent event) {
}

ivec2 CameraController::getSize() {
    return mSize;
}