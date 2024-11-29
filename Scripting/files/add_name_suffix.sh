#!/bin/bash

# Change to the directory where the files are located
cd /path/to/files

# Your name
your_name="_yourname"

# Loop through each file in the directory
for file in *; do
    # Check if the current item is a file (not a directory)
    if [ -f "$file" ]; then
        # Get the file extension
        file_extension="${file##*.}"
        
        # Check if the file has an extension
        if [[ "$file_extension" != "$file" ]]; then
            # Rename the file
            new_name="${file%.*}_${your_name}.${file_extension}"
            mv "$file" "$new_name"
            echo "Renamed $file to $new_name"
        fi
    fi
done

#Replace `/path/to/files` with the actual path to the directory 
#where your files are located. Modify the `your_name` variable with your 
#actual name. The script extracts the file extension and then renames the 
#file by adding `_yourname` before the extension. Make sure to back up 
#your files before running any script that modifies filenames.

#Save the script to a `.sh` file (e.g., `add_name_suffix.sh`), make it
#executable using `chmod +x add_name_suffix.sh`, and then run it using
# `./add_name_suffix.sh` in your terminal.
