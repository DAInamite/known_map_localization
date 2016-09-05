/*
 * KnownMapPreprocessor.h
 *
 *  Created on: 02.08.2016
 *      Author: jacob
 */

#ifndef KNOWN_MAP_LOCALIZATION_INCLUDE_PREPROCESSING_KNOWNMAPPREPROCESSOR_H_
#define KNOWN_MAP_LOCALIZATION_INCLUDE_PREPROCESSING_KNOWNMAPPREPROCESSOR_H_

#include "MapPreprocessor.h"

namespace known_map_localization {
namespace preprocessing {

class KnownMapPreprocessor;
typedef boost::shared_ptr<KnownMapPreprocessor> KnownMapPreprocessorPtr;
typedef boost::shared_ptr<KnownMapPreprocessor const> KnownMapPreprocessorConstPtr;

class KnownMapPreprocessor: public MapPreprocessor {
public:
	static KnownMapPreprocessorPtr instance();
protected:
	KnownMapPreprocessor();
private:
	static KnownMapPreprocessorPtr _instance;
};

} /* namespace preprocessing */
} /* namespace known_map_localization */

#endif /* KNOWN_MAP_LOCALIZATION_INCLUDE_PREPROCESSING_KNOWNMAPPREPROCESSOR_H_ */
