# The multi_user_commands.sh script automates logging in as a different user and executing a multi-line command using the expect tool. It starts by setting the target username and password. The script then spawns a shell using sudo to switch to the specified user and automatically enters the password when prompted. After login, it uses a heredoc to print a multi-line message as the target user. Finally, the script hands control back to the user, allowing interaction with the shell session. This script demonstrates how to automate user login and command execution in a secure environment.

#!/usr/bin/expect -f

# Set variables
set target_user "desired_username"
set password "your_password"

# Spawn a shell and start the login process
spawn sudo -u $target_user bash

# Expect the password prompt and send the password
expect "password:"
send "$password\r"

# Execute multi-line command as a different user using heredoc
send "cat << \"EOF\"
This is a multi-line command
that spans multiple lines
using heredoc and executed as a different user.
EOF\r"

# Interact with the shell
interact
