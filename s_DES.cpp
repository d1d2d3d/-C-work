// S_DES����ʵ��.cpp 
#include <iostream>
using namespace std;
void _corl_(int* l) //�������������СȫΪ5
{
    int x;
    x = l[0];
    for (int i = 1; i < 5; i++)
        l[i - 1] = l[i];
    l[4] = x;
}
int* P(int x[], int p[], int length) //������û����飬�Լ��û���
{
    int* x_p = (int*)malloc(length * sizeof(int));
    for (int i = 0; i < length; i++)
    {
        x_p[i] = x[(p[i] - 1)];
    }
    return x_p;
}
void key_c(int* K, int* k1, int* k2) //��Կ���ɣ�����8λ���������P10�û�����ѭ����λ��P8�û�
{
    // 1.P10�û�3��5,2,7,4,10,1,9,8,6
    int* temp;
    int P10[10] = { 3, 5, 2, 7, 4, 10, 1, 9, 8, 6 };
    temp = P(K, P10, 10);
    //��ѭ����һλ
    int l[5], r[5];

    for (int i = 0; i < 5; i++)
        l[i] = temp[i], r[i] = temp[i + 5]; //��Ϊ������������
    _corl_(l);
    _corl_(r);
    // P8�û���6,3,7,4,8,5,10,9��
    for (int i = 0; i < 5; i++)
    {
        temp[i] = l[i];
        temp[i + 5] = r[i];
    }
    int P8[8] = { 6, 3, 7, 4, 8, 5, 10, 9 };
    int* k_1 = P(temp, P8, 8);
    for (int i = 0; i < 8; i++)
        k1[i] = k_1[i]; //��Ϊp������ָ�뱻���㣬��for����k1��ֵ
                        //ѭ������λ
    for (int i = 0; i < 2; i++)
    {
        _corl_(l);
        _corl_(r);
    }
    // P8�û�
    for (int i = 0; i < 5; i++)
    {
        temp[i] = l[i];
        temp[i + 5] = r[i];
    }
    int* k_2 = P(temp, P8, 8);
    for (int i = 0; i < 8; i++)
        k2[i] = k_2[i];
    cout << "k1:";
    for (int i = 0; i < 8; i++)
        cout << k1[i];
    cout << endl;
    cout << "k2:";
    for (int i = 0; i < 8; i++)
        cout << k2[i];
    cout << endl;
}

