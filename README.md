# Minishell
  This project is about creating a simple shell.
# RULE
- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
- Not use more than one global variable. Think about it. You will have to explain its purpose.
- Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
- Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
- Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
- Implement redirections:
  < should redirect input.
  > should redirect output.
  << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
  ">>" should redirect output in append mode.
- 
