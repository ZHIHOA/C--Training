#include"calable.h"


Cala::Cala_na::Calable::Calable(){
    this->num = 5 ;
};

void Cala::Cala_na::Calable::fun(){
    
    Cala::Calz::Compute cm;
    cout<<cm.cat_num<<endl;
    cout<<"ʵ�ַ���"<<endl;

}

Cala::Calz::Compute::Compute(){
    this->neibor="˽�г�Ա����";
    cout<<"�����캯��"<<endl;
}

double Cala::Calz::Compute::sum(double a,double b){
    // cout<<neibor<<endl;
    return a+b;

}
