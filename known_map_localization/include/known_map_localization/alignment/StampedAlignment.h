/*
 * StampedAlignment.h
 *
 *  Created on: 02.08.2016
 *      Author: jacob
 */

#ifndef KNOWN_MAP_LOCALIZATION_INCLUDE_ALIGNMENT_STAMPEDALIGNMENT_H_
#define KNOWN_MAP_LOCALIZATION_INCLUDE_ALIGNMENT_STAMPEDALIGNMENT_H_

#include <ros/time.h>

#include "Alignment.h"

namespace kml {

/**
 * # StampedAlignment
 * Extends the Alignment with a time stamp.
 */
class StampedAlignment: public Alignment {
public:
	StampedAlignment();
	StampedAlignment(const Alignment &a);
	virtual ~StampedAlignment();

	/**
	 * Converts the alignment to a stamped tf transform.
	 * @note The scale factor is omitted when converting!
	 * @return The stamped tf transform
	 */
	tf::StampedTransform toTfStampedTransform() const;

	/**
	 * Get an alignment without any transformation.
	 * @return The identity alignment
	 */
	static StampedAlignment getIdentity();

	/// The ROS time stamp of the alignment
	ros::Time stamp;
};

} /* namespace kml */

#endif /* KNOWN_MAP_LOCALIZATION_INCLUDE_ALIGNMENT_STAMPEDALIGNMENT_H_ */
