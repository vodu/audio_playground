#===============================================================================
cmake_minimum_required(VERSION 3.12)

project(
    "hackAudio"
    VERSION 1.0.0
    LANGUAGES CXX
)

#===============================================================================
add_executable(${PROJECT_NAME} 
    main.cpp
    )

#===============================================================================
target_compile_features (${PROJECT_NAME} INTERFACE cxx_std_17)

#===============================================================================
target_include_directories(${PROJECT_NAME} PUBLIC "./include")


