/*
 * Map.cpp
 *
 *  Created on: Dec 21, 2008
 *      Author: richardmarcley
 */

#include "Map.h"
#include "Utils.h"

#include <iostream>
using namespace std;

Map::Map()
{
}

Map::Map(int length, int height) {
	this->length = length;
	this->height = height;
}

void Map::addMarker(MapMarker marker)
{
	markers.push_back(marker);
}

vector<MapMarker> Map::getMarkerById(string id)
{
	vector<MapMarker> foundMarkers;

	for (int i =0; i< markers.size(); i++) {
		if (markers[i].getId() == id) {
			foundMarkers.push_back(markers[i]);
		}
	}

	return foundMarkers;
}

MapMarker Map::getMarker(int index) {
	return markers[index];
}


