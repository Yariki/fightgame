#ifndef __FFVECTOR3_H__
#define __FFVECTOR3_H__

#include "orx.h"

class FFVector3
{
private:
	orxVECTOR _temp;

public:
	float _x;
	float _y;
	float _z;

public:
	FFVector3();
	FFVector3(float x, float y, float z);
	FFVector3(orxVECTOR a);
	FFVector3(orxVECTOR* a);
	FFVector3(const FFVector3& a);
	virtual ~FFVector3();

	void Set(float x, float y, float z);
	void Zero();
	
	FFVector3&	operator=(const FFVector3 &a);
	FFVector3	operator-() const;
	float		operator*(const FFVector3& a) const;
	FFVector3	operator*(const float a) const;
	FFVector3	operator/(const float a) const;
	FFVector3	operator+(const FFVector3& a) const;
	FFVector3	operator-(const FFVector3& a)  const;
	FFVector3&	operator+=(const FFVector3& a);
	FFVector3&	operator-=(const FFVector3& a);
	FFVector3&	operator/=(const FFVector3& a);
	FFVector3&	operator/=(const float a);
	FFVector3&	operator*=(const float a);
	bool		operator==(const FFVector3& a) const;
	bool		operator!=(const FFVector3& a) const;

	operator orxVECTOR();
	operator orxVECTOR*();

	friend FFVector3 operator*(const float a, const FFVector3 b);
};


inline FFVector3 FFVector3::operator-() const
{
	return FFVector3(-_x,-_y,-_z);
}

inline FFVector3& FFVector3::operator=(const FFVector3& a)
{
	_x = a._x;
	_y = a._y;
	_z = a._z;
	return *this;
}


#endif //__FFVECTOR3_H__