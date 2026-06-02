#include <iostream>
#include <string>
#include <cstring>

using namespace std;

//node lồng nhau có cấu trúc mainNode -- mainNode --- ... 
//                              |           |
//                           subNode     subNode
//                              |           |
//                           subNode     subNode

//hàm khởi tạo node con 
struct subNode{
    string data;
    subNode* subNext;
};

//node chính 
struct mainNode {
    string id;
    mainNode* next;
    subNode* childList;
};

//tạo node con
subNode* createSubNode(string value) {
    subNode* newNode = new subNode();

    newNode->data = value;
    newNode->subNext = nullptr;
    
    return newNode;
}

//tạo node chính
mainNode* createMainNode(string value) {
    mainNode* newNode = new mainNode();

    newNode->id = value;
    newNode->next = nullptr;
    newNode->childList = nullptr;

    return newNode;
}

//thêm list vào đầu danh sách nếu đề không yêu cầu thêm vào cuối
void addMainNode(mainNode* &head, string value) {
    mainNode* newNode = createMainNode(value);

    newNode->next = head;
    head = newNode;
}

//tạo subList cho mainNode
void addSubNode(mainNode* target, string value){
    if(target == nullptr) return;

    subNode* newNode = createSubNode(value);
    newNode->subNext = target->childList;
    target->childList = newNode;
}

//Hàm để in danh sách chính
void printList(mainNode* danhSach){
    if(danhSach == nullptr) return;

    mainNode* tmp  = danhSach;
    int n = 1;
    while(tmp != nullptr){
        cout << n << " : " << tmp->id << endl;
        tmp = tmp->next;
        n++; 
    }
}

//Hàm để in danh sách bao gồm cả subNode
void printSubList(mainNode* danhSach){
    if(danhSach == nullptr){
        cout << "nullptr" << endl;
    } else {
        //in các subnode của danhsach
        mainNode* ds = danhSach;
        
        while(ds != nullptr) {
            subNode* sdt = ds ->childList;
             cout << "--" << ds->id << "--" << endl;
             int n = 1;
            while(sdt != nullptr){
                cout << n << ": " << sdt->data << endl;
                sdt = sdt->subNext;
                n++; 
            }
            ds = ds->next;
        }
    }
}


//Hàm giải phóng bộ nhớ cho tiết kiệm ram (cho vui chơ đề chắc cũng ko cần);
void freeMemory(mainNode* &head) {
    while(head != nullptr){
    mainNode* nextHead = head->next;

    subNode* currentSub = head->childList;
    while(currentSub != nullptr) {
        subNode* nextSub = currentSub -> subNext;
        delete currentSub;
        currentSub = nextSub;
    }
    delete head;
    head = nextHead;
  }
}


