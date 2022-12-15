#include <forward_list>
#include <iterator>
#include "my_forward_list.h"


int main()
{
    std::cout << "*************************Size comparison*************************\n";
    std::forward_list<int> Sfl_0{};
    my_std::my_forward_list<int>Mfl_0{};
    my_std::my_forward_list<int>Mfl_1{4, 5};
    my_std::my_forward_list<int>Mfl_2{3};
    //my_std::my_forward_list<float>Mfl_2{ 4, 5.12 };
    my_std::my_allocator<int> M{};
    std::cout <<"Sizeof int: " << sizeof(int) << '\n';
    std::cout <<"Sizeof std_forward_list :"<< sizeof(Sfl_0) << '\n';
    std::cout <<"Sizeof my_forward_list: " << sizeof(Mfl_0) << '\n';
    std::cout <<"Sizeof my_allocator: " << sizeof(M) << '\n';
    std::cout << "*************************Functionality comparison*************************\n";
    

    /*Sfl_0.push_front(215);
    Mfl_0.push_front(11);
    std::cout << "---Standard forward_list first value: " << Sfl_0.front() << ". ---My my_forward_list first value: " << Mfl_0.front() << '\n';
    Sfl_0.push_front(63);
    Mfl_0.push_front(45);
    std::cout << "---Standard forward_list first value: " << Sfl_0.front() << ". ---My my_forward_list first value: " << Mfl_0.front() << '\n';
    auto d = Sfl_0.begin();
    std::cout << "----------------"<< *d << '\n';
    //auto D = Mfl_0.begin();
    //std::cout << "----------------" << *D << '\n';
    my_std::my_iterator<int> Mit_0;
    my_std::my_iterator<int> Mit_1 = Mit_0;
    Mit_1 = Mit_0;
    my_std::my_iterator<int> Mit_2;
    Mit_2 = Mit_0;
    std::cout << (Mit_2 == Mit_0) << '\n';
    std::cout << *Mit_2<<"--------------------"<<&Mit_2<< '\n';
    std::cout << *Mit_2++ << '\n';
    ++Mit_2;
    std::cout << (Mit_2 == Mit_0) << '\n';
    my_std::my_iterator<int>* Mit_3 = new my_std::my_iterator<int>{};
    delete Mit_3;*/
   
    
}

