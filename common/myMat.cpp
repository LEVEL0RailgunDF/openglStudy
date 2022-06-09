#pragma once
#include "myMat.h"

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
