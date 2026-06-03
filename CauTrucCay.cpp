#include <iostream>
#include <string>
using namespace std;


//Hàm khởi tạo node
struct node {
    int data;
    node *L, *R;
};

//hàm tạo node quen thuộc
node* createNode(int value){
    node* tmp = new node();
    tmp->data = value;
    tmp->L = nullptr;
    tmp->R = nullptr;
    
    return tmp;
};


//hàm thêm node thỏa mãn (giá trị lớn hơn hoặc bằng gốc thì qua phải, bé hơn qua trái)
void insertNodeInTree(node* &top, int value){
    node* newNode = createNode(value);
    if(top == nullptr) {
        top = newNode;
        return;
    }
    
    node* current = top;
    while(true){
        if(value < current->data) {
            if(current->L == nullptr){
                current->L = newNode;
                return;
            }
            current = current->L;
        } else {
            if(current->R == nullptr){
                current->R = newNode;
                return;
            }
            current = current->R;
        }
    }

}

//hàm duyệt Tiền thứ tự NLR (gốc, trái, phải)
void duyetNLR(node* T){
    if(T != nullptr){
        cout << T->data << " ";
        duyetNLR(T->L);
        duyetNLR(T->R);
    }
}

//dang them... thuat toan...

int main(){
    node* T = nullptr;

    //insert vao T
    insertNodeInTree(T, 5);
    insertNodeInTree(T, 4);
    insertNodeInTree(T, 10);
    insertNodeInTree(T, 1);
    insertNodeInTree(T, 50);

    duyetNLR(T);
}