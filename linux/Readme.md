# Shell Overview

## Environment Variables
- **Print environment variable**:  
  `printenv`
- **Print shell variable**:  
  `echo $<name>`
- **Set shell variable to environment**:  
  `export <name>`
- **Unset environment variable**:  
  `export -n <name>`
- **Unset shell variable**:  
  `unset <name>`

## Shell Options
- **Enable POSIX mode**:  
  `set -o posix`

## Directories Shortcuts
- `~` : Home directory  
- `.` : Current directory  
- `..` : Previous directory  
- `-` : Last opened directory

## Useful Commands
- **List files**:  
  `ls`

## Control Shortcuts
- **Move to start of line**:  
  `Ctrl + A`
- **Move to end of line**:  
  `Ctrl + E`
- **Reverse search through history**:  
  `Ctrl + R`

## History Commands
- **Run specific command from history**:  
  `!<number>`
- **Run last occurrence of a command**:  
  `!<command>`
- **Run previous command with `sudo`**:  
  `sudo !!`

## History Control
### HISTCONTROL
- `ignorespace` : Ignore commands starting with space
- `ignoredups` : Ignore repeated commands
- `erasedups` : Remove all duplicate entries and only keep the latest one

### HISTIGNORE
- **Ignore specific commands**:  
  `HISTIGNORE="<command>"`

- **Multiple ignored commands**:  
  `HISTIGNORE="<command>:<command>..."`

## File Matching
- `*` : Any number of characters  
- `?` : Matches one character  
- `[]` : One character in the list, e.g., `[0-9a-zA-Z]`  
- `!` : Negates the match  
- `{,}` : Expands to multiple matches

## Bash Shell Usage

### Meta Characters
- `$` : Value of a variable  
- `''` : Raw string  
- `""` : Allows variable expansion  
- `\` : Escape character

### Path Management
- **Push directory to stack**:  
  `pushd <path>`
- **Pop directory from stack**:  
  `popd +<path number>`
- **List all paths in stack**:  
  `dirs`
- **Change to a directory from stack**:  
  `cd ~<path number>`

### Command Substitution
- **Substitute and run command**:  
  `$(<command>)`  
  or  
  ``` `<command>` ```

## Pipes
- **Unnamed pipe**:  
  `|`
- **Named pipe**:  
  `mkfifo <pipe_name>`  
  _(Use `cat <pipe_name>` from another terminal)_

## Redirection
- `>` : Redirect stdout  
- `>>` : Append stdout  
- `2>` : Redirect stderr  
- `2>>` : Append stderr  
- `&>` : Redirect both stdout and stderr  
- `&>>` : Append both stdout and stderr  
- **Show and save output**:  
  `tee`  
  _(Use `tee -a` to append)_

Linux processes

ps - show process
options
-e show every process
-f full options
-F Extra options, memory, cpu etc
-l long format

ps -e --format uid,pid,ppid,%cpu,cmd : formating
ps -e --format uid,pid,ppid,%cpu,cmd --sort %cpu: formating

top : Real time process
options, press
l show or hide the load average/uptime
1 cpu cores
t toggle between
space select

Get process id
pidof <process_name>
pgrep <process_name>

kill <process_id> : kill process
killall <process_name>: kill all process


