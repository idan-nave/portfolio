#!/bin/bash

# Directory to start searching for .c and .h files
search_dir="/home/wd/ds"

# Destination directory where files will be copied
destination_dir="/home/wd/MAKEFILE"
# Ensure the destination directory exists
mkdir -p "$destination_dir/include" "$destination_dir/src"

# List of subdirectory names to include
subdirs=("sched" "pq" "uid" "task" "dll" "sorted_list")

# Iterate through the specified subdirectories and copy .c and .h files
for subdir in "${subdirs[@]}"; do
    src_subdir="${search_dir}/${subdir}"
    
    # Copy .h files to the include directory
    find "$src_subdir" -type f -name "*.h" -exec cp {} "$destination_dir/include" \;

    # Copy .c files to the src subdirectory
    find "$src_subdir" -type f -name "*.c" -exec cp {} "$destination_dir/src" \;
done

echo "Organized .c and .h files from specific subdirectories in $destination_dir"
