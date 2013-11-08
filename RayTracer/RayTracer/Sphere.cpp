//
//  Sphere.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "Sphere.h"

bool Sphere::intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const {
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

bool Sphere::shadowIntersect(const Ray& r, float tmin, float tmax, float time) const {
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