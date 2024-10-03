#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

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
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}


void hoanViMaTran(int** a, int size) {
    int viTri1, viTri2;
    do {
        viTri1 = rand() % size;
        viTri2 = rand() % size;
    } while (viTri1 == viTri2);

    cout << "Hoan vi 2 dong: " << viTri1 << " va " << viTri2 << endl;

    for (int j = 0; j < size; j++) {
        swap(a[viTri1][j], a[viTri2][j]);
    }
}

void sapXepGiamDan(int** a, int size) {
	for (int j = 1;j<size;j+=2) { // Duyet cac cot le j=1,3,5,....
		for (int i = 0; i<size-1;i++) {
			for (int k = i+1;k<size;k++) {
				if (a[i][j] < a[k][j]) {
					int temp = a[i][j];
					a[i][j] = a[k][j];
					a[k][j] = temp;
				}
			}
		}
	}
	cout << "Da sap xep cac cot giam dan" << endl;
}

void sapXepDuongCheoChinhTangDan(int** a, int size) {
	int* duongCheoChinh = new int[size];
	
	// Lay phan tu tren duong cheo chinh
	for (int i = 0; i < size;i++) {
		duongCheoChinh[i] = a[i][i];
	}
	
	for (int i =0;i < size-1;i++) {
		for (int j = i+1; j <size;j++) {
			if(duongCheoChinh[i] > duongCheoChinh[j]) {
				int temp = duongCheoChinh[i];
				duongCheoChinh[i] = duongCheoChinh[j];
				duongCheoChinh[j] = temp;
			}
		}
	}
	
	// Dua lai cac phan tu da sap xep vao duong cheo chinh
	for (int i = 0; i < size;i++) {
		a[i][i] = duongCheoChinh[i];
	}
	
	delete[] duongCheoChinh;
	
	cout << "da sap xep cac phan tu tren duong cheo chinh tang dan" << endl;
	
}

void ghiMaTranVaoFile(int** a, int size, const string& filename) {
	ofstream outfile(filename);
	if(outfile.is_open()) {
		outfile << size << endl; // Ghi kich thuoc ma tran o dong dau tien
		
		for(int i = 0; i <size;i++) {
			for (int j = 0;j<size;j++) {
				outfile << a[i][j] << " ";
			}
			outfile << endl;
		}
		outfile.close();
		cout << "Da ghi ma tran vao file " << filename << " thanh cong" << endl;
	} else {
		cout <<"Khong the mo file" << endl;
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
        cout << "1. Ma tran vuong ngau nhien" << endl;
        cout << "2. Xuat ma tran vuong" << endl;
        cout << "3. Hoan vi 2 dong ma tran" << endl;
        cout << "4. Sap xep cac cot le theo thu tu giam dan" << endl;
        cout << "5. Sap xep phan tu tren duong cheo chinh tang dan" << endl;
        cout << "6. Thoat" << endl;
        cout << "Lua chon cua ban: ";
        cin>>choice;
        
        switch(choice) {    
            case 1:
                mang2ChieuNgauNhien(a,size);
                ghiMaTranVaoFile(a,size, "MSSV.txt");
                break;
                
            case 2: 
                xuatMang2Chieu(a,size);
                break;

            case 3:
                hoanViMaTran(a,size);
                ghiMaTranVaoFile(a,size, "MSSV.txt");
                break;
            
			case 4:
				sapXepGiamDan(a,size);
				ghiMaTranVaoFile(a,size, "MSSV.txt");
				break; 
			
			case 5:
				sapXepDuongCheoChinhTangDan(a,size);
				ghiMaTranVaoFile(a,size, "MSSV.txt");
				break;
			
			case 6:
				cout<<"Thoat chuong trinh"<<endl;
				break;
							   
            case 7:
                cout << "Thoat chuong trinh" << endl;
                break;
                
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
        
    } while (choice!=0);


    
    
    for(int i =0; i<size;i++) {
        delete[] a[i];
    }
    delete[] a;

    return 0;
}
