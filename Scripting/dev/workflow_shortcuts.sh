# ###################################### Motivation ############################################
# the following file defines functionality for quick shortcuts for dev cycles, as a pyramid:
# using keboard buttons "/", ':', """, '[', ']', '\'.

# 1. if ctrl+shift+'/' is pressed in an opened folder browser context or in a current working directory in a terminal context, it sets the folder as a current 'working project'. the next shortcuts will be applied on that current set 'working project'.
# 2. if ctrl+shift+':' is pressed, it copys the project folder template from $HOME/idan/Dev/PortfolioDEV_PROJECTS_PATH/static_web_proj_template, to the current 'working project'.
# 3. if ctrl+shift+'"' is pressed, it inits a git working dir in the 'working project', as long as it had not already initialized before, by uses the following commands:
# 	echo "# <repo_with_same_working_project_folder_name>" >> README.md
# 	git init
# 	git add README.md
# 	git commit -m "first commit"
# 	git branch -M main
# 	git remote add origin git@github.com:idan-nave/<repo_with_same_working_project_folder_name>.git
# 	git push -u origin main
# 4. if ctrl+shift+'[' is pressed, it loads the 'working project' in vs code.
# 5. if ctrl+shift+']' is pressed, it loads the index.html or the main html file of the 'working project' in a live server of vs code.
# 6. if ctrl+shift+'\' is pressed, it commits the current status of the 'working project', prompting the user to add a comment for this commit, and then continues to push it to its remote repo (git push -u origin main).

# ###################################### Requirements ############################################
# 1. Save the following script as workflow_shortcuts.sh in a directory like $HOME/bin (ensure the directory is in your PATH for easy execution). Create the directory if it doesn’t exist.

# 2. Make the Script Executable
# Run the following commands to make the script executable:
# chmod +x $HOME/bin/workflow_shortcuts.sh

# 3. Configure Keybindings
# Use xdotool or a custom script executor like xdg-utils to associate the shortcuts. Configure the keybindings in the Ubuntu system settings.
#     Install Required Tools:
	# sudo apt update
	# sudo apt install xdotool
#     Assign the Shortcuts:
# Go to Settings > Keyboard > Custom Shortcuts, then create these shortcuts:
# Key Combination	Command
# Ctrl+Shift+/	bash ~/bin/workflow_shortcuts.sh set_project "$(pwd)"
# Ctrl+Shift+:	bash ~/bin/workflow_shortcuts.sh copy_template
# Ctrl+Shift+"	bash ~/bin/workflow_shortcuts.sh init_git
# Ctrl+Shift+[	bash ~/bin/workflow_shortcuts.sh open_vscode
# Ctrl+Shift+]	bash ~/bin/workflow_shortcuts.sh live_server
# Ctrl+Shift+\	bash ~/bin/workflow_shortcuts.sh commit_push

# 4. Notes
#     Ensure $HOME/bin is added to your PATH in ~/.bashrc or ~/.zshrc: 
#     use nano ~/.bashrc  # or nano ~/.zshrc if using zsh

# 	export PATH="$HOME/bin:$PATH"
#   export DEV_PROJECTS_PATH="/path/to/your/projects"
# 	export WORKING_PROJECT=""

# If you don’t want to modify your ~/.bashrc or ~/.zshrc, you can also set DEV_PROJECTS_PATH directly in your terminal session:
# export DEV_PROJECTS_PATH="/path/to/your/projects"

# This will override the default value for the current terminal session.
# 	Reload your shell:
# 	source ~/.bashrc
# Replace code commands with the appropriate command for your code editor or server if not using VS Code.

############################################ Implementation ######################################
#!/bin/bash

# File: workflow_shortcuts.sh
# Description: Set WORKING_PROJECT from file browser or terminal, save to bashrc, echo to terminal

# Function to load WORKING_PROJECT from ~/.bashrc if it's not set already
load_working_project() {
    # Source the ~/.bashrc to get updated WORKING_PROJECT value
    source ~/.bashrc

    # If WORKING_PROJECT is still empty, print an error
    if [[ -z "$WORKING_PROJECT" ]]; then
        echo "Error: WORKING_PROJECT is not set. Please set it first with the 'set_project' command."
        exit 1
    fi
}

