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

root_dir="$(pwd)"
include_dir="$root_dir/build/tekgin/include"


[[ ${CLEAN,,} != "true" ]] && rm "$include_dir" -r
cp "$root_dir"/include "$include_dir" -r
