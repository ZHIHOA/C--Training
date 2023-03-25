#ifndef CALABLE_H
#define CALABLE_H
#include<iostream>
using namespace std;

namespace Cala{
namespace Cala_na{
    class Calable
    {
    private:
        int num;

    public:
        Calable();
        void fun();
    };
} // namespace name

namespace Calz{

    class Compute{
        private:
            string neibor;
        public:
            int cat_num =90;
            Compute();
            double sum(double a,double b);
    };
    // int Compute::cat_num=90;
}
}
#endif