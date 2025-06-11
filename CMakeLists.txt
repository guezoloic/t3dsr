cmake_minimum_required(VERSION 3.10)
project(t3dsr C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.c)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS src/*.h)

add_executable(main ${SOURCES} ${HEADERS})