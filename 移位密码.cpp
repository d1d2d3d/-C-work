//��λ����
//�����������������Сд���������Ϊ��д���������������Сд�����ΪСд��
#include <iostream>
using namespace std;
#define max 100//����������ַ���
int tag;//���ܱ�־λ�����ܻ��߼���
char ming[max];
char mi[max];
//string test = "meet me after the party";//��������
int main()
{
    while (1) {
        // ming = { 0 };
        // mi = { 0 };//��ʼ��
        cout << "ѡ����: ����0/����1:";
        cin >> tag;
        int i, n, k;
        char c;
        if (tag == 0)//����y=x+k(mod26)
        {
            cout << "�ƶ�λ����";
            cin >> k;
            cout << "�������ģ�";
            //cin >> ming;
            fflush(stdin);//�������һ������Ļس���
            fgets(ming, sizeof(ming), stdin);//fgets ʵ�ֿ���������ո�
            cout << "���ģ�";
            i = 0;
            while (ming[i] != '\0')
            {
                if (ming[i] >= 'a' && ming[i] <= 'z')
                {
                    mi[i] = (ming[i] - 'a' + k) % 26 + 'A';//����a���ӡ�a��ʹ��ASCLL��ʵ��ӳ�䣬����������
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
        else if (tag == 1)//����,�������ΪСд
        {
            cout << "���������ģ�";
            fflush(stdin);//�������һ������Ļس���
            fgets(mi, sizeof(mi), stdin);//fgets ʵ�ֿ���������ո�
            cout << endl;
            cout << "��26����λ������һ��  ,�˹�ʶ��������ľ���:"
                << endl;
            cout << "��0λ��25λ�Ľ����"
                << endl;
            for (int j = 0; j < 26; j++)
            {
                i = 0;
                while (mi[i] != '\0')
                {
                    if (mi[i] >= 'a' && mi[i] <= 'z')
                    {
                        ming[i] = (mi[i] - 'a' + (26 - j)) % 26 + 'a';//����a���ӡ�a��ʹ��ASCLL��ʵ��ӳ��
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
            cout << "�������"
                << endl;
            break;
        }

    }
    system("pause");
}

