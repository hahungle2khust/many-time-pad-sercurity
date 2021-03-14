#include <iostream>
#include <fstream>

using namespace std;

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
    
    int dec[11][1000];

    //đổi xâu từ hex sang dec:
    for (int i = 0; i < 11; i++)
    {
        convert(xau[i], dec[i]);
    }
    //in kq:
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < xau[i].length() / 2; j++) {
            cout << dec[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
