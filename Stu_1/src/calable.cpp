#include"calable.h"


Cala::Cala_na::Calable::Calable(){
    this->num = 5 ;
};

void Cala::Cala_na::Calable::fun(){
    
    Cala::Calz::Compute cm;
    cout<<cm.cat_num<<endl;
    cout<<"实现方法"<<endl;

}

Cala::Calz::Compute::Compute(){
    this->neibor="私有成员变量";
    cout<<"构构造函数"<<endl;
}

double Cala::Calz::Compute::sum(double a,double b){
    // cout<<neibor<<endl;
    return a+b;

}
