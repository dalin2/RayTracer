//
//  ShapeInstance.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/12/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "Instance.h"
#include "ONB.h"

Instance::Instance(Matrix trans, Matrix trans_inverse, Shape* orig) : M(trans), N(trans_inverse), prim(orig) {}
Instance::Instance(Matrix trans, Shape* orig) : M(trans), N(trans), prim(orig) {N.invert();}

bool Instance::intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& rec) const {
    Vector3 no = transformLoc(N, r.origin()); //transformed ray origin into local coordinates
    Vector3 nd = transformVec(N, r.direction()); //transformed ray direction into local coordinates
    Ray tray(no, nd);
    
    if (prim -> intersect(tray, tmin, tmax, time, rec)) {
        rec.intersection = transformLoc(M, rec.intersection);
        Vector3 normal = transformVec(N.getTranspose(), rec.uvw.w()); //correct?? rec.uvw?
        ONB uvw;
        uvw.initFromW(normal);
        rec.uvw = uvw; //correct??
        return true;
    }
    return false;
}

bool Instance::shadowIntersect(const Ray& r, float tmin, float tmax, float time) const {
    Vector3 no = transformLoc(N, r.origin()); //transformed ray origin into local coordinates
    Vector3 nd = transformVec(N, r.direction()); //transformed ray direction into local coordinates
    Ray tray(no, nd);
    return prim -> shadowIntersect(tray, tmin, tmax, time);
}

