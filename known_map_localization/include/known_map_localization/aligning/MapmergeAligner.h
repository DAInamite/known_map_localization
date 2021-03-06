/*
 * MapmergeAligner.h
 *
 *  Created on: 07.08.2016
 *      Author: jacob
 */

#ifndef KNOWN_MAP_LOCALIZATION_INCLUDE_ALIGNING_MAPMERGEALIGNER_H_
#define KNOWN_MAP_LOCALIZATION_INCLUDE_ALIGNING_MAPMERGEALIGNER_H_

#include <mapmerge/grid_map.h>

#include <aligning/Aligner.h>

namespace kml {

/**
 * # Mapmerge Aligner
 *
 * This aligning algorithm uses the mapmerge library by Stefano Carpin to align two maps.
 *
 * ## Parameters
 * - **use_randomized_hough_transform**: Enable/disable randomized Hough transform
 * - **use_robust_algorithm**: Enable/disable use of robust algorithm version of mapmerge
 * - **number_of_hypotheses**: The number of hypotheses mapmerge should compute
 */
class MapmergeAligner: public Aligner {
public:
	MapmergeAligner();

	/**
	 * Aligns the two maps using the mapmerge algorithm and returns a vector of hypotheses.
	 * @param knownMap The known map
	 * @param slamMap The SLAM map
	 * @return A vector of hypotheses
	 */
	HypothesesVect align(nav_msgs::OccupancyGridConstPtr knownMap, nav_msgs::OccupancyGridConstPtr slamMap);

protected:
	/// This flag determines whether the randomized Hough transform should be used
	bool mUseRandomizedHoughTransform_;

	/// This flag determines whether the robust version of the algorithm should be used
	bool mUseRobustAlgorithm_;

	/// The number of hypotheses to be computed
	int mNumberOfHypotheses_;
};

/**
 * Copies the map to a grid_map, assuming, that the target gridMap already has the needed size.
 * @param occGrid The source map
 * @param gridMap The target map
 * @return True if map contains at least on occupied cell.
 */
bool copyOccupancyGridToGridMap(nav_msgs::OccupancyGridConstPtr occGrid, mapmerge::grid_map &gridMap);

} /* namespace kml */

#endif /* KNOWN_MAP_LOCALIZATION_INCLUDE_ALIGNING_MAPMERGEALIGNER_H_ */
