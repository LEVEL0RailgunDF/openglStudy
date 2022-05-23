#pragma once
#include "myMat.h"

vec2::vec2(GLfloat x, GLfloat y) {
	this->x = x;
	this->y = y;
}

inline vec2 vec2::operator+(const vec2& v2) const
{
	return vec2(this->x + v2.x,this->y + v2.y);
}

inline vec2 vec2::operator-(const vec2& v2) const
{
	return vec2(this->x - v2.x, this->y - v2.y);
}

inline vec2 vec2::operator/(const GLfloat num) const
{
	return vec2(this->x / num, this->y / num);
}