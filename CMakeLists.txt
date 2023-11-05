cmake_minimum_required(VERSION 3.22)

project(doom VERSION 1.0)

# Enable C++20 features
set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

# Find SDL2
find_package(SDL2 REQUIRED PATHS "C:/SDL2/")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${SOURCES}
)

# Link against SDL2 libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2)

target_include_directories(${PROJECT_NAME} 
    PUBLIC C:/SDL2/x86_64-w64-mingw32/include
    PUBLIC C:/glm)
