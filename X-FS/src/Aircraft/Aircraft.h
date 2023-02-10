
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

// Created by Arthur Meeh on 09.02.23.

#pragma once

#include <vector>
#include <filesystem>
#include "Vec3.h"
#include "nlohmann/json.hpp"

using namespace nlohmann;

namespace X::FS
{
	struct Transform
	{
		Math::Vec3 Position, Orientation;
	};

	struct Body {
		Transform Transform;
	};

	struct Wing {
		Transform Transform;
	};

	struct Module {
		std::string Name;
	};

	struct Gear {
		Transform Transform;
	};

	struct AircraftDesignation {
		std::string Manufacturer;
		std::string Model;
		std::string TypeDesignator;
	};

	struct AircraftVersion {
		unsigned int VersionMajor;
		unsigned int VersionMinor;
		unsigned int VersionPatch;
	};

	struct AircraftSpec {
		AircraftDesignation Designation;
		AircraftVersion Version;
		std::string Notes;
	};

	class Aircraft
	{
	 public:
		static std::shared_ptr<Aircraft> LoadFromJSON(json& data);

	 public:
		AircraftSpec p_Spec;
		Transform p_Transform;

	 private:
		std::vector<Wing> m_Wings;
		std::vector<Body> m_Bodies;
		std::vector<Gear> m_Gear;
		std::vector<Module> m_Modules;

		Math::Vec3 m_Velocity;
		Math::Vec3 m_AngularVelocity;
	};
};

