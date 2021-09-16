# C_Lisp_Interpeter
My own dialect of Lisp written in C.

## File Structure 
The source files are found in calculator. 
There is the main file main.c which contains proccess 
the command lines, file inputs, and repl loop. The code to 
generate the asbstract systax tree is in atree.c . The eval
and apply functions are in eval-apply.c . And the 
primitve functions implementations are in primfuncts.c .
