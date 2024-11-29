function open_project_folders()
{
    xdg-open "${HOME}/.../script.sh"
    cd "${HOME}/work_dir/ds"
    case "$1" in
        "scheduler")
            xdg-open "${HOME}/work_dir/ds/scheduler"
            # xdg-open "${HOME}/work_dir/ds/uid"
            xdg-open "${HOME}/work_dir/ds/task"
            xdg-open "${HOME}/work_dir/ds/pq"
            # xdg-open "${HOME}/work_dir/ds/sorted_list"
            ;;
        "sorted_list")
            xdg-open "${HOME}/work_dir/ds/dll"
            xdg-open "${HOME}/work_dir/ds/sorted_list"
            ;;
        "min_stack")
            xdg-open "${HOME}/work_dir/ds/min_stack"
            xdg-open "${HOME}/work_dir/ds/stack"
            ;;
        # Add more project cases as needed
        *)
            echo "Unknown project name"
            return 1
            ;;
    esac

    # Loop through opened folders
    for folder in "$@"; do
        if [ -d "$folder" ]; then
            echo "Opening folder: $folder"
            # Check if a makefile exists
            if [ -f "$folder/makefile" ]; then
                echo "makefile found in $folder"
                # Check if the "open" target is defined in the makefile
                if grep -q 'open:' "$folder/makefile"; then
                    echo "Executing 'make open' in $folder"
                    # Open the makefile
                    (cd "$folder" && make open)
                else
                    echo "'open' target not found in makefile in $folder"
                fi
            else
                echo "makefile not found in $folder"
            fi
        else
            echo "Folder not found: $folder"
        fi
    done
}

# Create an alias for the function
alias open_scheduler="open_project_folders scheduler pq task"
alias open_sorted_list="open_project_folders sorted_list dll"
alias open_min_stack="open_project_folders min_stack stack"
alias resrc="source ~/.bashrc"

#source ~/.bashrc
