#pragma once
#include <iostream>
#include "my_iterator.h"


namespace my_std {
    //Showing other classes in my_std namespace
    template<typename T> class node;
    template<typename T> class my_iterator;
    template<typename T> class my_allocator;
    template<typename T> class my_allocatorrrrrr;
    //************************************************* my_forward_list class
    template <typename T, typename Allocator = my_allocator<T>>
    class my_forward_list {
        public:
            //member type aliaces
            using value_type = T;
            using allocator_type = Allocator;
            using size_type = std::size_t;
            using difference_type = std::ptrdiff_t;
            using reference = value_type&;
            using const_reference = const value_type&;
            using pointer = std::allocator_traits<Allocator>::pointer;
            using const_pointer = std::allocator_traits<Allocator>::const_pointer;
            using iterator = my_std::my_iterator<T>;
            //using const_iterator = LegacyForwardIterator to const value_type
            ////////////////////////ALLOCATE MEMORY THROUGH ALLOCATOR TRAITS!!!
            my_forward_list();                                  //OK --> Default constructor. Constructs an empty container with a default-constructed allocator.
            //explicit my_forward_list(const Allocator& alloc);   //   --> Constructs an empty container with the given allocator alloc.
            my_forward_list(size_t count, const T& Val);        //OK --> Constructs the container with count copies of elements with value value.
            my_forward_list(size_t count);                      //OK --> Constructs the container with count default-inserted instances of T. No copies are made.
            //template<typename input_iterator>
            //my_forward_list(input_iterator first, input_iterator last);
            my_forward_list(const my_forward_list& other);      //


