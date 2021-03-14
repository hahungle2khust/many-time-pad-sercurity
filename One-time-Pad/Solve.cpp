#include <bits/stdc++.h>
#include <fstream>

using namespace std;

//đếm số ký tự xuất hiện lớn hơn 8 lần
void count(int arr[], int n, int space[], int *k) {
    int b[1000];
    for (int i = 0; i < n; i++)
    {
        int dem = 1;
        if (b[i]) {
            b[i] = 0;
            for (int j = 1+i; j < n; j++)
            {
                if (arr[j] == arr[i]) {
                    dem++;
                    b[j] = 0;
                }
            }
            if (dem >= 8) {
                space[*k] = arr[i];
                (*k) += 1;
            }
        }
    }
}

void input(string path, int arr[], int *k)
{
    fstream idx(path, ios::in);
    int num;

    while (!idx.eof())
    {
        idx >> num;
        arr[*k] = num;
        (*k) += 1;
    }
    idx.close();
}

string input(string path)
{
    fstream matma(path, ios::in);
    string s;

    while (!matma.eof())
    {
        matma >> s;
    }
    matma.close();
    return s;
}

//Đổi từ Hex sang Dec
int HexToDec(string hexVal)
{
    int len = hexVal.length();

    int base = 1;

    int dec_val = 0;

    // Extracting characters as digits from last character 
    for (int i = len - 1; i >= 0; i--)
    {
        // if character lies in '0'-'9', converting  
        // it to integral 0-9 by subtracting 48 from 
        // ASCII value. 
        if (hexVal[i] >= '0' && hexVal[i] <= '9')
        {
            dec_val += (hexVal[i] - 48) * base;

            // incrementing base by power 
            base = base * 16;
        }

        // if character lies in 'A'-'F' , converting  
        // it to integral 10 - 15 by subtracting 55  
        // from ASCII value 
        else if (hexVal[i] >= 'a' && hexVal[i] <= 'f')
        {
            dec_val += (hexVal[i] - 87) * base;

            // incrementing base by power 
            base = base * 16;
        }
    }

    return dec_val;
}

//Đổi từ Hex sang Dec (Với chuỗi Hex có 2n ký tự): lưu các phần tử đã chuyển đổi ấy vào 1 mảng a[]
void convert(string hex, int a[]) {
    int n = hex.length();
    for (int i = 0; i < n; i += 2)
    {
        string temp = "\0";
        temp += hex[i];
        temp += hex[i + 1];
        a[i / 2] = HexToDec(temp);
    }
}


int main() {
    string xau[11] = { input("ma1.txt"), input("ma2.txt"), input("ma3.txt"),
                       input("ma4.txt"), input("ma5.txt"), input("ma6.txt"),
                       input("ma7.txt"), input("ma8.txt"), input("ma9.txt"),
                       input("ma10.txt"), input("ma11.txt")
    };
    int a[11][2000], spx[11][500];
    int dec[11][1000];
    int k[11] = { 0 }, sizeS[11] = { 0 };

    input("idx0.txt", a[0], &k[0]);
    input("idx1.txt", a[1], &k[1]);
    input("idx2.txt", a[2], &k[2]);
    input("idx3.txt", a[3], &k[3]);
    input("idx4.txt", a[4], &k[4]);
    input("idx5.txt", a[5], &k[5]);
    input("idx6.txt", a[6], &k[6]);
    input("idx7.txt", a[7], &k[7]);
    input("idx8.txt", a[8], &k[8]);
    input("idx9.txt", a[9], &k[9]);
    input("idx10.txt", a[10], &k[10]);
    
    //đổi xâu từ hex sang dec:
    for (int i = 0; i < 11; i++)
    {
        convert(xau[i], dec[i]);
    }
    //ghi các index khoảng trắng
    for (int i = 0; i < 11; i++)
    {
        sort(a[i], a[i] + k[i]);
        count(a[i], k[i], spx[i], &sizeS[i]);
        /*for (int j = 0; j < sizeS[i]; j++)
        {
            cout << spx[i][j] << " ";
        }
        cout << endl;*/
    }

    //Tìm các vị trí khoảng trắng để xor
    int key[500];
    int countKey = 0;
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < xau[i].length() / 2; j++) {
            for (int k = 0; k < sizeS[i]; k++) {
                if (j == spx[i][k]) {
                    key[j] = dec[i][j] ^ 32;
                    countKey++;
                    //cout <<j << ": "<< key[j] << endl;
                }
            }
        }
    }

    //in ra bản rõ:
    for (int i = 0; i < xau[10].length()/2; i++)
    {
        printf("%c", dec[10][i] ^ key[i]);
    }

    return 0;
}