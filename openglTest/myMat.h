#pragma once
class vec2 {
	public:
		double x;
		double y;

	public:
		vec2(double x, double y);
		vec2 operator +(const vec2& v2) const;
		vec2 operator -(const vec2& v2) const;
		vec2 operator /(const double num) const;
};

vec2::vec2(double x=0, double y=0) {
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

inline vec2 vec2::operator/(const double num) const
{
	return vec2(this->x / num, this->y / num);
}
