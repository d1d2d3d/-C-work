//ά����������ļ��ܣ��������Ϊ��Сд����ԿҪ��Сд���룬��������ô�д
//�������� 
//���� VIGENERECIPHER
//��Կencryption
//����ZVIVLTKMQVTUGI
#include<iostream>
#include<string.h>
#define max 100
char ming[max];
char mi[max];
char key[max];
using namespace std;
void en_code(char ming[], char key[], int ming_length, int key_length)
{//ȥ���ո�
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
        key[i] = key[i] - 'a';//�ַ�����Կת��Ϊ���֣���ʾҪ��λ
    }
    for (int i = 0;i < strlen(ming); i = i + key_length)//�����ļ��϶�Ӧ��ת�������Կֵ��ʾ��λ
    {
        for (int j = 0;j < key_length;j++)
        {
            if (ming[i + j] > 'a' && ming[i + j] < 'z')//Сд
                mi[i + j] = (ming[i + j] - 'a' + key[j]) % 26 + 'A';
            else if (ming[i + j] > 'A' && ming[i + j] < 'Z')//��д
                mi[i + j] = (ming[i + j] - 'A' + key[j]) % 26 + 'A';

        }

    }
    cout << "����Ϊ��";
    cout << mi;
    cout << endl;
}
int main()
{
    int f[16];
    int i, c, a;
    int length;
    cout << "���ģ�";
    fflush(stdin);//�������һ������Ļس���
    fgets(ming, sizeof(ming), stdin);//���ܿո�����;
    ming[strlen(ming) - 1] = '\0';//ȥ�������һ���س���\n
    cout << "��Կ:";
    cin >> key;
    en_code(ming, key, strlen(ming), strlen(key));
    system("pause");

}
