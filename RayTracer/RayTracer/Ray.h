//
//  Ray.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Ray__
#define __RayTracer__Ray__

#include <iostream>
#include "Vector3.h"

class Ray {
public:
    Ray() {}
    Ray(const Vector3& a, const Vector3& b) {data[0] = a; data[1] = b;}
    Ray(const Ray& r) {*this = r;}
    Vector3 origin() const {return data[0];}
    Vector3 direction() const {return data[1];}
    Vector3 pointAtParameter(float t) const {return data[0] + t*data[1];}
    
private:
    Vector3 data[2];
};

#endif /* defined(__RayTracer__Ray__) */
