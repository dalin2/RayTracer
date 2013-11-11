//
//  Shape.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Shape__
#define __RayTracer__Shape__

#include <iostream>
#include "Ray.h"
#include "Texture.h"
#include "Vector3.h"
#include "Color.h"

//class Ray;
//class Color;


/*records t value for interesection (so we can retrieve (x, y, z) coordinates from parametric equations as well
 as the normal of the surface intersected and the color to be drawn */
struct IntersectRecord {
    float t;
    Vector3 normal;
    Vector2 uv; //used for 2D textures
    Vector3 intersection; //point of intersection
    Texture* tex; //texture of nearest interesected object
};

class Shape {
public:
    //time parameter to be used for motion blur in animation i.e. see DSphere
    virtual bool intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const=0;
    //useful to determine intersections for occluded objects as it is faster / more efficient
    virtual bool shadowIntersect(const Ray& r, float tmin, float tmax, float time) const=0;
};

#endif /* defined(__RayTracer__Shape__) */
