#!/bin/bash

# Find all empty directories and add a .gitkeep file
find . -type d -empty -exec sh -c 'touch "$0/.gitkeep"' {} \;

echo "Added .gitkeep to all empty directories."

#How it Works
  #  find . -type d -empty: Finds all empty directories starting from the current directory.
  #  -exec sh -c 'touch "$0/.gitkeep"' {}: Executes the touch command for each empty directory, creating a .gitkeep file inside it.
  #  echo: Outputs a confirmation message after execution.
#Steps to Use the Script
  # Make the script executable:  chmod +x add_gitkeep.sh
  # Run the script:   ./add_gitkeep.sh
