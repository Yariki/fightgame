#include "FFVector3.h"

FFVector3::FFVector3()
{
	_x = _y = _z = 0.0f;
	memset(&_temp,0,sizeof(orxVECTOR));
}

FFVector3::FFVector3(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	memset(&_temp,0,sizeof(orxVECTOR));
}

FFVector3::FFVector3(orxVECTOR a)
{
	_x = a.fX;
	_y = a.fY;
	_z = a.fZ;
	memset(&_temp,0,sizeof(orxVECTOR));
}

FFVector3::FFVector3(orxVECTOR* a)
{
	_x = a->fX;
	_y = a->fY;
	_z = a->fZ;
	memset(&_temp,0,sizeof(orxVECTOR));
}

FFVector3::FFVector3(const FFVector3& a)
{
	_x = a._x;
	_y = a._y;
	_z = a._z;
	memset(&_temp,0,sizeof(orxVECTOR));
}


FFVector3::~FFVector3(){}

void FFVector3::Set(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

void FFVector3::Zero()
{
	_x = _y = _z = 0.0f;
}





float FFVector3::operator*(const FFVector3& a) const
{
	return  _x * a._x + _y * a._y + _z * a._z;
}

FFVector3 FFVector3::operator*(const float a) const
{
	return FFVector3(_x * a, _y * a, _z * a);
}


FFVector3 FFVector3::operator/(const float a) const
{
	float inva = 1.0f / a;
	return FFVector3(_x * inva, _y * inva, _z * inva);
}

FFVector3 FFVector3::operator+(const FFVector3& a) const
{
	return FFVector3(_x + a._x, _y + a._y, _z + a._z);
}

FFVector3 FFVector3::operator-(const  FFVector3& a) const
{
	return FFVector3(_x - a._x, _y - a._y, _z - a._z);
}

FFVector3& FFVector3::operator+=(const FFVector3& a)
{
	_x += a._x;
	_y += a._y;
	_z += a._z;
	return *this;
}

FFVector3& FFVector3::operator-=(const FFVector3& a)
{
	_x -= a._x;
	_y -= a._y;
	_z -= a._z;
	return *this;
}

FFVector3& FFVector3::operator/=(const FFVector3& a)
{
	_x /= a._x;
	_y /= a._y;
	_z /= a._z;
	return *this;

}

FFVector3& FFVector3::operator/=(const float a)
{
	float inva = 1.0f / a;
	_x *= inva;
	_y *= inva;
	_z *= inva;
	return *this;
}

FFVector3& FFVector3::operator*=(const float a)
{
	_x *= a;
	_y *= a;
	_z *= a;
	return *this;

}

bool FFVector3::operator!=(const FFVector3& a) const
{
	return _x != a._x || _y != a._y || _z != a._z;
}

bool FFVector3::operator==(const FFVector3& a) const
{
	return _x == a._x && _y == a._y && _z == a._z;
}

FFVector3 operator*(const float a,const FFVector3 b)
{
	return FFVector3(b._x * a, b._y * a, b._z * a);
}

FFVector3::operator orxVECTOR()
{
	orxVECTOR a;
	a.fX = _x;
	a.fY = _y;
	a.fZ =  _z;
	return a;
}

FFVector3::operator orxVECTOR*()
{
	_temp.fX = _x;
	_temp.fY = _y;
	_temp.fZ =  _z;
	return &_temp;
}