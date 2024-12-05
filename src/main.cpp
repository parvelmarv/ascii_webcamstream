#include <opencv2/opencv.hpp>
#include "image_processing.hpp"

bool useSobel = false;

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

        imageToAsciiWindow(frame, useSobel);

        if (cv::waitKey(30) >= 0) {
            break;
        }
    }

    cap.release();

    return 0;
}
