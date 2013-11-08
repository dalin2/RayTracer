//
//  Camera.cpp
//  RayTracer
//
//  Created by Dustin Alin on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "Camera.h"

Camera::Camera(const Camera& orig)  {
    center = orig.center;
    corner = orig.corner;
    across = orig.across;
    up = orig.up;
    basis = orig.basis;
    u0 = orig.u0;
    u1 = orig.u1;
    v0 = orig.v0;
    v1 = orig.v1;
    d = orig.d;
    lens_radius = orig.lens_radius;
}

Camera::Camera(Vector3 c, Vector3 gaze, Vector3 vup, float aperture, float left, float right,
               float bottom, float top, float distance) {
    center = c;
    d = distance;
    u0 = left;
    u1 = right;
    v0 = bottom;
    v1 = top;
    
    lens_radius = aperture/2.0F;
    basis.initFromUV(-gaze, vup);
    corner = center + u0*basis.u() + v0*basis.v() - d*basis.w();
    across = (u0-u1)*basis.u();
    up = (v0-v1)*basis.v();
}

Ray Camera::getRay(float a, float b, float xi1, float xi2) {
    Vector3 origin = center + 2.0F*(xi1-0.5F)*lens_radius*basis.u() + 2.0F*(xi2-0.5F)*lens_radius*basis.v();
    Vector3 target = corner + across*a + up*b;
    return Ray(origin, normalize(target-origin));
}