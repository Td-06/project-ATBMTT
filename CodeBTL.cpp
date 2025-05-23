#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <cctype>

using namespace std;

//Bang anh xa hex sang binary
const string hex_to_bin[16] = {
    "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
    "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
};

//Bang anh xa binary sang hex
const char bin_to_hex[16] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

//Chuyentuhethaplucphansangnhiphan
string chuyenHe16SangNhiPhan(string s) {
    string nhiphan = "";
    for (int i = 0; i < s.length(); i++) {
        char c = toupper(s[i]);
        int index = (c >= '0' && c <= '9') ? (c - '0') : (c - 'A' + 10);
        nhiphan += hex_to_bin[index];
    }
    return nhiphan;
}

//Chuyentunhiphansanghethaplucphan
string chuyenNhiPhanSangHe16(string s) {
    string he16 = "";
    for (size_t i = 0; i < s.length(); i += 4) {
        string ch = s.substr(i, 4);
        int val = 0;
        for (int j = 0; j < 4; j++) {
            val = val * 2 + (ch[j] - '0');
        }
        he16 += bin_to_hex[val];
    }
    return he16;
}

//Chuyentunhiphansangthapphan
int chuyenNhiPhanSangThapPhan(string nhiphan) {
    int thapphan = 0;
    for (int i = nhiphan.length() - 1, j = 0; i >= 0; i--, j++) {
        if (nhiphan[i] == '1') {
            thapphan += (1 << j); // Thay pow(2, j)
        }
    }
    return thapphan;
}

//Chuyentuthapphansangnhiphan
string chuyenThapPhanSangNhiPhan(int num) {
    string ketqua = "";
    if (num == 0) return "0000";
    while (num > 0) {
        ketqua = (num % 2 == 0 ? "0" : "1") + ketqua;
        num /= 2;
    }
    while (ketqua.length() % 4 != 0) {
        ketqua = "0" + ketqua;
    }
    return ketqua;
}

//Hamhoanvicacbit
string hoanVi(string k, const int arr[], int n) {
    string hoanviketqua = "";
    for (int i = 0; i < n; i++) {
        hoanviketqua += k[arr[i] - 1];
    }
    return hoanviketqua;
}

//Dichtraicacbit
string dichTrai(string k, int sldich) {
    string s = "";
    for (int i = 0; i < sldich; i++) {
        for (size_t j = 1; j < k.length(); j++) {
            s += k[j];
        }
        s += k[0];
        k = s;
        s = "";
    }
    return k;
}

//TinhXORcuahaichuoinhiphan
string tinhXor(string a, string b) {
    string ketqua = "";
    for (size_t i = 0; i < a.length(); i++) {
        ketqua += (a[i] == b[i]) ? "0" : "1";
    }
    return ketqua;
}

//Banghoanvibandau
const int banghoanvibandau[64] = {58, 50, 42, 34, 26, 18, 10, 2,
                                  60, 52, 44, 36, 28, 20, 12, 4,
                                  62, 54, 46, 38, 30, 22, 14, 6,
                                  64, 56, 48, 40, 32, 24, 16, 8,
                                  57, 49, 41, 33, 25, 17, 9, 1,
                                  59, 51, 43, 35, 27, 19, 11, 3,
                                  61, 53, 45, 37, 29, 21, 13, 5,
                                  63, 55, 47, 39, 31, 23, 15, 7};

//BangmorongDbox
const int bangmorongdbox[48] = {32, 1, 2, 3, 4, 5, 4, 5,
                                6, 7, 8, 9, 8, 9, 10, 11,
                                12, 13, 12, 13, 14, 15, 16, 17,
                                16, 17, 18, 19, 20, 21, 20, 21,
                                22, 23, 24, 25, 24, 25, 26, 27,
                                28, 29, 28, 29, 30, 31, 32, 1};

