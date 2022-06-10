Work by Konstantina Papafragaki, Katerina Lionta, Nikos Boumakis.

To compile, run make in the project folder. The executable is stored in $project_folder/build
and is named 'parser'.

# Usage:

`parser OPTIONS`

where OPTIONS is:

-   `--in input_file` The file from which to read the source code, by default stdin
-   `--out output_file` The file where the generated intermediate code should be written, by default stdout
-   `--symbol` Write out the symbol table in stdout
-   `--quad` Generate quads and write them in output file
-   `--target executable_output` Generate target code

The following options are evaluated only with option `--target`

-   `--binary` The generated executable will be in binary format (this takes precedence)
-   `--text` The generated executable will be in text format (this is the default)

# Example:

To compile a program stored in file `test.alpha` without producing an executable and to write the quads to file `quads.txt` run the following command:

```
parser --in test.alpha --out quads.txt --quad
```

To compile a program stored in file `test.alpha` producing an executable and write it in text format to file `executable.atc` run the command:

```
parser --in test.alpha --target executable.atc
```

To compile a program stored in file `test.alpha` producing an executable and write it in text format to file `executable.abc` run the command:

```
parser --in test.alpha --target executable.abc --binary
```

# Notes

-   Run and tested in papaya.csd.uoc.gr
-   The printed quads follow the RISC-V opcode format. For example:
    -   `assign res, arg1` means `res = arg1` (assign to res the value of arg1)
    -   `add res, arg1, arg2` means `res = arg1+arg2` (assign to res the sum arg1 and arg2)
    -   `table_setelem op1, arg1, arg2` means `arg1[arg2] = op1` (assign op1 to index arg2 of arg1)
    -   `table_getelem op1, arg1, arg2` means `op1 = arg1[arg2]` (assign to op1 the element at index arg2 of arg1)
    -   `if_less arg1, arg2, label` means that if arg1 is less than arg2, go to quad label
-   The executables include the number of global variables in the program, in order not to leave for the runtime what can be done at compile-time
