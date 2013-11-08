//
//  Camera.cpp
//  RayTracer
//
//  Created by Dustin Alin on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "Camera.h"

Camera::Camera(const Camera& orig)  {
    e = orig.e;
    corner = orig.corner;
    across = orig.across;
    up = orig.up;
    basis = orig.basis;
    l = orig.l;
    r = orig.r;
    b = orig.b;
    t = orig.t;
    d = orig.d;
    lens_radius = orig.lens_radius;
}

Camera::Camera(Vector3 c, Vector3 gaze, Vector3 vup, float aperture, float left,
               float right, float bottom, float top, float distance) {
    e = c;
    d = distance;
    l = left;
    r = right;
    b = bottom;
    t = top;
    
    lens_radius = aperture/2.0F;
    basis.initFromUV(-gaze, vup);
    corner = e + l*basis.u() + b*basis.v() - d*basis.w();
    across = (l-r)*basis.u();
    up = (b-t)*basis.v();
}

Ray Camera::getRay(float a, float b, float xi1, float xi2) {
    Vector3 origin = e + 2.0F*(xi1-0.5F)*lens_radius*basis.u() + 2.0F*(xi2-0.5F)*lens_radius*basis.v();
    Vector3 target = corner + across*a + up*b;
    return Ray(origin, normalize(target-origin));
}