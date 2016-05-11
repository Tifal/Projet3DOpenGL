#include "marker.h"

Marker::Marker() {}

Marker::Marker(int id, float x, float y, float z)
{
    markerCoordinates[0] = x;
    markerCoordinates[1] = y;
    markerCoordinates[2] = z;

    redId = (id & 0x000000FF);
    greenId = (id & 0x0000FF00) >>  8;
    blueId = (id & 0x00FF0000) >> 16;
}

float Marker::getX() const {
    return markerCoordinates[0];
}

float Marker::getY() const {
    return markerCoordinates[1];
}

float Marker::getZ() const {
    return markerCoordinates[2];
}

int Marker::getRedId() const {
    return redId;
}

int Marker::getGreenId() const {
    return greenId;
}

int Marker::getBlueId() const {
    return blueId;
}

