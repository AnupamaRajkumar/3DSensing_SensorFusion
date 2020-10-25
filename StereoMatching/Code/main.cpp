/************************************************************************************************
A. Stereo matching techniques:
1. Naive stereo matching
2. Dynamic programming approach - make parameters tunable
B. Display disparity images
C. Save disparity images to 3D point cloud
Extra points : parallelising/fast implementation, compare solution to existing implementation
**************************************************************************************************/


#include <opencv2/opencv.hpp>
#include <iostream>
#include <string> 

#include "DynamicApproach.h"
#include "NaiveApproach.h"
#include "Utility.h"


int main(int argc, char** argv) {

  ////////////////
  // Parameters //
  ////////////////

  // camera setup parameters
  const double focal_length = 1247;
  const double baseline = 213;

  // stereo estimation parameters
  const int dmin = 67;
  int window_size = 7;
  double weight = 500;
  const double scale = 3;

  ///////////////////////////
  // Commandline arguments //
  ///////////////////////////

  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " IMAGE1 IMAGE2 " << std::endl;
    return 1;
  }

  cv::Mat image1 = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  cv::Mat image2 = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);

  if (!image1.data) {
    std::cerr << "No image1 data" << std::endl;
    return EXIT_FAILURE;
  }

  if (!image2.data) {
    std::cerr << "No image2 data" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Enter the window size:" << std::endl;
  std::cin >> window_size;
  std::cout << "Enter the occlusion weights:" << std::endl;
  std::cin >> weight;

  std::cout << "------------------ Parameters -------------------" << std::endl;
  std::cout << "focal_length = " << focal_length << std::endl;
  std::cout << "baseline = " << baseline << std::endl;
  std::cout << "window_size = " << window_size << std::endl;
  std::cout << "occlusion weights = " << weight << std::endl;
  std::cout << "disparity added due to image cropping = " << dmin << std::endl;
  std::cout << "scaling of disparity images to show = " << scale << std::endl;
  std::cout << "-------------------------------------------------" << std::endl;


  /*class instantiation*/
  Utility utility;
  Naive naive(window_size, image1, image2, dmin, focal_length, baseline);
  Dynamic dynamic(image1, image2, dmin, window_size, weight);


  int choice = 1;
  ////////////////////
  // Reconstruction menu //
  ////////////////////
  while (choice != 5) {

	  std::cout << "\nReconstruction Menu:" << std::endl;
	  std::cout << "1. Naive Approach" << std::endl;
	  std::cout << "2. OpenCV stereo matching methods" << std::endl;
	  std::cout << "3. Dynamic Programming Approach" << std::endl;
	  std::cout << "4. Generation of point clouds" << std::endl;
	  std::cout << "5. Exit" << std::endl;
	  std::cout << "Enter your choice:" << std::endl;
	  std::cin >> choice;
	  std::cout << "----------------------------------------------------" << std::endl;
	
	  std::stringstream out1;
	  cv::Mat naive_disparities = cv::Mat::zeros(image1.size().height, image1.size().width, CV_8UC1);
	  switch (choice) {
		case 1:
			/*Naive disparity image	*/	
			naive.NaiveMatchingCalculation();
			break;
		case 2:
			/*openCV stereo matching methods*/
			naive.NaiveMatching_OpenCV();
			break;
		case 3:
			/*Dynamic programming approach*/
			dynamic.DynamicApproachCalculation();
			break;
		case 4:
			// reconstruction
			/*utility.Disparity2PointCloud(output_file, image1.size().height, image1.size().width, naive_disparities,
				window_size, dmin, baseline, focal_length);*/
			break;
		case 5:
			exit(0);
			break;
		default:
			std::cout << "Enter correct choice" << std::endl;
			break;
	  }
  }

  cv::waitKey(0);

  return 0;
}
