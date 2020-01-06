# Third Party code

if(LSYSTEM_BUILD_TESTS)
    set(DOCTEST_WITH_MAIN_IN_STATIC_LIB OFF CACHE INTERNAL "")
    set(DOCTEST_WITH_TESTS OFF CACHE INTERNAL "")
    add_subdirectory(doctest)
endif()

if(LSYSTEM_BUILD_EXE)
    set(CXXOPTS_BUILD_EXAMPLES OFF CACHE INTERNAL "")
    set(CXXOPTS_BUILD_TESTS OFF CACHE INTERNAL "")
    set(CXXOPTS_BUILD_ENABLE_INSTALL OFF CACHE INTERNAL "")
    add_subdirectory(cxxopts)
endif()

add_subdirectory(glm)

