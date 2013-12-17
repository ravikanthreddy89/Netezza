
Implementation of UDx to compute Pearson's correlation coefficient. 
There is inbuilt analytic function which does the job. It returns the result as a one large char array. 
The one provided in this repo returns a table. 



Please follow the following steps to test the code.
===================================================================================

Step 1: Compilation and Registration of UDxs

->Please find the bash script file named "script", which contains the commands for compilation and registration of UDxs.
->Run that script.
->Make sure the source files are in the same directory in which the bash script is being executed and the executable bit of 
  the script is set.

Step 2: Creating Stored procedures

->File named "create_procedure" creates a stored procedure using NZ PL/SQL
->This procedures contains the whole process of creating a data matrix, generating correlation matrix for the same,
  extracting the top ten pairs and also prints the times for intermediate steps using raise notice.i
->This just registers the procedure, we have to call that procedure in the
   next step. 
-> run as : nzsql -f create_procedure;


->There is another file "test" this file contains a procedure with
  verification of the output from UDx and output from netezza's inbuilt
  correlation matrix generation function.
->If the output at the end of the test is 0 rows that implies the output of UDx  is correct.
->It works by using "minus" operator that outputs values different in two
  tables.
-> run as : nzsql -f test

Step 3: Running tests

->File named "run_test" contains a simple call to the above store procedure.
->Please change the input values in this file.This has to be done manually. 
->Execution of the below command does all the mentioned steps of creating input
  matrix, correlation matrix and extracting top 10 pairs.
-> run as: nzsql -f run_test;
 

Step 4: Purging 

->Two files are provided for this purpose 1) purge_tables 2) purge_procedures.
->"purge_tables" will delete the tables created when the test is run.
->"purge_procedures" will delete/drop all the UDxs and procedures used for the
   purpose of testing.



