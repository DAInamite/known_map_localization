/*
 * DecayFilter.h
 *
 *  Created on: 30.09.2016
 *      Author: jacob
 */

#ifndef KNOWN_MAP_LOCALIZATION_INCLUDE_KNOWN_MAP_LOCALIZATION_FILTER_DECAYFILTER_H_
#define KNOWN_MAP_LOCALIZATION_INCLUDE_KNOWN_MAP_LOCALIZATION_FILTER_DECAYFILTER_H_

#include <filter/Filter.h>

namespace known_map_localization {
namespace filter {

/**
 * # Decay Filter
 * Simple filter where the score of the current best hypothesis decays slowly over time.
 * Each time new hypotheses are available they are checked for a better one.
 *
 * ## Parameters
 * - **decay_factor**: The decay factor multiplied to the score each time new hypotheses arrive
 */
class DecayFilter: public Filter {
public:
	DecayFilter();

	/**
	 * Update the filtered hypothesis.
	 * @param hypotheses A vector of new hypotheses
	 */
	virtual void addHypotheses(const alignment::HypothesesVect &hypotheses);

protected:
	/**
	 * Check if the vector contains a better hypothesis than the currently used one.
	 * @param hypotheses A vector of new hypotheses
	 * @param betterHypothesis [out] The better hypothesis, if any is found
	 * @return True if a better hypothesis was found, otherwise false
	 */
	bool checkForBetterHypothesis(const alignment::HypothesesVect &hypotheses, alignment::Hypothesis &betterHypothesis) const;

	/**
	 * Returns whether it is a better hypothesis than the currently used one.
	 * @param hypothesis The hypothesis to be checked
	 * @return True if it it considered better
	 */
	virtual bool isBetter(const alignment::Hypothesis &hypothesis) const;

	/**
	 * Degrade the score of the current filtered alignment by the decay factor.
	 */
	void scoreDecay();

protected:
	/// Score of the current filtered alignment
	float mScore_;

	/// Decay factor multiplied to the score each time new hypotheses arrive
	float mDecayFactor_;
};

} /* namespace filter */
} /* namespace known_map_localization */

#endif /* KNOWN_MAP_LOCALIZATION_INCLUDE_KNOWN_MAP_LOCALIZATION_FILTER_DECAYFILTER_H_ */
