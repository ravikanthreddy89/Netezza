#include<iostream>
#include "udxinc.h"
#include<math.h>

//first state should be double
//second state should be int32

using namespace nz::udx_ver2;

class rms:public nz::udx_ver2::Uda{

 public:
   
  /*Constructor*/
  rms(UdxInit *pInit):Uda(pInit){}

  static nz::udx_ver2::Uda* instantiate(UdxInit *pInit);
  void initializeState(){
    setStateNull(0,false);
    setStateNull(1,false);
    setStateNull(2,false);

    double *sum_square=doubleState(0);
    double *sum=doubleState(1);
    double *count=doubleState(2);


    *sum_square=0;
    *sum=0;
    *count=0; 
  }

  void accumulate(){
    double *sum_square=doubleState(0);
    double *sum=doubleState(1);
    double *count=doubleState(2);

    *sum_square=*sum_square+(int32Arg(0)*int32Arg(0));
    *sum=*sum+(int32Arg(0));
    *count=*count+1;
  }

  void merge(){
    double *sum_square=doubleState(0);
    double *sum_total=doubleState(1);
    double *count_total=doubleState(2);


    double sum_squares=doubleArg(0);
    double sum_totals=doubleArg(1);
    double count_totals=doubleArg(2);

    *sum_square=*sum_square+sum_squares;
    *sum_total=*sum_total+sum_totals;
    *count_total=*count_total+count_totals;

  }

  ReturnValue finalResult(){
    double sum_squares=doubleArg(0);
    double sum=doubleArg(1);
    double count=doubleArg(2);

    double mean=(sum/count);   

    double ret=sqrt(sum_squares- (count*mean*mean));
    NZ_UDX_RETURN_DOUBLE(ret);
  }
};

nz::udx_ver2::Uda* rms::instantiate(UdxInit *pInit){
  return new rms(pInit);
}
