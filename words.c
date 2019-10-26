/*
    �������й�ʹ������˳���������ϣ��Ŀ��ŵ�ַ������ϣ�������ַ���Ͷ����������Ĵ洢�ṹ
    ÿ�ִ洢�ṹ�������ִ���������������ӡ����ͼ������������ƵĹؼ��ʷֱ����Creat��Print��Search
    ÿ�ִ洢�ṹ�����й��ܶ���װ�ڴ��йؼ���Function�ĺ�����
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX 1000
#define HashMax 30

typedef struct
{   //��ʾÿ�����ʵĳ���Ƶ��
    char word[30];
    int sum;
}WordData;

typedef struct LNode
{   //��ʾ����Ľڵ�
    WordData word_data;
    struct LNode *next;
}LNode;

typedef struct HNode
{   //��ʾ��ϣ��Ĵ洢��Ԫ
    WordData word_data;
    int flag;
}HNode;

int ListGetWords(WordData words[])
{   //���ļ��ж�ȡ���²�ͳ�ƴ�Ƶ���浽˳���
    FILE *fp;
    if((fp = fopen("InFile.txt", "r")) == NULL)
    {   //���ļ�
        printf("open file failed");
        exit(0);
    }
    int i = 0, flag = 1, j = 0, k, s = 0;        //flag = 1ʱ��ʾ��ȡ����, = 2ʱ����һ�����ʶ�ȡ������s��ʾ��ͬ���ʵ�����
    char c;     //���ļ���ȡ�ַ���ʱ���浽c��
    char w[30];     //����ȡ�ĵ����ݴ浽w��
    w[0] = 0;      //w�����ַ���Ϊ0
    while(!feof(fp))
    {   //�����ļ�
        c = fgetc(fp);
        if(c == ' ' || c == ',' || c == '.' || c == '\n' || c == '\\')
        {   
            if(flag == 1)
            {   //���ǰһʱ������¼�뵥�ʣ���ʾһ�����ʵĽ���
                flag = 2;
            }
            else    
            {   //����ʲôҲ����
                flag = 0;
            }           
        }
        else
        {   //���c����������ţ���ʾ������¼�뵥��״̬
            flag = 1;
        }
        if(flag == 1)
        {   //¼�뵥��״̬
            w[i] = c;
            i ++;
            w[i] = 0;   //�ַ�����β��Ϊ0
        }
        else if(flag == 2)
        {   //���һ�����ʸ�¼�������
            strlwr(w);      //���������ת����Сд
            for(k = 0; k < s; k ++)
            {   //����˳�������������Ƿ��Ѵ���
                if(strcmp(words[k].word, w) == 0)
                {   //����Ѿ����ڣ����õ��ʵ�����+1
                    words[k].sum ++;
                    i = 0;      //i��Ϊ0����ʾ˳��������иõ���
                    break;
                }
            }
            if(i)
            {   //���i��Ϊ0�����õ��ʷŵ�һ���µĴ���ռ���
                s ++;
                strcpy(words[s-1].word, w);
                words[s-1].sum ++;
                i = 0;
            }
            
        }
    }
    fclose(fp);
    return s;
}

int Partition(WordData words[], int low, int high)
{   //���������з�������λ�ã����̲ġ����ݽṹ��P245
    WordData word;
    word = words[low];
    char pivotkey[30];
    strcpy(pivotkey, word.word);
    while(low < high)
    {
        while(low < high && strcmp(words[high].word, pivotkey) >= 0)
        {
            high --;
        }
        words[low] = words[high];
        while(low < high && strcmp(words[low].word, pivotkey) <= 0)
        {
            low ++;
        }
        words[high] = words[low];
    }
    words[low] = word;
    return low;
}

void QuickListSort(WordData words[], int low, int high)
{   //��������
    int pivotloc;
    if(low < high)
    {
        pivotloc = Partition(words, low, high);
        QuickListSort(words, low, pivotloc - 1);
        QuickListSort(words, pivotloc + 1, high);
    }
}

void PrintList(WordData words[], int words_sum)
{   //��ӡ˳����д������Ϣ
    int i;
    for (i = 0; i < words_sum; i++)
    {
        printf("%-15s%d\n", words[i].word, words[i].sum);       
    }
}

WordData SearchList(WordData words[], int words_sum, char word[])
{   //˳����е��۰���ң������ݽṹ��P193
    int low = 0, high = words_sum, mid;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if(strcmp(words[mid].word, word) == 0)
        {
            return words[mid];
        }
        else if(strcmp(words[mid].word, word) > 0)
        {
            high = mid - 1;
        }
        else 
        {
            low = mid + 1;
        }
    }
    //���û���ҵ�����������ձ���
    WordData word_null;
    word_null.sum = 0;
    return word_null;
}

LNode *CreatLinkList(WordData words[], int words_sum)
{   //����˳�������ݴ�������
    LNode *rear, *p;
    LNode *W = (LNode *)malloc(sizeof(LNode));
    rear = W;
    int i;
    for(i = 0; i <= words_sum; i ++)
    {
        p = (LNode *)malloc(sizeof(LNode));
        p->word_data = words[i];
        rear->next = p;
        rear = p;
        rear->next = NULL;
    }
    return W;
}

void PrintLinkList(LNode *W)
{   //��ӡ�����е���Ϣ
    LNode *p;
    for(p = W->next; p->next; p = p->next)
    {
        printf("%-15s%d\n", p->word_data.word, p->word_data.sum);
    }
}

WordData SearchLinkList(LNode *W, char word[])
{   //˳���������
    LNode *p = W;
    for(;p->next; p = p->next)
    {
        if(strcmp(p->word_data.word, word) == 0)
        {
            return p->word_data;
        }
    }
    WordData word_null;
    word_null.sum = 0;
    return word_null;
}

void FunctionLinkList(WordData words[], int words_sum)
{
    LNode *W = CreatLinkList(words, words_sum);     //��������
    char fs[20];
    int f;    
    while(1)    
    {
        printf("\n$����$  ��ѡ���ܣ�\n1���鿴��Ƶͳ�ƽ��\n2�����ҵ���\n0����һ��\n>> ");
        gets(fs);       //���ַ�����������
        if(strlen(fs) != 1)
        {   //�������ַ����ĳ��Ȳ�Ϊ1���϶�Υ��
            printf("\n��Ч���룬������ѡ��\n");
            continue;
        }
        f = fs[0] - '0';    //���ַ�ת��Ϊ����
        if(f < 0 || f > 2)
        {   //���������ֲ���0��2֮�䣬ҲΥ��
            printf("\n��Ч���룬������ѡ��\n");
            continue;
        }
        switch(f)
        {
            case 1:

                printf("\n$����$  �����г��ֵĵ��ʼ���Ƶ�����£�\n");
                printf("����         ����  \n");
                PrintLinkList(W);
                break;

            case 2:

                printf("\n$����$  ��������Ҫ���ҵĵ��ʣ�\n>> ");
                char word[30];
                gets(word);
                WordData search_result;     //���ղ��ҵĽ��
                search_result = SearchLinkList(W, word);
                if(search_result.sum != 0)
                {
                    printf("\n����%s�������г��ֵĴ�����%d��\n", word, search_result.sum);
                }
                else
                {
                    printf("\n����%s�����ڣ�\n", word);
                }
                break;

            case 0:

                printf("\n");
                return ;
        }
    }
}

void FunctionList(WordData words[], int words_sum)
{   
    char fs[20];    
    int f;
    while(1)
    {
        printf("\n$˳���$  ��ѡ���ܣ�\n1���鿴��Ƶͳ�ƽ��\n2�����ҵ���\n0����һ��\n>> ");
        gets(fs);
        if(strlen(fs) != 1)
        {
            printf("\n��Ч���룬������ѡ��\n");
            continue;
        }
        f = fs[0] - '0';
        if(f < 0 || f > 2)
        {
            printf("\n��Ч���룬������ѡ��\n");
            continue;
        }
        switch(f)
        {
            case 1:
                
                printf("\n$˳���$  �����г��ֵĵ��ʼ���Ƶ�����£�\n");
                printf("����         ����  \n");
                PrintList(words, words_sum);
                break;

            case 2:

                printf("\n$˳���$  ��������Ҫ���ҵĵ��ʣ�\n>> ");
                char word[20];
                WordData search_result;
                // getchar();
                gets(word);
                search_result = SearchList(words, words_sum , word);
                if(search_result.sum != 0)
                {
                    printf("\n����%s�������г��ֵĴ�����%d��\n", word, search_result.sum);
                }
                else
                {
                    printf("\n����%s�����ڣ�\n", word);
                }
                break;

            case 0:

                printf("\n");
                return ;
        }
    } 
}

typedef struct HashLinkNode
{   //����ַ����ϣ��Ľڵ�
    WordData word;
    HashLinkNode *next;
}HashLinkNode;

int Hash(char word[])
{   //�����ַ���������ĸ�����ϣֵ����'a'�Ĳ���ǹ�ϣֵ
    int hash;
    hash = word[0] - 'a';   
    return hash;
}

void CreatLinkHash(WordData words[], int words_sum, HashLinkNode H[])
{   //��������ַ����ϣ��
    int i, hash;
    HashLinkNode *h, *p = (HashLinkNode *)malloc(sizeof(HashLinkNode));
    for(i = 0; i < HashMax; i ++)
    {   // ��ϣ���ʼ��
        H[i].next = NULL;
    }
    for(i = 0; i < words_sum; i ++)
    {   //��˳����е�Ԫ�ش��浽����ַ��ϣ����
        h = (HashLinkNode *)malloc(sizeof(HashLinkNode));
        h->word = words[i];
        h->next = NULL;
        hash = Hash(words[i].word);
        for(p = &H[hash]; p->next; p = p->next)
        {
            ;
        }
        p->next = h;
        h->next = NULL;
    }
}

void PrintLinkHash(HashLinkNode H[])
{
    int i;
    HashLinkNode *h;
    for(i = 0; i < HashMax; i ++)
    {
        for(h = H[i].next; h; h = h->next)
        {
            printf("%-15s%d\n", h->word.word, h->word.sum);
        }
    }
}

WordData SearchLinkHash(HashLinkNode H[], char word[])
{   //����Ҫ�ҵ��ַ����Ĺ�ϣֵ������ϣ��
    int hash = Hash(word);
    HashLinkNode *h;
    for(h = &H[hash]; h; h = h->next)
    {
        if(strcmp(word, h->word.word) == 0)
        {
            return h->word;
        }
    }
    WordData word_null;
    word_null.sum = 0;
    return word_null;
}

void CreatHashList(WordData words[], int words_sum, HNode HL[])
{   //�������ŵ�ַ����ϣ���ö���̽�ⷨ�����ͻ�������ݽṹ��P223
    int i, j, h;
    for(i = 0; i <= MAX; i ++)
    {   //��ʼ����ϣ��
        HL[i].flag = 0;
        HL[i].word_data.sum = 0;
    }
    for(i = 0; i <= words_sum; i ++)
    {
        h = Hash(words[i].word);
        if(HL[h].flag == 0)
        {
            HL[h].word_data = words[i];
            HL[h].flag = 1;
        }
        else
        {
            for(j = 1; j < sqrt(MAX); j ++)
            {   //����̽�ⷨ�����ͻ
                h = int(h + pow(-1, i+1) * pow(i, 2) + MAX) % MAX;
                if(HL[h].flag == 0)
                {
                    HL[h].word_data = words[i];
                    HL[h].flag = 1;
                    break;
                }
                h = int(h + pow(-1, i) * pow(i, 2) + MAX) % MAX;
                if(HL[h].flag == 0)
                {
                    HL[h].word_data = words[i];
                    HL[h].flag = 1;
                    break;
                }
            }
        }
    }
}

void PrintHashList(HNode HL[])
{   
    int i;
    for(i = 0; i < MAX; i ++)
    {
        if(HL[i].word_data.sum)
        {
            printf("%-15s%d\n", HL[i].word_data.word, HL[i].word_data.sum);
        }
    }
}

WordData SearchHashList(HNode HL[], char word[])
{
    int i;
    for(i = 0; i < MAX; i ++)
    {
        if(strcmp(HL[i].word_data.word, word) == 0)
        {
            return HL[i].word_data;
        }
    }
    WordData word_null;
    word_null.sum = 0;
    return word_null;
}

void FunctionHash(WordData words[], int words_sum)
{   
    char fs[20];
    int f, flag = 0;
    while(1)
    {
        printf("\n��ѡ���ϣ��ĳ�ͻ��������\n1�����ŵ�ַ��\n2������ַ��\n0����һ��\n>> ");
        gets(fs);
        if(strlen(fs) != 1)
        {
            printf("\n��Ч���룬������ѡ��\n");
            continue;
        }
        f = fs[0] - '0';
        if(f < 0 || f > 2)
        {
            printf("\n��Ч���룬������ѡ��\n");
            continue;
        }
        switch(f)
        {
            case 1:
                //ѡ�񿪷ŵ�ַ����ϣ��
                HNode HL[MAX];
                CreatHashList(words, words_sum, HL);
                while(1)
                {
                    printf("\n$���ŵ�ַ����ϣ��$  ��ѡ���ܣ�\n1���鿴��Ƶͳ�ƽ��\n2�����ҵ���\n0����һ��\n>> ");
                    gets(fs);
                    if(strlen(fs) != 1)
                    {
                        printf("\n��Ч���룬������ѡ��\n");
                        continue;
                    }
                    f = fs[0] - '0';
                    if(f < 0 || f > 2)
                    {
                        printf("\n��Ч���룬������ѡ��\n");
                        continue;
                    }
                    switch(f)
                    {
                        case 1:
                            
                            printf("\n$���ŵ�ַ����ϣ��$  �����г��ֵĵ��ʼ���Ƶ�����£�\n");
                            printf("����         ����  \n");
                            PrintHashList(HL);
                            break;

                        case 2:

                            printf("\n$���ŵ�ַ����ϣ��$  ��������Ҫ���ҵĵ��ʣ�\n>> ");
                            char word[20];
                            WordData search_result;
                            gets(word);
                            search_result = SearchHashList(HL, word);
                            if(search_result.sum != 0)
                            {
                                printf("\n����%s�������г��ֵĴ�����%d��\n", word, search_result.sum);
                            }
                            else
                            {
                                printf("\n����%s�����ڣ�\n", word);
                            }
                            break;

                        case 0:
                            
                            flag = 1;
                            break;
                    }
                    if(flag)
                    {
                        break;
                    }
                }
                break;     //case1   

            case 2:
                //ѡ������ַ����ϣ��
                flag = 0;
                HashLinkNode H[HashMax];
                CreatLinkHash(words, words_sum, H);        //��������ַ����ϣ��
                while(1)
                {
                    printf("\n$����ַ����ϣ��$  ��ѡ���ܣ�\n1���鿴��Ƶͳ�ƽ��\n2�����ҵ���\n0����һ��\n>> ");
                    gets(fs);
                    if(strlen(fs) != 1)
                    {
                        printf("\n��Ч���룬������ѡ��\n");
                        continue;
                    }
                    f = fs[0] - '0';
                    if(f < 0 || f > 2)
                    {
                        printf("\n��Ч���룬������ѡ��\n");
                        continue;
                    }
                    switch(f)
                    {
                        case 1:
                            
                            printf("\n$����ַ����ϣ��$  �����г��ֵĵ��ʼ���Ƶ�����£�\n");
                            printf("����         ����  \n");
                            PrintLinkHash(H);
                            break;

                        case 2:

                            printf("\n$����ַ����ϣ��$  ��������Ҫ���ҵĵ��ʣ�\n>> ");
                            char word[20];
                            WordData search_result;
                            gets(word);
                            search_result = SearchLinkHash(H, word);
                            if(search_result.sum != 0)
                            {
                                printf("\n����%s�������г��ֵĴ�����%d��\n", word, search_result.sum);
                            }
                            else
                            {
                                printf("\n����%s�����ڣ�\n", word);
                            }
                            break;

                        case 0:
                            
                            flag = 1;
                            break;
                    }//switch
                    if(flag)
                    {
                        break;
                    }
                }//while
                break;  //case2

            case 0:

                return ;
            
        }//switch1
    }//while
}

typedef struct BSTNode
{   //�������ڵ�
    WordData word;
    struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree;

BSTree InsertBST(BSTree T, WordData word)
{   //�������Ĳ����㷨�������ݽṹ��P201
    BSTNode *S;
    if(!T)
    {
        S = (BSTNode *)malloc(sizeof(BSTNode));
        S->word = word;
        S->lchild = S->rchild = NULL;
        T = S;
        return T;
    }
    else if(strcmp(word.word, T->word.word) > 0)
    {
        T->rchild = InsertBST(T->rchild, word);
    }
    else if(strcmp(word.word, T->word.word) < 0)
    {
        T->lchild = InsertBST(T->lchild, word);
    }
}

BSTree CreatBST(WordData words[], int words_sum)
{   //��������������
    BSTree T = NULL;
    int i;
    for(i = 0; i <= words_sum; i ++)
    {
        if(words[i].sum)
        {
            T = InsertBST(T, words[i]);
        }       
    }
    return T;
}

void PrintBST(BSTree T)
{
    if (T)
    {
        PrintBST(T->lchild); 
        printf("%-15s%d\n", T->word.word, T->word.sum);
        PrintBST(T->rchild);
    }
}

BSTNode *SearchBST(BSTree T, char word[])
{   //�������ĵݹ���ң������ݽṹ��P199
    if(!T || !strcmp(word, T->word.word))
    {
        return T;
    }
    else if(strcmp(T->word.word, word) > 0)
    {
        return SearchBST(T->lchild, word);
    }
    else if(strcmp(T->word.word, word) < 0)
    {
        return SearchBST(T->rchild, word);
    }
}

void FunctionBST(WordData words[], int words_sum)
{
    BSTree T = CreatBST(words, words_sum);
    char fs[20];
    int f;
    while(1)
    {
        printf("\n$����������$  ��ѡ���ܣ�\n1���鿴��Ƶͳ�ƽ��\n2�����ҵ���\n0����һ��\n>> ");
        gets(fs);
        if(strlen(fs) != 1)
        {
            printf("\n��Ч���룬������ѡ��\n");
            continue;
        }
        f = fs[0] - '0';
        if(f < 0 || f > 2)
        {
            printf("\n��Ч���룬������ѡ��\n");
            continue;
        }
        switch(f)
        {
            case 1:
                
                printf("\n$����������$  �����г��ֵĵ��ʼ���Ƶ�����£�\n");
                printf("����         ����  \n");
                PrintBST(T);
                break;

            case 2:

                printf("\n$����������$  ��������Ҫ���ҵĵ��ʣ�\n>> ");
                char word[20];
                BSTNode *t;
                gets(word);
                t = SearchBST(T, word);
                if(t)
                {
                    printf("\n����%s�������г��ֵĴ�����%d��\n", t->word.word, t->word.sum);
                }
                else
                {
                    printf("\n����%s�����ڣ�\n", word);
                }
                break;

            case 0:

                printf("\n");
                return ;
        }
    }
}

int main()
{
    WordData words[MAX];
    int words_sum, f;
    char fs[20];
    words_sum = ListGetWords(words);
    printf("����\"InFile\"�Ĵ�Ƶͳ����ɣ�\n");
    QuickListSort(words, 0, words_sum - 1);
    while(1)
    {
        printf("\nѡ��Ҫʹ�õĴ洢�ṹ��\n1��˳���\n2������\n3������������\n4����ϣ��\n0���˳�\n>> ");
        gets(fs);
        if(strlen(fs) != 1)
        {
            printf("\n��Ч���룬������ѡ��\n");
            continue;
        }
        f = fs[0] - '0';
        if(f < 0 || f > 4)
        {
            printf("\n��Ч���룬������ѡ��\n");
            continue;
        }
        switch(f)
        {
            case 1:

                FunctionList(words, words_sum);
                break;

            case 2:

                FunctionLinkList(words, words_sum);
                break;

            case 3:

                FunctionBST(words, words_sum);
                break;

            case 4:

                FunctionHash(words, words_sum);
                break;

            case 0:

                return 0;
        }
    }
}