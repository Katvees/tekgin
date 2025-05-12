cmake_minimum_required(VERSION 4.0)
project(Tekgin
	VERSION 0.0.1
	DESCRIPTION "Basic text adventure game engine"
	LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<TARGET_NAME:tekgin>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<TARGET_NAME:tekgin>")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<TARGET_NAME:tekgin>")

# Define source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create a library for the core game components
add_library(tekgin STATIC ${SOURCES} )

# Set include directories for the library
target_include_directories(tekgin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Same warnings for the library
target_compile_options(tekgin
	PRIVATE
	$<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
	$<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic>
	$<$<CXX_COMPILER_ID:MSVC>:/W4>
)
