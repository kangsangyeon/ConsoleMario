#pragma once

#include "ConsoleMario.h"
#include <cmath>
#include <ostream>

struct Vector2D
{
public:
	Vector2D();
	Vector2D(float _x, float _y);

	int GetRoundedX() const
	{
		return static_cast<int>(round(this->X));
	}
	int GetRoundedY() const
	{
		return static_cast<int>(round(this->Y));
	}

	float GetMagnitude() const
	{
		return sqrt((X * X) + (Y * Y));
	}

	Vector2D GetNormalized() const
	{
		Vector2D _newVector(*this);
		_newVector = _newVector / _newVector.GetMagnitude();
		return _newVector;
	}

	Vector2D GetRounded() const
	{
		Vector2D _newVector(*this);
		_newVector.X = static_cast<float>(_newVector.GetRoundedX());
		_newVector.Y = static_cast<float>(_newVector.GetRoundedY());
		return _newVector;
	}

	std::string ToString() const
	{
		return StringFormat<float>("{ %f, %f }", this->X, this->Y);
	}

	float X;
	float Y;

#pragma region OperatorOverrides

public:

	inline bool operator==(const Vector2D& _other) const
	{
		bool _xEqual = std::abs(_other.X - this->X) < std::numeric_limits<float>::epsilon();
		bool _yEqual = std::abs(_other.Y - this->Y) < std::numeric_limits<float>::epsilon();
		return _xEqual && _yEqual;
	}

	inline Vector2D operator*(const float _value) const {
		Vector2D _result{ *this };
		_result.X = _result.X * _value;
		_result.Y = _result.Y * _value;
		return _result;
	}

	inline Vector2D operator/(const float _value) const {
		Vector2D _result{ *this };
		_result.X = _result.X / _value;
		_result.Y = _result.Y / _value;
		return _result;
	}

	inline Vector2D operator+(const Vector2D& _other) const {
		Vector2D _result;
		_result.X = this->X + _other.X;
		_result.Y = this->Y + _other.Y;
		return _result;
	}

	inline Vector2D operator-(const Vector2D& _other) const {
		Vector2D _result;
		_result.X = this->X - _other.X;
		_result.Y = this->Y - _other.Y;
		return _result;
	}

	friend inline std::ostream& operator<<(std::ostream& _ost, Vector2D const& v)
	{
		_ost << StringFormat("{ %d, %d }", v.X, v.Y);
		return _ost;
	}


#pragma endregion OperatorOverrides

};

