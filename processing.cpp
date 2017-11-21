#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>


cv::Mat createNewbg() {
  return cv::Mat::zeros(1000, 1000, CV_8UC3);
}


cv::Mat colorThresholding(const cv::Mat &img) {
  cv::Mat gray, result;
  
  cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY); 
  cv::threshold(gray, result, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
  cv::cvtColor(result, result, cv::COLOR_GRAY2RGB);
  
  cv::MatIterator_<cv::Vec3b> itr = result.begin<cv::Vec3b>();
  cv::MatIterator_<cv::Vec3b> itr_end = result.end<cv::Vec3b>();
  for (; itr!=itr_end; itr++) {
    if ((*itr)[0] == 255) {
      (*itr)[0] = 0;
      (*itr)[1] = 0;
      (*itr)[2] = 255;
    } else {
      (*itr)[0] = 255;
      (*itr)[1] = 0;
      (*itr)[2] = 0;
    }
  }

  cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
  cv::imshow("image", result);
  cv::waitKey(0);
  cv::destroyAllWindows();

  return result;
}


cv::Mat pasteImage(const cv::Mat &bg, const cv::Mat &img, const int tx, const int ty) {
  cv::Mat result;
  bg.copyTo(result);

  cv::Mat mat = (cv::Mat_<double>(2,3) << 1.0, 0.0, tx, 0.0, 1.0, ty);
  cv::warpAffine(img, result, mat, result.size(), CV_INTER_LINEAR, cv::BORDER_TRANSPARENT);

  return result;
} 


int main(void) {
  cv::Mat src = cv::imread("images/1.jpg", cv::IMREAD_COLOR);

  if (src.empty()) {
    std::cerr << "Fialed to open an image file." << std::endl;
    return -1;
  }

  cv::Mat resize;
  cv::resize(src, resize, cv::Size(500, 500));
  
  cv::Mat result = createNewbg();

  for (int i=0; i<501; i+=500) {
    for (int j=0; j<501; j+=500) {
      result = pasteImage(result, colorThresholding(resize), i, j);
    }
  }
 
  cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
  cv::imshow("image", result);
  cv::imwrite("dest/result.jpg", result);
  cv::waitKey(0);
  cv::destroyAllWindows();
  
  return 0;
}
