# 42sh
Time has come. Make way for the famous 42sh!

### Mandatory part
- Minishell prerequisites
- [ ] Prompt display
- [ ] Run commands with their parameters and PATH monitoring
- [ ] Error monitoring without using erno, and return values of commands
- [ ]Correct spaces and tabulations monitoring
- 21sh prerequisites
- [ ] Full edition of commands line
- [ ] Redirection and aggregation operators
- [ ] Pipe
- [ ] Separator
- Built-ins
- [ ] cd
- [ ] echo
- [ ] exit
- [ ] type
- Logical operators
- [ ] "&&"
- [ ] "||"
- Monitoring of intern shell variables
- [ ] Intern variable creation depending on syntax: name=value
- [ ] Intern variable exportation to the enviroment via built-in export
- [ ] Possibility to list shell intern variables via built-in set
- [ ] Intern and enviroment variales revocation via built-in unset
- [ ] Enviroment variable creation for unique command
- [ ] Simple expansion of parameters depending on syntax ${}
- [ ] Exit code access of previous command via expansion ${?}
- [ ] Job control monitoring with built-ins jobs, fg, bg and the & operator
- [ ] Correct monitoring of all signals
- [ ] Each built-in must have the enounced options by POSIX standard execpt for explicit case ad set or unset

### Modular Part Features
- [ ] Inhibitors ” (double quote), ’ (simple quote) and \\.
- [ ] Complete management of the history.
- [ ] Alias management via built-ins alias and unalias.
- [ ] A hash table and built-in hash to interact with it.
- [ ] Contextual dynamic completion.
- [ ] Undecided.

#### Required package installation (linux)
```
sudo apt install libncurses5-dev
```
