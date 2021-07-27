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
	- [x] cd
	- [x] echo
	- [x] exit
	- [x] type
- Logical operators
	- [x] "&&"
	- [x] "||"
- Monitoring of internal shell variables
	- [x] Internal variable creation depending on syntax: name=value
	- [x] Internal variable exportation to the enviroment via built-in export
	- [x] Possibility to list shell internal variables via built-in set
	- [x] Internal and enviroment variables revocation via built-in unset
	- [x] Enviroment variable creation for unique command
	- [x] Simple expansion of parameters depending on syntax ${} (syntax is $EXPANSION)
	- [x] Exit code access of previous command via expansion ${?} (syntax is $?)
	- [x] Job control monitoring with built-ins jobs, fg, bg and the & operator
	- [x] Correct monitoring of all signals
	- [ ] Each built-in must have the enounced options by POSIX standard execept for explicit case ad set or unset

### Modular Part Features
- [x] Inhibitors ” (double quote), ’ (simple quote) and \\.
- [x] Complete management of the history.
- [x] Alias management via built-ins alias and unalias.
- [ ] A hash table and built-in hash to interact with it.
- [x] Contextual dynamic completion.
- [x] Built-in test with the required operators.
- [ ] Tests for modular part features.

### Issues
- [x] New opening quote in open quote.
- [x] Trailing pipe not implemented.
- [x] Fc carbage. Rewrite the whole built-in.
- [x] Line edition with command including newlines.
- [x] History exclamation expanded even if inside single quotes.
	- Exclamation parsing needs to be transfered to parser.
- [ ] Lexer does not recognize specified fd ie. 2> and 2>&1.
	- [ ] Redirection with specified fd ie. 2> does not work.
	- [ ] Redireciton with multiple specified fd ie. 2>&1 does not work.
- [x] Specific process should have own return value recorded after completion.
- [x] Cursor movement does not work with ctrl+key combination after commit 098687956be52f87e71d9ad68a4ce5d76ebe96ce, which fixed line edition with command including newlines.
- [x] Absolute path for the file where history commands are saved in.
- [x] Cd builtin does not align with the POSIX standard.
- [x] Type builtin cannot handle alias specification because aliases are expanded in lexer. (comment: use single quotes to avoid this.)
- [x] Shady stuff going on with the alias and unalias control including hashmap functions. Segfaults.
- [x] Two or more consecutive expandable aliases cause segmentation fault.
- [x] Export builtin can only modify existing enviroment variables. It cannot create new ones.
- [x] $ expansion segmentation fault if there is no value.
- [x] ~ expansion segmentation fault if there is no value in HOME.
- [x] $ expansion wont work if the expandable value is joined with slash ie. $HOME/Documents.
- [ ] Invalid pointer being freed sometimes when alias expansion is done.
- [x] Shell "freezes" if job is stopped.
- [x] Set signals to default when bringing job to the foreground.
- [x] Decide when and where shell updates current and previous jobs (current handling is supported).
- [x] Shady stuff going on when signal is sent to a process via kill. Try fix signals.
	- There is no way for the programs to know about sent signals if they are in background or stopped.
- [x] Improve line edition (up and down)
- [ ] Odd files being created to directory when history file fills up to the limit.
- [x] Reverse-i-search segfault.
- [x] segfault with command alias=hello' is cancelled with SIGINT during quote>
- [ ] hash builtin POSIX standard?
- [x] segfault when file is redireced as input.
- [ ] condition neglects job control.
- [ ] extra spaces with escape character \\.
- [ ] escape character does not quite work when dealing with quotes.
- [ ] issues with single quotes when executing set and alias builtins.

### Less serious issues.
- Aliases are expanded in lexer. This means that if the user wishes to find out specific alias using alias builtin, the argument has to be inside single quotes. Same syntax should be carried out when adding aliases to avoid undefined behavior.
- When using kill command the termination of background jobs works well. Stopped jobs have to be raised to the foreground so they can exit.
