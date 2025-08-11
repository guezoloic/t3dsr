cmake_minimum_required(VERSION 3.10)
project(t3dsr C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# ==== sources ====
file(GLOB_RECURSE C_SOURCES CONFIGURE_DEPENDS src/*.c)
file(GLOB_RECURSE CPP_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS src/*.h src/*.hpp)

file(GLOB MAIN_SRC CONFIGURE_DEPENDS src/main.*) 

set(ALL_SOURCES ${C_SOURCES} ${CPP_SOURCES})
list(REMOVE_ITEM ALL_SOURCES ${MAIN_SRC})

add_executable(main ${MAIN_SRC} ${ALL_SOURCES} ${HEADERS})
if(NOT MSVC)
    target_link_libraries(main m)
endif()


# ==== tests ====
enable_testing()
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS tests/*.c)

foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src} ${ALL_SOURCES})
    if(NOT MSVC)
        target_link_libraries(${test_name} m)
    endif()
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()