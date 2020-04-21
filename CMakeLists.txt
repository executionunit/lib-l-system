cmake_minimum_required(VERSION 3.16)

project(ExUnitLSystems LANGUAGES CXX)

option(LSYSTEM_BUILD_TESTS "LSystem Unit Tests" OFF)
option(LSYSTEM_BUILD_EXE "LSystem Executable" OFF)

#Third Party Libs.
add_subdirectory(tp)

add_subdirectory(lsystemlib)

if(LSYSTEM_BUILD_EXE)
    set(LSYSTEM_EXE_LIBS lsystemlib cxxopts glm::glm)
    set(LSYSTEM_EXE_SRCS
        main.cpp
        turtle.h
		turtle.cpp
        pngturtle.h
        pngturtle.cpp
		modelturtle.h
		modelturtle.cpp
		boundsturtle.h
		boundsturtle.cpp
        utility.cpp
        utility.h
		)

    set(LSYSTEM_EXE_TEST_SRCS
        test_lsystem_exe.cpp
        utility.cpp
        utility.h
    )

    add_executable(lsystemexe ${LSYSTEM_EXE_SRCS})
    target_link_libraries(lsystemexe ${LSYSTEM_EXE_LIBS})
    target_include_directories(lsystemexe PRIVATE "tp/stb")

    if(LSYSTEM_BUILD_TESTS)
        add_executable(lsystemexe_tests ${LSYSTEM_EXE_TEST_SRCS})
        target_link_libraries(lsystemexe_tests doctest::doctest lsystemlib glm::glm)
        set_target_properties(lsystemexe_tests PROPERTIES FOLDER "unittests" )
    endif()


endif()

