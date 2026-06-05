#include <iostream>
using namespace std;

//Quick sort


//hàm sort
void swap (int &a, int &b){
    int tmp = b;
    b = a;
    a = tmp;
}

//hàm chia phe
int partition(int arr[], int low, int high){
    int pivot = arr[high];   //chọn phần tử cuối cùng làm chốt(pivot)
    int i = (low - 1);    //i là phần tử ngăn cách giữa low và high

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

//khảo nghiệm trong hàm main

int main() {
    int arr[] = {1, 5, 12, 67, 123, 2, 3, 2, 9, 14};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "mảng trước khi sắp sếp: \n";
    for(auto i : arr){
        cout << i << " ";
    }
    
    cout << "\nMảng sau khi sắp sếp\n";
    quickSort(arr,0, n - 1);
    for(auto i : arr){
        cout << i << " ";
    }
}