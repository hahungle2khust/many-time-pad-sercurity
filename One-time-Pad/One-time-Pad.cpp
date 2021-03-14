#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std; 

//Đổi Hex sang Bin
string HexToBin(string hexdec)
{
    long int i = 0;
    string binary = "\0";

    while (hexdec[i]) {

        switch (hexdec[i]) {
        case '0':
            binary += "0000";
            break;
        case '1':
            binary += "0001";
            break;
        case '2':
            binary += "0010";
            break;
        case '3':
            binary += "0011";
            break;
        case '4':
            binary += "0100";
            break;
        case '5':
            binary += "0101";
            break;
        case '6':
            binary += "0110";
            break;
        case '7':
            binary += "0111";
            break;
        case '8':
            binary += "1000";
            break;
        case '9':
            binary += "1001";
            break;
        case 'A':
        case 'a':
            binary += "1010";
            break;
        case 'B':
        case 'b':
            binary += "1011";
            break;
        case 'C':
        case 'c':
            binary += "1100";
            break;
        case 'D':
        case 'd':
            binary += "1101";
            break;
        case 'E':
        case 'e':
            binary += "1110";
            break;
        case 'F':
        case 'f':
            binary += "1111";
            break;
        default:
            cout << "\nInvalid hexadecimal digit "
                << hexdec[i];
        }
        i++;        
    }
    return binary;
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

// thêm các ký tự 0 vào trc xâu ngắn hơn
string addzero(string s1, string s2) {
    string s = "\0";
    int n = s1.length() - s2.length();
    for (int i = 0; i < n; i++) {
        s += "0";
    }
    return s + s2;
}

//thực hiện phép xor 2 xâu
string xoring(string a, string b) {
    string ans = "";

    if (a.length() > b.length())
        b = addzero(a, b);
    else
        a = addzero(b, a);

    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] == b[i])
            ans += "0";
        else
            ans += "1";
    }
    return ans;
}

//xor 2 mảng:
void xorArray(int a[], int b[], int c[], int lena, int lenb) {
    if (lena < lenb) {
        for (int i = 0; i < lena; i++)
        {
            c[i] = a[i] ^ b[i];
        }
    }
    else
    {
        for (int i = 0; i < lenb; i++)
        {
            c[i] = a[i] ^ b[i];
        }
    }
}

//kiểm tra ký tự có nghĩa
bool checkAlp(int dec) {
    if ((dec >= 65 && dec <= 90) || (dec >= 97 && dec <= 122) || dec == 0)
    {
        return true;
    }
    else return false;
}

