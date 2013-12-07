#include<iostream>
#include "udxinc.h"
#include<math.h>

//first state should be double
//second state should be int32

using namespace nz::udx_ver2;

class cor:public nz::udx_ver2::Uda{

 public:
   
  /*Constructor*/
  cor(UdxInit *pInit):Uda(pInit){}

  static nz::udx_ver2::Uda* instantiate(UdxInit *pInit);
  void initializeState(){
    setStateNull(0,false);//sum square
    setStateNull(1,false);//just sum
    setStateNull(2,false);//count
    setStateNull(3,false);
    setStateNull(4,false);
    setStateNull(5,false);

    double *x_sum_square=doubleState(0);
    double *x_sum=doubleState(1);
    double *y_sum_square=doubleState(2);
    double *y_sum=doubleState(3);
    double *xy_product_sum=doubleState(4);
    double *count=doubleState(5);


    *x_sum_square=0;
    *x_sum=0;
    *y_sum_square=0;
    *y_sum=0;
    *xy_product_sum=0;
    *count=0; 
  }

  void accumulate(){
    double *x_sum_square=doubleState(0);
    double *x_sum=doubleState(1);
    double *y_sum_square=doubleState(2);
    double *y_sum=doubleState(3);
    double *xy_product_sum=doubleState(4);
    double *count=doubleState(5);

    int32 x=int32Arg(0);
    int32 y=int32Arg(1);

    *x_sum_square=*x_sum_square+(x*x);
    *x_sum=*x_sum+(x);
    *y_sum_square=*y_sum_square+(y*y);
    *y_sum=*y_sum+y;
    *xy_product_sum=*xy_product_sum+(x*y);
    *count=*count+1;
  }

  void merge(){
    double *x_sum_square_total=doubleState(0);
    double *x_sum_total=doubleState(1);
    double *y_sum_square_total=doubleState(2);
    double *y_sum_total=doubleState(3);
    double *xy_product_sum_total=doubleState(4);
    double *count_total=doubleState(5);


    double x_sum_square=doubleArg(0);
    double x_sum=doubleArg(1);
    double y_sum_square=doubleArg(2);
    double y_sum=doubleArg(3);
    double xy_product_sum=doubleArg(4);
    double count=doubleArg(5);
   
    *x_sum_square_total=*x_sum_square_total+x_sum_square;
    *x_sum_total=*x_sum_total+x_sum;
    *y_sum_square_total=*y_sum_square_total+y_sum_square;
    *y_sum_total=*y_sum_total+y_sum;
    *xy_product_sum_total=*xy_product_sum_total+xy_product_sum;
    *count_total=*count_total+count;

  }

  ReturnValue finalResult(){
   double x_square=doubleArg(0);
   double x_sum=doubleArg(1);
   double y_square=doubleArg(2);
   double y_sum=doubleArg(3);
   double xy_product_sum=doubleArg(4);
   double count=doubleArg(5);

   double x_mean=(x_sum/count);
   double y_mean=(y_sum/count);

   double numerator=(xy_product_sum-(count*x_mean*y_mean));
   double denominator=sqrt((x_square-(count*x_mean*x_mean))*(y_square-(count*y_mean*y_mean)));

   double ret=(numerator/denominator);
   NZ_UDX_RETURN_DOUBLE(ret);
  }
};

nz::udx_ver2::Uda* cor::instantiate(UdxInit *pInit){
  return new cor(pInit);
}
