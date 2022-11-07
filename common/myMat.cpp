#pragma once
#include "myMat.h"


vec2::vec2(GLfloat s = GLfloat(0.0))
{
	this->x = s;
	this->y = s;
}

vec2::vec2(GLfloat x, GLfloat y) {
	this->x = x;
	this->y = y;
}

vec2 vec2::operator+(const vec2& v2) const
{
	return vec2(this->x + v2.x, this->y + v2.y);
}

vec2 vec2::operator-(const vec2& v2) const
{
	return vec2(this->x - v2.x, this->y - v2.y);
}

vec2 vec2::operator/(const GLfloat num) const
{
	return vec2(this->x / num, this->y / num);
}



vec3::vec3(GLfloat s = GLfloat(0.0))
{
	this->x = s;
	this->y = s;
	this->z = s;
}

vec3::vec3(GLfloat x, GLfloat y, GLfloat z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3 vec3::operator+(const vec3& v3) const
{
	return vec3(this->x + v3.x, this->y + v3.y, this->z + v3.z);
}

vec3 vec3::operator-(const vec3& v3) const
{
	return vec3(this->x - v3.x, this->y - v3.y, this->z - v3.z);
}

vec3 vec3::operator/(const GLfloat num) const
{
	return vec3(this->x / num, this->y / num, this->z / num);
}




vec4::vec4(GLfloat s = GLfloat(0.0))
{
	this->x = s;
	this->y = s;
	this->z = s;
	this->w = s;
}

vec4::vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}


vec4::vec4(const vec3& v, const float w = 1.0)
{
	x = v.x;  y = v.y;  z = v.z; this->w = w;
}

vec4 vec4::operator+(const vec4& v4) const
{
	return vec4(this->x + v4.x, this->y + v4.y, this->z + v4.z,this->w + v4.w);
}

vec4 vec4::operator-(const vec4& v4) const
{
	return vec4(this->x - v4.x, this->y - v4.y, this->z - v4.z, this->w - v4.w);
}

vec4 vec4::operator/(const GLfloat num) const
{
	return vec4(this->x / num, this->y / num, this->z / num,this->w / num);
}

vec4 vec4::operator - () const
{
	return vec4(-x, -y, -z, -w);
}


mat4::mat4(GLfloat s) {
	_m[0].x = s;
	_m[1].y = s;
	_m[2].z = s;
	_m[3].w = s;

}

mat4::mat4(const vec4& a, const vec4& b, const vec4& c, const vec4& d) {
	_m[0] = a;
	_m[1] = b;
	_m[2] = c;
	_m[3] = d;

}

mat4::mat4(GLfloat m00, GLfloat m10, GLfloat m20, GLfloat m30,
	GLfloat m01, GLfloat m11, GLfloat m21, GLfloat m31,
	GLfloat m02, GLfloat m12, GLfloat m22, GLfloat m32,
	GLfloat m03, GLfloat m13, GLfloat m23, GLfloat m33) {


	_m[0] = vec4(m00, m10, m20, m30);
	_m[1] = vec4(m01, m11, m21, m31);
	_m[2] = vec4(m02, m12, m22, m32);
	_m[3] = vec4(m03, m13, m23, m33);

}


mat4 mat4::operator *(const mat4& m) const {

	mat4  a(0.0);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				a[i][j] += _m[i][k] * m[k][j];
			}
		}
	}

	return a;
}