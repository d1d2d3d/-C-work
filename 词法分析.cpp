/*测试数据
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
int n = 1;//行号
int k = 0;
//关键字 
string key[6] = { "main","int","char","if","else","while" };//关键字
int key_n[6] = { 1,2,3,4,5,6 };//关键字对应种别码
// 专用符号
string symbol[17] = { "=","+","-","*","/","(",")","{","}",",",";",">","<",">=","<=","==","!=" };//专用符号
int symbolNum[17] = { 21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37 };//专用符号对应种别码
char symbol_1[13] = { '=','+','-','*','/','(',')','{','}',',',';','>','<' };
int issymbol(char ch);//检验是否为专用符号
int  lookup_key(char ch[]);//在关键字表中查找,找到返回对应类别码，没找到返回0；
int  lookup_sym(char ch[]);//在z专用表表中查找,找到返回对应类别码，没找到返回0；
void GETCHAR(FILE* fp);//词法分析函数
void out(int c, char* val, FILE* f)//因为时后面加的写入文件，所以输出显得很麻烦
{
    cout << '(' << c << ',' << val << ')' << "  ";
    fprintf(f, "%d,%d,%s      ", n, c, val);
}
char ch;

int issymbol(char ch)//检验是否为专用符号
{
    for (int i = 0; i < 13; i++)
    {
        if (symbol_1[i] == ch)
            return 1;
    }
    return 0;
}
int  lookup_key(char ch[])//在关键字表中查找,找到返回对应类别码，没找到返回0；
{
    for (int i = 0; i < 6; i++)
    {
        if (key[i] == ch)
            return i + 1;
    }
    return 0;
}
int  lookup_sym(char ch[])//在专用符号表中查找,找到返回对应类别码，没找到返回0；
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
    int c;//标识
    int i = 0;
    int j = 0;//单词数
    char* TOKEN = new char;//存每次取出的单词
    ch = fgetc(fp);
    if (ch == EOF)
    {
        cout << endl << "程序读取完毕"
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

    //第一个是数字,则只能为数字
    else if ('0' <= ch && ch <= '9')
    {
        TOKEN[0] = ch;     i = 1;
        while (1) {
            ch = fgetc(fp);
            if ('0' <= ch && ch <= '9')//数字
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
    //第一个是字母
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
    //运算码
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
            << ch << "  ";//vscode 格式化代码问题这里只能放在两行
        fputs("error", f);
        fputc(ch, f);
        for (int i = 0;i < 3;i++)
            fputc(32, f);

    }

    if (ch == EOF)
    {
        cout << endl << "程序读取完毕\n";
        return;
    }
}

int main()
{
    FILE* fp;
    FILE* f;
    fopen_s(&fp, "F:\\c_1.txt", "r");
    fopen_s(&f, "F:\\c.txt", "w");
    cout << "按下回车获取二元组";
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
