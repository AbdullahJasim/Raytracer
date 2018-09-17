#pragma once
#ifndef VECTOR_3
#define VECTOR_3

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3 {
public:
	vec3();
	vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; };

	//If a function is inline, the compiler places a copy of the code of that function at each point where the function is called at compile time.
	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }

	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	//Overriding operators to perform standard vector operations
	inline const vec3& operator+() const { return *this;  } //+ operation
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } //- operation
	inline float operator[] (int i) const { return e[i]; } //array[i]
	inline float& operator[] (int i) { return e[i]; } //&array[i]

	friend inline vec3 operator+(const vec3 &v1, const vec3 &v2);
	friend inline vec3 operator-(const vec3 &v1, const vec3 &v2);
	friend inline vec3 operator*(const vec3 &v1, const vec3 &v2);
	friend inline vec3 operator/(const vec3 &v1, const vec3 &v2);
	friend inline vec3 operator* (float t, const vec3 &v);
	friend inline vec3 operator* (const vec3 &v, float t);

	inline vec3& operator+=(const vec3 &v2); //vector1 += vector2
	inline vec3& operator-=(const vec3 &v2); //vector1 -= vector2
	inline vec3& operator*=(const vec3 &v2); //vector1 *= vector2
	inline vec3& operator/=(const vec3 &v2); //vector1 /= vector2
	inline vec3& operator*=(const float t); //vector1 * constant
	inline vec3& operator/=(const float t); //vector1 / constant

	inline float length() const { return sqrt(e[0]* e[0] + e[1] * e[1] + e[2] * e[2]); } //get length of a vector
	inline float squared_length() const { return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); } //get the square of its vector
	inline void make_unit_vector(); //normalize the vector
	friend inline vec3 unit_vector(vec3 v);

	float e[3];
};

#endif