//
//  UVSphere.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "UVSphere.h"

UVSphere::UVSphere(const Vector3& c, float r, Texture* txt) {
    center = Vector3(c); radius = float(r); tex = Texture(txt);
}

bool UVSphere::intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const {
    Vector3 temp = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = 2*dot(r.direction(), temp);
    double c = dot(temp, temp) - radius*radius;
    double discriminant = b*b - 4.0*a*c;
    
    if (discriminant > 0.0f) {
        discriminant = sqrt(discriminant);
        double t = (-b - discriminant) / (2.0*a);
        if (t < tmin) {t = (-b + discriminant) / (2.0*a);}
        if (t < tmin || t > tmax) {return false;}
        
        //valid intersection
        record.t = t;
        record.intersection = r.origin() + t*r.direction();
        Vector3 n = record.normal = (record.intersection - center) / radius;
        
        //calculate UV coords
        float two_pi = 6.28318530718f;
        float theta = acos(n.z());
        float phi = atan2(n.y(), n.x());
        if (phi < 0.0f) {phi += two_pi;}
        
        float one_over_two_pi = .159154943092f;
        float one_over_pi = .3183098861874f;
        
        record.uv = Vector2(phi*one_over_two_pi, (M_PI - theta) * one_over_pi);
        record.tex = tex;
        return true;
    }
    return false;
}
bool UVSphere::shadowIntersect(const Ray& r, float tmin, float tmax, float time) const {
    Vector3 temp = r.origin() - center;
    
    double a = dot(r.direction(), r.direction());
    double b = 2*dot(r.direction(), temp);
    double c = dot(temp, temp) - radius*radius;
    
    double discriminant = b*b - 4*a*c;
    
    //check if ray intersects sphere
    
    if (discriminant > 0) {
        discriminant = sqrt(discriminant);
        double t = (-b - discriminant) / (2.0*a);
        if (t < tmin) {t = (-b + discriminant) / (2.0*a);}
        if (t < tmin || t > tmax) {return false;}
        
        //valid intersection
        return true;
    }
    return false;
    
}
