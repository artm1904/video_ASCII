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

  std::cout << "Video FPS: " << fps << std::endl;
  std::cout << "Video Frame Count: " << frame_count << std::endl;

  cap.release();


  return 0;
}