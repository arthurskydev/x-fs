
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
#include "Aircraft/Aircraft.h"

namespace X::FS
{

	class Engine
	{
	 public:
		~Engine();

		std::shared_ptr<Aircraft> AddAircraft(std::shared_ptr<Aircraft>& aircraft);
		void Update();
	 private:
		std::vector<std::shared_ptr<Aircraft>> m_Aircraft;
	};

} // X::FS
