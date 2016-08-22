/*
 * MapPreprocessor.cpp
 *
 *  Created on: 02.08.2016
 *      Author: jacob
 */

#include <opencv2/imgproc/imgproc.hpp>

#include <preprocessing/MapPreprocessor.h>

#include <cv_bridge/cv_bridge.h>
#include <mapstitch/utils.h>
#include <tf/transform_datatypes.h>

namespace known_map_localization {
namespace preprocessing {

MapPreprocessor::MapPreprocessor(std::string topicName, std::string paramName) :
		enabled(false) {
	if (ros::isInitialized()) {
		ros::NodeHandle nh("~");

		preprocessedMapPublisher = nh.advertise<sensor_msgs::Image>(topicName,
				1, true);
		nh.getParam(paramName, enabled);
	}
}

MapPreprocessor::~MapPreprocessor() {
}

bool MapPreprocessor::process(nav_msgs::OccupancyGridPtr map) {
	assert(map);
	bool success = true;

	// convert to matrix
	cv::Mat img = matFromOccupancyGrid(map);

	if (enabled) {
		success = processMap(img, map->info);
		overwriteMapContent(map, img);
	}

	if(success) {
		publishResult(img);
	} else {
		ROS_WARN("Map preprocessing failed.");
	}

	return success;
}

cv::Mat MapPreprocessor::matFromOccupancyGrid(
		nav_msgs::OccupancyGridConstPtr map) {
	return occupancyGridToCvMat(map.get());
}

nav_msgs::OccupancyGridPtr MapPreprocessor::occupancyGridFromMat(
		const cv::Mat &img) {
	return boost::make_shared<nav_msgs::OccupancyGrid>(cvMatToOccupancyGrid(&img));
}

void MapPreprocessor::overwriteMapContent(nav_msgs::OccupancyGridPtr map,
		const cv::Mat &content) {
	nav_msgs::OccupancyGridConstPtr preprocessedMap = occupancyGridFromMat(content);
	map->data = preprocessedMap->data;
	map->info.width = preprocessedMap->info.width;
	map->info.height = preprocessedMap->info.height;
}

void MapPreprocessor::publishResult(const cv::Mat &img) {
	if(ros::isInitialized()) {
		cv_bridge::CvImage intermediateResultImage;
		intermediateResultImage.encoding = sensor_msgs::image_encodings::MONO8;
		intermediateResultImage.image = img;
		intermediateResultImage.header.stamp = ros::Time::now();
		preprocessedMapPublisher.publish(intermediateResultImage.toImageMsg());
	}
}

void MapPreprocessor::crop(cv::Mat &img, nav_msgs::MapMetaData &map) {
	cv::Mat points, mask;
	cv::threshold(img, mask, 1, 255, cv::THRESH_BINARY_INV);
	cv::findNonZero(mask, points);
	cv::Rect boundingBox = cv::boundingRect(points);

	// crop
	img = img(boundingBox).clone();

	cv::Point2i offset(boundingBox.x, boundingBox.y);
	updateMapOrigin(map, offset);

	map.height = img.rows;
	map.width = img.cols;
}

void MapPreprocessor::updateMapOrigin(nav_msgs::MapMetaData &map, cv::Point2i origin) {
	tf::Pose offset(tf::Quaternion::getIdentity(), tf::Vector3(origin.x * map.resolution, origin.y * map.resolution, 0));

	tf::Transform oldOrigin;
	tf::poseMsgToTF(map.origin, oldOrigin);
	tf::Transform newOrigin = oldOrigin * offset;

	tf::poseTFToMsg(newOrigin, map.origin);
}

} /* namespace preprocessing */
} /* namespace known_map_localization */
