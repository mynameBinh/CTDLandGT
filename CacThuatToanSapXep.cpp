#include <iostream>
using namespace std;

//Heap sort (Thuật toán vun đống)


//ham swap 
void swap(int &a, int &b) {
    int tmp = b;
    b = a;
    a = tmp;
}
//hàm vun đống: khôi phục tính chất max heap tại nút i
void heapify(int arr[], int n, int i){
    int largest = i;   //khởi tạo nút cha lớn nhất tại i
    int left = 2 * i + 1;   //vị trí của nút con trái
    int right = 2 * i + 2;  //vị trí của nút con phải

    //nếu con trái nằm trong giới hạn của đống và lớn hơn largest thì gán largest = con trái
    if(left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    //nếu con phải nằm trong giới hạn của đống và lớn hơn largest thì gán largest = con phải
    if(right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    //nếu largest đã bị thay đổi thì
    if(largest != i) {
        //hoán vị nút cha với nút lớn nhất
        swap(arr[i], arr[largest]);
        //gọi đệ quy cho cây con vừa hoán vị để đảm bảo tính chất đống
        heapify(arr, n, largest);
    }
}

//Hàm sắp xếp vun đống
void heapSort(int arr[], int n){
    //bước 1: xây dựng Max Heap (Build Heap)
    //bắt đầu từ nút cha cuối cùng (n/2 - 1) lùi ngược lên nút gốc
    for (int i = n/2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    //Bước 2: trích xuất phần tử và sắp xếp
    for (int i = n - 1; i >= 0; i--){
        //bước này là bước đưa phần tử lớn(ở nút gốc, vì đã được Max heap ở bước 1) nhất về cuối mảng
        swap(arr[0], arr[i]);

        //gọi heapify trên nút gốc với kích thước đống đã giảm đi i
        // để tìm phần tử lớn nhất tiếp theo đẩy lên gốc 
        heapify(arr, i, 0);
    }

}



int main(){
    int arr[] = {1 ,5, 5, 123, 5432, 2, 7, 11, 63, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    //ham truoc khi sap xep
    cout << "Hàm trước khi sắp xếp:\n";
    for(auto i : arr){
        cout << i << " ";
    }
    //ham sau khi sap xep;
    cout << "\nHàm sau khi sắp xếp\n";
    heapSort(arr, n);
    for(auto i : arr) {
        cout << i << " ";
    }
}