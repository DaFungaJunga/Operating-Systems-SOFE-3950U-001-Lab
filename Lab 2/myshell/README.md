# Instructions

Enter 'make' into terminal to compile code.
Enter './myshell' to run myshell


# User Help Functions

```cd <directory> ```
Change the current default directory to ```<directory>```. If the ```<directory>``` argument is not present, report the current directory. If the directory does not exist an appropriate error should be reported. This command should also change the PWD environment variable.

```clr ```
Clear the screen.

```dir <directory> ```
List the contents of the directory.

```environ ```
List all the environment strings.

```echo <comment> ```
Display ```<comment>``` on the display followed by a new line (multiple spaces/tabs reduced to a single space).

```help ```
Display the user manual using the more filter.

```pause ```
Pause the operation of the shell until ```Enter``` is pressed.

```quit ```
Quit the shell.

I/O Redirection
---------------
Supports i/o-redirection on either or both ```stdin``` and/or ```stdout``` using ```<```, ```>```, or ```>>``` arguements.
