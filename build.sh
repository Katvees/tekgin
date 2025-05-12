cmake -S . -G "Unix Makefiles" -B build
cmake --build build

root_dir="$(pwd)"
include_dir="$root_dir/build/tekgin/include" 

header_paths="$(find "$root_dir"/src -name "*.[h]pp" -type f)"

trash "$include_dir" -r
mkdir "$include_dir" -p
ln -s . "$include_dir/libtekgin"
for header_path in $header_paths; do
	new_header="${header_path/src/build\/tekgin\/include}"
	mkdir "${new_header%/*}" -p
	ln "$header_path" "$new_header" -f
done
