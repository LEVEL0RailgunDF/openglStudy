#pragma once

//----------------------vec2------------------------
class vec2 {
	public:
		GLfloat x;
		GLfloat y;

	public:
		vec2(GLfloat x = 0 , GLfloat y = 0);
		vec2 operator +(const vec2& v2) const;
		vec2 operator -(const vec2& v2) const;
		vec2 operator /(const GLfloat num) const;
};


vec2::vec2(GLfloat x, GLfloat y) {
	this->x = x;
	this->y = y;
}

inline vec2 vec2::operator+(const vec2& v2) const
{
	return vec2(this->x + v2.x, this->y + v2.y);
}

inline vec2 vec2::operator-(const vec2& v2) const
{
	return vec2(this->x - v2.x, this->y - v2.y);
}

inline vec2 vec2::operator/(const GLfloat num) const
{
	return vec2(this->x / num, this->y / num);
}












//----------------------vec2------------------------
class vec3 {
public:
	GLfloat x;
	GLfloat y;
	GLfloat z;

public:
	vec3(GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);
	vec3 operator +(const vec3& v2) const;
	vec3 operator -(const vec3& v2) const;
	vec3 operator /(const GLfloat num) const;
};


vec3::vec3(GLfloat x , GLfloat y , GLfloat z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

inline vec3 vec3::operator+(const vec3& v3) const
{
	return vec3(this->x + v3.x, this->y + v3.y,this->z + v3.z);
}

inline vec3 vec3::operator-(const vec3& v3) const
{
	return vec3(this->x - v3.x, this->y - v3.y, this->z - v3.z);
}

inline vec3 vec3::operator/(const GLfloat num) const
{
	return vec3(this->x / num, this->y / num,this->z / num);
}
