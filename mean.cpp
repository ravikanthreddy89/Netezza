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
    int32 *mean=int32State(0);
    *mean=1; 
  }

  void accumulate(){
    int32 *mean=int32State(0);
    *mean=*mean+int32Arg(0);
  }

  void merge(){
    int32 *mean=int32State(0);
    int32 next=int32Arg(0);
    *mean=*mean+next;
  }

  ReturnValue finalResult(){
    int32 total=int32Arg(0);
    NZ_UDX_RETURN_INT32(total);
  }
};

nz::udx_ver2::Uda* Mean::instantiate(UdxInit *pInit){
  return new Mean(pInit);
}
