// TestForFramework.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include <iostream>

using namespace std;

#include "FFInclude.h"
#include "FFVector3.h"



int _tmain(int argc, _TCHAR* argv[])
{
	FFVector3 a,b,c;
	b.Set(1.0,1.0,1.0);
	c.Set(2.0,1.0,3.0);
	a = b + c;
	a = b - c; 
	float temp = b * c;
	a = b / 2;

	orxVECTOR vec;
	vec.fX = 1.0;
	vec.fY = 2.0;
	vec.fZ = 3.0;
	a = vec;

	a.Set(3.0,2.0,1.0);

	vec = a;

	a += b;
	a = b;

	if(a == b)
		std::cout << "Equal" << std::endl;
	if(a != c)
		std::cout << "Not Equal" << std::endl;

	

	return 0;
}