            //iterator begin() { return Head; }
            void push_front(const T& Val);                      //
            T& front();                                         //
            //void dlt(node<T, Allocator>* n) { delete n; }
            //~my_forward_list() { dlt(Head); }
            //values
        private:
            node<T>* Head{};
            node<T>* Tail{};
            //static Allocator::template rebind<node<T>>::other List_Alloc;             //___creating a static object of type my_allocator<node<T>> using defaul my_allocator<T>
            //improtant is to ALWAYS add a keyword "template" before a template type defined inside another templete type!!!
            static std::allocator_traits<Allocator>::template rebind_alloc<node<T>> List_Alloc; //creating a rebined object which will allocate memory for our nodes.
    };
    //template<typename T, typename Allocator> Allocator::template rebind<node<T>>::other my_forward_list<T, Allocator>::List_Alloc{};
    template<typename T, typename Allocator> std::allocator_traits<Allocator>::template rebind_alloc<node<T>> my_forward_list<T, Allocator>::List_Alloc{};
    //*************************************************node class
    template<typename T> class node{
        private:
            node(const T& Val = {}) :val{ Val } {}
            ~node(){}
            //values
            T val{};
            node* Next{};
            //friends
            friend class my_forward_list<T>;
            friend class my_iterator<T>;
    };
    //*************************************************my_allocator class
    template <typename T>
    class my_allocator {
    public:
        //member type aliaces
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using propagate_on_container_move_assignment = std::true_type;
        using is_always_equal = std::true_type;
        //member type
        template<class U> struct rebind {
            typedef my_allocator<U> other;
        };
        //functions
        constexpr my_allocator() { std::cout << "<><>my_allocator default constructor creates my_allocator object\n"; }
        my_allocator(const my_allocator& copy) {};
        ~my_allocator() {};
        T* allocate(size_t n = sizeof(T));
        void deallocate(T* ptr, size_t n);
        //values
        static int val_mem_count;
    };
    template<typename T> int my_allocator<T>::val_mem_count = 0;

}
    /*We can’t separate the definition of templates class from its declaration and put it inside a.cpp file!!!!!!!
    - a template is not a class or a function. A template is a “pattern” that the compiler uses to generate a family of classes or functions.
    - in order for the compiler to generate the code, it must see both the template definition(not just declaration) and the specific types/whatever used to “fill in” the template.
      For example, if you’re trying to use a Foo<int>, the compiler must see both the Foo template and the fact that you’re trying to make a specific Foo<int>.
    - your compiler probably doesn’t remember the details of one .cpp file while it is compiling another .cpp file. BTW this is called the “separate compilation model.”*/

    ////////////////////////////////////////////////////////////////////////////my_forward_list DEFINITIONS
    //OK
    template<typename T, typename Allocator>
    my_std::my_forward_list<T, Allocator>::my_forward_list() {}
    //OK
    template <typename T, typename Allocator>
    my_std::my_forward_list<T, Allocator>::my_forward_list(size_t count, const T& Val) {
        if (count) {
            //Head = Allocator::rebind<node<T>>::other::allocate(sizeof(node<T>));      //Direct callin case allocate() is static
            Head = List_Alloc.allocate(sizeof(node<T>));                                //Allocate memory for first NODE
            Head->val = Val;
            Head->Next = nullptr;
            Tail = Head;
            //std::cout << Head->val << " -> Head adress ->" << Head << '\n';
            if (count > 1) {
                for (size_t i = 1; i < count; i++) {
                    node<T>* Temp_0 = List_Alloc.allocate(sizeof(node<T>));
                    Temp_0->val = Val;
                    Temp_0->Next = Head;
                    Head = Temp_0;
                    //std::cout << Head->val << " -> Head adress ->" << Head << '\n';
                }
            }
            //std::cout << Tail->val << " -> Tail adress ->" << Tail << '\n';
        }
        else std::cout << "First parameter should be greater then 0!\n";
    }
    //OK
    template <typename T, typename Allocator>
    my_std::my_forward_list<T, Allocator>::my_forward_list(size_t count) {
        if (count) {
            Head = List_Alloc.allocate(sizeof(node<T>));                                //Allocate memory for NODE
            Head->val = {};
            Head->Next = nullptr;
            Tail = Head;
            //std::cout << Head->val << " -> Head adress ->" << Head << '\n';
            if (count > 1) {
                for (size_t i = 1; i < count; i++) {
                    node<T>* Temp_0 = List_Alloc.allocate(sizeof(node<T>));
                    Temp_0->val = {};
                    Temp_0->Next = Head;
                    Head = Temp_0;
                    //std::cout << Head->val << " -> Head adress ->" << Head << '\n';
                }
            }
            //std::cout << Tail->val << " -> Tail adress ->" << Tail << '\n';
        }
        else std::cout << "First parameter should be greater then 0!\n";
    }
    //
    template<typename T, typename Allocator>
    my_std::my_forward_list<T, Allocator>::my_forward_list(const my_forward_list& other){
        if (other.Head && other.Head == other.Tail) {
            Head = List_Alloc.allocate(sizeof(node<T>));
            Head->val = other.Head->val;
            Tail = Head;
        }
        else {
            Head = List_Alloc.allocate(sizeof(node<T>));
            Head->val = other.Head->val;
            Tail = List_Alloc.allocate(sizeof(node<T>));
            Tail->val = other.Tail->val;
            if (other.Head->Next != Tail) {
                node<T>* Temp_0 = other.Head->Next;
                node<T>* Temp_2{};
                while (Temp_0 != other.Tail) {
                    node<T>* Temp_1 = List_Alloc.allocate(sizeof(node<T>));
                    Temp_1->val = Temp_0->val;
                    Temp_2->Next = Temp_1;
                    if (Temp_0 == other.Head->Next)
                        Head->Next = Temp_1;
                    Temp_2 = Temp_1;
                    Temp_0 = Temp_0->Next;
                    //std::cout << Head->val << " -> Head adress ->" << Head << '\n';
                }
            }
        }
    }
    //
    template <typename T, typename Allocator>
    T& my_std::my_forward_list<T, Allocator>::front() {
        return Head->val;
    }
    //
    template<typename T, typename Allocator>
    void my_std::my_forward_list<T, Allocator>::push_front(const T& Val) {
        node<T>* Temp_0 = new node<T>{ Val };  //Allocate memory for NODE
        Temp_0->val = Val;
        if (Head) {
            Temp_0->Next = Head;
            Head = Temp_0;
        }
        else
            Head = Tail = Temp_0;
    }
    ////////////////////////////////////////////////////////////////////////////my_allocator DEFINITIONS
    //OK
    template <typename T>
    T* my_std::my_allocator<T>::allocate(size_t n) {
        if (n <= 0) {
            std::cout << "wrong number of bytes for memmory alocation!!!\n";
            return nullptr;
        }
        else {
            T* ptr = static_cast<T*> (std::malloc(n));
            if (!ptr) throw std::bad_alloc{};
            std::cout << ">>>my_allocator -> Memory has been allocated! Number of allocated nodes: *****" << ++val_mem_count << '\n';
            return ptr;
        }
    }
    //OK
    template <typename T>
    void my_std::my_allocator<T>::deallocate(T* ptr, size_t n) {
        if (ptr) std::free(ptr);
        std::cout << "<<<my_allocator -> Memory is DEallocated. Number of allocated nodes: *****" << val_mem_count-- << '\n';
    }