//Banghoanvithang
const int banghoanvithang[32] = {16, 7, 20, 21,
                                 29, 12, 28, 17,
                                 1, 15, 23, 26,
                                 5, 18, 31, 10,
                                 2, 8, 24, 14,
                                 32, 27, 3, 9,
                                 19, 13, 30, 6,
                                 22, 11, 4, 25};

//BangSbox
const int bangsbox[8][4][16] = {
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}
};

//Banghoanvicuoi
const int banghoanvicuoi[64] = {40, 8, 48, 16, 56, 24, 64, 32,
                                39, 7, 47, 15, 55, 23, 63, 31,
                                38, 6, 46, 14, 54, 22, 62, 30,
                                37, 5, 45, 13, 53, 21, 61, 29,
                                36, 4, 44, 12, 52, 20, 60, 28,
                                35, 3, 43, 11, 51, 19, 59, 27,
                                34, 2, 42, 10, 50, 18, 58, 26,
                                33, 1, 41, 9, 49, 17, 57, 25};

//Hamnhapdulieu
void nhapDuLieu(string& vanbangoc, string& khoa) {
    cout << "Nhap van ban goc(16 ky tu): ";
    cin >> vanbangoc;
    bool hople = false;
    while (!hople) {
        if (vanbangoc.length() != 16) {
            cout << "Du lieu khong hop le!\nVui long nhap 16 ky tu thap luc phan: ";
            cin >> vanbangoc;
            continue;
        }
        hople = true;
        for (int i = 0; i < vanbangoc.length(); i++) {
            char c = vanbangoc[i];
            if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) || c == ' ' || c == '\t') {
                hople = false;
                break;
            }
        }
        if (!hople) {
            cout << "Du lieu khong hop le!\nVui long nhap 16 ky tu thap luc phan: ";
            cin >> vanbangoc;
        }
    }
    for (int i = 0; i < vanbangoc.length(); i++) {
        vanbangoc[i] = toupper(vanbangoc[i]);
    }

    cout << "Nhap khoa(16 ky tu): ";
    cin >> khoa;
    hople = false;
    while (!hople) {
        if (khoa.length() != 16) {
            cout << "Du lieu khong hop le!\nVui long nhap 16 ky tu thap luc phan: ";
            cin >> khoa;
            continue;
        }
        hople = true;
        for (int i = 0; i < khoa.length(); i++) {
            char c = khoa[i];
            if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) || c == ' ' || c == '\t') {
                hople = false;
                break;
            }
        }
        if (!hople) {
            cout << "Du lieu khong hop le!\nVui long nhap 16 ky tu thap luc phan: ";
            cin >> khoa;
        }
    }
    for (int i = 0; i < khoa.length(); i++) {
        khoa[i] = toupper(khoa[i]);
    }
}

//Hamxuatketqua
void xuatKetQua(const string& vanbanmahoa, const string& vanbangoc) {
    cout << "\nKetquamahoa\n";
    cout << "Vanbanmahoa: " << vanbanmahoa << endl;
    cout << "\nKetquagiaima\n";
    cout << "Vanbangoc: " << vanbangoc << endl;
}

