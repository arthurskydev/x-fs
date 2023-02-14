
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

#include "X-FS.h"
#include "yaml-cpp/yaml.h"
#include <fstream>
#include <filesystem>
#include <iostream>

int main(int argc, const char** argv)
{
	if (argc < 2) {
		std::cout << "Please provide the directory to the Spec.yaml file as an argument to this application" << std::endl;
	}

	X::FS::Engine engine;
	auto path = std::filesystem::path(std::string(argv[1]) + "Spec.yaml");
	std::cout << path << std::endl;

	if (!std::filesystem::exists(path)) {
		throw std::runtime_error("file not found");
	}

	auto fs = std::ifstream(path);
	auto data = YAML::Load(fs);
	auto aircraft = X::FS::Aircraft::LoadFromConfig(data);
	engine.AddAircraft(aircraft);
}