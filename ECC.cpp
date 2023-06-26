//P(X1,Y1);Q(x2,y2)
//x1=x2&&y2=-y1则P+Q=(0,0)
//否则
//x3=k^2-x1-x2
//y3 = k(x1 - x3) - y1
//if P!=Q k=(y2-y1/x2-x1)
//   p=Q  k=(3x1^2+a)/(2y1).a是x^3+ax+b中的a。
//本实例中所有运算都在模11中；
//本题只是简单实现ppt上的例子  (10,9)到{（8,2），（10,2）}的加密解密。
#include <iostream>
using namespace std;

typedef struct point
//点的定义
{
    int x;
    int y;
}point;

int nG[12][2] = { {2,7}, {5,2}  ,{8,3} ,{10,2} ,{3,6},{7,9},{7,2},{3,5},{10,9},{8,8},{5,9},{2,4} };//阶群以数组形式给出
int a = 1;
int b = 6;
int p = 11;//公钥
int key = 7;//私钥
point m;//要发送的消息明文
//m.x=10,m.x=9 ,要发送的消息
point C1;
point C2;//密文
//m.x=10,m.x=9 ,要发送的消息
//int r = 3;//发送A选取的随机数,这个是要自己输入的
//圆锥曲线为a=1 b=6；既Ep=（1,6），一个生成元为2,7；
//大素数P=11，
//B的私钥为7，A要发送的编码为(10,9)
//两点的加法运算 
point add(point p1, point p2)
{//这里的矩阵加法不一定完善，只针对本题
    point P;
    int k;
    int x1 = p1.x;int y1 = p1.y;
    int x2 = p2.x;int y2 = p2.y;//为了对照书上公式
    //不涉及无穷远，只有相同和不想同的相加
    int x3, y3;
    if (p1.x == -1 && p1.y == -1)
    {
        P = p2;
        return P;
    }
    else if (p2.x == -1 && p2.y == -1)
    {
        P = p1;
        return P;
    }//本题好像没有用到
    else if ((x2 == x1) && (y2 == y1))
    {
        //相同点相加
        {
            for (int i = 1; i < 50;i++)
            {
                if ((2 * y1 * i) % 11 == (3 * x1 * x1 + 1) % 11)
                {
                    k = i;
                    break;
                }
            }
        }
    }
    else
    {
        //不同点相加k=(y2-y1/x2-x1)
        for (int i = 1; i < 50;i++)
        {
            if (((y2 - y1 + 11) % 11 == ((x2 - x1 + 11)) * i % 11))//+11是为了防止相减小于0 的情况出现。
            {
                k = i;
                break;
            }
        }
    }
    x3 = ((k * k - x1 - x2) % 11 + 11) % 11;
    y3 = ((k * (x1 - x3) - y1) % 11 + 11) % 11;//防止为负
    P.x = x3;P.y = y3;
    return P;
}

int main()
{
    point O;
    O.x = -1;O.y = -1;
    cout << "题目已给信息信息：\n";
    cout << "公钥:y^2=x^3+x+6(mod11)\n";
    cout << "生成元(2,7)\n";
    cout << "私钥7\n";
    cout << "阶群和阶数也已经以给出";
    for (int i;i < 12;i++)
    {
        cout << nG[i][0] << ',' << nG[i][1] << "   ";
    }
    // cout << "要发送的消息已经编码为(10,9)\n";
    cout << "\n加密和解密都只要求输出点集\n\n\n\n";

    int r;
    cout << "输入明文的编码：";
    cin >> m.x;cin >> m.y;
    // m.x = 10;m.y = 9;// 明文
    cout << "要发送的消息编码为(明文)：";
    cout << '(' << m.x << "," << m.y << ')';
    cout << endl;
    //密钥生成K=k*G，私钥k=7,生成元G=（2,7）都不用自己算
    //K=7G
    point K, K1;
    K.x = nG[key - 1][0];K.y = nG[key - 1][1];
    //K.x = nG[key - 1][0];K.y = nG[key - 1][1];
  //加密C1=m+rK;(10,9)+3(7,2),
//或者按照例字上全部用已给的表去变换查找，但是我觉得那样有太大的偶然性，因为m是9a那一步好像太过偶然。所以还是写了一个简易的圆锥曲线加法。
    //C2=rG,不用自己算
    cout << "请输入随机数1-12(因为是实现ppt这里不采用随机的而是手动输入):";
    cin >> r;
    //阶为11；
    K1 = add(O, K);//1
    for (int i = 1;i < r;i++)
    {
        K1 = add(K1, K);
    }
    C1 = add(m, K1);
    C2.x = nG[r - 1][0];C2.y = nG[r - 1][1];
    printf("密文:rG=(%d,%d),m+rK=(%d,%d)"
        , C2.x, C2.y, C1.x, C1.y);//因为vscode自动格式化的问题这里只能放在两行
    //解密m=C1-kC2
    point mi;
    K1 = add(O, C2);//1
    for (int i = 1;i < key;i++)
    {
        K1 = add(K1, C2);//
    }
    //C1 - mi;(x,y)和（x,-y）是关于椭圆曲线加法互逆的
    K1.y = -K1.y;
    mi = add(C1, K1);
    printf("\n解密后的明文编码为(%d,%d)\n", mi.x, mi.y);
    system("pause");
}