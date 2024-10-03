#include <iostream>
using namespace std;

void nhapMang2Chieu(int** a, int size) {
    for(int i =0; i < size;i++) {
        for(int j=0; j<size;j++) {
            cout << "Nhap phan tu a[" << i << "][" << j << "]: ";
            cin >> a[i][j];
        }
    }
}

void xuatMang2Chieu(int** a, int size) {
    cout << "ma tran 2 chieu: " << endl;
    for(int i = 0;i < size;i++) {
        for(int j=0; j<size;j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int size;
    cout << "Nhap kich thuoc cua ma tran vuong: ";
    cin >> size;
    
    int** a = new int*[size];
    for(int i = 0;i< size;i++) {
        a[i] = new int[size];
    }
    
    nhapMang2Chieu(a, size);
    
    xuatMang2Chieu(a, size);
    
    for(int i =0; i<size;i++) {
        delete[] a[i];
    }
    delete[] a;

    return 0;
}
