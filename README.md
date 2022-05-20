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

# Example:

To compile a program stored in file `test.alpha` and to write the quads to file `quads.txt` run the following command:

```
parser --in test.alpha --out quads.txt --quad
```

Run and tested in papaya.csd.uoc.gr
