#ifndef GEOH
#define GEOH
#include "ray.h"
using namespace std;
class material;
typedef struct hit_record {
	float t;
	vec3 p;
	vec3 nv;

}hit_record;

class hitable { //geometry parent class
	public:
		virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const = 0;
};

class sphere : public hitable {
	public:
		sphere() {}
		sphere(vec3 c, float r,vec3 _kd=vec3(1.0,1.0,1.0), float w_ri = 0.0f, float w_ti = 0.0f) : 
			center(c), radius(r), kd(_kd), w_r(w_ri), w_t(w_ti) {};
		virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
		vec3 center;
		float radius;
		vec3 kd;
		float w_r;//reflected
		float w_t;//transmitted
};

bool sphere::hit(const ray &r, float tmin, float tmax, hit_record & rec) const {
	/*
	   To-do:
	   compute whether the ray intersect the sphere
	 */
	//bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - a*c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(discriminant))/a;
		if (temp < tmax && temp > tmin) {
			rec.t=temp;        
			rec.p=r.point_at_parameter(temp);
			rec.nv=rec.p-center;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < tmax && temp > tmin) {
			rec.t=temp;           
			rec.p=r.point_at_parameter(temp);
			rec.nv=rec.p-center;
			return true;
		}
	}
	return false;
	//}


}

vec3 reflect(const vec3 &d, const vec3 &nv) {
	//compute the reflect direction
	//To-do
	vec3 uv=unit_vector(d);
	vec3 un=unit_vector(nv);
	float cos1 = -dot(un,uv);
	return uv+2*cos1*un;	
}

vec3 refract(const vec3& v, const vec3& n, float r) {
	//compute the refracted direction
	//To-do
	//r==(n1/n2)
	vec3 uv=unit_vector(v);
	vec3 un=unit_vector(n);
	float cos1 = -dot(un,uv);
	float sin2=r*sqrt(1-cos1*cos1);
	float cos2=sqrt(1-sin2*sin2);
	vec3 re=r*uv+(r*cos1-cos2)*un;

	if(cos1 > 0.0)
		return re;
	else
		return vec3(0,0,0)-re;

}
#endif
