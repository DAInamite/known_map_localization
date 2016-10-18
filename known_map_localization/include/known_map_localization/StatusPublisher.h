/*
 * Status.h
 *
 *  Created on: 17.10.2016
 *      Author: jacob
 */

#ifndef KNOWN_MAP_LOCALIZATION_INCLUDE_KNOWN_MAP_LOCALIZATION_STATUSPUBLISHER_H_
#define KNOWN_MAP_LOCALIZATION_INCLUDE_KNOWN_MAP_LOCALIZATION_STATUSPUBLISHER_H_

#include <boost/smart_ptr.hpp>

#include <ros/ros.h>
#include <ros/wall_timer.h>

#include <known_map_localization/Status.h>

namespace kml {

typedef enum {
	STATUS_INIT = 0,
	STATUS_NO_POS = 1,
	STATUS_POS = 2,
	STATUS_VALIDATED_POS = 3
} Status;

class StatusPublisher {
public:
	StatusPublisher(float rate = 10);

	void setStatus(Status s, unsigned int nSupportingGpsPos = 0);
	Status getStatus() const;

private:
	void tick(const ros::WallTimerEvent& event);
	void publishStatus() const;

private:
	ros::Publisher mStatusPublisher_;
	ros::WallTimer mTimer_;
	Status mStatus_;
	unsigned int mNSupportingGpsPos_;
};

typedef boost::shared_ptr<StatusPublisher> StatusPublisherPtr;

} /* namespace kml */

#endif /* KNOWN_MAP_LOCALIZATION_INCLUDE_KNOWN_MAP_LOCALIZATION_STATUSPUBLISHER_H_ */