//Merge Sort để sắp xếp theo thứ tự tăng dần (sắp xếp lại cho giống với đề, vì đề hay sắp sẵn)
void splitList(mainNode* source, mainNode* &front, mainNode* &back){
    if(source == nullptr || source->next == nullptr){
        front = source;
        back = nullptr;
        return;
    }

    mainNode* fast = source->next;
    mainNode* slow = source;

    while(fast != nullptr){
        fast = fast->next;
        if(fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    front = source;
    back = slow->next;

    slow->next = nullptr;
}
//trộn merge
mainNode* mergeSortList(mainNode* left, mainNode* right) {
    if(left == nullptr) return right;
    if(right == nullptr) return left;

    mainNode* result = nullptr;

    if(left->id <= right->id) {
        result = left;
        result->next = mergeSortList(left->next, right);
    } else {
        result = right;
        result->next = mergeSortList(left, right->next);
    }

    return result;
}
//mergesort chinh
void mergeSort(mainNode* &head){
    if(head == nullptr || head->next == nullptr) return;

    mainNode* a = nullptr;
    mainNode* b = nullptr;

    //cat head ra bang cach goi ham
    splitList(head, a, b);

    //tiếp tục đệ quy để cắt a và b
    mergeSort(a);
    mergeSort(b);

    //gop chung lai
    head = mergeSortList(a,b);
}



//hàm tìm địa chỉ của từ khóa cần tìm (Thuật toán tìm kiếm theo key trả về địa chỉ)
mainNode* findId(mainNode* head, string keycmp){
    mainNode* tmp = head;

    while(tmp->id <= keycmp){
        if(tmp->id == keycmp){
            return tmp;
        }
        tmp = tmp->next;
    }
    return nullptr;
}

//hàm xóa node tìm được dựa trên hàm findId (Thuật toán xóa node)
void removeNode(mainNode* &head, mainNode* &target){
    if(target == nullptr) return;
    mainNode* current = head;
    if(target == current) {
        head = target->next;
    } else {
        while(current != nullptr && current->next != target){
            current = current->next;
        }
        if(current != nullptr){
            current->next = target->next;
        }
    }

    //xoa subnode
    subNode* currentSub = target->childList;
    while(currentSub != nullptr){
        subNode*nextSub = currentSub->subNext;
        delete currentSub;
        currentSub = nextSub;
    }
    delete target;
}

//hàm đảo ngược danh sách
void reverseNode(mainNode* &head){
    if(head == nullptr) return;
    
    mainNode* prev = nullptr;
    mainNode* current = head;
    mainNode* next = nullptr;

    while(current != nullptr){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

//hàm thêm node chèn vào vị trí chỉ định (THEO INDEX)
void insertNodeAtPos(mainNode* &head, string ID, int pos){
    mainNode* newNode = createMainNode(ID);
    if(pos <= 1){
        newNode->next = head;
        head = newNode;
        return;
    }

    mainNode* current = head;
    int index = 0;
    while(current != nullptr && index <= pos - 1){
        current = current->next;
        index++;
    }

    if(current == nullptr) return;

    newNode->next = current->next;
    current->next = newNode;
}

int main () {
    mainNode* danhSachTruyen = nullptr;
    addMainNode(danhSachTruyen, "dora");
    addMainNode(danhSachTruyen, "naru");
    addMainNode(danhSachTruyen, "cona");
    addMainNode(danhSachTruyen, "hatsu");
    addMainNode(danhSachTruyen, "lufy");
    addMainNode(danhSachTruyen, "taki");

    //sap xep lai nhu trong de
    mergeSort(danhSachTruyen);

    //them childlist vao ds truyen
    addSubNode(findId(danhSachTruyen, "naru"), "câu truyện về cậu bé tay trắng trở thành Hokage");
    addSubNode(findId(danhSachTruyen, "dora"), "Cuộc phiêu lưu kỳ bí trên mặt trăng");
    addSubNode(findId(danhSachTruyen, "dora"), "Cuộc phiêu lưu kỳ bí dưới đại dương");
    addSubNode(findId(danhSachTruyen, "dora"), "Cuộc phiêu lưu kỳ bí ngoài hành tinh Astora");
    addSubNode(findId(danhSachTruyen, "cona"), "Án mạng trong phòng kín");
    addSubNode(findId(danhSachTruyen, "cona"), "Án mạng trong phòng kín");
    addSubNode(findId(danhSachTruyen, "lufy"), "Cậu bé cao su");
    addSubNode(findId(danhSachTruyen, "lufy"), "Cậu bé cao su hóa thành gear 5");
    addSubNode(findId(danhSachTruyen, "taki"), "Tên cậu là gì?");


    //in danh sach truyện và truyện(subnode)
    cout << "=====danh sách truyện và truyện con trong danh sách=====" << endl;
    printSubList(danhSachTruyen);
    cout << endl;

    //Sử dụng hàm xóa
    cout << "==== Trước khi xóa ====" << endl;
    printList(danhSachTruyen);

    cout << "==== sau khi xóa ====" << endl;
    mainNode* nodeCanXoa = findId(danhSachTruyen, "naru");
    string thongBaoXoa = nodeCanXoa->id;
    removeNode(danhSachTruyen, nodeCanXoa);

    printList(danhSachTruyen);
    cout << "Đã xóa danh sách truyện về: " << thongBaoXoa << endl;
    cout << endl;


    //thử sử dụng hàm đảo ngược danh sách
    cout << "======đảo ngược danh sách truyện=======" << endl;
    reverseNode(danhSachTruyen);
    printList(danhSachTruyen);
    cout << endl;

    //thêm node vào vị trí thứ n
    cout << "==== thêm danh sách vào vị trí thứ n = 3 ====" << endl;
    insertNodeAtPos(danhSachTruyen, "hehe", 3);
    printList(danhSachTruyen); //vì danh sách bị sắp xếp ở trên nên thứ tự sẽ không được hoàn hảo

    //giải phóng bộ nhớ
    freeMemory(danhSachTruyen);

}