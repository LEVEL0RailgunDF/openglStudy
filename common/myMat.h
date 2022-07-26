#pragma once

#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif





const GLfloat DegreesToRadians = M_PI / 180.0;






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


	friend std::ostream& operator << (std::ostream& os, const vec4& v) {
		return os << "( " << v.x << ", " << v.y
			<< ", " << v.z << ", " << v.w << " )";
	}
	GLfloat& operator [] (int i) { return *(&x + i); }
	const GLfloat operator [] (int i) const { return *(&x + i); }
};





//----------------------mat4------------------------
class mat4 {
public:
	vec4  _m[4];

public:
	mat4(GLfloat s = 1.0);
	mat4(const vec4& a, const vec4& b, const vec4& c, const vec4& d);
	mat4(GLfloat m00, GLfloat m10, GLfloat m20, GLfloat m30,
		GLfloat m01, GLfloat m11, GLfloat m21, GLfloat m31,
		GLfloat m02, GLfloat m12, GLfloat m22, GLfloat m32,
		GLfloat m03, GLfloat m13, GLfloat m23, GLfloat m33);


	mat4 operator *(const mat4& m) const;

	friend std::ostream& operator << (std::ostream& os, const mat4& m) {
		return os << std::endl
			<< m[0] << std::endl
			<< m[1] << std::endl
			<< m[2] << std::endl
			<< m[3] << std::endl;
	}

	vec4& operator [] (int i) { return _m[i]; }
	const vec4& operator [] (int i) const { return _m[i]; }

};

inline
mat4 RotateX( const GLfloat theta )
{
    GLfloat angle = DegreesToRadians * theta;

    mat4 c;
    c[2][2] = c[1][1] = cos(angle);
    c[2][1] = sin(angle);
    c[1][2] = -c[2][1];
    return c;
}

inline
mat4 RotateY( const GLfloat theta )
{
    GLfloat angle = DegreesToRadians * theta;

    mat4 c;
    c[2][2] = c[0][0] = cos(angle);
    c[0][2] = sin(angle);
    c[2][0] = -c[0][2];
    return c;
}

inline
mat4 RotateZ( const GLfloat theta )
{
    GLfloat angle = DegreesToRadians * theta;

    mat4 c;
    c[0][0] = c[1][1] = cos(angle);
    c[1][0] = sin(angle);
    c[0][1] = -c[1][0];
    return c;
}

