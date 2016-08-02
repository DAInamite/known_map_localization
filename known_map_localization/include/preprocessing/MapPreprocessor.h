/*
 * MapPreprocessor.h
 *
 *  Created on: 02.08.2016
 *      Author: jacob
 */

#ifndef KNOWN_MAP_LOCALIZATION_INCLUDE_PREPROCESSING_MAPPREPROCESSOR_H_
#define KNOWN_MAP_LOCALIZATION_INCLUDE_PREPROCESSING_MAPPREPROCESSOR_H_

#include <string>

#include <boost/shared_ptr.hpp>

#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>

namespace known_map_localization {
namespace preprocessing {

class MapPreprocessor {
public:
	MapPreprocessor(std::string topicName, std::string paramName);
	virtual ~MapPreprocessor();

	bool process(nav_msgs::OccupancyGridPtr map);

protected:
	virtual bool processMap(cv::Mat &img, nav_msgs::MapMetaData &mapMetaData) = 0;

private:
	static cv::Mat matFromOccupancyGrid(nav_msgs::OccupancyGridConstPtr map);
	static nav_msgs::OccupancyGridPtr occupancyGridFromMat(const cv::Mat &img);
	static void overwriteMapContent(nav_msgs::OccupancyGridPtr map, const cv::Mat &content);
	void publishResult(const cv::Mat &img);

	ros::Publisher preprocessedMapPublisher;
	bool enabled;
};

typedef boost::shared_ptr<MapPreprocessor> MapPreprocessorPtr;
typedef boost::shared_ptr<MapPreprocessor const> MapPreprocessorConstPtr;
} /* namespace preprocessing */
} /* namespace known_map_localization */

#endif /* KNOWN_MAP_LOCALIZATION_INCLUDE_PREPROCESSING_MAPPREPROCESSOR_H_ */