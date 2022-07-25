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

	GLfloat& operator [] (int i) { return *(&x + i); }
	const GLfloat operator [] (int i) const { return *(&x + i); }
};





//----------------------mat4------------------------
class mat4 {
public:
	vec4  _m[4];

public:
	mat4(GLfloat s);
	mat4(const vec4& a, const vec4& b, const vec4& c, const vec4& d);
	mat4(GLfloat m00, GLfloat m10, GLfloat m20, GLfloat m30,
		GLfloat m01, GLfloat m11, GLfloat m21, GLfloat m31,
		GLfloat m02, GLfloat m12, GLfloat m22, GLfloat m32,
		GLfloat m03, GLfloat m13, GLfloat m23, GLfloat m33);



	vec4& operator [] (int i) { return _m[i]; }
	const vec4& operator [] (int i) const { return _m[i]; }
};
