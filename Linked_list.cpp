#include <iostream>
struct Node {
    int val{};
    Node(int v = 0) : val{ v } { std::cout << "Creating node Nr_ " << ++coun << '\n'; Last = this; Head = this; }
    Node* Next{};
    Node* Last{};
    Node* Head{};
    static int coun;
    ~Node() { if (Next) delete Next; std::cout << "deleting node Nr_ " << coun--<<'\n'; }
};

int Node::coun = -1;
//Insertion values in the linked_list
void insert_node(Node* Base_node, int v){
    Node* Current = new Node{ v };      //create a new node
    Current->Next = nullptr;            //setting new node`s next to 0
    Base_node->Last->Next = Current;    //setting previous node`s next
    Base_node->Last = Current;          //establish new last node
    Current = nullptr;
}
//reverse linked_list  a->b->c->d->e
void reverse_list(Node* Base_node) {
    Node* Temp_instance = new Node{};
    Temp_instance = Base_node;
    Node* Temp_0 = new Node{};
    Node* Temp_1 = new Node{};
    Temp_0 = Base_node;  //A
    std::cout << Temp_0->val << '\n';
    Base_node = Temp_0->Next; //B
    std::cout << Base_node->val << '\n';
    Temp_1 = Base_node->Next;  //C
    //std::cout << Temp_1->val << '\n';
    Temp_0->Next = nullptr;
    while (Temp_1) {
        Base_node->Next = Temp_0; //B->A
        Temp_0 = Base_node; //B
        Base_node = Temp_1; //C
        std::cout <<"BAZA " << Base_node->val << '\n';
        Temp_1 = Base_node->Next;//D
        if (!Temp_1) Base_node->Next = Temp_0;
    }
    std::cout << Base_node->val << "------------\n";
    std::cout << Base_node->Next->val << "------------\n";
    std::cout << Base_node->Next->Next->val << "------------\n";
    std::cout << Base_node->Next->Next->Next->val << "------------\n";
    std::cout << Base_node << "------------\n";
    std::cout << Base_node->Next<< "------------\n";
    std::cout << Base_node->Next->Next<< "------------\n";
    std::cout << Base_node->Next->Next->Next<< "------------\n";
    Temp_instance->Head = Base_node;
    Temp_0 = nullptr;
    Temp_1 = nullptr;
    Base_node = nullptr;
}
//Traversal Linked_list values
void Show_linked_list(Node* Temp_head) {
    Node* Temp = new Node{};
    Temp = Temp_head;
    while (Temp) {
        std::cout << Temp->val<<"; ";
        Temp = Temp->Next;
    }
    std::cout << std::endl;
}
//Recursive traversal Linked_list values
void Showlinked_list_recursive(Node* Temp_head) {
    if (!Temp_head) std::cout << '\n';
    else {
        std::cout << Temp_head->val << "; ";
        Showlinked_list_recursive(Temp_head->Next);
    }
}

//////////////////
void Show_linked_listtttttttttt(Node* Temp_head) {
    Node* Temp = new Node{};
    Temp = Temp_head->Head;
    while (Temp) {
        std::cout << Temp->val << "; ";
        Temp = Temp->Next;
    }
    std::cout << std::endl;
}


int main()
{
    Node F{ 74 };
    std::cout << F.Next << '\n';
    insert_node(&F, 13);
    std::cout << F.Next << '\n';
    insert_node(&F, 553);
    std::cout << F.Next << '\n';
    insert_node(&F, 83);
    std::cout << F.Next << '\n';
    Show_linked_list(&F);
    Showlinked_list_recursive(&F);
    reverse_list(&F);
    std::cout<<&F<<'\n';
    Show_linked_listtttttttttt(&F);
}
