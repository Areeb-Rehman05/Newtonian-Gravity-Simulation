cmake_minimum_required(VERSION 3.14)
project(MySDLProject)

set(CMAKE_CXX_STANDARD 17)

# Find SDL2
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

# ----------- Source Files -----------
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(solarSim ${SOURCES})

# Include headers
target_include_directories(solarSim PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2TTF_INCLUDE_DIRS}
)

# Link Everything
target_link_libraries(solarSim
    ${SDL2_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
)