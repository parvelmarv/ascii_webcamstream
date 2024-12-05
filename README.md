# ASCII Webcam Stream

This project uses OpenCV to capture webcam frames, process them, and display an ASCII art representation of the webcam feed with Sobel edge detection. This readme is currently targeting Windows users. That said, the project should work just as fine on mac and linux. 

## Prerequisites

Before you start, you'll need to install the following dependencies:

### 1. **OpenCV**

OpenCV is used for image processing, including capturing webcam frames, converting them to grayscale, resizing them, and applying Sobel edge detection.

#### Installing OpenCV

- Download OpenCV from the official release page:
   - OpenCV 4.10.0: [OpenCV Releases](https://opencv.org/releases/)

- Follow the installation instructions on the OpenCV page based on your operating system.

   For Windows:
   - Extract the downloaded OpenCV package.
   - Set up environment variables to point to the OpenCV installation.

### 2. **Setting Up System Environment Variables for OpenCV**

You need to configure your system’s environment variables to make sure OpenCV is correctly linked with your project.

#### Windows:
- Open the **System Properties** window (Windows + Pause/Break → Advanced System Settings → Environment Variables).
- Under **System variables**, add the following:
  - **Variable Name**: `OPENCV_DIR`
  - **Variable Value**: Path to your OpenCV folder (e.g., `C:\opencv\build`)

- Edit the **Path** variable in **System variables** and add:
  - `C:\opencv\build\x64\vc15\bin` (Update with the correct path where OpenCV was installed).

## Building the Project

To build the project, follow these steps:

1. **Clone the repository**

   Run the following command to clone the repository:

   ```bash
   git clone https://github.com/parvelmarv/ascii_webcamstream.git
   cd ascii_webcamstream
   
2. **Install CMake**

   If you don’t have CMake installed, you can download it from the official website: CMake Downloads. 

    ```bash
    mkdir build
    cd build
    cmake ..
    make

3. **Run the Program**

    After the build is complete, run the program:
   
      `./openCV_test`

    This will open your webcam feed, convert it to ASCII art, apply Sobel edge detection, and display the results in a window.
