#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <random>
#include <string>


cv::Mat createNewbg() {
  return cv::Mat::ones(1000, 1000, CV_8UC3);
}


cv::Vec3b randomColor(){ 
  std::random_device seed;
  std::mt19937 mt(seed());
  std::uniform_int_distribution<int> rand5(0, 1);
  return cv::Vec3b(rand5(mt) * 255, rand5(mt) * 255, rand5(mt) * 255);
}


void kmeans(const cv::Mat &img) {
  cv::Mat points;
  img.convertTo(points, CV_32FC3);
  points = points.reshape(3, img.rows * img.cols);

  const int cluster_count = 3;

  cv::Mat_<int> clusters(points.size(), CV_32SC1);
  cv::Mat centers;

  cv::kmeans(points, cluster_count, clusters, 
	     cvTermCriteria(CV_TERMCRIT_EPS|CV_TERMCRIT_ITER, 10, 1.0),
             1, cv::KMEANS_PP_CENTERS, centers);
  cv::kmeans(points, cluster_count, clusters,
    cvTermCriteria(CV_TERMCRIT_EPS|CV_TERMCRIT_ITER, 10, 1.0),
    1, cv::KMEANS_PP_CENTERS, centers);

  cv::Mat dst_img(img.size(), img.type());
  cv::MatIterator_<cv::Vec3b> itd = dst_img.begin<cv::Vec3b>();
  cv::MatIterator_<cv::Vec3b> itd_end = dst_img.end<cv::Vec3b>();
  
  for (int i=0; itd != itd_end; ++itd, ++i) {
    cv::Vec3f &color = centers.at<cv::Vec3f>(clusters(i), 0);
    (*itd)[0] = cv::saturate_cast<uchar>(color[0]);
    (*itd)[1] = cv::saturate_cast<uchar>(color[1]);
    (*itd)[2] = cv::saturate_cast<uchar>(color[2]);
  }

  cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
  cv::imshow("image", dst_img);
  cv::waitKey(0);
  cv::destroyAllWindows();
}


cv::Mat detect(const cv::Mat &img) {
  cv::Mat gray, mono;
  cv::Mat result = cv::Mat::zeros(img.rows, img.cols, CV_8UC3);

  cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
  cv::threshold(gray, mono, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
  cv::namedWindow("image", 1);
  cv::imshow("image", mono);
  cv::waitKey(0);
  cv::destroyAllWindows();
  
  std::vector<std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;

  cv::findContours(mono, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

  int idx = 0;
  for( ; idx >= 0; idx = hierarchy[idx][0]) {
    cv::drawContours(result, contours, idx, cv::Scalar(255, 255, 0), CV_FILLED, 8, hierarchy);
  }
  
  cv::namedWindow("image", 1);
  cv::imshow("image", result);
  cv::waitKey(0);
  cv::destroyAllWindows();

  return result;
}


cv::Mat colorThresholding(const cv::Mat &img) {
  cv::Mat gray, result;
  
  cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY); 
  cv::threshold(gray, result, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
  cv::cvtColor(result, result, cv::COLOR_GRAY2RGB);

  cv::Vec3b white = randomColor();
  cv::Vec3b black = randomColor();
  for(int y = 0; y < result.rows; y++) {
    for(int x = 0; x < result.cols; x++) {
      if (result.data[y * result.step + x * result.elemSize()] == 255) {
        result.at<cv::Vec3b>(y, x) = white;
      } else {
        result.at<cv::Vec3b>(y, x) = black;
      }
    }
  }

  return result;
}


cv::Mat pasteImage(const cv::Mat &bg, const cv::Mat &img, const int tx, const int ty) {
  cv::Mat result;
  bg.copyTo(result);

  cv::Mat mat = (cv::Mat_<double>(2,3) << 1.0, 0.0, tx, 0.0, 1.0, ty);
  cv::warpAffine(img, result, mat, result.size(), CV_INTER_LINEAR, cv::BORDER_TRANSPARENT);

  return result;
}


cv::Mat openImage(const std::string name) {
  cv::Mat src = cv::imread(name, cv::IMREAD_COLOR);

  if (src.empty()) {
    std::cerr << "Fialed to open an images file." << std::endl;
  }

  return src;
}


int main(void) {
  cv::Mat src1 = openImage("images/1.jpg");
  cv::Mat src2 = openImage("images/2.jpg");
  cv::Mat src3 = openImage("images/3.jpg");
  cv::Mat src4 = openImage("images/4.jpg");

  cv::Mat resize1, resize2, resize3, resize4;
  cv::resize(src1, resize1, cv::Size(500, 500));
  cv::resize(src2, resize2, cv::Size(500, 500));
  cv::resize(src3, resize3, cv::Size(500, 500));
  cv::resize(src4, resize4, cv::Size(500, 500));

  // detect(src1);
  kmeans(src1);
  
  cv::Mat result = createNewbg();
  
  result = pasteImage(result, colorThresholding(resize1), 0, 0);
  result = pasteImage(result, colorThresholding(resize2), 500, 0);
  result = pasteImage(result, colorThresholding(resize3), 0, 500);
  // result = pasteImage(result, colorThresholding(resize4), 500, 500);

  cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
  cv::imshow("image", result);
  cv::imwrite("dest/result.jpg", result);
  cv::waitKey(0);
  cv::destroyAllWindows();
  
  return 0;
}
