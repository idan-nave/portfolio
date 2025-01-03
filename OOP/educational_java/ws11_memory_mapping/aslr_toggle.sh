#!/bin/bash

# Function to display the menu and get user choice
show_menu() {
    echo "======================================"
    echo "1. Disable ASLR"
    echo "2. Enable ASLR"
    echo "3. Exit"
    echo "======================================"
    read -p "Please select an option (1-3): " choice
}

# Function to disable ASLR
disable_aslr() {
    echo "Disabling ASLR..."
    echo 0 > /proc/sys/kernel/randomize
    echo "ASLR is now disabled."
}

# Function to enable ASLR
enable_aslr() {
    echo "Enabling ASLR..."
    echo 2 > /proc/sys/kernel/randomize
    echo "ASLR is now enabled."
}

# Main loop to handle user input
while true; do
    show_menu
    
    case $choice in
        1)
            disable_aslr
            ;;
        2)
            enable_aslr
            ;;
        3)
            echo "Exiting..."
            exit 0
            ;;
        *)
            echo "Invalid option. Please select a valid option."
            ;;
    esac
done

