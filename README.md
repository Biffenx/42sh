# 42sh
Time has come. Make way for the famous 42sh!

### Mandatory part
- Minishell prerequisites
	- [x] Prompt display
	- [x] Run commands with their parameters and PATH monitoring
	- [x] Error monitoring without using erno, and return values of commands
	- [x] Correct spaces and tabulations monitoring
- 21sh prerequisites
	- [x] Full edition of command line
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
- Monitoring of internal shell variables
	- [ ] Internal variable creation depending on syntax: name=value
	- [ ] Internal variable exportation to the enviroment via built-in export
	- [ ] Possibility to list shell internal variables via built-in set
	- [ ] Internal and enviroment variables revocation via built-in unset
	- [ ] Enviroment variable creation for unique command
	- [ ] Simple expansion of parameters depending on syntax ${}
	- [ ] Exit code access of previous command via expansion ${?}
	- [ ] Job control monitoring with built-ins jobs, fg, bg and the & operator
	- [ ] Correct monitoring of all signals
	- [ ] Each built-in must have the enounced options by POSIX standard execept for explicit case ad set or unset

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

### Issues
- [x] New opening quote in open quote.
- [ ] Trailing pipe not implemented.
- [ ] Fc carbage. Rewrite the whole built-in.
- [x] Line edition with command including newlines.
- [ ] History exclamation expanded even if inside single quotes.
- [ ] Redirection with specified fd ie. 2> does not work.
- [ ] Redireciton with multiple specified fd ie. 2>&1 does not work.
