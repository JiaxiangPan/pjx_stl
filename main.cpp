#include"stl/Vector.h"
//#include<iostream>

using namespace pjx::stl;
//using namespace std;

int main()
{
    Vector<int> v;
    //std::cout << "hello world" << std::endl;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.show();

    // v.reserve(7);
    // v.show();

    // v.resize(10);
    // v.show();

    // v.resize(4);
    // v.show();

    // //v.at(4);
    // std::cout << v.at(3) << std::endl;
    // std::cout << v[2] << std::endl;

    // std::cout << "the first element of vector is :" << v.front() << std::endl;
    // std::cout << "the last element of vector is :" << v.back() << std::endl;
    
    // std::cout << v.empty() << std::endl;
    //v.clear();
    //v.show();

    // Vector<int> v1;
    // for(int i = 0; i < 4; i++)
    // {
    //     v1.push_back(i+10);
    // }
    // v.swap(v1);
    // v.show();
    // v1.show();

    // Vector<int> v2;
    // v2 = v;
    // v2.show();

    // std::cout << "test for Iterator" << std::endl;
    // for(Vector<int>::Iterator it = v2.begin(); it != v2.end(); it ++)
    // {
    //     std::cout << *it << ",";
    // }
    // std::cout << std::endl;

   v.insert(v.begin()+1,7);
   v.show();
    return 0;
}
