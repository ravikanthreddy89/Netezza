Netezza
=======

Custom implementation of co-relation analytic function available on netezza.

Netezza ships with various analytic functions for processing data.
The aim of this project is to implement a user defined functions (UDF/UDTF/UDA) to generate
the co-relation matrix for given data set.

Helper functions

1) matrix_generate(int4, int4) 
  
  Eg. Invocation =>select * from table(matrix_generate(m,n)) 
   This UDTF generates a matrix of size mxn with random values and returns the matrix as table.

Work in progress. Annoyance caused is regretted.
