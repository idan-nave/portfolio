############################## THIS IS IDAN'S POOL OF BASH FUNCTIONS ##############################


##########################################################################################
# Function to list installed packages based on different flags
function list_installed_packages() {
    local flag="$1"
    local query_format=""
    case "$flag" in
        type)
            query_format#='%{NAME} %{GROUP}'
            ;;
        size)
            query_format='%{NAME} %{SIZE}'
            ;;
        percentage)
            query_format='%{NAME} %{SIZE} %{USERPCT}'
            ;;
        date)
            query_format='%{NAME} %{INSTALLTIME}'
            ;;
        source)
            query_format='%{NAME} %{SOURCE}'
            ;;
        lastused)
            query_format='%{NAME} %{INSTALLTIME} %{LASTUSEDTIME}'
            ;;
        path)
            query_format='%{NAME} %{INSTALLTIME} %{INSTALLROOT}'
            ;;
        *)
            echo "Invalid flag. Please choose one of the following: type, size, percentage, date, source, lastused, path"
            return 1
            ;;
    esac

    # Get the list of installed packages and sort based on the selected flag
    local package_list=$(rpm -qa --queryformat "$query_format\n" | sort)

    # Display the sorted list of packages
    echo "$package_list"
}

##########################################################################################
function Copy_single_file_to_tmp_subdir() {
if [[ -f $1 ]]
then
	 cp $1 /tmp/$1
	 echo "copied"
else
	echo "not copied"
fi
}
function Copy_multi_files_to_tmp_subdir() {
for val in $@
do 
	if [[ -f $val ]]
	then
		 cp $val /tmp/$val
		 echo "$val copied"
	else
		echo "$val not copied"
	fi 
done
}
function Copy_while_files_to_tmp_subdir() {
len=$#
echo "$len len is \n"
while [ ! $# -eq 0  ]
do 
	
	if [[ -f $1 ]]
	then
		 var=cp $1 /tmp/$counter
		 echo "$1 copied $var"
	else
		echo "$1 not copied"
	fi 
	shift
done
}

##########################################################################################
function edit_temp_file() {
  local temp_file
  temp_file=$(mktemp)

  # Open the temporary file for editing with gedit
  gedit "$temp_file" &

  # Wait for the user to finish editing
  read -rp "Press Enter to continue..."

  # Perform further actions with the contents of the edited file if needed
  # For example, you can read the contents of the file using 'cat' command:
  # content=$(cat "$temp_file")

  # Remove the temporary file
  rm "$temp_file"
}
