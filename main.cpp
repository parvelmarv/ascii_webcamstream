#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>

char pixelToAscii(int pixelValue) {
    const std::string ascii_chars = " .:coOP#@";
    return ascii_chars[pixelValue * (ascii_chars.length() - 1) / 255];
}

void imageToAsciiWindow(const cv::Mat& image) {
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

    cv::Mat grad_x, grad_y, abs_grad_x, abs_grad_y, sobel;
    cv::Sobel(gray_fullsize, grad_x, CV_16S, 1, 0, 3);
    cv::Sobel(gray_fullsize, grad_y, CV_16S, 0, 1, 3);
    cv::convertScaleAbs(grad_x, abs_grad_x);
    cv::convertScaleAbs(grad_y, abs_grad_y);
    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, sobel);

    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            int sobelPixel = sobel.at<uchar>(y, x);
            int blendedPixel = (sobelPixel);
            asciiImage.at<cv::Vec3b>(y, x) = cv::Vec3b(blendedPixel, blendedPixel, blendedPixel);
        }
    }

    int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = 0.3;
    int thickness = 1;
    for (int y = 0; y < resized.rows; ++y) {
        for (int x = 0; x < resized.cols; ++x) {
            int pixelValue = gray.at<uchar>(y, x);
            char asciiChar = pixelToAscii(pixelValue);
            std::string asciiStr(1, asciiChar);

            if (asciiChar == '@') {
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        int imgX = x * 8 + j;
                        int imgY = y * 8 + i;

                        if (imgX < asciiImage.cols && imgY < asciiImage.rows) {
                            asciiImage.at<cv::Vec3b>(imgY, imgX) = cv::Vec3b(255, 255, 255);
                        }
                    }
                }
            } else {
                int textWidth, textHeight;
                int baseline;
                cv::Size textSize = cv::getTextSize(asciiStr, fontFace, fontScale, thickness, &baseline);

                int textX = x * 8 + (8 - textSize.width) / 2;
                int textY = y * 8 + (8 + textSize.height) / 2;

                cv::putText(asciiImage, asciiStr, cv::Point(textX, textY), fontFace, fontScale, cv::Scalar(255, 255, 255), thickness);
            }
        }
    }

    cv::namedWindow("ASCII + Sobel Image", cv::WINDOW_NORMAL);
    cv::resizeWindow("ASCII + Sobel Image", image.cols, image.rows);
    cv::imshow("ASCII + Sobel Image", asciiImage);
}

int main() {
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the webcam." << std::endl;
        return -1;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);

    cv::Mat frame;
    while (true) {
        cap >> frame;

        if (frame.empty()) {
            std::cerr << "Error: Failed to capture image." << std::endl;
            break;
        }

        imageToAsciiWindow(frame);

        if (cv::waitKey(30) >= 0) {
            break;
        }
    }

    return 0;
}