void f(int R[], int K[]) //���ܹ��̵�f����,������E/p��չ�û������s���û���P4�û�
{
    // E/p��չ�û���4,1,2,3,2,3,4,1��
    int* temp;
    int E_P[8] = { 4, 1, 2, 3, 2, 3, 4, 1 };
    temp = P(R, E_P, 8);
    //��λ���
    for (int i = 0; i < 8; i++)
    {
        temp[i] = temp[i] ^ K[i];
    }

    // s��,��λ���룬��λ���s[��_1,_4),(2,

    int l[4], r[4];
    int S0[4][4] = { 1, 0, 2, 3, 2, 3, 0, 1, 0, 1, 3, 2, 3, 2, 1, 0 };
    int S1[4][4] = { 0, 1, 2, 3, 2, 0, 3, 1, 1, 3, 0, 2, 3, 2, 1, 0 };
    for (int i = 0; i < 4; i++)
    {
        l[i] = temp[i], r[i] = temp[i + 4];
    }
    int x1 = S0[(l[0] * 2 + l[3])][(l[1] * 2 + l[2])];
    int x2 = S1[r[0] * 2 + r[3]][r[1] * 2 + r[2]];
    //ת��Ϊ2���Ʋ�����P4�û���2,4,3,1��
    R[0] = x1 / 2;
    R[1] = x1 % 2;
    R[2] = x2 / 2;
    R[3] = x2 % 2;
    int P4[4] = { 2, 4, 3, 1 };
    int* R_1 = P(R, P4, 4);
    for (int i = 0; i < 4; i++)
        R[i] = R_1[i];
}
//���ܣ�
void Decode(int ming_wen[], int k1[], int k2[]) //����,������������ʽ����
//����IP�û���F������ip���û������
{
    // IP�û�
    int* temp = (int*)malloc(sizeof(int) * 8);
    int IP[8] = { 2, 6, 3, 1, 4, 8, 5, 7 };
    temp = P(ming_wen, IP, 8);

    //
    int l0[4], R0[4], r0[4], r1[4], R1[4], l2[4];
    for (int i = 0; i < 4; i++)
        l0[i] = temp[i], r0[i] = temp[i + 4], R0[i] = temp[i + 4];
    f(r0, k2);
    //

    for (int i = 0; i < 4; i++)
    {
        r1[i] = l0[i] ^ r0[i];
        R1[i] = r1[i];
    }

    //
    f(r1, k1);
    for (int i = 0; i < 4; i++)
    {
        l2[i] = R0[i] ^ r1[i];
    }
    //
    //����l2,r1,Ϊip��任�����룻
    for (int i = 0; i < 4; i++)
    {
        temp[i] = l2[i];
        temp[i + 4] = R1[i];
    }
    // ip��任��4,1,3��5,7,2,8,6��
    int IP_ni[8] = { 4, 1, 3, 5, 7, 2, 8, 6 };
    temp = P(temp, IP_ni, 8); // temp��Ϊ���ģ�ת��Ϊ�������
    cout << "����Ϊ:" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << temp[i];
    }
}
//����
void Encode(int ming_wen[], int k1[], int k2[]) //����,������������ʽ����
//����IP�û���F������ip���û������
{

    // IP�û�
    int* temp = (int*)malloc(sizeof(int) * 8);
    int IP[8] = { 2, 6, 3, 1, 4, 8, 5, 7 };
    temp = P(ming_wen, IP, 8);

    //
    int l0[4], R0[4], r0[4], r1[4], R1[4], l2[4];
    for (int i = 0; i < 4; i++)
        l0[i] = temp[i], r0[i] = temp[i + 4], R0[i] = temp[i + 4];
    f(r0, k1);
    //

    for (int i = 0; i < 4; i++)
    {
        r1[i] = l0[i] ^ r0[i];
        R1[i] = r1[i];
    }

    //
    f(r1, k2);
    for (int i = 0; i < 4; i++)
    {
        l2[i] = R0[i] ^ r1[i];
    }
    //
    //����l2,r1,Ϊip��任�����룻
    for (int i = 0; i < 4; i++)
    {
        temp[i] = l2[i];
        temp[i + 4] = R1[i];
    }
    // ip��任��4,1,3��5,7,2,8,6��
    int IP_ni[8] = { 4, 1, 3, 5, 7, 2, 8, 6 };
    temp = P(temp, IP_ni, 8); // temp��Ϊ���ģ�ת��Ϊ�������
    cout << "����Ϊ:" << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << temp[i];
    }
}
int main()
{
    int k[10], k1[8], k2[8];
    while (1)
    {
        cout << "�˵���" << endl;
        cout << "1.����" << endl;
        cout << "2.����" << endl;
        int in;
        cin >> in;
        switch (in)
        {
        case 1:
            printf("����������ԿK:");
            for (int i = 0; i < 10; i++)
                scanf("%1d", &k[i]);
            key_c(k, k1, k2);
            int ming[8];
            printf("����������:");
            for (int i = 0; i < 8; i++)
                scanf("%1d", &ming[i]);
            Encode(ming, k1, k2);
            cout << endl;
            break;
        case 2:
            printf("����������ԿK:");
            for (int i = 0; i < 10; i++)
                scanf("%1d", &k[i]);
            key_c(k, k1, k2);
            printf("����������:");
            int mi[8];
            for (int i = 0; i < 8; i++)
                scanf("%1d", &mi[i]);
            Decode(mi, k1, k2);
            cout << endl;
            break;
        }
    }

    return 0;
}
