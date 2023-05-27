#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
/*全局变量*/
int mSIZE;/*物理块数*/
int pSIZE;/*页面引用串个数*/
static int memery[10] = { 0 };/*物理块中的页号*/
static int page[100] = { 0 };/*页面号引用串*/
static int temp[100][10] = { 0 };/*辅助数组*/
/*置换算法函数*/
void FIFO();
void LRU();
void OPT();
/*辅助函数*/
void Myprint(unsigned int t);
void designBy();
void download();
void mDelay(unsigned int Delay);
/*主函数*/
void main()
{
    int i, k, code;
    system("color 0A");
    designBy();
    printf("┃请按任意键进行初始化操作                          ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf(">>>");
    _getch();
    system("cls");
    system("color 0B");
    printf("请输入物理块的个数(M<=10)：");
    scanf_s("%d", &mSIZE);
    printf("请输入页面号引用串的个数（p<=100）: ");
    scanf_s("%d", &pSIZE);
    puts("请依次输入页面好引用串（连续输入，无需隔开）：");
    for (i = 0; i < pSIZE; i++)
        scanf_s("%1d", &page[i]);
    download();
    system("cls");
    system("color 0E");
    do {
        puts("输入的页面好引用串为：");
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
        printf("* 请选择页面置换算法：\t\t\t          *       \n");
        printf("---------------------------------------------*\n");
        printf("*1.先进先出(FIFO)      2.最近最久未使用(LRU) *\n");
        printf("*3.最佳(OPT)           4.退出                *\n");
        printf("* * * * * * * * * * * * * * * * * * * * * *  *\n");
        printf("请选择操作:[ ]\b\b");
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
            designBy();/*显示设计者信息后推出*/
            printf("┃谢谢使用页面置换算法演示器             正版授权 ㊣┃\n");
            printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
            exit(0);
        default:
            printf("输入错误，请重新输入：");
        }
        printf("请按任意键重新选择置换算法：>>>");
        _getch();
        system("cls");
    } while (code != 4);
    _getch();
}
    /*载入数据*/
    void download()
    {
        int i;
        system("color 0D");
        printf("╔════════════╗\n");
        printf("║正在载入数据，请稍候!!! ║\n");
        printf("╚════════════╝\n");
        printf("Loading...\n");
        printf("                                         O");
        for (i = 0; i < 51; i++)
            printf("\b");
        for (i = 0; i < 50; i++)
        {
            mDelay((pSIZE + mSIZE) / 2);
            printf(">");
        }
        printf("\nFinish.\n 载入成功，请按任意键进入置换算法选择界面；>>>");
        _getch();
    }
    /*设置延迟*/
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


    /*显示设计者信息*/
    void designBy()
    {
        printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
        printf("┃㊣              课题三：页面置换算法            ㊣┃\n");
        printf("┃                学  号：                        ┃\n");
        printf("┃                姓  名:                         ┃\n");
        printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
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
            printf("缺页次数：%d\t\t缺页率：%d/%d\n", t + mSIZE, t + mSIZE, pSIZE);
            printf("置换次数：%d\t\t访问命中率：%d%%\n", t, (pSIZE - (t + mSIZE)) * 100 / pSIZE);
            printf("----------------------------------------\n");
        }
    }
        
        /*计算函数*/
    void compute()
    {
        int i;
        printf("正在进行相关计算，请稍候");
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

            

   /*先进先出页面置换算法*/
    void FIFO()
    {
        int memery[10] = { 0 };
        int time[10] = { 0 }; // 记录进入物理块的时间
        int i, j, k, m;
        int max = 0;       // 记录换出页
        int count = 0;     // 记录置换次数

        for (i = 0; i < mSIZE; i++)
        {
            memery[i] = page[i];
            time[i] = i;
            for (j = 0; j < mSIZE; j++)
                temp[i][j] = memery[j];
        }

        for (i = mSIZE; i < pSIZE; i++)
        {
            /*判断新页面号是否在物理块中*/
            for (j = 0, k = 0; j < mSIZE; j++)
            {
                if (memery[j] != page[i])
                    k++;
            }
            if (k == mSIZE) /*如果不在物理块中*/
            {
                count++;
                /*计算换出页*/
                max = time[0] < time[1] ? 0 : 1;
                for (m = 2; m < mSIZE; m++)
                    if (time[m] < time[max])
                        max = m;
                memery[max] = page[i];
                time[max] = i; /*记录该页进入物理块的时间*/
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

        // 输出引用串和结果
        printf("引用串:\n ");
        for (i = 0; i < pSIZE; i++)
            printf("%d ", page[i]);
        printf("\n");

        printf("结果:\n");
        for (i = 0; i < pSIZE; i++)
        {
            for (j = 0; j < mSIZE; j++)
                printf("%d ", temp[i][j]);
            printf("\n");
        }
    }


    /*最近最久未使用的置换算法*/
    void LRU()
    {
        int memery[10] = { 0 };
        int flag[10] = { 0 }; /*记录页面的访问时间*/
        int i, j, k, m;
        int max = 0; /*记录换出页*/
        int count = 0; /*记录置换次数*/
        /*前 mSIZE 个数直接放入*/
        for (i = 0; i < mSIZE; i++)
        {
            memery[i] = page[i];
            flag[i] = i;
            for (j = 0; j < mSIZE; j++)
                temp[i][j] = memery[j];
        }
        for (i = mSIZE; i < pSIZE; i++)
        {
            /*判断新页面号是否在物理块中*/
            for (j = 0, k = 0; j < mSIZE; j++)
            {
                if (memery[j] != page[i])
                    k++;
                else
                    flag[j] = i; /*刷新该页的访问时间*/
            }
            if (k == mSIZE) /*如果不在物理块中*/
            {
                count++;
                /*计算换出页*/
                max = flag[0] < flag[1] ? 0 : 1;
                for (m = 2; m < mSIZE; m++)
                    if (flag[m] < flag[max])
                        max = m;
                memery[max] = page[i];
                flag[max] = i; /*记录该页的访问时间*/
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

        // 输出引用串和结果
        printf("引用串:\n ");
        for (i = 0; i < pSIZE; i++)
            printf("%d ", page[i]);
        printf("\n");

        printf("结果:\n");
        for (i = 0; i < pSIZE; i++)
        {
            for (j = 0; j < mSIZE; j++)
                printf("%d ", temp[i][j]);
            printf("\n");
        }
    }


    
    /*最佳置换算法*/
    void OPT()
    {
        int memery[10] = { 0 };
        int next[10] = { 0 }; // 记录下一次访问时间
        int i, j, k, l, m;
        int max;            // 记录换出页
        int count = 0;      // 记录置换次数
        int flag = 0;       // 用于标记是否找到合适的置换页

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
                    flag = 1; // 页面已在内存中
                    break;
                }
            }

            if (!flag) // 页面不在内存中
            {
                count++;

                // 获取物理块中各页的下一次访问时间
                for (m = 0; m < mSIZE; m++)
                {
                    for (l = i + 1; l < pSIZE; l++)
                    {
                        if (memery[m] == page[l])
                            break;
                    }
                    next[m] = (l == pSIZE) ? pSIZE : l;
                }

                // 查找换出页
                max = 0;
                for (m = 1; m < mSIZE; m++)
                {
                    if (next[m] > next[max])
                        max = m;
                }

                // 置换页面
                memery[max] = page[i];
            }

            for (j = 0; j < mSIZE; j++)
                temp[i][j] = memery[j];
            flag = 0;
        }

        compute();
        print(count);

        // 输出每个时刻的页面配置
         // 输出引用串和结果
        printf("引用串:\n ");
        for (i = 0; i < pSIZE; i++)
            printf("%d ", page[i]);
        printf("\n");

        printf("结果:\n");
        for (i = 0; i < pSIZE; i++)
        {
            for (j = 0; j < mSIZE; j++)
                printf("%d ", temp[i][j]);
            printf("\n");
        }
    }
