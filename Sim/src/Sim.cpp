//
// Created by Arthur on 05.02.2023.
//

#include <exception>
#include "Sim.h"
#include "spdlog/spdlog.h"

namespace X_FS {
    Sim::Sim() {
        try {
            m_Window = Window();
        } catch (std::exception& exception) {
            spdlog::error("Starting sim returned exception: {}", exception.what());
        }
    }

    Sim::~Sim() = default;
}