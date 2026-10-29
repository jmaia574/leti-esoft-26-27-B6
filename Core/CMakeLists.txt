project(Core)

add_library(Core
        headers/domain/shared/Result.h
        headers/domain/shared/StringUtils.h
        sources/domain/shared/Result.cpp
        sources/domain/shared/StringUtils.cpp

        headers/domain/parameter/Parameter.h
        sources/domain/parameter/Parameter.cpp
        headers/domain/parameter/ParameterRepository.h
        sources/domain/parameter/ParameterRepository.cpp
        headers/domain/parameter/RegisterParameter.h
        sources/domain/parameter/RegisterParameter.cpp
)

# Make Core headers available to this library and its consumers
target_include_directories(Core PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
)