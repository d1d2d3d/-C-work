/*��������
else if ('0' <= ch1 && ch1 <= '9')
    {
        TOKEN[0] = ch;     i = 1;
        while (1) {
            ch1 = fgetc(fp) ;
            if ('0' <= ch1 && ch1 <= '9')
            {
                TOKEN[i] = ch1;
                i++;
            }
    }
*/
#include <iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max_len 15
#define ID 10
#define NUM 20

#define MAX 100
using namespace std;
int n = 1;//�к�
int k = 0;
//�ؼ��� 
string key[6] = { "main","int","char","if","else","while" };//�ؼ���
int key_n[6] = { 1,2,3,4,5,6 };//�ؼ��ֶ�Ӧ�ֱ���
// ר�÷���
string symbol[17] = { "=","+","-","*","/","(",")","{","}",",",";",">","<",">=","<=","==","!=" };//ר�÷���
int symbolNum[17] = { 21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37 };//ר�÷��Ŷ�Ӧ�ֱ���
char symbol_1[13] = { '=','+','-','*','/','(',')','{','}',',',';','>','<' };
int issymbol(char ch);//�����Ƿ�Ϊר�÷���
int  lookup_key(char ch[]);//�ڹؼ��ֱ��в���,�ҵ����ض�Ӧ����룬û�ҵ�����0��
int  lookup_sym(char ch[]);//��zר�ñ���в���,�ҵ����ض�Ӧ����룬û�ҵ�����0��
void GETCHAR(FILE* fp);//�ʷ���������
void out(int c, char* val, FILE* f)//��Ϊʱ����ӵ�д���ļ�����������Եú��鷳
{
    cout << '(' << c << ',' << val << ')' << "  ";
    fprintf(f, "%d,%d,%s      ", n, c, val);
}
char ch;

int issymbol(char ch)//�����Ƿ�Ϊר�÷���
{
    for (int i = 0; i < 13; i++)
    {
        if (symbol_1[i] == ch)
            return 1;
    }
    return 0;
}
int  lookup_key(char ch[])//�ڹؼ��ֱ��в���,�ҵ����ض�Ӧ����룬û�ҵ�����0��
{
    for (int i = 0; i < 6; i++)
    {
        if (key[i] == ch)
            return i + 1;
    }
    return 0;
}
int  lookup_sym(char ch[])//��ר�÷��ű��в���,�ҵ����ض�Ӧ����룬û�ҵ�����0��
{
    for (int i = 0; i < 17; i++)
    {
        if (symbol[i] == ch)
            return symbolNum[i];
    }
    return 0;
}

void GETCHAR(FILE* fp, FILE* f)
{
    int c;//��ʶ
    int i = 0;
    int j = 0;//������
    char* TOKEN = new char;//��ÿ��ȡ���ĵ���
    ch = fgetc(fp);
    if (ch == EOF)
    {
        cout << endl << "�����ȡ���"
            << endl;
        return;
    }
    if (ch == ' ' || ch == '\t') return;

    if (ch == '\n')
    {
        fputc('\n', f);
        n++;
        cout << endl << endl;
        return;
    }

    //��һ��������,��ֻ��Ϊ����
    else if ('0' <= ch && ch <= '9')
    {
        TOKEN[0] = ch;     i = 1;
        while (1) {
            ch = fgetc(fp);
            if ('0' <= ch && ch <= '9')//����
            {
                TOKEN[i] = ch;
                i++;
            }
            else if (ch == ' ')
            {
                TOKEN[i] = '\0';
                out(NUM, TOKEN, f);
                break;
            }
            else
            {
                out(NUM, TOKEN, f);
                fseek(fp, -1, 1);
                break;
            }
        }
    }
    //��һ������ĸ
    else if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
    {
        TOKEN[0] = ch; i = 1;
        while (1)
        {
            ch = fgetc(fp);
            if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
            {
                TOKEN[i] = ch;
                i++;
            }
            else if ('0' <= ch && ch <= '9')
            {
                TOKEN[i] = ch;
                i++;
            }
            else if (ch == ' ')
            {
                TOKEN[i] = '\0';
                c = lookup_key(TOKEN);
                if (c == 0) out(ID, TOKEN, f);
                else out(c, TOKEN, f);
                break;
            }
            else if (issymbol(ch))
            {
                    TOKEN[i] = '\0';
                c = lookup_key(TOKEN);
                if (c == 0) out(ID, TOKEN, f);
                else out(c, TOKEN, f);
                i = 0;
                TOKEN[i] = ch;
                i++;
                ch = fgetc(fp);
                if (ch == '=')
                {
                    TOKEN[i] = '=';
                    i++;
                }
                else fseek(fp, -1, 1);
                TOKEN[i] = '\0';
                c = lookup_sym(TOKEN);
                out(c, TOKEN, f);
                break;
            }
            else
            {
                TOKEN[i] = '\0';
                c = lookup_key(TOKEN);
                if (c == 0) out(ID, TOKEN, f);
                else out(c, TOKEN, f);
                fseek(fp, -1, 1);
                break;
            }
        }
    }
    //������
    else if (issymbol(ch))
    {
        TOKEN[0] = ch; i = 1;
        while (1)
        {
            ch = fgetc(fp);
            if (ch == '=')
            {
                TOKEN[i] = ch;
                i++;
            }
            else if (ch == ' ')
            {
                break;
            }
            else if (issymbol(ch))
            {
                TOKEN[i] = '\0';
                c = lookup_sym(TOKEN);
                out(c, TOKEN, f);
                i = 0;
                TOKEN[i] = ch;
                i++;
                break;
            }
            else
            {
                fseek(fp, -1, 1);
                break;
            }
        }
        TOKEN[i] = '\0';
        c = lookup_sym(TOKEN);
        out(c, TOKEN, f);
    }
    else
    {
        cout << "error"
            << ch << "  ";//vscode ��ʽ��������������ֻ�ܷ�������
        fputs("error", f);
        fputc(ch, f);
        for (int i = 0;i < 3;i++)
            fputc(32, f);

    }

    if (ch == EOF)
    {
        cout << endl << "�����ȡ���\n";
        return;
    }
}

int main()
{
    FILE* fp;
    FILE* f;
    fopen_s(&fp, "F:\\c_1.txt", "r");
    fopen_s(&f, "F:\\c.txt", "w");
    cout << "���»س���ȡ��Ԫ��";
    getchar();
    while (1) {
        GETCHAR(fp, f);
        if (ch == EOF) break;
    }
    fclose(fp);
    fclose(f);
    system("pause");
    return 0;
}
