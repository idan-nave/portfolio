function Git_Create_Project_by_Template() {
  # Check if both source and destination folders are provided
  if [ -z "$1" ]; then
    echo "Please provide a project name."
    return 1
  fi

  if [ -z "$2" ]; then
    source_file="$HOME/wd/Templates/prj_tmplt.zip"
  else
    source_folder="$1"
  fi

  destination_folder="$HOME/wd/Git_WD/c/$1"

  # Check if the project folder already exists
  if [ -d "$destination_folder" ]; then
    echo "A project with the name '$1' already exists."
    echo "Aborting project creation."
    return 1
  fi

  # Check if the source folder does not exist
  if [ ! -f "$source_file" ]; then
    echo "Source file '$source_file' does not exist."
    return 1
  fi

  # Create the destination folder
  mkdir -p "$destination_folder"

  # Extract contents of source folder to destination folder
	#   tar -xf "$source_file" -C "$destination_folder"  
  unzip "$source_file" -d "$destination_folder" || {
    echo "Failed to extract template folder."
    return 1
  }

  # add the project to the git WD
  cd $HOME/wd/Git_WD/
  git add .
  #git commit -m "added project: $1"

  # Output Git status
  git status
}

function Git_Delete_Project_by_Name() {
  # Check if a project name is provided
  if [ -z "$1" ]; then
    echo "Please provide a project name."
    return 1
  fi

  project_name="$1"
  project_path="$HOME/wd/Git_WD/$project_name"

  # Check if the project folder exists
  if [ ! -d "$project_path" ]; then
    echo "Project '$project_name' does not exist."
    return 1
  fi

  # Prompt for user credentials
  read -rp "Please enter your username: " username
  read -rsp "Please enter your password: " password
  echo

  # Confirm deletion
  read -rp "Are you sure you want to delete project '$project_name'? (y/n): " confirm

  if [[ "$confirm" == [Yy]* ]]; then
    # Delete the project folder
    rm -rf "$project_path"
    echo "Project '$project_name' deleted successfully."
  else
    echo "Deletion aborted."
  fi
}

function cd_last_git_dir() {
  log_file="$HOME/.git_last_dir.log"
  git_projects_dir="/home/idan/Dev/Git_Projects"

  # Read the last used Git directory from the log file
  if [ -f "$log_file" ]; then
    last_dir=$(tail -n 1 "$log_file")
  fi

  # Check if the last directory is a valid Git repository in the Git projects directory
  if [ -n "$last_dir" ] && [ -d "$last_dir" ] && [ "${last_dir:0:${#git_projects_dir}}" == "$git_projects_dir" ] && git -C "$last_dir" rev-parse --is-inside-work-tree >/dev/null 2>&1; then
    # Change directory to the last used Git directory
    cd "$last_dir" >/dev/null 2>&1

    # Print Git status
    git status
  else
    echo "No last used Git directory found. changed to main user's Git folder"
    cd "$git_projects_dir" >/dev/null 2>&1
  fi
}



# Example usage: Git_Create_Project_by_Template <source_folder> <destination_folder>
# Git_Create_Project_by_Template "template.tar.gz" "new_project"

# function that push all the way, and sets the default branch to main if no second argument 
function commit_and_push()
{
    local commit_message="$1"
    local remote_branch="${2:-main}"
    
    if [[ -z $commit_message ]]; then
        read -p "Enter a commit message: " commit_message
    fi
    
    # Check if the commit message is still empty
    if [[ -z $commit_message ]]; then
        echo "No commit message provided. Aborting commit and push."
        return 1
    fi
    
    cd $HOME/wd/Git_WD/
    
	# Add .gitkeep files to empty folders
	# find . -type d -empty -not -path "./.git/*" -exec touch {}/.gitkeep \;
    # Add .gitkeep files to empty folders recoursively (dirs inside dirs)
    find . -type d -empty -not -path "./.git/*" -exec bash -c 'for d; do touch "$d/.gitkeep"; done' bash {} +
    
    git add .
    git commit -m "$commit_message"
    git config credential.helper store
    git push origin "$remote_branch"
}
