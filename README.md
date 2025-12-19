# minishell

minishell is a minimal Unix shell implemented in C as part of the 42 curriculum, master  
The project aims to reproduce core Bash behavior while respecting strict constraints and focusing on low-level system understanding, master  

## Mandatory Features

- Interactive prompt using readline, master  
- Execution of external commands using PATH resolution, master  
- Built-in commands:
  - echo (with -n)
  - cd
  - pwd
  - export
  - unset
  - env
  - exit, master  
- Pipes (`|`) with correct process chaining, master  
- Redirections:
  - `<` input
  - `>` output
  - `>>` append
  - `<<` heredoc, master  
- Environment variable expansion (`$VAR`), master  
- Proper exit status handling (`$?`), master  
- Signal handling (Ctrl-C, Ctrl-\) matching Bash behavior, master  

## Extra Features

- `~` expansion to the user’s home directory, master  
- Safe handling of unclosed quotes (`'` and `"`), preventing crashes and undefined behavior, master  
- AST-based parsing for clear separation between parsing and execution logic, master  



to build the project write make in the terminal after cloning the repo
make re to rebuild
