#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Player
{
    int serial, votes, rank;
    char name[15];
}Player;

Player *InitPlayers(int sum)
{
    Player *players = (Player *)malloc(sum * sizeof(Player));
    printf("�������λѡ�ֵ���ź�������\n");
    int ser, i;
    char name[15];
    Player player;
    for(i = 0; i < sum; i ++)
    {
        scanf("%d", &(players + i)->serial);
        getchar();
        gets((players + i)->name);
        (players + i)->votes = 0;
    }
    return players;
}

void Vote(Player *players)
{
    printf("������ϲ����ѡ�ֵ����ΪTaͶƱ������0��ʾͶƱ����\n");
    int ser = 1;
    while(ser)
    {
        scanf("%d", &ser);
        (players + ser - 1)->votes ++;
    }
}

void SelectSort(Player *players, int sum)
{   //ѡ������
    Player *p;
    Player temp;
    int i, j, max;
    for(i = 0; i < sum; i ++)
    {
        max = i;
        for(j = i + 1; j < sum; j ++)
        {
            if((players + j)->votes > (players + max)->votes)
            {
                max = j;
            }
        }
        temp = *(players + i);
        *(players + i) = *(players + max);
        *(players + max) = temp;
        if(i == 0 || (players + i)->votes != (players + i - 1)->votes)
        {
            (players + i)->rank = i + 1;
        }
        else
        {
            (players + i)->rank = (players + i - 1)->rank;
        }
    }
}

void BubbleSort(Player *players, int sum)
{   //ð������
    int flag = 1, i ,j ,m = sum;
    Player player;
    while ((m > 0) && (flag))
    {
        flag = 0;
        for(j = 0; j <= m; j ++)
            if((players + j)->votes < (players + j + 1)->votes)
            {
                flag = 1;
                player = *(players + j);
                *(players + j) = *(players + j + 1);
                *(players + j + 1) = player;
            }
            -- m;
    }
    for(i = 0; i < sum; i ++)
    {
        if(i == 0 || (players + i)->votes != (players + i - 1)->votes)
        {
            (players + i)->rank = i + 1;
        }
        else
        {
            (players + i)->rank = (players + i - 1)->rank;
        }
    }
}

int Partition(Player *players, int low, int high)
{
    Player player;
    player = *(players + low);
    int vote = player.votes;
    while (low < high)
    {
        while(low < high && (players + high)->votes <= vote)
        {
            high --;
        }
        *(players + low) = *(players + high);
        while(low < high && (players + low)->votes >= vote)
        {
            low ++;
        }
        *(players + high) = *(players + low);
    }
    *(players + low) = player;
    return low;
}

void QuickSort(Player *players, int low, int high)
{   //��������
    int pivotloc;
    if(low < high)
    {
        pivotloc = Partition(players, low, high);
        QuickSort(players, low, pivotloc - 1);
        QuickSort(players, pivotloc + 1, high);
    }
    for(int i = 0; i < high; i ++)
    {
        if(i == 0 || (players + i)->votes != (players + i - 1)->votes)
        {
            (players + i)->rank = i + 1;
        }
        else
        {
            (players + i)->rank = (players + i - 1)->rank;
        }
    }
}

void Print(Player *players, int sum)
{   //���ѡ�ֵ�������Ϣ
    int i;
    printf("ѡ�ֵ�������Ϣ���£�\n");
    for(i = 0; i < sum; i ++)
    {
        switch((players + i)->rank)
        {
            case 1:
                if(i == 0 || (players + i)->rank != (players + i - 1)->rank)
                {
                    printf("�ھ���%d��ѡ��%s\t%dƱ", (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                else
                {
                    printf("\t%d��ѡ��%s\t%dƱ", (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                break;

            case 2:
                if((players + i)->rank != (players + i - 1)->rank)
                {
                    printf("\n�Ǿ���%d��ѡ��%s\t%dƱ", (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                else
                {
                    printf("\t%d��ѡ��%s\t%dƱ", (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                break;

            case 3:
                if((players + i)->rank != (players + i - 1)->rank)
                {
                    printf("\n������%d��ѡ��%s\t%dƱ", (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                else
                {
                    printf("\t%d��ѡ��%s\t%dƱ", (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                break;

            default:
                if((players + i)->rank != (players + i - 1)->rank)
                {
                    printf("\n��%d����%d��ѡ��%s\t%dƱ", (players + i)->rank, (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                else
                {
                    printf("\t%d��ѡ��%s\t%dƱ", (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                break;
        }
    }
}

int main()
{
    Player *players;
    printf("����ѡ�ֵ�������Ϊ��");
    int sum;
    scanf("%d", &sum);
    players = InitPlayers(sum);
    Vote(players);
    int f;
    printf("\nѡ�����򷽷���\n\t1.ѡ������\n\t2.ð������\n\t3.��������\n");
    scanf("%d", &f);
    switch(f)
    {
        case 1:
            SelectSort(players, sum);
            break;

        case 2:
            BubbleSort(players, sum);
            break;

        case 3:
            QuickSort(players, 0, sum);
            break;
    }
    Print(players, sum);
    return 0;
}
