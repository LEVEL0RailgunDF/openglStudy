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