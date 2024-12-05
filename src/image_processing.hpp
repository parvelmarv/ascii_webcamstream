#pragma once

namespace cv {
    class Mat;
}

char pixelToAscii(int pixelValue);
void imageToAsciiWindow(const cv::Mat& image, bool useSobel);
void applySobelFilter(const cv::Mat& image, cv::Mat& sobel);
