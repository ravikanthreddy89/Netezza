#include<iostream>

class Box{

public:
  int l;
  int h;
  int b;

  void setheight(int a){
    h=a;
   }
  void setbreadth(int a){
    b=a;
   }

  int getarea(){
    return h*b;
  }
};// end of Box class definition

 class rectangle:public Box{
  public:
    int get_rectangle_area(){
      return getarea();
    }
  };// end of rectangle class definition

using namespace std;

  int main(void){
      Box b;
      rectangle r;
      b.setheight(10);
      b.setbreadth(10);

      r.setheight(10);
      r.setbreadth(10);

      cout<<"b height :"<<b.h<<endl;
      cout<<"b breadth :"<<b.b<<endl;

      cout<<"r height :"<<r.h<<endl;
      cout<<"r breadth :"<<r.b<<endl;

      cout<<"area of rectangle is "<<r.get_rectangle_area()<<endl;

      cout<<"area of recatangle is :"<<b.getarea()<<endl;
      return 0;
 }
