# 42sh
Time has come. Make way for the famous 42sh!

#### Required package installation (linux)
```
sudo apt install libncurses5-dev
```

#### Keybindings
| KEY  | FUNCTION |
| ------------- | ------------- |
| <kbd>right</kbd> | Move cursor right. |
| <kbd>left</kbd> | Move cursor left. |
| <kbd>ctrl+right</kbd> | Move cursor to the beginning of a word. |
| <kbd>ctrl+left</kbd> | Move cursor to the ending of a word. |
| <kbd>ctrl+up</kbd> | Move cursor to the upper line. |
| <kbd>ctrl+down</kbd> | Move cursor to the lower line. |
| <kbd>up</kbd> | Navigate to older command in history. |
| <kbd>down</kbd> | Navigate to newer command in history. |
| <kbd>ctrl+r</kbd> | Reverse-i-search. |
| <kbd>home</kbd> | Move cursor to the beginning of current command. |
| <kbd>end</kbd> | Move cursor to the ending of current command. |
| <kbd>ctrl+l</kbd> | Clear input buffer. |
| <kbd>ctrl+u</kbd> | Cut left side of the command from cursor. |
| <kbd>ctrl+k</kbd> | Cut right side of the command from cursor. |
| <kbd>ctrl+p</kbd> | Paste internal clipboard content. |

### Mandatory part
- Minishell prerequisites
	- [x] Prompt display
	- [x] Run commands with their parameters and PATH monitoring
	- [x] Error monitoring without using erno, and return values of commands
	- [x] Correct spaces and tabulations monitoring
- 21sh prerequisites
	- [x] Full edition of command line
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
	- [x] Internal variable creation depending on syntax: name=value
	- [x] Internal variable exportation to the enviroment via built-in export
	- [x] Possibility to list shell internal variables via built-in set
	- [x] Internal and enviroment variables revocation via built-in unset
	- [ ] Enviroment variable creation for unique command
	- [ ] Simple expansion of parameters depending on syntax ${} (syntax is $EXPANSION)
	- [x] Exit code access of previous command via expansion ${?} (syntax is $?)
	- [ ] Job control monitoring with built-ins jobs, fg, bg and the & operator
	- [x] Correct monitoring of all signals
	- [ ] Each built-in must have the enounced options by POSIX standard execept for explicit case ad set or unset

### Modular Part Features
- [ ] Inhibitors ” (double quote), ’ (simple quote) and \\.
- [ ] Complete management of the history.
- [x] Alias management via built-ins alias and unalias.
- [ ] A hash table and built-in hash to interact with it.
- [ ] Contextual dynamic completion.
- [ ] Built-in test with the required operators.

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
- [x] Cursor movement does not work with ctrl+key combination after commit 098687956be52f87e71d9ad68a4ce5d76ebe96ce, which fixed line edition with command including newlines.
- [x] Absolute path for the file where history commands are saved in.
- [ ] Cd builtin does not align with the POSIX standard.
- [x] Type builtin cannot handle alias specification because aliases are expanded in lexer. (comment: use single quotes to avoid this.)
- [x] Shady stuff going on with the alias and unalias control including hashmap functions. Segfaults.
- [ ] Two or more consecutive expandable aliases cause segmentation fault.
- [x] Export builtin can only modify existing enviroment variables. It cannot create new ones.
- [ ] $ expansion segmentation fault if there is no value.

### Less serious issues.
- Aliases are expanded in lexer. This means that if the user wishes to find out specific alias using alias builtin, the argument has to be inside single quotes. Same syntax should be carried out when adding aliases to avoid undefined behavior.