//HammahoaDES
string maHoa(string vanbangoc, const string rkb[], const string rk[]) {
    vanbangoc = chuyenHe16SangNhiPhan(vanbangoc);

    //Hoanvibandau
    vanbangoc = hoanVi(vanbangoc, banghoanvibandau, 64);
    cout << "Sauhoanvibandau: " << chuyenNhiPhanSangHe16(vanbangoc) << endl;

    //Chiadoi
    string phaitrai = vanbangoc.substr(0, 32);
    string phaiphai = vanbangoc.substr(32, 64);

    for (int i = 0; i < 16; i++) {
        //MorongDbox
        string phaiphaimorong = hoanVi(phaiphai, bangmorongdbox, 48);

        //XORvoikhoavong
        string xor_x = tinhXor(phaiphaimorong, rkb[i]);

        //ThaythebangSbox
        string sbox_str = "";
        for (int j = 0; j < 8; j++) {
            int row = chuyenNhiPhanSangThapPhan(xor_x[j * 6] + string(1, xor_x[j * 6 + 5]));
            int col = chuyenNhiPhanSangThapPhan(xor_x.substr(j * 6 + 1, 4));
            int val = bangsbox[j][row][col];
            sbox_str += chuyenThapPhanSangNhiPhan(val);
        }

        //Hoanvithang
        sbox_str = hoanVi(sbox_str, banghoanvithang, 32);

        //XORvoinua trai
        string ketqua = tinhXor(phaitrai, sbox_str);
        phaitrai = ketqua;

        //Hoandoi
        if (i != 15) {
            string temp = phaitrai;
            phaitrai = phaiphai;
            phaiphai = temp;
        }
        cout << "Vong " << i + 1 << " " << chuyenNhiPhanSangHe16(phaitrai) << " " << chuyenNhiPhanSangHe16(phaiphai) << " " << rk[i] << endl;
    }

    //Kethop
    string kethop = phaitrai + phaiphai;

    //Hoanvicuoi
    string vanbanmahoa = hoanVi(kethop, banghoanvicuoi, 64);
    return vanbanmahoa;
}

int main() {
    string vanbangoc, khoa;
    
    //Nhapvanbangocvakhoa
    nhapDuLieu(vanbangoc, khoa);

    //Taokhoa
    khoa = chuyenHe16SangNhiPhan(khoa);

    //Bangbobitchanle
    const int bangbobitchanle[56] = {57, 49, 41, 33, 25, 17, 9,
                                     1, 58, 50, 42, 34, 26, 18,
                                     10, 2, 59, 51, 43, 35, 27,
                                     19, 11, 3, 60, 52, 44, 36,
                                     63, 55, 47, 39, 31, 23, 15,
                                     7, 62, 54, 46, 38, 30, 22,
                                     14, 6, 61, 53, 45, 37, 29,
                                     21, 13, 5, 28, 20, 12, 4};

    //Laykhoa56bit
    khoa = hoanVi(khoa, bangbobitchanle, 56);

    //Bangsolandi bit
    const int bangsldichbit[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    //Bangnenkhoa
    const int bangnenkhoa[48] = {14, 17, 11, 24, 1, 5,
                                 3, 28, 15, 6, 21, 10,
                                 23, 19, 12, 4, 26, 8,
                                 16, 7, 27, 20, 13, 2,
                                 41, 52, 31, 37, 47, 55,
                                 30, 40, 51, 45, 33, 48,
                                 44, 49, 39, 56, 34, 53,
                                 46, 42, 50, 36, 29, 32};

    //Chiadoi
    string phaitrai = khoa.substr(0, 28);
    string phaiphai = khoa.substr(28, 56);

    string rkb[16], rk[16];
    for (int i = 0; i < 16; i++) {
        //Dichbit
        phaitrai = dichTrai(phaitrai, bangsldichbit[i]);
        phaiphai = dichTrai(phaiphai, bangsldichbit[i]);

        //Kethop
        string kethopchuoi = phaitrai + phaiphai;

        //Nenkhoa
        string khoavong = hoanVi(kethopchuoi, bangnenkhoa, 48);

        rkb[i] = khoavong;
        rk[i] = chuyenNhiPhanSangHe16(khoavong);
    }

    //Mahoa
    cout << "\nMahoa\n";
    string vanbanmahoa = chuyenNhiPhanSangHe16(maHoa(vanbangoc, rkb, rk));

    //Giaima
    cout << "\nGiaima\n";
    string rkb_dao[16], rk_dao[16];
    for (int i = 0; i < 16; i++) {
        rkb_dao[i] = rkb[15 - i];
        rk_dao[i] = rk[15 - i];
    }
    string vanban = chuyenNhiPhanSangHe16(maHoa(vanbanmahoa, rkb_dao, rk_dao));

    //Xuatketqua
    xuatKetQua(vanbanmahoa, vanban);

    return 0;
}