//in ra thứ tự của ký tự có nghĩa
void idxAlp(int rs[], int idx[], int *k ,int len) 
{
    for (int i = 0; i < len; i++)
    {
        /*cout << rs[0][1][i];
        printf(": %c\n", rs[0][1][i]);*/
        if (checkAlp(rs[i]) == true) {
            idx[*k] = i;
            (*k) += 1;
        }
    }
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

//void output(string path, int **idx, int len[], int i) {
//    ofstream text(path);
//    for (int j = 1; j < 11; j++)
//    {
//        for (int k = 0; k < len[j]; k++)
//        {
//            text << idx[j][k] << " ";
//        }
//        text << endl;
//    }
//    text.close();
//}

int main()
{   
    string xau[11] = { input("ma1.txt"), input("ma2.txt"), input("ma3.txt"),
                       input("ma4.txt"), input("ma5.txt"), input("ma6.txt"),
                       input("ma7.txt"), input("ma8.txt"), input("ma9.txt"),
                       input("ma10.txt"), input("ma11.txt") 
    };

    int dec[11][1000];

    int rs[11][11][1000];

    int k_idx[11][11] = { 0 };
    int idxAlpha[11][11][1000];

    //int spa_idx0[1000];

    //đổi tất cả các mã từ hex sang dec
    for (int i = 0; i < 11; i++)
    {
        convert(xau[i], dec[i]);
    }
    
    //xor lần lượt tất cả các mã với nhau (55 kết quả) và lấy ra thứ tự của các ký tự có nghĩa
    for (int i = 0; i < 10; i++)
    {
        for (int j = i+1; j < 11; j++)
        {
            xorArray(dec[i], dec[j], rs[i][j], xau[i].length() / 2, xau[j].length() / 2);

            if (xau[i].length() < xau[j].length())
            {
                idxAlp(rs[i][j], idxAlpha[i][j], &k_idx[i][j], xau[i].length() / 2);
            }
            else
            {
                idxAlp(rs[i][j], idxAlpha[i][j], &k_idx[i][j], xau[j].length() / 2);
            }
        }
    }

    //in các output ra các file txt: index các vị trí có nghĩa
    ofstream idx ("idx0.txt");
    for (int j = 1; j < 11; j++)
    {
        for (int k = 0; k < k_idx[0][j]; k++)
        {
            idx << idxAlpha[0][j][k] << " ";
        }
        idx << endl;
    }
    idx.close();

    ofstream idx1("idx1.txt");

    for (int k = 0; k < k_idx[0][1]; k++)
    {
        idx1 << idxAlpha[0][1][k] << " ";
    }
    idx1 << endl;
    for (int j = 2; j < 11; j++)
    {

        for (int k = 0; k < k_idx[1][j]; k++)
        {
            idx1 << idxAlpha[1][j][k] << " ";
        }
        idx1 << endl;
    }
    idx1.close();

    ofstream idx2("idx2.txt");
    for (int j = 0; j < 2; j++)
    {
        for (int k = 0; k < k_idx[j][2]; k++)
        {
            idx2 << idxAlpha[j][2][k] << " ";
        }
        idx2 << endl;
    }
      
    for (int j = 3; j < 11; j++)
    {
        for (int k = 0; k < k_idx[2][j]; k++)
        {
            idx2 << idxAlpha[2][j][k] << " ";
        }
        idx2 << endl;
    }
    idx2.close();

    ofstream idx3("idx3.txt");
    for (int j = 0; j < 3; j++)
    {
        for (int k = 0; k < k_idx[j][3]; k++)
        {
            idx3 << idxAlpha[j][3][k] << " ";
        }
        idx3 << endl;
    }
    for (int j = 4; j < 11; j++)
    {
        for (int k = 0; k < k_idx[3][j]; k++)
        {
            idx3 << idxAlpha[3][j][k] << " ";
        }
        idx3 << endl;
    }
    idx3.close();

    ofstream idx4("idx4.txt");
    for (int j = 0; j < 4; j++)
    {
        for (int k = 0; k < k_idx[j][4]; k++)
        {
            idx4 << idxAlpha[j][4][k] << " ";
        }
        idx4 << endl;
    }
    for (int j = 5; j < 11; j++)
    {
        for (int k = 0; k < k_idx[4][j]; k++)
        {
            idx4 << idxAlpha[4][j][k] << " ";
        }
        idx4 << endl;
    }
    idx4.close();

    ofstream idx5("idx5.txt");
    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < k_idx[j][5]; k++)
        {
            idx5 << idxAlpha[j][5][k] << " ";
        }
        idx5 << endl;
    }
    for (int j = 6; j < 11; j++)
    {
        for (int k = 0; k < k_idx[5][j]; k++)
        {
            idx5 << idxAlpha[5][j][k] << " ";
        }
        idx5 << endl;
    }
    idx5.close();

    ofstream idx6("idx6.txt");
    for (int j = 0; j < 6; j++)
    {
        for (int k = 0; k < k_idx[j][6]; k++)
        {
            idx6 << idxAlpha[j][6][k] << " ";
        }
        idx6 << endl;
    }
    for (int j = 7; j < 11; j++)
    {
        for (int k = 0; k < k_idx[6][j]; k++)
        {
            idx6 << idxAlpha[6][j][k] << " ";
        }
        idx6 << endl;
    }
    idx6.close();

    ofstream idx7("idx7.txt");
    for (int j = 0; j < 7; j++)
    {
        for (int k = 0; k < k_idx[j][7]; k++)
        {
            idx7 << idxAlpha[j][7][k] << " ";
        }
        idx7 << endl;
    }
    for (int j = 8; j < 11; j++)
    {
        for (int k = 0; k < k_idx[7][j]; k++)
        {
            idx7 << idxAlpha[7][j][k] << " ";
        }
        idx7 << endl;
    }
    idx7.close();

    ofstream idx8("idx8.txt");
    for (int j = 0; j < 8; j++)
    {
        for (int k = 0; k < k_idx[j][8]; k++)
        {
            idx8 << idxAlpha[j][8][k] << " ";
        }
        idx8 << endl;
    }
    for (int j = 9; j < 11; j++)
    {
        for (int k = 0; k < k_idx[8][j]; k++)
        {
            idx8 << idxAlpha[8][j][k] << " ";
        }
        idx8 << endl;
    }
    idx8.close();

    ofstream idx9("idx9.txt");
    for (int j = 0; j < 9; j++)
    {
        for (int k = 0; k < k_idx[j][9]; k++)
        {
            idx9 << idxAlpha[j][9][k] << " ";
        }
        idx9 << endl;
    }
    for (int j = 10; j < 11; j++)
    {
        for (int k = 0; k < k_idx[9][j]; k++)
        {
            idx9 << idxAlpha[9][j][k] << " ";
        }
        idx9 << endl;
    }
    idx9.close();

    ofstream idx10("idx10.txt");
    for (int j = 0; j < 10; j++)
    {
        for (int k = 0; k < k_idx[j][10]; k++)
        {
            idx10 << idxAlpha[j][10][k] << " ";
        }
        idx10 << endl;
    }
    idx10.close();

    //in kết quả xor của mật mã với 10 còn lại:
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < xau[10].length()/2; j++)
        {
            printf("%c", rs[i][10][j]);
            /*cout << rs[i][10][j] << " ";*/

        }
        cout << endl<<"-------------------------------------------"<<endl;
    }

    return 0;
}