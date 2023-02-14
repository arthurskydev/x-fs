
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

#include "yaml-cpp/yaml.h"
#include <string>
#include <array>

namespace X::FS {
	struct AircraftDesignation {
		std::string Manufacturer;
		std::string Model;
		std::string TypeDesignation;
	};

	inline void operator >> (const YAML::Node& node, AircraftDesignation& d) {
		d.Manufacturer = node["Manufacturer"].as<std::string>();
		d.Model = node["Model"].as<std::string>();
		d.TypeDesignation = node["TypeDesignation"].as<std::string>();
	}

	struct AircraftVersion {
		unsigned int VersionMajor;
		unsigned int VersionMinor;
		unsigned int VersionPatch;
	};

	inline void operator >> (const YAML::Node& node, AircraftVersion& v) {
		auto str = node.as<std::string>();
		auto versionNumbers = std::array<unsigned int, 3>();
		auto delim = ".";
		size_t pos;
		char i = 0;
		while ((pos = str.find(delim)) != std::string::npos) {
			versionNumbers[i] = std::stoi(str.substr(0, pos));
			str.erase(0, pos + 1);
			i++;
		}

		v.VersionMajor = versionNumbers[0];
		v.VersionMinor = versionNumbers[1];
		v.VersionPatch = versionNumbers[2];
	}

	typedef std::string ObjectType;

	inline const ObjectType c_ObjectTypeBody = "Body";
	inline const ObjectType c_ObjectTypeWing = "Wing";

	static std::vector<ObjectType> c_ObjectTypes {
		c_ObjectTypeBody,
		c_ObjectTypeWing
	};

	struct AircraftObject {
		ObjectType Type;
	};

	inline void operator >> (const YAML::Node& node, AircraftObject& obj) {
		obj.Type = node["Type"].as<std::string>();
	}

	struct AircraftSpec {
		AircraftDesignation Designation;
		AircraftVersion Version;
		std::string Notes;
		std::vector<AircraftObject> Objects{};
	};

	inline void operator >> (const YAML::Node& node, AircraftSpec& s) {
		node["Version"] >> s.Version;
		node >> s.Designation;

		auto tree = node["Tree"];
		for (int i = 0; i < tree.size(); i++) {
			AircraftObject object{};
			tree[i] >> object;
			s.Objects.push_back(object);
		}
	}
}
