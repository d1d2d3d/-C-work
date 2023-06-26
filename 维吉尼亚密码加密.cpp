//维吉尼亚密码的加密，输入可以为大小写，密钥要求小写输入，输出明文用大写
//测试数据 
//明文 VIGENERECIPHER
//密钥encryption
//密文ZVIVLTKMQVTUGI
#include<iostream>
#include<string.h>
#define max 100
char ming[max];
char mi[max];
char key[max];
using namespace std;
void en_code(char ming[], char key[], int ming_length, int key_length)
{//去除空格
    for (int i = 0;i < ming_length;i++)
    {
        if (ming[i] == ' ')
        {
            for (int j = i;j < ming_length;j++)
            {
                ming[j] = ming[j + 1];
            }

        }
    }
    for (int i = 0;i < key_length;i++)
    {
        key[i] = key[i] - 'a';//字符串密钥转换为数字，表示要几位
    }
    for (int i = 0;i < strlen(ming); i = i + key_length)//对明文加上对应的转化后的密钥值表示移位
    {
        for (int j = 0;j < key_length;j++)
        {
            if (ming[i + j] > 'a' && ming[i + j] < 'z')//小写
                mi[i + j] = (ming[i + j] - 'a' + key[j]) % 26 + 'A';
            else if (ming[i + j] > 'A' && ming[i + j] < 'Z')//大写
                mi[i + j] = (ming[i + j] - 'A' + key[j]) % 26 + 'A';

        }

    }
    cout << "密文为：";
    cout << mi;
    cout << endl;
}
int main()
{
    int f[16];
    int i, c, a;
    int length;
    cout << "明文：";
    fflush(stdin);//清除掉上一个输入的回车符
    fgets(ming, sizeof(ming), stdin);//接受空格输入;
    ming[strlen(ming) - 1] = '\0';//去除掉最后一个回车符\n
    cout << "密钥:";
    cin >> key;
    en_code(ming, key, strlen(ming), strlen(key));
    system("pause");

}
