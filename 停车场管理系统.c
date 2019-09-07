#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 5
#define Price 5

typedef struct{
    char car_id[9];
    float begin_time;
    float end_time;
}Car;

typedef struct {
    Car *base;
    Car *top;
    int stacksize; 
}SqStack;

Car Pop(SqStack *S){
    return *--S->top;
}

void Push(SqStack *S,Car car){
    *S->top ++ = car;
}

typedef struct QNode{
    Car car;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct LQueue{
    QNode *front;
    QNode *rear;
}LQueue;

SqStack *InitSqStack(){								
	SqStack *S;
	S = (SqStack *)malloc(sizeof(SqStack));
	S->base = (Car *)malloc(sizeof(Car)*MAXSIZE);
	S->top = S->base;
	S->stacksize = MAXSIZE;
	return S;
}

LQueue *InitLQueue(){
    LQueue *Q;
    Q->front = Q->rear = (QNode *)malloc(sizeof(QNode));
    Q->front->next = NULL;
    return Q;
}

void EnQueue(LQueue *Q,Car car){
	QNode *p = (QNode *)malloc(sizeof(QNode));
    p->car = car;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
}

Car DeQueue(LQueue *Q){
	QNode *p = Q->front->next;
	Car car = p->car;
	Q->front->next = p->next;
	if(Q->rear == p) Q->rear = Q->front;
	free(p);
	return car;
}

void PopStack(SqStack *S, Car *p){
    SqStack *T;
	Car *q;
	Car car;
	T = InitSqStack();
	while(S->top-1>p){
		Push(T,Pop(S));
	}
	car = Pop(S);
	while(T->top != T->base){
		Push(S,Pop(T));
	} 
}

void Enter(SqStack *S, LQueue *Q, Car car){
    if(S->top - S->base == S->stacksize){     
    	printf("ͣ�������������ĳ����ѽ���㳵���ŶӵȺ�\n\n");
       
	    EnQueue(Q,car);
    }
    else{
        //??????
        Push(S, car);
        printf("���ĳ����ѽ���ͣ��������ʼ�Ʒѣ�\n\n");
    }
}

void Out(SqStack *S, LQueue *Q, Car car){
	float time_long;
    Car *p;
    Car c;
    float cost;
    int flag=0;
    if(S->top == S->base){
        printf("\nͣ������û�иó���!");
    }
    else{
        for(p = S->base;p <= S->top;p++){
            if(strcmp(p->car_id,car.car_id) == 0) {
            	cost = Price*(car.end_time - p->begin_time);
            	time_long = car.end_time - p->begin_time;
				PopStack(S,p);
				flag = 1;
            	printf("���ĳ������뿪ͣ����������ʱ--%.2f--ʱ��������Ҫ֧����",time_long);
               	printf("\n---%.2fԪ\n\n", cost);
            	break;
        	}
        }
        if(Q->front != Q->rear){
        	c = DeQueue(Q);
        	c.begin_time = car.end_time;
        	Push(S,c);
        	printf("ͣ�������п�λ������--%s--�Ѵӱ㳵������ͣ��������ʼ�Ʒѣ�\n\n",c.car_id); 
    	}
        if(!flag){
			printf("ͣ������û�иó�!\n\n");
		}
    }
}

int main(){
    SqStack *S;
    LQueue *Q;
    S = InitSqStack();
    
    Q->front = Q->rear = (QNode *)malloc(sizeof(QNode));
    Q->front->next = NULL;
    //Q = InitLQueue();
    Car car;
    int flag;       
    float time;
    int hour,minute;
    printf("\n-------------��ӭ����Eternal��ͣ������-------------\n\n");
    //?????????????
    while(1){
		printf("\n******************************************\n");
    	printf("��ѡ�����ͣ������0���뿪����1���˳�ϵͳ����2����\n");
    	printf("-------------\t");
    	scanf("%d",&flag);
    	if(2 == flag) break; 
    	getchar();
    	printf("��������ĳ��ƺţ�������8λ����\n");
    	printf("-------------\t");
    	gets(car.car_id);
    	printf("������ͣ��/�뿪ʱ�䣨��ʽΪʱ���֣�\n");
    	printf("-------------\t");
    	scanf("%d:%d",&hour,&minute);
    	time = hour + (float)minute/60;

    	if(0 == flag){
        	car.begin_time = time;
        	Enter(S,Q,car);
    	}
    	else{
        	car.end_time = time;
        	Out(S,Q,car);
    	}
	}
    return 0;
}
