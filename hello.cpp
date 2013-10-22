#include<iostream>
#include "udxinc.h"
#include <string.h>

using namespace nz::udx_ver2;

/*Remember you need to define two functions 1) instantiate() 2) evaluate()*/
class hello:public nz::udx_ver2::Udf{

public:
  hello(UdxInit *pInit):Udf(pInit){}

  static nz::udx_ver2::Udf* instantiate(UdxInit *pInit);

  /*Define evaluate method*/
  virtual nz::udx_ver2::ReturnValue evaluate(){
    StringArg *str;
    str=stringArg(0);
    int lengths=str->length;
    char *data=str->data;
    int32 retval=0;
    if(lengths>=9)if(memcmp("ravikanth",data,9)==0)
		    retval=1;

    NZ_UDX_RETURN_INT32(retval);
  }


};// end of hello class declaration

/*define the instantiate function */
nz::udx_ver2::Udf* hello::instantiate(UdxInit *pInit){
  return new hello(pInit);
}
