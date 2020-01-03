cmake_minimum_required(VERSION 3.16)

project(ExUnitLSystems LANGUAGES CXX)

option(LSYSTEM_BUILD_TESTS "LSystem Unit Tests" OFF)
option(LSYSTEM_BUILD_EXE "LSystem Executable" OFF)

#Third Party Libs.
add_subdirectory(tp)

add_subdirectory(lsystemlib)

if(LSYSTEM_BUILD_EXE)
    set(LSYSTEM_EXE_LIBS lsystemlib cxxopts)
    set(LSYSTEM_EXE_SRCS
        main.cpp
        turtle.h
		turtle.cpp
        pngturtle.h
        pngturtle.cpp)

    add_executable(lsystemexe ${LSYSTEM_EXE_SRCS})
    target_link_libraries(lsystemexe ${LSYSTEM_EXE_LIBS})
    target_include_directories(lsystemexe PRIVATE "tp/stb")
endif()

