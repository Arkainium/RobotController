/*
 * Observation.cpp
 *
 *  Created on: Jan 13, 2009
 *      Author: Geotty
 */

#include <math.h>
#include "Utils.h"
#include "Observation.h"

#include <iostream>

double Observation::calculateLikelihoodForPosition(Position position) const {
	vector<MapMarker> markers = map->getMarkerById(markerId);

	double probability = 0;

	for (int i = 0; i < markers.size(); i++) {
		double likelihood = calculateLikelihoodForMarkerAndPosition(markers[i],
				position);

		if (likelihood > probability)
			probability = likelihood;
	}

	return probability;
}

double Observation::calculateLikelihoodForMarkerAndPosition(MapMarker marker,
		Position position) const {

	double expectedBearing = marker.getBearing(position);
	double deltaAngle = fabs((double) (bearing - expectedBearing));

	double distanceToMarker = position.getDistance(Position(marker.getX(),
			marker.getY(), 0));

	if (distanceToMarker < 5) return 0;

	double variance = 100 / distanceToMarker * Utils::toRadians(this->variance);

	double expectation = Utils::gaussian(deltaAngle, 0, variance)
			/ Utils::gaussian(0, 0, variance);

	return expectation;
}
