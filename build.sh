#!/usr/bin/env bash

# Parse input variables
for arg in "$@"; do
	eval "${arg%%=*}"=\'"${arg#*=}"\'
done

if [[ ${CLEAN,,} == "true" ]]; then
	echo "Cleaning build directory..."
	rm -rf build/{,.}*
fi
cmake -S . -G "$GENERATOR" -B build $BUILD_ARGS
cmake --build build
