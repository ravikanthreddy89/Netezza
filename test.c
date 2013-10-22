#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>

int main(argc,argv)
int argc;
char **argv[];
{
  double **data,**co_matrix;
  int variables,rows,rms,mean;
  int i,j,k;
  double temp;

 
  if(argc!=3){
    printf("Inavalid number of command line arguments\n");
    printf("Usage : <object_file> <number of variables> <number of rows/observations>\n");
    exit(0);
  }
  variables=atoi((const char *)argv[1]);
  rows=atoi((const char *)argv[2]);
  mean=rows;
  rms=rows+1;


  /*allocate memory to the data*/
  data=(double **)malloc(sizeof(double *)*variables);
  for(i=0;i<variables;i++) data[i]=(double *)malloc(sizeof(double)*(rows+2));

  /*Allocate memory to the co-relation matrix nxn*/
  co_matrix=(double **)malloc(sizeof(double *)*variables);
  for(i=0;i<variables;i++) co_matrix[i]=(double *)malloc(sizeof(double)*variables);

  for(i=0;i<variables;i++){
    temp=0; 
   for(j=0;j<rows;j++){
     data[i][j]=(rand()%10);
     temp=temp+data[i][j];
       }
   data[i][mean]=(temp/rows);/*dump the mean after the last observation*/
  }

  /*Print the data generated*/

  printf("This is the matrix generated \n");
  for(i=0;i<variables;i++){
    for(j=0;j<rows;j++) printf("%lf ",data[i][j]);
    printf("\n");
  }

  /*Dump the root means square value of each variable as last observation*/
  for(i=0;i<variables;i++){
    temp=0;
    for(j=0;j<rows;j++){
      temp=temp+pow((data[i][j]-data[i][mean]),2);
     }
    data[i][rms]=sqrt(temp);
  }

  printf("this is matrix after computing mean and rms \n");

   for(i=0;i<variables;i++){
    for(j=0;j<rows+2;j++) printf("%lf ",data[i][j]);
    printf("\n");
  }

  /*Fill the co-relation matrix*/
  for(i=0;i<variables;i++){
    for(j=0;j<variables;j++){
      temp=0;
      co_matrix[i][j]=(temp/(data[i][rms]*data[j][rms]));
      }
  } 

  /*print the co-relation matrix*/
  for(i=0;i<variables;i++){
    for(j=0;j<rows;j++){
      printf("%lf ");     
     }
    printf("\n");
  }

  

 
  return 0;
}
