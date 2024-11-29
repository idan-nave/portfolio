###########################################################################################
function compile_and_debug() {
  local source_file="$1"
  local breakpoint

  # Compile C program with debugger permissions
  gcc -g -o program "$source_file"

  # Output the program code to the terminal with line numbers
  nl "$source_file"

  # Prompt for a breakpoint
  read -p "Enter the line number for the breakpoint: " breakpoint

  # Generate a unique filename for the core file
  current_date=$(date +%Y%m%d)
  current_hour=$(date +%H%M%S)
  core_filename="core_files/core_${current_date}_${current_hour}_breakpoint_${breakpoint}"

  # Run the program with GDB and generate a core file
  mkdir -p core_files
  ulimit -c unlimited
  gdb -ex "break $source_file:$breakpoint" -ex "run" -ex "generate-core-file $core_filename" -ex "quit" ./program

  # Check if a core file was generated
  if [ -f "$core_filename" ]; then
    # Analyze the core file for error and warning messages
    echo "Core file analysis:"
    gdb -ex "core $core_filename" -ex "bt" -ex "quit" ./program
  else
    echo "No core file generated."
  fi
}
###########################################################################################
function compile() {
  local source_file="$1"
  local filename="${source_file%.*}"  # Remove the file extension
  local executable="${filename}_program"

  # Check if the source file exists
  if [ ! -f "$source_file" ]; then
    echo "Source file '$source_file' not found."
    exit 1
  fi

  # Compile C program with debugging symbols and enable warnings
  gcc -g -Wall -o "$executable" "$source_file"
}

###########################################################################################
function valgrind_check() {
  local program_file="$1"

  # Check if the program file exists
  if [ ! -f "$program_file" ]; then
    echo "Program file '$program_file' not found."
    exit 1
  fi

  # Create a unique filename for the Valgrind report
  current_date=$(date +%Y%m%d)
  current_hour=$(date +%H%M%S)
  report_filename="valgrind_reports/report_${current_date}_${current_hour}.txt"
  xtree_report_filename="valgrind_reports/xtree_report_${current_date}_${current_hour}.txt"

  # Run the program with Valgrind and save the report to a file
  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="$report_filename" --xtree-memory=full --xtree-memory-file="$xtree_report_filename" "./$program_file" > /dev/null 2>&1

  # Display the Valgrind report on the terminal
  echo "Valgrind report:"
  cat "$report_filename"

  # Display the XTree report on the terminal
  echo "XTree report:"
  cat "$xtree_report_filename"

  # Delete the xtmemory.kcg.* file
  rm -f xtmemory.kcg.*
}

function copy_latest_core()
{
    # Directory containing core dump files
    coredump_dir="/var/lib/apport/coredump"

    # Get the most recently modified file in the directory
    latest_file=$(ls -t "$coredump_dir" | head -n 1)

    # Check if a file exists
    if [[ -n "$latest_file" ]]; then
        # Copy the file to the current working directory
        cp "${coredump_dir}/${latest_file}" ./core
        echo "File copied successfully as 'core'."
    else
        echo "No core dump file found."
    fi
}

