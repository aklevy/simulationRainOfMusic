    #ifndef ZONEGRID_H
#define ZONEGRID_H

#include "ofMain.h"


class zoneGrid
{
public:
    zoneGrid(int width, int height, int depth);

    // Draw choregraphy zone
    void drawZone();

    // Draw grid in the "ground"
    void drawGrid();

    // Draw vertical axes in the zone
    void drawAxes();

    // Modify axis to be displayed
    void modifyAxis(int axis);

    // Get zone dimension
    ofVec3f dimension();

private:
        int _widthZone, _heightZone, _depthZone;
        bool x_axis, y_axis, z_axis;
};

#endif // ZONEGRID_H
