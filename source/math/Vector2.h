#pragma once

template<typename T>
struct Vector2
{
	T X, Y;

	Vector2() {}
	Vector2(T x, T y) : X(x), Y(y) {}
};

typedef Vector2<int> Point;
typedef Vector2<int> Size;