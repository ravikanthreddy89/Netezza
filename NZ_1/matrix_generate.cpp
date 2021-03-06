#include<iostream>
#include<string>
#include "udxinc.h"

using namespace nz::udx_ver2;

class matrix_generate:public Udtf {

public:
  int rows;
  int cols;
  int i,j,k;

public:
  matrix_generate(UdxInit *pInit):Udtf(pInit){}

  static Udtf* instantiate(UdxInit*);

  /*Process each input row*/
  virtual void newInputRow(){
    int32 r=int32Arg(0);
    rows=r;
    r=int32Arg(1);
    cols=r;
  }

  /*function to customize the output*/
  void calculateShape(UdxOutputShaper *shaper){

  logMsg(LOG_DEBUG,"The value of columns : %d \n",cols );
   if(shaper->numArgs()!=2) throwUdxException("Expecting proper number of arguments ra nee ayya!!!");

    int nType=0;
    nType=shaper->argType(1);
    char heading[sizeof(int32)];
    for(i=0;i<shaper->int32Arg(1);i++){
      nType=shaper->argType(1);
      sprintf(heading,"X%d",(i+1));
     //    shaper->addOutputColumn(nType,heading);
     shaper->addOutputColumn(UDX_DOUBLE,heading);
    }
   }

  /*Output rows*/
  virtual DataAvailable nextOutputRow(){
    double *ret;
 
     if(rows==0) return Done;
     
     for(j=0;j<cols;j++){
     ret=doubleReturnColumn(j);
     *ret=((rand()%99)+1);
      }
     rows=rows-1;
     return MoreData;
    
    }
  //end of output row method

 
};//end of class defintion

Udtf* matrix_generate::instantiate(UdxInit *pInit){

  return new matrix_generate(pInit);
}
