#pragma once

// ----------------------------------------------------------------------------------------
// Vectors.h
// the vectors of 2D, 3D and 4D 
// 
// BASE : https://github.com/ValveSoftware/openvr/blob/master/samples/shared/Vectors.h
// ----------------------------------------------------------------------------------------

#ifndef VECTORS_H_DEF
#define VECTORS_H_DEF

#include <cmath>
#include <iostream>

struct Vector2 {
	float x;
	float y;

	Vector2() :x(0), y(0) {};
	Vector2(float x, float y) :x(x), y(y) {};

	// utils functions (基本機能)
	void     set(float x, float y);                    //
	float    length() const;                           //
	float    distance(const Vector2& vec) const;       //
	Vector2& normalize();                              //
	float    dot(const Vector2& vec) const;            // ドット積。いわゆる内積
	bool     equal(const Vector2& vec, float e) const; //

	// operators
	Vector2  operator-() const;                        // 単項演算子
	Vector2  operator+(const Vector2& rhs) const;      // 
	Vector2  operator-(const Vector2& rhs) const;      //
	Vector2& operator+=(const Vector2& rhs);           //
	Vector2& operator-=(const Vector2& rhs);           //
	Vector2  operator*(const float scale) const;       // 
	Vector2  operator*(const Vector2& rhs) const;      // 各要素の積
	Vector2& operator*=(const float scale);            //
	Vector2& operator*=(const Vector2& rhs);           // 各要素の積に置き換え
	Vector2  operator/(const float scale) const;       // 
	Vector2& operator/=(const float scale);            //
	bool     operator==(const Vector2& rhs) const;     //
	bool     operator!=(const Vector2& rhs) const;     //
	bool     operator<(const Vector2& rhs) const;      //
	float    operator[](int index) const;              // 下付き演算子？
	float&   operator[](int index);                    // 下付き演算子？

	friend Vector2 operator*(const float a, const Vector2 vec);
	friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);
};

struct Vector3 {
	float x;
	float y;
	float z;

	Vector3() :x(0), y(0), z(0) {};
	Vector3(float x, float y, float z) :x(x), y(y), z(z) {};

	// utils functions
	void     set(float x, float y, float z);
	float    length() const;
	float    distance(const Vector3& vec) const;
	Vector3& normalize();
	float    dot(const Vector3& vec) const;
	Vector3  cross(const Vector3& vec) const;
	bool     equal(const Vector3& vec, float e) const;

	// operators
	Vector3  operator-() const;
	Vector3  operator+(const Vector3& rhs) const;
	Vector3  operator-(const Vector3& rhs) const;
	Vector3& operator+=(const Vector3& rhs);
	Vector3& operator-=(const Vector3& rhs);
	Vector3  operator*(const float scale) const;
	Vector3  operator*(const Vector3& rhs) const;
	Vector3& operator*=(const float scale);
	Vector3& operator*=(const Vector3& rhs);
	Vector3  operator/(const float scale) const;
	Vector3& operator/=(const float scale);
	bool     operator==(const Vector3& rhs);
	bool     operator!=(const Vector3& rhs);
	bool     operator<(const Vector3& rhs) const;
	float    operator[](int index) const;
	float&   operator[](int index);
};

struct Vector4 {
	float x;
	float y;
	float z;
	float w;

	Vector4() :x(0), y(0), z(0), w(0) {};
	Vector4(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {};

	// util functions
	void     set(float x, float y, float z, float w);
	float    length() const;
	float    distance(const Vector4& vec) const;
	Vector4& normalize();
	float    dot(const Vector4& vec)const;
	bool     equal(const Vector4& vec, float e) const;

	/// operators
	Vector4  operator-() const;
	Vector4  operator+(const Vector4& rhs) const;
	Vector4  operator-(const Vector4& rhs) const;
	Vector4& operator+=(const Vector4& rhs);
	Vector4& operator-=(const Vector4& rhs);
	Vector4  operator*(const float scale) const;
	Vector4  operator*(const Vector4& rhs) const;
	Vector4& operator*=(const float scale) const;
	Vector4& operator*=(const Vector4& rhs);
	Vector4  operator/(const float scale) const;
	Vector4& operator/=(const float scale);
	bool     operator==(const Vector4& rhs) const;
	bool     operator!=(const Vector4& rhs) const;
	bool     operator<(const Vector4& rhs) const;
	float    operator[](int index) const;
	float&   operator[](int index);

	friend Vector4 operator*(const float a, const Vector4 vec);
	friend std::ostream operator<<(std::ostream& os, const Vector4& vec);
};

// inline functions for Vector2

inline Vector2 Vector2::operator-() const {
	return Vector2(-x, -y);
}

inline Vector2 Vector2::operator+(const Vector2& rhs) const {
	return Vector2(x + rhs.x, y + rhs.y);
}

#endif // !VECTORS_H_DEF