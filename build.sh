#!/usr/bin/env bash

# Parse input variables
for arg in "$@"; do
	eval "${arg%%=*}"=\'"${arg#*=}"\'
done

if [[ ${NO_FORMAT,,} == "true" ]] || [[ ${NO_FORMAT,,} == "yes" ]] || [[ ${NO_FORMAT,,} == "on" ]]; then
	echo "Skipped formatting"
else
	echo "Formatting files.."
	clang-format src/**/*.cpp{,m} -i
fi

if [[ ${CLEAN,,} == "true" ]] || [[ ${CLEAN,,} == "yes" ]] || [[ ${CLEAN,,} == "on" ]]; then
	echo "Cleaning build directory..."
	rm -rf build/{,.}*
fi

cmake -S . -G "$GENERATOR" -B build $BUILD_ARGS
cmake --build build
