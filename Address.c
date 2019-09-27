//  ͨѶ¼ģ��ϵͳ

#include<stdio.h>
#include<string.h>
#include<math.h>

#define M 20

typedef struct Info
{
    char tele[15];
    char add[15];
    char name[15];
    int flag = 0;       //flag��Ǹÿռ��Ƿ��ѱ���䣬����ѱ���䣬flag��Ϊ1
}Info;

int Hash(char tele[15])
{   //��ϣ�����Ĺ��죺�ֻ�������֮����ȡ��M
    int i, sum = 0;
    for(i = 0; i < strlen(tele); i ++)
    {
        sum += tele[i] - '0';
    }
    return sum % M;
}

void EnHashList(Info address[M], Info info)
{
    int i, h = Hash(info.tele);
    if(address[h].flag == 0)
    {   //�����ϣֵ����û��Ԫ�أ�����Ԫ�ر��浽��λ��
        info.flag = 1;
        address[h] = info;
        return ;
    }
    else
    {
        for(i = 1; i < sqrt(M); i ++)
        {   //����̽�ⷨ�����ͻ
            h = int(h + pow(-1, i+1) * pow(i, 2) + M) % M;
            if(address[h].flag == 0)
            {
                info.flag = 1;
                address[h] = info;
                return ;
            }
            h = int(h + pow(-1, i) * pow(i, 2) + M) % M;
            if(address[h].flag == 0)
            {
                info.flag = 1;
                address[h] = info;
                return ;
            }
        }
    }
    printf("¼��ͨѶ¼ʧ�ܣ�\n");
}

int SearchHash(Info address[M], char tele[15])
{
    int h, i;
    h = Hash(tele);
    if(strcmp(tele, address[h].tele) == 0)
    {
        return h;
    }
    else
    {
        for(i = 1; i < sqrt(M); i ++)
        {   //����̽�ⷨ�����ͻ
            h = int(h + pow(-1, i+1) * pow(i, 2) + M) % M;
            if(strcmp(tele, address[h].tele) == 0)
            {
                return h;
            }
            h = int(h + pow(-1, i) * pow(i, 2) + M) % M;
            if(strcmp(tele, address[h].tele) == 0)
            {
                return h;
            }
        }
    }
    printf("ͨѶ¼��û�и���\n");
    return -1;
}

int main()
{
    Info address[M];
    Info info;
    char tele[15];
    int i, f, h;
    while(1)
    {
        printf("\nѡ���ܣ�\n1. ¼���µ���ϵ��\n2. ��ѯ��ϵ��\n3. ��ʾ���е���ϵ��\n4. �˳�ϵͳ\n��");
        scanf("%d", &f);
        getchar();
        if(f == 4)
        {
            break;
        }
        switch(f)
        {
            case 1:

                printf("\n���������½���ϵ�˵����ơ��绰����͵�ַ\n");
                
                gets(info.name);
                gets(info.tele);
                gets(info.add);
                EnHashList(address, info);                  //�������ϵ�˵���Ϣ���浽��ϣ����
                printf("��ϵ���ѱ��浽ͨѶ¼��\n\n");
                break;

            case 2:

                printf("\n������Ҫ��ѯ����ϵ�˵��ֻ��ţ�\n");
                gets(tele);
                h = SearchHash(address, tele);          //�ҵ��ֻ��Ŷ�Ӧ��Ԫ���ڹ�ϣ���е�λ��
                printf("\n����ϵ�˵ľ�����ϢΪ��\n%s\n%s\n%s\n", address[h].name, address[h].tele, address[h].add);
                break;

            case 3:

                printf("\n����ͨѶ¼��������ϵ�˵���Ϣ���£�\n");
                for(i = 0; i < M; i ++)
                {
                    if(address[i].flag)         //�����ϣ����flagΪ1��Ԫ��
                    {
                        printf("\n%s\n%s\n%s\n", address[i].name, address[i].tele, address[i].add);
                    }
                }
                break;
        }
    }
    return 0;
}