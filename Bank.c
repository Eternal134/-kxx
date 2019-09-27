#include<stdio.h>
#include<stdlib.h>

typedef struct 
{
    int begin_time;
    int end_time;
}Cust;

typedef struct QNode
{
    Cust cust;
    struct QNode *next;
}QNode;

typedef struct LQueue
{
    QNode *front;
    QNode *rear;
    int sum;        
}LQueue;

LQueue *InitQueue()
{
    LQueue *Q = (LQueue *)malloc(sizeof(LQueue));
    Q->front = Q->rear = (QNode *)malloc(sizeof(QNode));
    Q->front->next = NULL;
    Q->sum = 0;
    return Q;
}

void EnQueue(LQueue *Q, Cust cust)
{
    QNode *p = (QNode *)malloc(sizeof(QNode));
    p->cust = cust;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    Q->sum ++ ;
}

Cust DeQueue(LQueue *Q)
{
    QNode *p = Q->front->next;
    Cust cust = p->cust;
    Q->front->next = p->next;
	if(Q->rear == p) Q->rear = Q->front;
	free(p);
    Q->sum -- ;
	return cust;
}

void Bank(LQueue *Q[4])
{
    Cust cust;
    int i;
    int hour, minutes, time = 0, f, p = 0;
    int time_all = 0, sum_all = 0;
    while(1)
    {
        printf("���ڵ�ʱ���ǣ�\n");
        scanf("%d:%d", &hour, &minutes);
        if(time > hour * 60 + minutes)
        {
            printf("Error!��ǰʱ�䲻��С���ϴ������ʱ�䣡����������\n");
            continue;
        }
        time = hour * 60 + minutes;
        printf("�������������ѡ����Ӧ�Ĺ���:\n\t1���пͻ��������� 2���пͻ��뿪���� 3�����й���\n��");
        scanf("%d",&f);
        int flag = 0, win;
        QNode *q;
        switch (f)
        {
            case 1:

                cust.begin_time = time;
                sum_all ++ ;
                for(i = 0; i < 4; i++)
                {
                    if(Q[i]->sum == 0)
                    {
                        EnQueue(Q[i], cust);
                        flag = 1;
                        printf("�ͻ��Ѿ���%d�Ŵ��ڰ���ҵ��.\n", i+1);
                        break;
                    }
                    if(Q[p]->sum > Q[i]->sum)
                    {
                        p = i;
                    }
                }
                if(!flag)
                {
                    EnQueue(Q[p], cust);
                    printf("�ͻ�����%d�Ŵ����Ŷ�.\n", p+1);
                }
                break;
    
            case 2:

                cust.end_time = time;
                printf("�пͻ��뿪�Ĵ����ǣ�\n");
                scanf("%d", &win);
                if(Q[win-1]->sum == 0)
                {
                    printf("Error���ô����Ѿ�û�����ˣ�\n");
                    break;    
                }
                time_all += time - Q[win-1]->front->next->cust.begin_time;
                DeQueue(Q[win]);
                printf("%d�Ŵ��ڰ���ҵ��Ŀͻ��Ѿ��뿪.\n", win);
                break;

            case 3:
                printf("����ҵ��ϵͳ�Ѿ��رգ�\n");
                flag = 3;
                for(i = 0; i < 4; i ++)
                {
                    for(q = Q[i]->front->next; q->next; q = q->next)
                    {
                        time_all += time - q->cust.begin_time;
                    }
                }
                break;
        }
        if(flag == 3)
        {
            break;
        }
        printf("\n");
    }

    float time_aver = time_all / sum_all;
    int h;
    float m;
    h = int(time_aver / 60);
    m = time_aver - h * 60;
    printf("����ͻ���ƽ���ȴ�ʱ��Ϊ:\t%dʱ%.2f��\n", h, m);
}

int main()
{
    LQueue *Q[4];
    for(int i = 0; i < 4; i ++)
    {
        Q[i] = InitQueue();
    }
    Bank(Q);
    return 0;
} 