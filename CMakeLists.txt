cmake_minimum_required(VERSION 3.10)

project(ISM)

add_executable(
  main
  src/main.c
  src/utils.c
  src/kernels.c
  src/benchmark.c
)

target_link_libraries(
  main
  -march=native
  -Ofast
  -ftree-vectorize
)

if (DEBUG)
  add_definitions(-DDEBUG)
endif()
if (DEBUG2)
  add_definitions(-DDEBUG2)
endif()

if (BENCHMARK)
  add_definitions(-DBENCHMARK)
endif()

