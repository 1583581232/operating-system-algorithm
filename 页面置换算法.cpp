#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
/*ȫ�ֱ���*/
int mSIZE;/*�������*/
int pSIZE;/*ҳ�����ô�����*/
static int memery[10] = { 0 };/*������е�ҳ��*/
static int page[100] = { 0 };/*ҳ������ô�*/
static int temp[100][10] = { 0 };/*��������*/
/*�û��㷨����*/
void FIFO();
void LRU();
void OPT();
/*��������*/
void Myprint(unsigned int t);
void designBy();
void download();
void mDelay(unsigned int Delay);
/*������*/
void main()
{
    int i, k, code;
    system("color 0A");
    designBy();
    printf("���밴��������г�ʼ������                          ��\n");
    printf("������������������������������������������������������\n");
    printf(">>>");
    _getch();
    system("cls");
    system("color 0B");
    printf("�����������ĸ���(M<=10)��");
    scanf_s("%d", &mSIZE);
    printf("������ҳ������ô��ĸ�����p<=100��: ");
    scanf_s("%d", &pSIZE);
    puts("����������ҳ������ô����������룬�����������");
    for (i = 0; i < pSIZE; i++)
        scanf_s("%1d", &page[i]);
    download();
    system("cls");
    system("color 0E");
    do {
        puts("�����ҳ������ô�Ϊ��");
        for (int k = 0; k <= (pSIZE - 1) / 20; k++)
        {
            for (i = 20 * k; (i < pSIZE) && (i < 20 * (k + 1)); i++)
            {
                if (((i + 1) % 20 == 0 || (((i + 1) % 20 && (i == pSIZE - 1)))))
                    printf("%d\n", page[i]);
                else
                    printf("%d", page[i]);

            }
        }
        printf("* * * * * * * * * * * * * * * * * * * * * * * \n");
        printf("* ��ѡ��ҳ���û��㷨��\t\t\t          *       \n");
        printf("---------------------------------------------*\n");
        printf("*1.�Ƚ��ȳ�(FIFO)      2.������δʹ��(LRU) *\n");
        printf("*3.���(OPT)           4.�˳�                *\n");
        printf("* * * * * * * * * * * * * * * * * * * * * *  *\n");
        printf("��ѡ�����:[ ]\b\b");
        scanf_s("%d", &code);
        switch (code)
        {
        case 1:
            FIFO();
            break;
        case 2:
            LRU();
            break;
        case 3:
            OPT();
            break;
        case 4:
            system("cls");
            system("color 0A");
            designBy();/*��ʾ�������Ϣ���Ƴ�*/
            printf("��ллʹ��ҳ���û��㷨��ʾ��             ������Ȩ �I��\n");
            printf("������������������������������������������������������\n");
            exit(0);
        default:
            printf("����������������룺");
        }
        printf("�밴���������ѡ���û��㷨��>>>");
        _getch();
        system("cls");
    } while (code != 4);
    _getch();
}
    /*��������*/
    void download()
    {
        int i;
        system("color 0D");
        printf("�X�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
        printf("�U�����������ݣ����Ժ�!!! �U\n");
        printf("�^�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
        printf("Loading...\n");
        printf("                                         O");
        for (i = 0; i < 51; i++)
            printf("\b");
        for (i = 0; i < 50; i++)
        {
            mDelay((pSIZE + mSIZE) / 2);
            printf(">");
        }
        printf("\nFinish.\n ����ɹ����밴����������û��㷨ѡ����棻>>>");
        _getch();
    }
    /*�����ӳ�*/
    void mDelay(unsigned int Delay)
    {
        unsigned int j;
        for (; Delay > 0; Delay--)
        {
            for (int i = 0; i < 124; i++)
            {
                printf("\b");
            }
        }
    }


    /*��ʾ�������Ϣ*/
    void designBy()
    {
        printf("������������������������������������������������������\n");
        printf("���I              ��������ҳ���û��㷨            �I��\n");
        printf("��                ѧ  �ţ�202196124060              ��\n");
        printf("��                ��  ��: ����Ӣ                    ��\n");
        printf("�ǩ���������������������������������������������������\n");
    }
    void print(unsigned int t)
    {
        int i, j, k, l;
        int flag;
        for (k = 0; k <= (pSIZE - 1) / 20; k++)
        {
            for (i = 20 * k; (i < pSIZE) && (i < 20 * (k + 1)); i++)
            {
                if (((i + 1) % 20 == 0 || (((i + 1) % 20 && (i == pSIZE - 1)))))
                {
                    printf("%d\n", page[i]);
                }
                else
                {
                    printf("%d", page[i]);
                }
            }
            for (j = 0; j < mSIZE; j++)
            {
                for (i = 20 * k; (i < mSIZE + 20 * k) && (i < pSIZE); i++)
                {
                    if (i >= j)
                    {
                        printf("|%d|", temp[i][j]);
                    }
                    else
                    {
                        printf("||'");
                    }
                }
                for (i = mSIZE + 20 * k; (i < pSIZE) && (i < 20 * (k + 1)); i++)
                {
                    flag = 0;
                    for (l = 0; l < mSIZE; l++)
                    {
                        if (temp[i][l] == temp[i - 1][l])
                        {
                            flag++;
                        }
                    }
                    if (flag == mSIZE)
                    {
                        printf("  ");
                    }
                    else
                    {
                        printf("|%d|", temp[i][j]);
                    }
                    if (i % 20 != 0)
                    {
                        printf(" ");
                    }
                }
            }
            printf("\n");
            printf("----------------------------------------\n");
            printf("ȱҳ������%d\t\tȱҳ�ʣ�%d/%d\n", t + mSIZE, t + mSIZE, pSIZE);
            printf("�û�������%d\t\t���������ʣ�%d%%\n", t, (pSIZE - (t + mSIZE)) * 100 / pSIZE);
            printf("----------------------------------------\n");
        }
    }
        
        /*���㺯��*/
    void compute()
    {
        int i;
        printf("���ڽ�����ؼ��㣬���Ժ�");
        for (i = 1; i < 20; i++)
        {
            mDelay(15);
            if (i % 4 == 0)
                printf("\b\b\b\b\b\b      \b\b\b\b\b\b");
            else
                printf("......");
        }
        for (i = 0; i++ < 30; printf("\b"));
        for (i = 0; i++ < 30; printf(" "));
        for (i = 0; i++ < 30; printf("\b"));
    }

            

   /*�Ƚ��ȳ�ҳ���û��㷨*/
    void FIFO()
    {
        int memery[10] = { 0 };
        int time[10] = { 0 }; // ��¼����������ʱ��
        int i, j, k, m;
        int max = 0;       // ��¼����ҳ
        int count = 0;     // ��¼�û�����

        for (i = 0; i < mSIZE; i++)
        {
            memery[i] = page[i];
            time[i] = i;
            for (j = 0; j < mSIZE; j++)
                temp[i][j] = memery[j];
        }

        for (i = mSIZE; i < pSIZE; i++)
        {
            /*�ж���ҳ����Ƿ����������*/
            for (j = 0, k = 0; j < mSIZE; j++)
            {
                if (memery[j] != page[i])
                    k++;
            }
            if (k == mSIZE) /*��������������*/
            {
                count++;
                /*���㻻��ҳ*/
                max = time[0] < time[1] ? 0 : 1;
                for (m = 2; m < mSIZE; m++)
                    if (time[m] < time[max])
                        max = m;
                memery[max] = page[i];
                time[max] = i; /*��¼��ҳ����������ʱ��*/
                for (j = 0; j < mSIZE; j++)
                    temp[i][j] = memery[j];
            }
            else
            {
                for (j = 0; j < mSIZE; j++)
                    temp[i][j] = memery[j];
            }
        }

        compute();
        print(count);

        // ������ô��ͽ��
        printf("���ô�:\n ");
        for (i = 0; i < pSIZE; i++)
            printf("%d ", page[i]);
        printf("\n");

        printf("���:\n");
        for (i = 0; i < pSIZE; i++)
        {
            for (j = 0; j < mSIZE; j++)
                printf("%d ", temp[i][j]);
            printf("\n");
        }
    }


    /*������δʹ�õ��û��㷨*/
    void LRU()
    {
        int memery[10] = { 0 };
        int flag[10] = { 0 }; /*��¼ҳ��ķ���ʱ��*/
        int i, j, k, m;
        int max = 0; /*��¼����ҳ*/
        int count = 0; /*��¼�û�����*/
        /*ǰ mSIZE ����ֱ�ӷ���*/
        for (i = 0; i < mSIZE; i++)
        {
            memery[i] = page[i];
            flag[i] = i;
            for (j = 0; j < mSIZE; j++)
                temp[i][j] = memery[j];
        }
        for (i = mSIZE; i < pSIZE; i++)
        {
            /*�ж���ҳ����Ƿ����������*/
            for (j = 0, k = 0; j < mSIZE; j++)
            {
                if (memery[j] != page[i])
                    k++;
                else
                    flag[j] = i; /*ˢ�¸�ҳ�ķ���ʱ��*/
            }
            if (k == mSIZE) /*��������������*/
            {
                count++;
                /*���㻻��ҳ*/
                max = flag[0] < flag[1] ? 0 : 1;
                for (m = 2; m < mSIZE; m++)
                    if (flag[m] < flag[max])
                        max = m;
                memery[max] = page[i];
                flag[max] = i; /*��¼��ҳ�ķ���ʱ��*/
                for (j = 0; j < mSIZE; j++)
                    temp[i][j] = memery[j];
            }
            else
            {
                for (j = 0; j < mSIZE; j++)
                    temp[i][j] = memery[j];
            }
        }
        compute();
        print(count);

        // ������ô��ͽ��
        printf("���ô�:\n ");
        for (i = 0; i < pSIZE; i++)
            printf("%d ", page[i]);
        printf("\n");

        printf("���:\n");
        for (i = 0; i < pSIZE; i++)
        {
            for (j = 0; j < mSIZE; j++)
                printf("%d ", temp[i][j]);
            printf("\n");
        }
    }


    
    /*����û��㷨*/
    void OPT()
    {
        int memery[10] = { 0 };
        int next[10] = { 0 }; // ��¼��һ�η���ʱ��
        int i, j, k, l, m;
        int max;            // ��¼����ҳ
        int count = 0;      // ��¼�û�����
        int flag = 0;       // ���ڱ���Ƿ��ҵ����ʵ��û�ҳ

        for (i = 0; i < mSIZE; i++)
        {
            memery[i] = page[i];
            for (j = 0; j < mSIZE; j++)
                temp[i][j] = memery[j];
        }

        for (i = mSIZE; i < pSIZE; i++)
        {
            for (j = 0; j < mSIZE; j++)
            {
                if (memery[j] == page[i])
                {
                    flag = 1; // ҳ�������ڴ���
                    break;
                }
            }

            if (!flag) // ҳ�治���ڴ���
            {
                count++;

                // ��ȡ������и�ҳ����һ�η���ʱ��
                for (m = 0; m < mSIZE; m++)
                {
                    for (l = i + 1; l < pSIZE; l++)
                    {
                        if (memery[m] == page[l])
                            break;
                    }
                    next[m] = (l == pSIZE) ? pSIZE : l;
                }

                // ���һ���ҳ
                max = 0;
                for (m = 1; m < mSIZE; m++)
                {
                    if (next[m] > next[max])
                        max = m;
                }

                // �û�ҳ��
                memery[max] = page[i];
            }

            for (j = 0; j < mSIZE; j++)
                temp[i][j] = memery[j];
            flag = 0;
        }

        compute();
        print(count);

        // ���ÿ��ʱ�̵�ҳ������
         // ������ô��ͽ��
        printf("���ô�:\n ");
        for (i = 0; i < pSIZE; i++)
            printf("%d ", page[i]);
        printf("\n");

        printf("���:\n");
        for (i = 0; i < pSIZE; i++)
        {
            for (j = 0; j < mSIZE; j++)
                printf("%d ", temp[i][j]);
            printf("\n");
        }
    }
