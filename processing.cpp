#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


int main(void) {
  cv::Mat src = cv::imread("images/1.jpg", cv::IMREAD_COLOR);

  if (src.empty()) {
    std::cerr << "Fialed to open an image file." << std::endl;
    return -1;
  }
 
  cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
  cv::imshow("image", src);
  cv::waitKey(0);
  cv::destroyAllWindows(); 
  
  return 0;
}
