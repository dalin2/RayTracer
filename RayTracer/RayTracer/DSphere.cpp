//
//  DSphere.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "DSphere.h"

DSphere::DSphere(const Vector3& oc, float r, const Color& rgb, float min_time, float max_time) {
    ocenter = Vector3(oc); radius = float(r); color = Color(rgb);
    mintime = float(min_time); max_time = float(max_time);
}

bool DSphere::intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const {
    Vector3 center = getCenter(time);
    Vector3 temp = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = 2*dot(r.direction(), temp);
    double c = dot(temp, temp) - radius*radius;
    //discriminant of quadratic equation -- check if > 0 to determine number roots/interesctions
    double discriminant = b*b - 4*a*c;
    
    if (discriminant > 0) {//ray intersects sphere at two places
        discriminant = sqrt(discriminant);
        double t = (-b - discriminant) / (2*a);
        if ( t < tmin) {t = (-b + discriminant) / (2*a);} //check if t is within tmin and tmax
        if (t < tmin || t > tmax) {return false;} //t is not within valid interval
        
        //have a valid intersection
        record.t = t;
        record.normal = normalize(r.origin() + t*r.direction() - center);
        record.color = color;
        return true;
    }
    return false;
}

bool DSphere::shadowIntersect(const Ray& r, float tmin, float tmax, float time) const {
    Vector3 center = getCenter(time);
    Vector3 temp = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = 2*dot(r.direction(), temp);
    double c = dot(temp, temp) - radius*radius;
    
    //discriminant of quadratic equation -- check if > 0 to determin number roots/interesctions
    double discriminant = b*b - 4*a*c;
    
    if (discriminant > 0) {//ray intersects sphere at two places
        discriminant = sqrt(discriminant);
        double t = (-b - discriminant) / (2*a);
        if (t < tmin) {t = (-b + discriminant) / (2*a);} //check if t is within tmin and tmax
        if (t < tmin || t > tmax) {return false;} //t is not within valid interval
        
        //have a valid interesction
        return true;
    }
    return false;
}

Vector3 DSphere::getCenter(float t) const {
    float realtime = t * maxtime + (1.0f - t) * mintime;
    return Vector3(ocenter.x() + realtime, ocenter.y() + realtime, ocenter.x() + realtime);
}
