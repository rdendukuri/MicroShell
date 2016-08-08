# MicroShell

A sime unix shell using  fork(), pipe() and dup() without using system().

 The shell understands a special symbol "||", by which you can 
    pipe the output of one command to next command.  To simplify, 
    this assignment only requires one pipe between two commands, such 
    as in "cat myfile || sort".  Please note that the standard 
    Unix/Linux pipe is "|", which is different from what our 
    microshell would understand.

Any number of pipes can be created.
