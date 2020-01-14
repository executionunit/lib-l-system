
set(LSYSTEM_LIB_SRCS
    lsystem.h
    lsystem.cpp

    lsystemlibconfig.h
)

if(LSYSTEM_BUILD_TESTS)
    set(LSYSTEM_TEST_SRCS test_lsystem.cpp)
endif()

add_library(lsystemlib ${LSYSTEM_LIB_SRCS})
target_include_directories(lsystemlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(lsystemlib INTERFACE cxx_std_11)

if(LSYSTEM_BUILD_TESTS)
    add_executable(lsystem_tests ${LSYSTEM_TEST_SRCS})
    target_link_libraries(lsystem_tests doctest::doctest lsystemlib)
    set_target_properties(lsystem_tests PROPERTIES FOLDER "unittests" )
endif()