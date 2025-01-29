add_subdirectory(lib/spdlog)
include_directories(lib/spdlog/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hh *.cc)

set(SOURCES ${SOURCES})

add_executable(${BINARY} ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})
