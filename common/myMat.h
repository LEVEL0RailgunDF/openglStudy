#pragma once

//----------------------vec2------------------------
class vec2 {
	public:
		GLfloat x;
		GLfloat y;

	public:
		vec2(GLfloat s) ;
		vec2(GLfloat x , GLfloat y );
		vec2 operator +(const vec2& v2) const;
		vec2 operator -(const vec2& v2) const;
		vec2 operator /(const GLfloat num) const;
};




//----------------------vec3------------------------
class vec3 {
public:
	GLfloat x;
	GLfloat y;
	GLfloat z;

public:
	vec3(GLfloat s);
	vec3(GLfloat x, GLfloat y , GLfloat z );
	vec3 operator +(const vec3& v2) const;
	vec3 operator -(const vec3& v2) const;
	vec3 operator /(const GLfloat num) const;
};


//----------------------vec4------------------------
class vec4 {
public:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;

public:
	vec4(GLfloat s);
	vec4(GLfloat x , GLfloat y , GLfloat z , GLfloat w);
	vec4 operator +(const vec4& v2) const;
	vec4 operator -(const vec4& v2) const;
	vec4 operator /(const GLfloat num) const;
};



