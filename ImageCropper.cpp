#include "ImageCropper.h"
#include "math.h"

ImageCropper::ImageCropper()
{

}

bool ImageCropper::mousePressCropRuntimeImg(Point mousePosition) { /// nhấn vào điểm góc trái trên hoặc phải dưới nếu ở đủ gân sẽ set idx cho
                                                                    // mouseCropRuntimeImgIndex  để đánh dấu là topleft hay bottom right
    for (int idxCounter = 0; idxCounter < 2; idxCounter++) {                    // cropPointRuntimeImage[0] = Point(0,0)
        int coorX = cropPointRuntimeImage[idxCounter].x;                        // cropPointRuntimeImage[1] = Point(800,500) 
        int coorY = cropPointRuntimeImage[idxCounter].y;
        if ((mousePosition.x >= (coorX - WARP_POINT_OFFSET)) && (mousePosition.x <= (coorX + WARP_POINT_OFFSET))) { 
            if ((mousePosition.y >= (coorY - WARP_POINT_OFFSET)) && (mousePosition.y <= (coorY + WARP_POINT_OFFSET))) {
                mouseCropRuntimeImgIndex = idxCounter + 1; // set index để biết
                return true;
            }
        }
    }
    return false;
}

void ImageCropper::mouseReleaseCropRuntimeImg() {  // reset lại index khi buông
    mouseCropRuntimeImgIndex = 0;
}

bool ImageCropper::mouseMoveCropRuntimeImg(Point mousePosition) { 
    if (mouseCropRuntimeImgIndex == 0) { // nếu di chuyển chuột không nằm trong khoảng offset
        return false;
    }
    cropPointRuntimeImage[mouseCropRuntimeImgIndex - 1] = mousePosition; // update giá trị mới 
    return true;
}

cv::Mat ImageCropper::drawCropRuntimeImageRect(cv::Mat imageSource) { // vẽ hình chữ nhật để crop
    cv::Mat returnImg = imageSource.clone();   // copy ảnh
    cv::rectangle(returnImg, cropPointRuntimeImage[0], cropPointRuntimeImage[1], DRAW_COLOR_RED, RECT_LINE_SIZE, LINE_AA); // vẽ hình chữ nhật
    cv::circle(returnImg, cropPointRuntimeImage[0], DRAG_CIRCLE_SIZE, DRAW_COLOR_GREEN, CIRCLE_LINE_SIZE, LINE_AA); // chấm xanh ở nút trái trên
    cv::circle(returnImg, cropPointRuntimeImage[1], DRAG_CIRCLE_SIZE, DRAW_COLOR_GREEN, CIRCLE_LINE_SIZE, LINE_AA); // chấm xanh ở nút phải dưới
    return returnImg;
}



/// SAM4PATTERN
bool ImageCropper::mousePressCropPatternImg(Point mousePosition) { // press
    for (int idxCounter = 0; idxCounter < 2; idxCounter++) {
        int coorX = cropPointPatternImage[idxCounter].x;
        int coorY = cropPointPatternImage[idxCounter].y;
        if ((mousePosition.x >= (coorX - WARP_POINT_OFFSET)) && (mousePosition.x <= (coorX + WARP_POINT_OFFSET))) {
            if ((mousePosition.y >= (coorY - WARP_POINT_OFFSET)) && (mousePosition.y <= (coorY + WARP_POINT_OFFSET))) {
                mouseCropPatternImgIndex = idxCounter + 1;
                return true;
            }
        }
    }
    return false;
}

void ImageCropper::mouseReleaseCropPatternImg() { // release
    mouseCropPatternImgIndex = 0;
}

bool ImageCropper::mouseMoveCropPatternImg(Point mousePosition) {  // move
    if (mouseCropPatternImgIndex == 0) {
        return false;
    }
    cropPointPatternImage[mouseCropPatternImgIndex - 1] = mousePosition;
    return true;
}

cv::Mat ImageCropper::drawCropPatternImageRect(cv::Mat imageSource) {  // draw
    cv::Mat returnImg = imageSource.clone();
    cv::rectangle(returnImg, cropPointPatternImage[0], cropPointPatternImage[1], DRAW_COLOR_RED, RECT_LINE_SIZE, LINE_AA);
    cv::circle(returnImg, cropPointPatternImage[0], DRAG_CIRCLE_SIZE, DRAW_COLOR_GREEN, CIRCLE_LINE_SIZE, LINE_AA);
    cv::circle(returnImg, cropPointPatternImage[1], DRAG_CIRCLE_SIZE, DRAW_COLOR_GREEN, CIRCLE_LINE_SIZE, LINE_AA);
    return returnImg;
}



// CROP ROI
cv::Mat ImageCropper::cropRuntimeImage(cv::Mat imageSource, double scale) {
    Point2i topLeft, botRight;
    topLeft.x = (int)(cropPointRuntimeImage[0].x * (1 / scale)); 
    topLeft.y = (int)(cropPointRuntimeImage[0].y * (1 / scale));

    botRight.x = (int)(cropPointRuntimeImage[1].x * (1 / scale));
    botRight.y = (int)(cropPointRuntimeImage[1].y * (1 / scale));

    return imageSource(Range(topLeft.y, botRight.y), Range(topLeft.x, botRight.x));
}

cv::Mat ImageCropper::cropRuntimeImage(cv::Mat imageSource) {
    return imageSource(Range(cropPointRuntimeImage[0].y, cropPointRuntimeImage[1].y),
        Range(cropPointRuntimeImage[0].x, cropPointRuntimeImage[1].x));
}


// CROP PATTERN
cv::Mat ImageCropper::cropPatternImage(cv::Mat imageSource, double scale) {
    Point2i topLeft, botRight;

    topLeft.x = (int)(cropPointPatternImage[0].x * (1 / scale));
    topLeft.y = (int)(cropPointPatternImage[0].y * (1 / scale));

    botRight.x = (int)(cropPointPatternImage[1].x * (1 / scale));
    botRight.y = (int)(cropPointPatternImage[1].y * (1 / scale));

    return imageSource(Range(topLeft.y, botRight.y), Range(topLeft.x, botRight.x));
}

cv::Mat ImageCropper::cropPatternImage(cv::Mat imageSource) {
    return imageSource(Range(cropPointPatternImage[0].y, cropPointPatternImage[1].y),
        Range(cropPointPatternImage[0].x, cropPointPatternImage[1].x));
}



Point ImageCropper::getCropPointRuntimeImage(int index) {  // lấy giá trị góc của ROI
    if ((index >= 0) && (index < 2)) {
        return cropPointRuntimeImage[index];
    }
    return Point(0, 0);
}

Point ImageCropper::getCropPointPatternImage(int index) { // lấy giá trị góc của pattern
    if ((index >= 0) && (index < 2)) {
        return cropPointPatternImage[index];
    }
    return Point(0, 0);
}

void ImageCropper::setCropPointRuntimeImage(Point setPoint, int index) {// set giá trị cho góc ROI
    if ((index >= 0) && (index < 2)) {
        cropPointRuntimeImage[index] = setPoint;
    }
}

void ImageCropper::setCropPointPatternImage(Point setPoint, int index) { // set giá trị chho góc pattern
    if ((index >= 0) && (index < 2)) {
        cropPointPatternImage[index] = setPoint;
    }
}