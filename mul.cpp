#include<iostream>
#include "udxinc.h"

using namespace nz::udx_ver2;

class mul:public nz::udx_ver2::Udf{

public:
 mul(UdxInit *pInit):Udf(pInit){}

  static nz::udx_ver2::Udf* instantiate(UdxInit *pInit);

  virtual nz::udx_ver2::ReturnValue evaluate(){
    int32 a;
    int32 b;
    a=int32Arg(0);
    b=int32Arg(1);
    int64 retval=0;
    retval=(a*b);

    NZ_UDX_RETURN32(retval);

  }
};//end of mul class definition

Udf* mul::instantiate(){
  return new mul();
}
