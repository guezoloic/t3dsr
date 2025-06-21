cmake_minimum_required(VERSION 3.10)
project(t3dsr C)

set(CMAKE_C_STANDARD 17)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.c)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS src/*.h)

add_executable(main ${SOURCES} ${HEADERS})

# ==== tests ====
enable_testing()

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS tests/*.c)
list(FILTER SOURCES EXCLUDE REGEX ".*src/main\\.c$")

if(TEST_SOURCES)
    add_executable(tests ${TEST_SOURCES} ${SOURCES})
    add_test(NAME tests COMMAND tests)
endif()
