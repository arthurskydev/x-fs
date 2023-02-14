
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
#include "yaml-cpp/yaml.h"
#include "Body.h"
#include "Wing.h"
#include "Spec.h"
#include "Gear.h"
#include "Module.h"

namespace X::FS
{

	class Aircraft
	{
	 public:
		explicit Aircraft(AircraftSpec spec);
		static std::shared_ptr<Aircraft> LoadFromConfig(YAML::Node config);

	 public:
		AircraftSpec p_Spec;

	 private:
		std::vector<Wing> m_Wings;
		std::vector<Body> m_Bodies;
		std::vector<Gear> m_Gear;
		std::vector<Module> m_Modules;

		Transform m_Transform;
		Vec3 m_Velocity;
		Vec3 m_AngularVelocity;
	};
};

