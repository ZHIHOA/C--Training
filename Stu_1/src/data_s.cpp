#include<iostream>

using namespace std;

struct student
{
    /* data */
    string name;
    int age;
    string hobby;
};
int main()
{
    student *stu ;
    (*stu).age=19;
    // stu.hobby="socer";
    // stu.name="Tom";

    cout<<"����:"<<stu->age<<","<<"��Ȥ��"<<stu->hobby<<","<<"���֣�"<<(*stu).name<<endl;
    cout<<"end"<<endl;

}
