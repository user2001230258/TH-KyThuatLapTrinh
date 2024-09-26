#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <set>
#include <iomanip>

using namespace std;

struct Diem {
    float diemBTVN;
    float diemKT;
    float diemThi;
};

struct SinhVien {
    string maSV;
    string hoTen;
    Diem diem;
};

// Hàm phát sinh tên ngẫu nhiên
string generateName() {
    const string ho[] = {"Nguyen", "Tran", "Le", "Pham", "Hoang", "Dang", "Vu"};
    const string tenLot[] = {"Van", "Thi", "Minh", "Ngoc", "Thanh", "Mai", "Quoc", "Hoang"};
    const string ten[] = {"An", "Binh", "Cuong", "Duy", "Khoi", "Linh", "Ha", "Phong", "Quang", "Tuan"};

    string hoNgauNhien = ho[rand() % (sizeof(ho) / sizeof(ho[0]))];
    string tenLotNgauNhien = tenLot[rand() % (sizeof(tenLot) / sizeof(tenLot[0]))];
    string tenNgauNhien = ten[rand() % (sizeof(ten) / sizeof(ten[0]))];

    return hoNgauNhien + " " + tenLotNgauNhien + " " + tenNgauNhien;
}

// Hàm phát sinh mã sinh viên ngẫu nhiên không trùng
string generateMaSV(set<string>& maSVSet) {
    string maSV;
    do {
        maSV = to_string(1000 + rand() % 9000);
    } while (maSVSet.find(maSV) != maSVSet.end());
    maSVSet.insert(maSV);
    return maSV;
}

// Hàm phát sinh điểm ngẫu nhiên từ 0 đến 10
float generateRandomScore() {
    return static_cast<float>(rand() % 101) / 10.0f; // Điểm từ 0.0 đến 10.0
}

// Hàm khởi tạo thông tin cho một sinh viên
void initSinhVien(SinhVien &sv, set<string>& maSVSet) {
    sv.maSV = generateMaSV(maSVSet);
    sv.hoTen = generateName();
    sv.diem.diemBTVN = generateRandomScore();
    sv.diem.diemKT = generateRandomScore();
    sv.diem.diemThi = generateRandomScore();
}

// Hàm tính điểm trung bình của một sinh viên theo công thức mới
float tinhDiemTrungBinh(const SinhVien &sv) {
    return (0.2f * sv.diem.diemBTVN) + (0.3f * sv.diem.diemKT) + (0.5f * sv.diem.diemThi);
}

// Hàm ghi thông tin sinh viên vào file
void ghiSinhVien(const SinhVien &sv, ofstream &outfile) {
    outfile << sv.maSV << endl;
    outfile << sv.hoTen << endl;
    outfile << sv.diem.diemBTVN << endl;
    outfile << sv.diem.diemKT << endl;
    outfile << sv.diem.diemThi << endl;
}

// Hàm đọc thông tin sinh viên từ file
SinhVien docSinhVien(ifstream &infile) {
    SinhVien sv;
    getline(infile, sv.maSV);
    getline(infile, sv.hoTen);
    infile >> sv.diem.diemBTVN >> sv.diem.diemKT >> sv.diem.diemThi;
    infile.ignore();
    return sv;
}

// Hàm hiển thị danh sách sinh viên
void hienThiDanhSach(SinhVien *dsSinhVien, int n) {
    cout << "\nDanh sách sinh viên:\n";
    for (int i = 0; i < n; i++) {
        cout << "Mã sinh viên: " << dsSinhVien[i].maSV << endl;
        cout << "Họ tên: " << dsSinhVien[i].hoTen << endl;
        cout << "Điểm bài tập: " << dsSinhVien[i].diem.diemBTVN << endl;
        cout << "Điểm kiểm tra: " << dsSinhVien[i].diem.diemKT << endl;
        cout << "Điểm thi: " << dsSinhVien[i].diem.diemThi << endl;

        // Hiển thị điểm trung bình với 1 chữ số thập phân
        cout << fixed << setprecision(1);
        cout << "Điểm trung bình: " << tinhDiemTrungBinh(dsSinhVien[i]) << endl;
        cout << "-----------------------" << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    set<string> maSVSet;
    SinhVien *dsSinhVien = nullptr;
    int n = 0;

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Thêm sinh viên\n";
        cout << "2. Ghi danh sách sinh viên vào file\n";
        cout << "3. Đọc danh sách sinh viên từ file\n";
        cout << "4. Hiển thị danh sách sinh viên\n";
        cout << "5. Thoát\n";
        cout << "Chọn: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Nhập số lượng sinh viên muốn thêm: ";
                int them;
                cin >> them;
                SinhVien *newList = new SinhVien[n + them];
                for (int i = 0; i < n; i++) {
                    newList[i] = dsSinhVien[i];
                }
                delete[] dsSinhVien;
                dsSinhVien = newList;
                for (int i = n; i < n + them; i++) {
                    initSinhVien(dsSinhVien[i], maSVSet);
                }
                n += them;
                cout << "Đã thêm " << them << " sinh viên." << endl;
                break;
            }
            case 2: {
                ofstream outfile("sinhvien.txt");
                if (!outfile) {
                    cerr << "Không thể mở file để ghi." << endl;
                    break;
                }
                for (int i = 0; i < n; i++) {
                    ghiSinhVien(dsSinhVien[i], outfile);
                }
                outfile.close();
                cout << "Đã ghi thông tin sinh viên vào file sinhvien.txt." << endl;
                break;
            }
            case 3: {
                ifstream infile("sinhvien.txt");
                if (!infile) {
                    cerr << "Không thể mở file để đọc." << endl;
                    break;
                }
                n = 0;
                while (infile.peek() != EOF) {
                    n++;
                    docSinhVien(infile);
                }
                infile.clear(); // Reset EOF flag
                infile.seekg(0); // Move to the beginning of the file

                dsSinhVien = new SinhVien[n];
                for (int i = 0; i < n; i++) {
                    dsSinhVien[i] = docSinhVien(infile);
                }
                infile.close();
                cout << "Đã đọc thông tin sinh viên từ file." << endl;
                break;
            }
            case 4: {
                if (dsSinhVien) {
                    hienThiDanhSach(dsSinhVien, n);
                } else {
                    cout << "Chưa có danh sách sinh viên nào." << endl;
                }
                break;
            }
            case 5:
                cout << "Thoát chương trình." << endl;
                break;
            default:
                cout << "Tùy chọn không hợp lệ. Vui lòng chọn lại." << endl;
                break;
        }
    } while (choice != 5);

    delete[] dsSinhVien; // Giải phóng bộ nhớ
    return 0;
}

