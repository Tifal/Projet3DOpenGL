#ifndef MARKER_H
#define MARKER_H

class Marker
{
public:
    Marker();
    Marker(int id, float x, float y, float z);
    Marker(int id, const Marker& marker);
    float getX() const;
    float getY() const;
    float getZ() const;
    int getRedId() const;
    int getGreenId() const;
    int getBlueId() const;

private:
    float markerCoordinates[3];
    int redId;
    int greenId;
    int blueId;
};

#endif // MARKER_H
