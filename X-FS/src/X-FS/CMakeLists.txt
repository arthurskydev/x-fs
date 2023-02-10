set(SOURCE_FILES
        Engine/Engine.cpp
        Engine/Engine.h
        Aircraft/Aircraft.cpp
        Aircraft/Aircraft.h
        Math/Vec3.h Math/Transform.h Aircraft/Spec.h)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
