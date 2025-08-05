cmake_minimum_required(VERSION 3.16)
project(solarSim)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# ----------- Harfbuzz -----------
FetchContent_Declare(
  harfbuzz
  GIT_REPOSITORY https://github.com/harfbuzz/harfbuzz.git
  GIT_TAG 11.3.3
)
FetchContent_MakeAvailable(harfbuzz)
# set(HarfBuzz_INCLUDE_DIRS "${harfbuzz_SOURCE_DIR}/src" "${harfbuzz_BINARY_DIR}/src")
# set(HarfBuzz_LIBRARY harfbuzz)
# set(HarfBuzz_FOUND TRUE)

set(HarfBuzz_FOUND TRUE CACHE BOOL "HarfBuzz was found")
set(HarfBuzz_INCLUDE_DIRS "${harfbuzz_SOURCE_DIR}/src" CACHE PATH "HarfBuzz includes")
set(HarfBuzz_LIBRARY harfbuzz CACHE STRING "HarfBuzz library target")
set(HarfBuzz_VERSION 11.3.3 CACHE STRING "HarfBuzz version")

# ----------- FreeType -----------
FetchContent_Declare(
  freetype
  GIT_REPOSITORY https://github.com/freetype/freetype.git
  GIT_TAG VER-2-13-2
)
FetchContent_MakeAvailable(freetype)

# Set these variables before SDL2_ttf configuration
set(FREETYPE_INCLUDE_DIRS "${freetype_SOURCE_DIR}/include" "${freetype_BINARY_DIR}/include")
set(FREETYPE_LIBRARY freetype)
set(FREETYPE_FOUND TRUE)

# ----------- SDL2 -----------
FetchContent_Declare(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-2.30.0
)
FetchContent_MakeAvailable(SDL2)

# ----------- SDL_ttf -----------
FetchContent_Declare(
  SDL_ttf
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
  GIT_TAG release-2.22.0
)
FetchContent_MakeAvailable(SDL_ttf)

# ----------- Source Files -----------
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(solarSim ${SOURCES})

target_include_directories(solarSim PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

# ----------- Link Everything -----------
target_link_libraries(solarSim
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
    ${FREETYPE_LIBRARY}
    harfbuzz
)