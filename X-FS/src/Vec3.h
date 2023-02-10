
//     X::FS - A flight dynamics simulation engine
//     Copyright (C) 2023  Arthur Meeh
//
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

// Created by Arthur Meeh on 10.02.23.

#pragma once

#include "nlohmann/json.hpp"

namespace X::Math
{

	struct Vec3
	{
		Vec3(double x, double y, double z) : X(x), Y(y), Z(z)
		{

		}

		Vec3() : X(0), Y(0), Z(0)
		{

		}

		double X, Y, Z;

		[[nodiscard]] Vec3 Add(const Vec3& other) const
		{
			return { X + other.X, Y + other.Y, Z + other.Z };
		}

		[[nodiscard]] Vec3 Subtract(const Vec3& other) const
		{
			return { X - other.X, Y - other.Y, Z - other.Z };
		}

		[[nodiscard]] Vec3 Negate() const
		{
			return { -X, -Y, -Z };
		}

		Vec3 operator+(const Vec3& other) const
		{
			return Add(other);
		}

		Vec3 operator-() const
		{
			return Negate();
		}

		Vec3 operator-(const Vec3& other) const
		{
			return Subtract(other);
		}

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Vec3, X, Y, Z)
	};

}
