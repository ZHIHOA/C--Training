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

    cout<<"ÄêÁä:"<<stu->age<<","<<"ĞËÈ¤£º"<<stu->hobby<<","<<"Ãû×Ö£º"<<(*stu).name<<endl;
    cout<<"end"<<endl;

}
