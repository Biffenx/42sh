# 42sh
Time has come. Make way for the famous 42sh!

### Mandatory part
- Minishell prerequisites
	- [x] Prompt display
	- [x] Run commands with their parameters and PATH monitoring
	- [x] Error monitoring without using erno, and return values of commands
	- [x] Correct spaces and tabulations monitoring
- 21sh prerequisites
	- [ ] Full edition of command line
	- [ ] Redirection and aggregation operators
	- [x] Pipe
	- [x] Separator
- Built-ins
	- [ ] cd
	- [x] echo
	- [x] exit
	- [x] type
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
- [x] Trailing pipe not implemented.
- [ ] Fc carbage. Rewrite the whole built-in.
- [x] Line edition with command including newlines.
- [ ] History exclamation expanded even if inside single quotes.
- [ ] Lexer does not recognize specified fd ie. 2> and 2>&1.
	- [ ] Redirection with specified fd ie. 2> does not work.
	- [ ] Redireciton with multiple specified fd ie. 2>&1 does not work.
- [x] Specific process should have own return value recorded after completion.
- [ ] Cursor movement does not work with ctrl+key combination after commit 098687956be52f87e71d9ad68a4ce5d76ebe96ce, which fixed line edition with command including newlines.
- [x] Absolute path for the file where history commands are saved in.
- [ ] Cd builtin does not align with the POSIX standard.
- [x] Type builtin cannot handle alias specification because aliases are expanded in lexer. (comment: use single quotes to avoid this.)