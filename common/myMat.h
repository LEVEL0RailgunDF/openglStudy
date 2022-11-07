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


inline
vec3 cross(const vec3& a, const vec3& b)
{
	return vec3(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
};


inline
GLfloat dot(const vec3& u, const vec3& v) {
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline
GLfloat length(const vec3& v) {
	return std::sqrt(dot(v, v));
}

inline
vec3 normalize(const vec3& v) {
	return v / length(v);
}


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
	vec4(const vec3& v, const float w);
	vec4 operator +(const vec4& v2) const;
	vec4 operator -(const vec4& v2) const;
	vec4 operator /(const GLfloat num) const;
	vec4 operator - () const;


	friend std::ostream& operator << (std::ostream& os, const vec4& v) {
		return os << "( " << v.x << ", " << v.y
			<< ", " << v.z << ", " << v.w << " )";
	}
	GLfloat& operator [] (int i) { return *(&x + i); }
	const GLfloat operator [] (int i) const { return *(&x + i); }
};


inline
GLfloat dot(const vec4& u, const vec4& v) {
	return u.x * v.x + u.y * v.y + u.z * v.z + u.w + v.w;
}

inline
GLfloat length(const vec4& v) {
	return std::sqrt(dot(v,v));
}

inline
vec4 normalize(const vec4& v) {
	return v / length(v);
}

inline
vec3 cross(const vec4& a, const vec4& b)
{
	return vec3(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

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

	operator const GLfloat* () const
	{
		return static_cast<const GLfloat*>(&_m[0].x);
	}

	operator GLfloat* ()
	{
		return static_cast<GLfloat*>(&_m[0].x);
	}

};



inline
mat4 Translate(const GLfloat x, const GLfloat y, const GLfloat z)
{
	mat4 c;
	c[0][3] = x;
	c[1][3] = y;
	c[2][3] = z;
	return c;
}

inline
mat4 Translate(const vec3& v)
{
	return Translate(v.x, v.y, v.z);
}

inline
mat4 Translate(const vec4& v)
{
	return Translate(v.x, v.y, v.z);
}



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

inline
mat4 LookAt(const vec4& eye, const vec4& at, const vec4& up)
{
	vec4 n = normalize(eye - at);
	vec4 u = vec4(normalize(cross(up, n)), 0.0);
	vec4 v = vec4(normalize(cross(n, u)), 0.0);
	vec4 t = vec4(0.0, 0.0, 0.0, 1.0);
	mat4 c = mat4(u, v, n, t);
	return c * Translate(-eye);
}

inline
mat4 Frustum(const GLfloat left, const GLfloat right,
	const GLfloat bottom, const GLfloat top,
	const GLfloat zNear, const GLfloat zFar)
{
	mat4 c;
	c[0][0] = 2.0 * zNear / (right - left);
	c[0][2] = (right + left) / (right - left);
	c[1][1] = 2.0 * zNear / (top - bottom);
	c[1][2] = (top + bottom) / (top - bottom);
	c[2][2] = -(zFar + zNear) / (zFar - zNear);
	c[2][3] = -2.0 * zFar * zNear / (zFar - zNear);
	c[3][2] = -1.0;
	c[3][3] = 0.0;
	return c;
}