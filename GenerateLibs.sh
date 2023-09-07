#!/bin/bash

# Directory containing your C++ source files and headers
source_dir="Engine"

# Destination directory for the generated shared libraries
dest_dir="Libs"

# Create the destination directory if it doesn't exist
mkdir -p "$dest_dir"

# Find all .cpp files in the source directory
cpp_files=$(find "$source_dir" -name "*.cpp")

# Loop through each .cpp file
for cpp_file in $cpp_files; do
    # Extract the base file name (without extension)
    base_name=$(basename -- "$cpp_file")
    base_name_no_ext="${base_name%.cpp}"

    # Generate the shared library with the same base name
    output_lib="$dest_dir/lib$base_name_no_ext.so"

    # Compile the .cpp file into a shared library
    g++ -shared -o "$output_lib" -fPIC "$cpp_file"

    echo "Generated: $output_lib"
done

# Copy all generated .so files to the destination directory
cp -f -r "$dest_dir"/*.so "$dest_dir"

# Find all .h files in the source directory
header_files=$(find "$source_dir" -name "*.h")

# Copy all .h files to the destination directory
for header_file in $header_files; do
    cp -f "$header_file" "$dest_dir"
    echo "Copied: $header_file"
done
