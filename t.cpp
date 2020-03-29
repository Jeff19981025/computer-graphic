#include <iostream>
#include "geo.h"
#include "vec3.h"

int main (){

	vec3 l=vec3(-1.0,-1.0,-1.0);
	vec3 n=vec3(0.0,1.0,0.0);
	float r=1.0;
	cout<<"reflect"<<reflect(l,n)<<"\n"<<"refract"<<refract(l,n,r)<<endl;
}
