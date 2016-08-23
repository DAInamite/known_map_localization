/*
 * MapmergeKnownMapPreprocessor.cpp
 *
 *  Created on: 07.08.2016
 *      Author: jacob
 */

#include <preprocessing/MapmergeKnownMapPreprocessor.h>

namespace known_map_localization {
namespace preprocessing {

bool MapmergeKnownMapPreprocessor::processMap(cv::Mat &img, nav_msgs::MapMetaData &mapMetaData) {

	// edge detection using Canny detector
	cv::Mat edges;
	cv::Canny(img, edges, 50, 150, 3);
	edges.convertTo(img, CV_8U);

	// invert
	img = cv::Scalar::all(255) - img;

	// make edges thicker; edgeRadius is half the width of the edge in meters
	float edgeRadius = 0.1;
	unsigned int kernelRadius = std::max(1., floor(edgeRadius / mapMetaData.resolution));
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2*kernelRadius+1, 2*kernelRadius+1));
	cv::erode(img, img, kernel);

	// restore to correct free value
	restoreMap(img);

	return true;
}

} /* namespace preprocessing */
} /* namespace known_map_localization */