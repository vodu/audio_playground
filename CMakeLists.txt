cmake_minimum_required(VERSION 3.8)

project(
    audio_playground
    LANGUAGES CXX
)

add_executable(main 
    main.cpp
    )

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -std=c99")
