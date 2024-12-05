#include "image_processing.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

char pixelToAscii(int pixelValue) {
    const std::string ascii_chars = " .:+coOP#@";
    return ascii_chars[pixelValue * (ascii_chars.length() - 1) / 255];
}

void applySobelFilter(const cv::Mat& image, cv::Mat& sobel) {
    cv::Mat grad_x, grad_y;
    cv::Sobel(image, grad_x, CV_16S, 1, 0, 3);
    cv::Sobel(image, grad_y, CV_16S, 0, 1, 3);
    cv::Mat grad_x_float, grad_y_float;
    grad_x.convertTo(grad_x_float, CV_32F);
    grad_y.convertTo(grad_y_float, CV_32F);
    cv::Mat grad_magnitude;
    cv::magnitude(grad_x_float, grad_y_float, grad_magnitude);
    cv::convertScaleAbs(grad_magnitude, sobel);
}

void processImage(const cv::Mat& image) {
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::Mat sobel;
    applySobelFilter(gray, sobel);
    cv::imshow("Original Image", image);
    cv::imshow("Grayscale Image", gray);
    cv::imshow("Sobel Filtered Image", sobel);
}

void imageToAsciiWindow(const cv::Mat& image, bool useSobel) {
    cv::Mat gray_fullsize;
    cv::cvtColor(image, gray_fullsize, cv::COLOR_BGR2GRAY);
    int scaleFactor = 8;
    int width = image.cols / scaleFactor;
    int height = image.rows / scaleFactor;
    cv::Mat resized;
    cv::resize(image, resized, cv::Size(width, height));
    cv::Mat gray;
    cv::cvtColor(resized, gray, cv::COLOR_BGR2GRAY);
    cv::Mat asciiImage(image.rows, image.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat sobel;
    applySobelFilter(gray_fullsize, sobel);
    cv::Mat input;
    if (useSobel == true) {
        input = sobel;
    } else {
        input = asciiImage;
    }
    for (int y = 0; y < resized.rows; ++y) {
        for (int x = 0; x < resized.cols; ++x) {
            int pixelValue = gray.at<uchar>(y, x);
            char asciiChar = pixelToAscii(pixelValue);
            std::string asciiStr(1, asciiChar);
            int fontFace = cv::FONT_HERSHEY_SIMPLEX;
            double fontScale = 0.3;
            int thickness = 1;
            int baseline;
            cv::Size textSize = cv::getTextSize(asciiStr, fontFace, fontScale, thickness, &baseline);
            int textX = x * 8 + (8 - textSize.width) / 2;
            int textY = y * 8 + (8 + textSize.height) / 2;
            cv::putText(input, asciiStr, cv::Point(textX, textY), fontFace, fontScale, cv::Scalar(255, 255, 255), thickness);
        }
    }
    cv::namedWindow("ASCII Art Image", cv::WINDOW_NORMAL);
    cv::resizeWindow("ASCII Art Image", image.cols, image.rows);
    cv::imshow("ASCII Art Image", input);
}
