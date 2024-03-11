#include <iostream>
#include "GeoMatch.h"
#include "ImageCropper.h"

#define PYRAMID_DOWN_LEVEL 1


String path_template = "imgSrc/template.bmp";
String path_template_flip = "imgSrc/template-flip.bmp";

String path_source = "imgSrc/sample-2.bmp";


ImageMatch::GeoMatch GeoMatching;


int main()
{
    GeoMatching.addGeoMatchModel(path_template, "side a");
    //GeoMatching.addGeoMatchModel(path_template_flip, "side b");
    GeoMatching.setImageSource(path_source);
    GeoMatching.matching(false ,3);
    waitKey(0);
}

