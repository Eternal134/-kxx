#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{   /*  
     * �˴��Ľṹ���������ô���
     *   һ����ջ�б�ʾ����ͨ����·������ʱ n ��ʾͨ·����һ���ķ���ֵΪ1ʱ��ʾ�²�����2��ʾ�²����ң�
     * 3��ʾ�²����ϣ�4��ʾ�²����£�
     *   �����ڽṹ�������б�ʾ�Թ��������� n ��ʾ�ýڵ��һЩ�����ֵΪ0ʱ��ʾ����ͨ����1��ʾ��ǽ�ڡ�����
     * ����ͨ����2��ʾ�ýڵ��Ѿ��߹���3��ʾ�ýڵ��Ѿ��߹��ҴӴ˽ڵ�ͨ���ǡ���·����
     */
    int x, y, n;               
}Data;


typedef struct StackNode
{   //��ջ�ڵ�����
    Data data;            
    struct StackNode *next;
}StackNode;

StackNode *InitStack()
{   //��ʼ����ջ
    StackNode *S = (StackNode *)malloc(sizeof(StackNode));          //SҲ�ǽṹ�壬��Ҫ����ռ�
    S->next = NULL;
    return S;           //**ע��**����������ջ��β����һ��û��ֵ�Ľڵ㣬��λ��ջ�Ľ�βʱ����Ҫ�ж���һ�ڵ��Ƿ��Ǹÿսڵ�
}

StackNode *Push(StackNode *S, Data data)
{   //��ջѹջ
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    p->data = data;
    p->next = S;
    S = p;
    return S;
}

StackNode *Pop(StackNode *S)
{   //��ջ��ջ
    Data data = S->data;
    StackNode *p = S;
    S = S->next;
    free(p);
    return S;
}

StackNode *Maze(StackNode *S, Data *coord, int m, int n, int flag)
{
    if(!flag)
    {
        S = Push(S, coord[0]);
        coord[0].n = 2;
    }
    
    int a, b;
    
    while (S->data.x != m-1 && S->data.y != n-1)
    {
        //���ߡ����ĵ��nֵ��Ϊ2
        a = S->data.x;
        b = S->data.y;           //a,b��ʾ��ǰջ��Ԫ�ص�����

        if (b > 1 && coord[a*n + b-1].n == 0)
        //������̽
        {
            S->data.n = 1;
         coord[a*n + b-1].n = 2;
            S = Push(S, coord[a*n + b-1]);
            continue;
        }
        if (b < n && coord[a*n + b+1].n == 0)
        //������̽
        {
            S->data.n = 2;
            coord[a*n + b+1].n = 2;
            S = Push(S, coord[a*n + b+1]);
            continue;
        }
        if (a > 1 && coord[(a-1)*n + b].n == 0)
        //������̽
        {
            S->data.n = 3;
            coord[(a-1)*n + b].n = 2;
            S = Push(S, coord[(a-1)*n + b]);
            continue;
        }
        if (a < m && coord[(a+1)*n + b].n == 0)
        //������̽
        {
            S->data.n = 4;
            coord[(a+1)*n + b].n = 2;
            S = Push(S, coord[(a+1)*n + b]);
            continue;
        }
        //�����Χû�п����ߵ�·����ջ�е����ýڵ㲢�Ѹ������n��Ϊ3

        if(S->next->next == NULL)
        {   //����ڵ���Χû��ͨ·���Ҹýڵ����Թ�����ڣ���ʾ���Թ��޽�
            return S;
        }
        S = Pop(S);
        coord[a*n + b].n = 3;
    }//while

    //����һϵ�� if-else �ж����һ�����߷�
    if(S->data.x == 0)
    {   //���x��0����ʾ���ڿ��ϲ�ǽ�ڣ���һ��Ӧ�������ߣ������ж�����
        S->data.n = 3;
    }
    else if(S->data.x == m-1)
    {
        S->data.n = 4;
    }
    if(S->data.y == 0)
    {
        S->data.n = 1;
    }
    else if(S->data.y == n-1)
    {
        S->data.n = 2;
    }
    return S;
}

int OutputPath(StackNode *S)
{
    StackNode *T = InitStack();         //�����������ջS�е�����
    StackNode *p = S;       //�������ѭ������
    while (p->next)
    {   //��ջS�е�Ԫ�ص���ŵ�T��
        T = Push(T, p->data);
        p = p->next;
    }
    
    printf("�Թ���һ��ͨ·Ϊ����Ԫ���ǰ��λ����ʾ���꣬���һλ��������1Ϊ��2Ϊ�ң�3Ϊ�ϣ�4Ϊ�£���\n");
    for (p = T; p->next; p = p->next)
    {   //��T�е�Ԫ���������
        printf("%d %d %d\n",p->data.x + 1, p->data.y + 1, p->data.n);
    }
    return 0;
}

int main()
{   
    StackNode *S = InitStack();
    int m, n, i, j;             //�Թ��Ŀ�Ϊm����Ϊn��i,jΪѭ������
    printf("��������Թ��ĸߺͿ�\n");
    scanf("%d%d",&n,&m);

    Data coord[m][n];           //�ṹ�����飬�����洢�Թ�
    printf("���ڿ�ʼ��������Թ�(0Ϊͨ·��1Ϊ��·�����е�һ��Ԫ��Ϊ�Թ���ڣ��ҳ������Ҳ���²�)��\n");
    //�����Թ���Ϣ
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &coord[i][j].n);
            coord[i][j].x = i;
            coord[i][j].y = j;
        }
    }

    int flag = 0;           //flag�����ж��Ƿ��Ѿ������һ��ͨ·������ǣ�flag��Ϊ1
    while(1)
    {   
        S = Maze(S, *coord, m, n, flag);            //����Թ���һ��ͨ·
        if(S->next->next == NULL && flag)
        {   //���S��ֻ��һ���ڵ����Ѿ������һ��ͨ·�����Թ�û��������
            printf("�Թ��������⣡\n");
            break;
        }
        else if(S->next->next == NULL && !flag)
        {   //���S��ֻ��һ���ڵ���û�������ͨ·��֤�����Թ��޽�
            printf("�Թ��޽⣡\n");
            return 0;
        }
        flag = 1;
        OutputPath(S);              //��������·��

        printf("ͨ·��ʾΪ��\n");
        for(i = 0; i < m; i++)
        {   //��*��ʾͨ·
            for ( j = 0; j < n; j++)
            {
                if(coord[i][j].n == 2)
                {
                    printf("* ");
                }
                else if(coord[i][j].n == 3)
                {
                    printf("0 ");
                }
                else
                {
                    printf("%d ",coord[i][j].n);
                }
        }
        printf("\n");
        }//for
        
        coord[S->data.x][S->data.y].n = 3;              //���ϴ�����ĳ��ڵ�nֵ��Ϊ3
        S = Pop(S);                 //�����ڴ�S��ɾ����׼������һ��ͨ·
    }//while
    return 0;
}