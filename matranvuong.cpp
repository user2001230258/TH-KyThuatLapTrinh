#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void nhapMang2Chieu(int** a, int size) {
    for(int i =0; i < size;i++) {
        for(int j=0; j<size;j++) {
            cout << "Nhap phan tu a[" << i << "][" << j << "]: ";
            cin >> a[i][j];
        }
    }
}

void mang2ChieuNgauNhien(int** a, int size) {
    srand(static_cast<unsigned int>(time(0)));
    
    for (int i =0 ;i<size;i++) {
        for(int j = 0;j<size;j++) {
            a[i][j] = rand() % 100;
        }
    }
}

void xuatMang2Chieu(int** a, int size) {
    cout << "Ma tran vuong: " << endl;
    for(int i = 0;i < size;i++) {
        for(int j=0; j<size;j++) {
            cout << a[i][j] << "  ";
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
    int choice;
    do {
        cout << "---------------------------------------" << endl;
        cout << "1. Nhap ma tran vuong" << endl;
        cout << "2. Ma tran vuong ngau nhien" << endl;
        cout << "3. Xuat ma tran vuong" << endl;
        cout << "4. Thoat" << endl;
        cout << "Lua chon cua ban: ";
        cin>>choice;
        
        switch(choice) {
            case 1:
                nhapMang2Chieu(a,size);
                break;
                
            case 2:
                mang2ChieuNgauNhien(a,size);
                break;
                
            case 3: 
                xuatMang2Chieu(a,size);
                break;
                
            case 4:
                cout << "Thoat chuong trinh" << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
        
    } while (choice!=4);


    
    
    for(int i =0; i<size;i++) {
        delete[] a[i];
    }
    delete[] a;

    return 0;
}
