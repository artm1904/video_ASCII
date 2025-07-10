#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>



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

  int frameDurationMS = 1000 / fps;
  //   int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
  //   int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

  int width = 150;
  int height = 50;

  cv::Mat frame, grayFrame, resizedFrame;

  while (true) {
    cap >> frame;

    if (frame.empty()) {
      break;
    }

    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

    cv::resize(grayFrame, resizedFrame, cv::Size(width, height), 0, 0, cv::INTER_CUBIC);


    std::string asciiFrame;
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        int pixelValue = resizedFrame.at<uchar>(i, j);
      }
    }


  }

  cap.release();

  return 0;
}