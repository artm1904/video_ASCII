#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <thread>

constexpr char pixelToAscii(int pixelValue) {
  // const std::string ASCII_CHARS = "@%#*+=-:. ";
  const std::string_view ASCII_CHARS = " .:-=+*#%@";
  const int index = pixelValue * (ASCII_CHARS.length() - 1) / 255;
  return ASCII_CHARS[index];
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <video_path>" << std::endl;
    return 1;
  }

  std::string video_path = argv[1];

  cv::VideoCapture cap(video_path);

  if (!cap.isOpened()) {
    std::cerr << "Error opening video file" << std::endl;
    return 1;
  }

  double fps = cap.get(cv::CAP_PROP_FPS);
  int frame_count = cap.get(cv::CAP_PROP_FRAME_COUNT);

  //   std::cout << "Video FPS: " << fps << std::endl;
  //   std::cout << "Video Frame Count: " << frame_count << std::endl;
  // int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
  // int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

  int frameDurationMS = 1000 / fps;

  int width = 150;

  int frameWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
  int frameHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

  const float aspectRatioCorrection = 0.52f;
  int height = static_cast<int>(static_cast<float>(width * frameHeight) / frameWidth *
                                aspectRatioCorrection);

  cv::Mat frame, grayFrame, resizedFrame;

  while (true) {
    cap >> frame;

    if (frame.empty()) {
      break;
    }

    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

    cv::resize(grayFrame, resizedFrame, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);

    std::string asciiFrame;

    // reserv memory to avoid continiues alocations
    asciiFrame.reserve(height * (width + 1));
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        asciiFrame += pixelToAscii(resizedFrame.at<uchar>(i, j));
      }
      asciiFrame += "\n";
    }

    // Use ANSI escape-code for clear screen
    std::cout << "\033[2J\033[1;1H";
    std::cout << asciiFrame << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(frameDurationMS));
  }

  cap.release();

  return 0;
}