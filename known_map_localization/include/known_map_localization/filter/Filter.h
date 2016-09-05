/*
 * Filter.h
 *
 *  Created on: 02.08.2016
 *      Author: jacob
 */

#ifndef KNOWN_MAP_LOCALIZATION_INCLUDE_FILTER_FILTER_H_
#define KNOWN_MAP_LOCALIZATION_INCLUDE_FILTER_FILTER_H_

#include <vector>
#include <exception>

#include "alignment/Hypothesis.h"

namespace known_map_localization {
namespace filter {

class Filter;
typedef boost::shared_ptr<Filter> FilterPtr;
typedef boost::shared_ptr<Filter const> FilterConstPtr;

/**
 * # Filter
 */
class Filter {
public:
	static FilterPtr instance();

	virtual ~Filter();

	/**
	 * Add new hypotheses and update the filtered alignment accordingly.
	 * Multiple possible implementations are given by subclasses of Filter.
	 * @param hypotheses New hypotheses
	 */
	virtual void addHypotheses(const alignment::HypothesesVect &hypotheses) = 0;

	/**
	 * Get the filtered alignment, if available. If it isn't available, an exception is thrown.
	 * @return The filtered alignment
	 * @throw AlignmentNotAvailable, if filtered alignment is not available
	 */
	const alignment::Alignment& getAlignment() const;

	/**
	 * Check if the filtered alignment is available.
	 * @return State of the filtered alignment
	 */
	bool isAvailable() const;

protected:
	Filter();

protected:
	/// the current filtered alignment
	alignment::Alignment filteredAlignment;

	/// flag indicating if filtered alignment is available
	bool ready;

private:
	static FilterPtr _instance;
};

} /* namespace filter */
} /* namespace known_map_localization */

#endif /* KNOWN_MAP_LOCALIZATION_INCLUDE_FILTER_FILTER_H_ */
