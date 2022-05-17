/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "../include/maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    // build a map
    std::map<Point<3>, TileImage*> tileMap;
    // build a kd-tree using theTiles
    vector<Point<3>> pvec(theTiles.size());
    for (unsigned i = 0; i < theTiles.size(); i++) {
        pvec[i] = convertToXYZ(theTiles[i].getAverageColor());
        tileMap[pvec[i]] = &theTiles[i];
    }
    KDTree<3> kd(pvec);
    // create a mosaic canvas object
    MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    for (int x = 0; x < theSource.getRows(); x++) {
        for (int y = 0; y < theSource.getColumns(); y++) {
            Point<3> curr_pixel = convertToXYZ(theSource.getRegionColor(x, y));
            curr_pixel = kd.findNearestNeighbor(curr_pixel);
            // find the corresponding tile and paint
            canvas->setTile(x, y, tileMap[curr_pixel]);
        }
    }

    return canvas;
}
