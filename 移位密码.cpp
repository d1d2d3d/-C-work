//移位密码
//加密输入明文任意大小写，加密输出为大写，解密输入任意大小写，输出为小写。
#include <iostream>
using namespace std;
#define max 100//明密文最大字符数
int tag;//功能标志位，解密或者加密
char ming[max];
char mi[max];
//string test = "meet me after the party";//测试数据
int main()
{
    while (1) {
        // ming = { 0 };
        // mi = { 0 };//初始化
        cout << "选择功能: 加密0/解密1:";
        cin >> tag;
        int i, n, k;
        char c;
        if (tag == 0)//加密y=x+k(mod26)
        {
            cout << "移动位数：";
            cin >> k;
            cout << "输入明文：";
            //cin >> ming;
            fflush(stdin);//清除掉上一个输入的回车符
            fgets(ming, sizeof(ming), stdin);//fgets 实现可以正常输空格
            cout << "密文：";
            i = 0;
            while (ming[i] != '\0')
            {
                if (ming[i] >= 'a' && ming[i] <= 'z')
                {
                    mi[i] = (ming[i] - 'a' + k) % 26 + 'A';//减‘a’加‘a’使用ASCLL码实现映射，而不用数组
                }
                if (ming[i] >= 'A' && ming[i] <= 'Z')
                {
                    mi[i] = (ming[i] - 'A' + k) % 26 + 'A';
                }
                if (ming[i] == ' ')
                {
                    mi[i] = ming[i];
                }
                cout << mi[i];
                i++;
            }
            cout << endl;
        }
        else if (tag == 1)//解密,解密输出为小写
        {
            cout << "请输入密文：";
            fflush(stdin);//清除掉上一个输入的回车符
            fgets(mi, sizeof(mi), stdin);//fgets 实现可以正常输空格
            cout << endl;
            cout << "将26个移位都尝试一遍  ,人工识别有意义的句子:"
                << endl;
            cout << "移0位到25位的结果："
                << endl;
            for (int j = 0; j < 26; j++)
            {
                i = 0;
                while (mi[i] != '\0')
                {
                    if (mi[i] >= 'a' && mi[i] <= 'z')
                    {
                        ming[i] = (mi[i] - 'a' + (26 - j)) % 26 + 'a';//减‘a’加‘a’使用ASCLL码实现映射
                    }
                    if (mi[i] >= 'A' && mi[i] <= 'Z')
                    {
                        ming[i] = (mi[i] - 'A' + (26 - j)) % 26 + 'a';
                    }
                    if (mi[i] == ' ')
                    {
                        mi[i] = ming[i];
                    }
                    cout << ming[i];
                    i++;
                }
            }
        }
        else
        {
            cout << "输入错误"
                << endl;
            break;
        }

    }
    system("pause");
}

