#################### MAKE SURE TO TEST ON BASH BEFORE GO TO TEST ON LOGIN #####################

# Function to check and enable the firewall
function check_firewall() {
     # Check if firewalld daemon is installed
     if ! command -v firewall-cmd >/dev/null 2>&1; then
        echo "Firewalld is not installed. Installing..."
        if sudo apt update && sudo apt install firewalld; then
            echo "Firewalld installed successfully."
        else
            echo "Failed to install Firewalld. Please check for any errors."
            return 1
        fi
    else
        echo "Firewalld is already installed."
    fi

    # Check the status of the firewalld daemon service
    if ! systemctl is-active --quiet firewalld; then
        echo "Firewall is not active. Enabling firewall..."
        sudo systemctl start firewalld
        sudo systemctl enable firewalld
        echo "Firewall enabled."
    else
        echo "Firewall is already active."
    fi
}

# Function to check and update clamav_daemon
function check_clamav_daemon() {
    # Check if ClamAV daemon is installed
    if ! command -v clamdscan &> /dev/null; then
        echo "ClamAV daemon is not installed. Installing..."
        sudo apt-get install clamav-daemon -y
    fi
    # Check the status of the ClamAV daemon service
    if systemctl is-active --quiet clamav-daemon; then
        echo "ClamAV daemon is running."

        # Check if ClamAV daemon service is enabled
        if systemctl is-enabled --quiet clamav-daemon; then
            echo "ClamAV daemon is enabled."
        else
            echo "ClamAV daemon is not enabled. Enabling the service..."
            sudo freshclam
            sudo systemctl enable clamav-daemon
            sudo systemctl start clamav-daemon
            echo "ClamAV daemon started."
        fi
    fi
}


# Function to check and update Rkhunter
function check_rkhunter() {
    if ! command -v rkhunter &> /dev/null; then
        echo "Rkhunter is not installed. Installing Rkhunter..."
        sudo apt install rkhunter -y  # Adjust the package manager command as needed
        sudo rkhunter --update
        echo "Rkhunter installed and updated."
    else
        echo "Rkhunter is already installed."
    fi
}

# Function to report active SSH connections - BEAWARE - try netstat w or w/o sudo to test stability
function report_ssh_connections() {
    echo "Report of SSH Connections:"
    echo "-------------------------"

    # Get the list of active SSH connections
    active_connections=$( sudo netstat -tnpa | grep 'ESTABLISHED.*sshd')

    if [ -z "$active_connections" ]; then
        echo "No active SSH connections found."
    else
        echo "$active_connections"
    fi

    echo

    # Check SSH security settings
    echo "SSH Security Check:"
    echo "-------------------"

    # Check if the SSH server allows root login
    root_login=$(grep -i '^PermitRootLogin' /etc/ssh/sshd_config | awk '{print $2}')
    if [ "$root_login" == "yes" ]; then
        echo "Root login is enabled. Consider disabling it for better security."
    else
        echo "Root login is disabled. Good job!"
    fi

    # Check SSH protocol version
    protocol_version=$(grep -i '^Protocol' /etc/ssh/sshd_config | awk '{print $2}')
    if [ "$protocol_version" == "2" ]; then
        echo "SSH protocol version 2 is used. This is the recommended version."
    else
        echo "SSH protocol version 1 is used. Consider upgrading to version 2 for better security."
    fi

    # Check SSH password authentication
    password_auth=$(grep -i '^PasswordAuthentication' /etc/ssh/sshd_config | awk '{print $2}')
    if [ "$password_auth" == "yes" ]; then
        echo "Password authentication is enabled. Consider using SSH key-based authentication."
    else
        echo "Password authentication is disabled. Good job!"
    fi
}

# Function to check if sudo credentials are required - prevents login break
function check_sudo_credentials() {
  local sudo_output=$(sudo -n true 2>&1)
  if [[ $sudo_output == *"password"* ]]; then
    echo "Sudo credentials are expected. Exiting..."
    exit 0
  fi
}

# Function to run checks and display messages
function run_security_checks() {
    #/usr/bin/apt update
    #check_sudo_credentials
    
    sudo ufw enable
    check_sudo_credentials
    
    check_firewall
    check_sudo_credentials
    
    check_clamav_daemon
    check_sudo_credentials
    
    check_rkhunter
    check_sudo_credentials
    
    report_ssh_connections
    check_sudo_credentials
    
    w
    notify-send "Security Check Done"
}

# Run security checks on login
run_security_checks


