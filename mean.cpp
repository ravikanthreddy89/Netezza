#include<iostream>
#include "udxinc.h"

using namespace nz::udx_ver2;

class Mean:public nz::udx_ver2::Uda{

 public:
   
  /*Constructor*/
  Mean(UdxInit *pInit):Uda(pInit){}

  static nz::udx_ver2::Uda* instantiate(UdxInit *pInit);
  void initializeState(){
    setStateNull(0,false);
    setStateNull(0,false);

    float *mean=floatState(0);
    int32 *count=int32State(0);
    *mean=0;
    count=0; 
  }

  void accumulate(){
    float *mean=floatState(0);
    int32 *count=int32State(0);

    *mean=*mean+int32Arg(0);
    *count=*count+1;
  }

  void merge(){
    float *mean_original=floatState(0);
    int32 *count_total=int32State(0);

    float *mean=floatArg(0);
    int32 count=int32Arg(0);

    *mean_original=*mean_original+*mean;
    *count_total=*count_total+count;

  }

  ReturnValue finalResult(){
    float total_sum=floatArg(0);
    int32 n=int32Arg(0);
    float mean=(total/n);

    NZ_UDX_RETURN_INT32(mean);
  }
};

nz::udx_ver2::Uda* Mean::instantiate(UdxInit *pInit){
  return new Mean(pInit);
}
