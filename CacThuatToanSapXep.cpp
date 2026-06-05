#include <iostream>
using namespace std;

//=== QUICK SORT ===

void swap (int &a, int &b){
    int tmp = b;
    b = a;
    a = tmp;
}

//hàm chia phe
int partition(int arr[], int low, int high){
    int pivot = arr[high];   //chọn phần tử cuối cùng làm chốt(pivot)
    int i = (low - 1);    //i là phần tử ngăn cách giữa low và high
//Heap sort (Thuật toán vun đống)

    for(int j = low; j <= high - 1; j++) {
        if(arr[j] < pivot) {      //nếu mà phần tử j < pivot thì tăng i lên 1 và đổi chỗ arr[i] với [j] còn không thì bỏ qua
            i++;
            swap(arr[i], arr[j]);
        }
    }

    //cuối cùng là đặt pivot vào đằng sau phần tử ngăn cách i
    swap(arr[i + 1], arr[high]);

    return i + 1;
}

//hàm quicksort chính
void quickSort(int arr[], int low, int high){
    if(low < high){
        int pi = partition(arr, low, high);   //cắt và trả về phần tử pivot ngăn cách giữa low và high

        quickSort(arr, low, pi-1);  //đệ quy phía bên trái của pivot và thực hiện lặp như trên cho đến khi sắp sếp xong
        quickSort(arr, pi+1, high); // tương tự phía bên phải
    }
}



//===HEAP SORT===
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
    quickSort(arr, 0, n-1); //heap sort: heapSort(arr, n);
    for(auto i : arr) {
        cout << i << " ";
    }
}