# Function to set working project based on focus context
# Function to set WORKING_PROJECT in ~/.bashrc
set_working_project() {
    local project_path="$1"

    # Check if WORKING_PROJECT is already set
    if ! grep -q "export WORKING_PROJECT=" ~/.bashrc; then
        # Add the export line to .bashrc if it's not already set
        echo "export WORKING_PROJECT=\"$project_path\"" >> ~/.bashrc
        echo "WORKING_PROJECT set to $project_path"
    else
        # If WORKING_PROJECT is already set, update the value
        sed -i "s|export WORKING_PROJECT=.*|export WORKING_PROJECT=\"$project_path\"|" ~/.bashrc
        echo "WORKING_PROJECT updated to $project_path"
    fi

    # Reload .bashrc to apply changes
    source ~/.bashrc
}

# Function to copy the project template
copy_project_template() {
    # Load the WORKING_PROJECT from ~/.bashrc
    load_working_project

    TEMPLATE_DIR="$DEV_PROJECTS_PATH/Scripting/static_web_proj_template"
    if [[ -d "$WORKING_PROJECT" ]]; then
        cp -r "$TEMPLATE_DIR"/* "$WORKING_PROJECT"/
        echo "Template copied to $WORKING_PROJECT"
    else
        echo "Error: Working project is not set or doesn't exist."
    fi
}

# Function to initialize a Git repository
init_git_repo() {
    # Load the WORKING_PROJECT from ~/.bashrc
    load_working_project

    if [[ -d "$WORKING_PROJECT" ]]; then
        cd "$WORKING_PROJECT" || exit
        if [[ ! -d .git ]]; then
            REPO_NAME=$(basename "$WORKING_PROJECT")
            echo "# $REPO_NAME" >> README.md
            git init
            git add README.md
            git commit -m "first commit"
            git branch -M main
            git remote add origin "git@github.com:idan-nave/$REPO_NAME.git"
            git push -u origin main
            echo "Git repository initialized in $WORKING_PROJECT"
        else
            echo "Git repository already initialized."
        fi
    else
        echo "Error: Working project is not set or doesn't exist."
    fi
}

# Function to open the working project in VS Code
open_in_vscode() {
    # Load the WORKING_PROJECT from ~/.bashrc
    load_working_project

    if [[ -d "$WORKING_PROJECT" ]]; then
        code "$WORKING_PROJECT"
        echo "Opened $WORKING_PROJECT in VS Code."
    else
        echo "Error: Working project is not set or doesn't exist."
    fi
}

# Function to load the project in a live server
load_live_server() {
    # Load the WORKING_PROJECT from ~/.bashrc
    load_working_project

    if [[ -d "$WORKING_PROJECT" ]]; then
        INDEX_FILE=$(find "$WORKING_PROJECT" -type f -name "index.html" | head -n 1)
        if [[ -n "$INDEX_FILE" ]]; then
            code "$INDEX_FILE" --open-url "vscode://vscode.live-server"
            echo "Loaded $INDEX_FILE in live server."
        else
            echo "Error: No index.html found in $WORKING_PROJECT."
        fi
    else
        echo "Error: Working project is not set or doesn't exist."
    fi
}

# Function to commit and push changes
commit_and_push() {
    # Load the WORKING_PROJECT from ~/.bashrc
    load_working_project

    if [[ -d "$WORKING_PROJECT" ]]; then
        cd "$WORKING_PROJECT" || exit
        if [[ -d .git ]]; then
            read -p "Enter commit message: " COMMIT_MSG
            git add .
            git commit -m "$COMMIT_MSG"
            git push -u origin main
            echo "Changes committed and pushed to remote repo."
        else
            echo "Error: Git repository is not initialized in $WORKING_PROJECT."
        fi
    else
        echo "Error: Working project is not set or doesn't exist."
    fi
}

# Main control for shortcuts
case "$1" in
    set_project)
        set_working_project "$2"  # $2 will be the directory from the file browser (if available)
        ;;
    copy_template)
        copy_project_template
        ;;
    init_git)
        init_git_repo
        ;;
    open_vscode)
        open_in_vscode
        ;;
    live_server)
        load_live_server
        ;;
    commit_push)
        commit_and_push
        ;;
    *)
        echo "Usage: $0 {set_project|copy_template|init_git|open_vscode|live_server|commit_push} [arguments]"
        ;;
esac
