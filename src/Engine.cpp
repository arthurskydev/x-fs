
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

#include "Engine.h"

namespace X::FS
{
	Engine::~Engine()
	{
		std::for_each(m_Aircraft.begin(), m_Aircraft.end(), [](Aircraft* aircraft) -> void
		{ delete aircraft; });
	}

	void Engine::Update()
	{

	}

	Aircraft* Engine::Load(Aircraft* aircraft)
	{
		m_Aircraft.push_back(aircraft);
		return aircraft;
	}
} // X::FS