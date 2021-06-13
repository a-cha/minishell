# Minishell

###### _Simple shell written in c99_

The goal of the project is to mimic bash behavior.

#### Features:
- Pipes
- Redirections 
- Environment variables
- Signals (`ctrl-C` `ctrl-D` `ctrl-\\`)
- Error management

#### Build-in commands:
- echo
- cd
- pwd
- export
- unset
- env
- exit

For all another commands there is a call their binary by `execve()` function.

## Usage

Run `make` inside the repository's directory to build `minishell` binary. Now the program at your disposal.
