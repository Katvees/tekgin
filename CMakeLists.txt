cmake_minimum_required(VERSION 4.0)
project(Tekgin
	VERSION 0.0.1
	DESCRIPTION "Basic text adventure game engine"
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

foreach(OUTPUTCONFIG RUNTIME LIBRARY ARCHIVE)
  set(CMAKE_${OUTPUTCONFIG}_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<TARGET_NAME:tekgin>")
endforeach()

file(GLOB_RECURSE MODULE_INTERFACES CONFIGURE_DEPENDS "src/*.cppm")
file(GLOB_RECURSE MODULE_IMPLEMENTATIONS CONFIGURE_DEPENDS "src/*.cpp")

add_library(tekgin STATIC SHARED)

target_sources(tekgin
	PUBLIC
		FILE_SET CXX_MODULES
		BASE_DIRS "src"
		FILES ${MODULE_INTERFACES}
	PRIVATE
		${MODULE_IMPLEMENTATIONS}
)

target_compile_features(tekgin PUBLIC cxx_std_23)

target_compile_options(tekgin
	PRIVATE
	$<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
	$<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic>
	$<$<CXX_COMPILER_ID:MSVC>:/W4>
)

target_compile_options(tekgin
  PRIVATE
	-fmodules
	-stdlib=libc++
	-fexperimental-library
)

target_link_options(tekgin
  PRIVATE
	-stdlib=libc++
	-fexperimental-library
)
