
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

#include "Aircraft.h"
#include "Spec.h"

namespace X::FS {
	Aircraft::Aircraft(AircraftSpec spec)
	{

	}

	std::shared_ptr<Aircraft> Aircraft::LoadFromConfig(YAML::Node config)
	{
		AircraftSpec spec{};
		config >> spec;

		return std::make_shared<Aircraft>(Aircraft(spec));
	}
}
