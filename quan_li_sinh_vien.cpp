#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>
#include <map>


using namespace std;

struct sinhvien{
    string name,ID;
    float diem,GPA;
    int somon;
};
struct thoikb{
    string monhoc , phong;
    int tiet;
    int thu;
};

// ham tao lich hoc ngau nhien
void lich(vector <thoikb>& tk_list){
     vector <string> monhoc = {"giaitich" , "VLBD" ,"VL2","LTHDT","PBL","AnhVanB1"};
     srand(time(0));
     tk_list.clear();
     for(int i = 0;i< monhoc.size();i++){
        thoikb tk;
        tk.monhoc = monhoc[i] ;
        tk.phong = rand() % 100 + 1;
        tk.thu = rand() % 8 + 2;
        tk.tiet = rand() % 14 + 1;
        tk_list.push_back(tk);
     }
     //hien thi thoi khoa bieu
     cout <<"thoi khoa bieu cua sinh vien: " << endl;
     for(auto &tk : tk_list){
        cout << "mon hoc: " << tk.monhoc 
             << "tiet: " << tk.tiet
             << "thu: " << tk.thu 
             << "phong: " << tk.phong << endl;
     }
}
// ham them sinh vien
void themsv(vector <sinhvien>& s){
     sinhvien sv;
     cout << "nhap ma sinh vien: " ;
     getline(cin,sv.ID) ;
     cin.ignore();
     cout << "nhap ten sinh vien: " ;
     getline(cin,sv.name);
     cin.ignore();
     s.push_back(sv); 
}
//hien thi danh sach sinh vien
void show(const vector <sinhvien>& s){
    cout << "danh sach sinh vien: " << endl;
    for(const auto &sv : s){
     cout << "ma sinh vien: " << sv.ID << endl;
     cout << "ten sinh vien: " << sv.name << endl;
     cout << "diem sinh vien: " << sv.diem << endl;
     cout << "GPA: " << sv.GPA << endl;
    }
}
// ham nhap diem sinh vien 
void nhapdiem(vector <sinhvien>& s){
     for(auto &sv : s){
       cout << "nhap diem cho sinh vien: " << endl;
       cin >> sv.somon;
       if(sv.somon <= 0){
          cout << "so mon phai > 0" << endl;
          return;
       }
       float tong = 0;
       float diem_mon;
      for(int i = 0;i<sv.somon;i++){
         cout << "nhap diem mon thu " << i+1 ;
         cin >> diem_mon ;
         tong += diem_mon;
      }
      sv.diem = tong;
      sv.GPA = sv.diem / sv.somon ;
      cout << "GPA cua sinh vien la: " << sv.GPA << endl;
     }
}
// ham luu danh sach vao file
void savestudents(vector <sinhvien>& sv, const string& filename){
   fstream sfile;
   sfile.open("luu_file.txt",ios::out|ios::app);
   for(auto &sv_item : sv){
      sfile << sv_item.name << "," << sv_item.ID << "," << sv_item.GPA << endl;
   }
   sfile.close();
   cout << "da luu vao file!" << filename << endl;
}
// doc danh sach tu file
void readstudents(vector<sinhvien>& sv, const string& filename){
   fstream infile;
   infile.open("danh_sach.txt" , ios::in);
   if(!infile){
       cout << "khong mo duoc file!" << endl;
       return;
   }
   sv.clear();
   string line;
   while(getline(infile, line)){
       stringstream ss(line);
       string name, id, gpa_str;
       getline(ss, name, ',');
       getline(ss, id, ',');
       getline(ss, gpa_str);

       sinhvien sv_temp;
       sv_temp.name = name;
       sv_temp.ID = id;
       sv_temp.GPA = stof(gpa_str);
       sv.push_back(sv_temp);
   }
   infile.close();
   cout << "Da doc file thanh cong!" << endl;
}

// xep loai sinh vien 
void arrange(vector <sinhvien>& sv_list){
    for(auto &sv : sv_list){
      if(sv.GPA >= 9.5){
         cout << "xep loai xuat sac: " << sv.name << " " << sv.GPA << endl;
      }
      else if(sv.GPA < 9.5 && sv.GPA >= 8.5){
         cout << "xep loai gioi: " << sv.name << " " << sv.GPA << endl;
      }
      else if(sv.GPA < 8.5 && sv.GPA >= 7){
         cout << "xep loai kha: " << sv.name << " " << sv.GPA << endl;
      }
      else {
         cout << "xep loai yeu: " << sv.name << " " << sv.GPA << endl;
      }
   }
}
// tim sinh vien 
void lookfor(const vector <sinhvien>& sv ){
    string Name;
    cout << "nhap ten can tim: " ;
    cin.ignore();
    getline(cin,Name);
    bool found = false ;
    for(const auto &s : sv){
      if(Name == s.name){
         cout <<"tim thay ten: " << s.name << "GPA: " << s.ID << endl;
         found = true;
      }
    }
    if(!found){
      cout <<"khong tim thay sinh vien!"<< endl;
    }
}
  int main() {
    vector<sinhvien> s;
    int choice;
    do {
        cout << "lua chon: " << endl;
        cout << "0. thoat chuong trinh " << endl;
        cout << "1. them sinh vien " << endl;
        cout << "2. hien thi danh sach sinh vien " << endl;
        cout << "3. xep loai sinh vien " << endl;
        cout << "4. luu danh sach sinh vien vao file " << endl;
        cout << "5. doc danh sach tu file " << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;     
        cin.ignore(); 
        switch (choice) {
            case 1:
                themsv(s);
                break;
            case 2:
                show(s);
                break;
            case 3:
                arrange(s);
                break;
            case 4:
                savestudents(s, "luu_file.txt");
                break;
            case 5:
                readstudents(s, "danh_sach.txt");
                break;
            case 0:
                cout << "thoat chuong trinh!" << endl;
                break;
            default:
                cout << "lua chon khong hop le!" << endl;
        }
    } while (choice != 0);
    return 0;
}
