# Minishell (125/100)

**Minishell** is a project at 42 School that involves creating a simple shell program. The goal is to build a basic command-line interpreter based on bash, that can execute shell commands and provide some shell features.

## Features
- Custom implementation of a shell program.
- Supports executing simplified built-in commands (echo, cd, pwd, env, export, unset, exit) as well as shell commands.
- Provides basic shell features such as environment variable expansion, redirection, piping, and signal handling.
- Supports priority operators and wildcards (bonus).

## Usage
1. Clone the repository:
   <pre>
   git clone https://github.com/Thawnder/minishell.git
   </pre>
2. Compile the minishell program:
   <pre>
   make
   </pre>
3. Run the minishell program:
   <pre>
   ./minishell
   </pre>

## Example
<pre>
$ ./minishell
minishell$ pwd
/home/bpleutin/Work/42/Minishell
minishell$ cd Libft
minishell$ pwd
/home/bpleutin/Work/42/Minishell/Libft
minishell$ cd
minishell$ pwd
/home/bpleutin
minishell$ exit
$
</pre>
