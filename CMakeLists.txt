cmake_minimum_required(VERSION 3.1.3)
project(SaltedRadish)

# Add source and header files
file(GLOB HDRS "*.h")
file(GLOB SRCS "*.cpp")

find_package(SDL2 REQUIRED)

# Create a library called "SaltedRadish".
add_library (SaltedRadish ${HDRS} ${SRCS})

# Make sure the compiler can find include files for our SaltedRadish library
target_include_directories (SaltedRadish PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(SaltedRadish SDL2::SDL2)