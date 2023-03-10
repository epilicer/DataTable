
## Data Table

Here is an example of a table of drug molecules with associated data:

Molecule          Solubility              Molecular Weight  
Paracetamol       4.97                    151  
Caffeine          5.05                    194  
Indomethacin      0.4                     358  
Trimethoprim      3.14                    290  

Write a simple data table class that can represent collections of molecules with associated properties. 
The properties can be numeric or text types. 

Write a code that can combine two data tables. 
You may wish to provide the ability to take set unions, differences and intersections. 
You may also wish to think about how to combine tables that have different property columns.

## How to compile

g++ DataTable.cpp -o DataTable
-or-
python DataTable.py

## For Qt based compilation

Use the **qmake** tool to generate a **Makefile** based on your **.pro** file. 
If you do not have a **.pro** file, you can create one by running `qmake -project` command.
Edit **.pro** file if needed, and run the `qmake` command to generate the **Makefile**.
Now you can use `make` command to compile the program. 
If you have file specific **Makefile** you can compile it by using its own name, for example `make -f SimpleCalculatorMakefile` command to compile the program.

