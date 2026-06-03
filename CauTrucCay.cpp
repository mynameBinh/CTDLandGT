#include <iostream>
#include <string>
using namespace std;


//Hàm khởi tạo node
struct node {
    int data;
    node *Left, *Right;
};

//hàm tạo node quen thuộc
node* createNode(int value){
    node* tmp = new node();
    tmp->data = value;
    tmp->Left = nullptr;
    tmp->Right = nullptr;
    
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
            if(current->Left == nullptr){
                current->Left = newNode;
                return;
            }
            current = current->Left;
        } else {
            if(current->Right == nullptr){
                current->Right = newNode;
                return;
            }
            current = current->Right;
        }
    }

}


//PHẦN 1: CÁC THUẬT TOÁN DUYỆT CÂY CƠ BẢN
//hàm duyệt Tiền thứ tự NLR (gốc, trái, phải)
void duyetNLR(node* T){
    if(T != nullptr){
        cout << T->data << " ";
        duyetNLR(T->Left);
        duyetNLR(T->Right);
    }
}

//hàm duyệt Trung thứ tự LNR (Trái, gốc, phải) in từ phải sang trái sẽ in theo tăng dần
void duyetLNR(node* T){
    if(T != nullptr){
        duyetLNR(T->Left);
        cout << T->data << " ";
        duyetLNR(T->Right);
    }
}

//Hàm duyệt Hậu thứ tự LRN(trái - phải - gốc)
void duyetLRN(node* T){
    if(T != nullptr){
        duyetLRN(T->Left);
        duyetLRN(T->Right);
        cout << T->data << " ";
    }
}


//PHẦN 2: ĐO LƯỜNG VÀ ĐẾM (DỄ RA THI NHẤT)
//Hàm đo lường: TÍNH CHIỀU CAO CỦA CÂY  (đã ra trong đề thi câu 3a đề 2024-2025)
int treeHeight(node* T){
    if(T == nullptr) return 0;

    int Hleft = treeHeight(T->Left);
    int Hright = treeHeight(T->Right);

    return 1+(Hleft < Hright ? Hright : Hleft);
}

//Hàm đếm tổng số nút
int countNode(node* T){
    if(T == nullptr) return 0;
    return 1 + countNode(T->Left) + countNode(T->Right);
}

//Đếm số nút lá (nút không có con)
int countLeafNode(node* T){
    if(T == nullptr) return 0;
    if(T->Left == nullptr && T->Right == nullptr) return 1;
    return countLeafNode(T->Left) + countLeafNode(T->Right);
}

//Tính cấp của cây (CÂU 3b - ĐỀ 2022-2023)
// đề yêu cầu nói là: 0 (rỗng/1 nút), 1 (cây suy biến - mỗi nút có max 1 con), 2 (cây có ít nhất 1 nút có 2 con).
int coutNodeLevel(node* T){
    if(T == nullptr ||  (T->Left == nullptr && T->Right == nullptr)) return 0;
    if(T->Left != nullptr && T->Right != nullptr) return 2; //nếu nút có 2 con thì cấp 2 luôn hehe

    int levelLeft = coutNodeLevel(T->Left);
    int levelRight = coutNodeLevel(T->Right);

    if(levelLeft == 2 || levelRight == 2) return 2;

    return 1;
}

//PHẦN 3: TÌM KIẾM VÀ QUAN HỆ
//Tìm giá trị nhỏ nhất trong cây(đã ra thi Câu 3a - đề 2023-2024)
int min(node* T){
    int minVal = T->data;

    if(T->Left != nullptr){
        int minLeft = min(T->Left);
        if(minLeft < minVal) minVal = minLeft;
    }

    if(T->Right != nullptr){
        int minRight = min(T->Right);
        if(minRight < minVal) minVal = minRight;
    }

    return minVal;
}

//Tìm nút cha của nút p (đã ra thi câu 3b - đề 2024-2025)
node* pDad(node* T, node* p){
    if(T == nullptr || T == p) return nullptr;  //nếu T rỗng hoặc T là chính p thì null vì mồ côi cha

    if(T->Left == p || T->Right == p) return T;  //nếu trái phái chứa p thì nó là daddy của p

    //tìm bên trái trước
    node* left = pDad(T->Left, p);
    if(left != nullptr) return left;

    //trái không có thì tìm bên phải
    node* right = pDad(T->Right, p);
    return right;
}

//Tính mức của nút p(đã ra đề câu 3c - 2024-2025)
//Mức của gốc là 1 (không biết giáo trình trường mình là mức mấy 0 hoặc 1). Cứ đi xuống 1 nhánh thì mức tăng 1.
int mucNode(node* T, node* p) {
    if(T == nullptr) return 0;
    if(T == p) return 1;

    int mucLeft = mucNode(T->Left, p);
    if(mucLeft > 0) return 1 + mucLeft; // đã tìm thấy mức trái

    int mucRight = mucNode(T->Right, p);
    if(mucRight > 0) return 1 + mucRight; // da tim thay muc phai

    return 0; //neu ca 2 khong co
}


int main(){
    node* T = nullptr;

    //insert vao T
    insertNodeInTree(T, 5);
    insertNodeInTree(T, 4);
    insertNodeInTree(T, 10);
    insertNodeInTree(T, 1);
    insertNodeInTree(T, 50);

    //Duyệt tiền thứ tự
    cout << "Duyệt tiền thứ tự: \n";
    duyetNLR(T);
    
    //Duyet trung thứ tự
    cout << "\nDuyệt trung thứ tự: \n";
    duyetLNR(T);

    //Duyệt Hậu thứ tự
    cout << "\nDuyet Hậu thứ tự: \n";
    duyetLRN(T);

    //Đếm chiều cao của cây
    cout << "\nChiều cao của cây là: ";
    cout << treeHeight(T);

    //Đếm tổng số nút
    cout << "\nĐếm tổng số nút có trong cây: ";
    cout << countNode(T);

    //Đếm tổng số nút lá
    cout << "\nTổng số nút lá (nút không có con): ";
    cout << countLeafNode(T);

    //Đếm cấp của nút
    cout << "\nCaap của nút là: ";
    cout << coutNodeLevel(T);

    //Tìm giá trị nhỏ nhất trong cây
    cout << "\nGía trị nhỏ nhất trong cây là: ";
    cout << min(T);

    //Tìm cha cho bé p
    // giả xử p = 50
    node* p = T->Right->Right; //50
    cout << "\nCha của bé p là: ";
    node* value = pDad(T, p);
    cout << value->data;


    //Mức của bé p                ^
    // giả xử p = 50 của cái trên |
    cout << "\nMức của bé p là: ";
    cout << mucNode(T, p);

}