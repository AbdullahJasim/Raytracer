#pragma once
#ifndef VECTOR_3
#define VECTOR_3

#include <math.h>
#include <stdlib.h>
#include <iostream>

class Vec3 {
public:
	float e[3];

	Vec3() {}
	Vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; };

	//Inline functions are linked with everyday constructor of the object. Thus sacrificing a bit of overhead
	//but saving a lot of time if they're called often. And in case of operators they are
	//The 'inline' keyword is only a suggestion to the compiler, it's not guaranteed
	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }

	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	//Overriding operators to perform standard vector operations
	inline const Vec3& operator+() const { return *this;  } //+ operation
	inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); } //- operation
	inline float operator[] (int i) const { return e[i]; } //array[i]
	inline float& operator[] (int i) { return e[i]; } //&array[i]

	inline Vec3& operator+=(const Vec3 &v2); //vector1 += vector2
	inline Vec3& operator-=(const Vec3 &v2); //vector1 -= vector2
	inline Vec3& operator*=(const Vec3 &v2); //vector1 *= vector2
	inline Vec3& operator/=(const Vec3 &v2); //vector1 /= vector2
	inline Vec3& operator*=(const float t); //vector1 * constant
	inline Vec3& operator/=(const float t); //vector1 / constant

	inline float length() const { return sqrt(e[0]* e[0] + e[1] * e[1] + e[2] * e[2]); } //get length of a vector
	inline float squared_length() const { return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); } //get the square of its vector
	inline void make_unit_vector(); //normalize the vector
};

#endif