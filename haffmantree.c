#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define inf 32767
typedef struct{
	//�����������Ľṹ������ 
	int weight;
	int parent,lchild,rchild;
}HTNode,*Huffmantree;

typedef struct{
	//ͳ��������ַ���Ƶ�ʵĽṹ�� 
	char c;
	int num;
}Diff;
	
void Select(Huffmantree HT,int n,int *s,int *ss){
	//ѡ��ǰn�������Ȩֵ��С���������ĺ��� 
	int j,min1=inf,min2=inf,temp;												 
	for(j=1;j<=n;j++){															//���ҳ���С��һ�� 
		if(HT[j].weight<min1&&HT[j].parent==0){
			*s=j;	min1=HT[j].weight;
		}
	}
	temp=min1;																	//��temp������С��Ȩֵ 
	HT[*s].weight=inf;															//�������С��Ȩֵ�ĳ����޴� 
	for(j=1;j<=n;j++){															//���ҳ���ʱ��С��Ȩֵ�Ľ�㣬��Ȩֵ�ڶ�С�Ľ�� 
		if(HT[j].weight<min2&&HT[j].parent==0){									
			*ss=j;	min2=HT[j].weight;
		}
	}
	HT[*s].weight=temp;															//����С��Ȩֵ�Ļ��� 
}

Huffmantree CreatHuffmantree(int dn,Diff *diff){
	//������������ 
	int a,b,i;
	int *s1=&a,*s2=&b;
	int m=2*dn-1;																//�������ù���������Ҫ�Ŀռ�m 
	Huffmantree HT=(HTNode *)malloc((m+1)*sizeof(HTNode));						//���ٹ��������Ŀռ� 
	
	for(i=1;i<=m;i++){															//��ÿ���ڵ��˫�׺����Һ��Ӷ���Ϊ0 
		HT[i].parent=HT[i].rchild=HT[i].lchild=0;
	}
	for(i=1;i<=dn;i++){															//����ͳ�Ƶ����ַ����ֵ�Ƶ�ʣ��Թ�������������Ȩֵ��ʼ�� 
		HT[i].weight=diff[i-1].num;
	}
	for(i=dn+1;i<=m;i++){														//������֪�Ľ��ȷ��δ֪�Ľ�� 
		Select(HT,i-1,s1,s2);													//ѡ��ǰi�������Ȩֵ��С������ 
		HT[*s1].parent=i;	HT[*s2].parent=i;									//�����ǵ�˫�׽����Ϊi 
		HT[i].lchild=*s1;	HT[i].rchild=*s2;									//��i�������Һ��ӷֱ�ָ��s1��s2 
		HT[i].weight=HT[*s1].weight+HT[*s2].weight;								//i����ȨֵΪs1��s2��Ȩֵ֮�� 
	}
	return HT;																	//�����Ѿ������õĹ������� 
}

char **Huffmancode(Huffmantree HT,int n){
	//���ݽ����Ĺ��������Բ�ͬ�ַ����б��� 
	int start,c,f,i;															
	char **HC=(char **)malloc((n+1)*sizeof(char));								//���ٴ������б����ָ������HC 
	char *cd=(char *)malloc(n*sizeof(char));									//��ʱ�����ַ���cd 
	cd[n-1]='\0';																//��cd�����һ���ַ���Ϊ0 
	for(i=1;i<=n;i++){															//���ַ�����Ĺ��� 
		start=n-1;																//ÿȷ��һλ���룬�Ӻ���ǰд��cd����n-1λ�ÿ�ʼд 
		c=i;f=HT[i].parent;														//c�Ǵ�ȷ��������ַ���fָ��c��˫�׽ڵ� 
		while(f!=0){															//û�з��ʵ������ʱ 
			start--;															//��ȷ���ı�����ǰ�ƶ�һλ 
			if(HT[f].lchild==c) cd[start]='0';									//���f��������c�������0 
			else cd[start]='1';													//�������1 
			c=f;f=HT[f].parent;													//c��Ϊf��f���������� 
		}
		HC[i]=(char *)malloc((n-start)*sizeof(char));							//���ٴ��汾��ȷ�����ַ�������ַ����ռ� 
		strcpy(HC[i],&cd[start]);												//��cd�е��ַ���д��HC�� 
	}
	free(cd);																	//�ͷ�cd�Ŀռ� 
	return HC;																	//���ر�����Ϣ 
}

int main(){
	//----------------ͳ���ַ����г��ֵ��ַ���Ƶ��----------------- 
	char str[50];																//������Ҫ������ַ��� 
	printf("������Ҫ������ַ���������0�Խ���\n");
	gets(str);																	//������Ҫ������ַ��� 
	while(strcmp(str,"0")){														//��û������0ʱ�ظ����²��� 
	int i,j,len,dn=1;															//����ѭ������i,j,�ַ�������len����ͬ���ַ�����dn 
	Diff diff[20];																//���崢�治ͬ���ַ������ֺ�Ƶ�ʵĽṹ������ 
	len=strlen(str);															//������Ҫ������ַ����ĳ��� 
	diff[0].c=str[0];	diff[0].num=1;
	for(i=1;i<len;i++){															//���������ÿ���ַ� 
		for(j=0;j<dn;j++){														//����ǰ���ʵ����ַ����Ѿ�ȷ�������ַ��Ƚ� 
			if(diff[j].c==str[i]){												//���������ͬ���ַ������ַ���Ƶ�ʼ�1 
				diff[j].num++;
				break;
			}
		}
		if(j==dn){																//���j==dn�������ϲ�ѭ��û����ǰ��������������µ�Ԫ�� 
			diff[j].c=str[i];													//��ʱ�������ַ�����Ϣ����һ���µĽṹ������Ŀռ� 
			diff[j].num=1;
			dn++;																//dn��1 
		}
	}
	Diff d;																		//�����Ƕ��Ѿ�ȷ���Ĳ��ظ����ַ�����ASCII��ð������ 
	for(i=0;i<dn-1;i++)
		for(j=0;j<dn-i-1;j++){
			if(diff[j].c>diff[j+1].c){
				d=diff[j];	diff[j]=diff[j+1];	diff[j+1]=d;
			}
		}
	printf("�ַ����г��ֵ��ַ�����Ƶ�ʣ�����ASCII�����У�\n");
	for(i=0;i<dn;i++){
		printf("%c:%d ",diff[i].c,diff[i].num);
	}
	//-------------����������ַ���������Ӧ�Ĺ�������--------------
	Huffmantree HT;																//�����������HT 
	HT=CreatHuffmantree(dn,diff);												//������������ 
	printf("\n�����Ĺ��������Ĵ洢�ṹ����̬��\n");
	for(i=1;i<=2*dn-1;i++){
		printf("%d %d %d %d %d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	} 
	//-------------------��ÿ���ַ��Ĺ���������--------------------
	char **code=Huffmancode(HT,dn);												//����ÿ���ַ��Ĺ����������ָ������code 
	printf("ÿ���ַ���Ӧ�Ĺ���������Ϊ��\n");
	for(i=1;i<=dn;i++){											
		printf("%c:%s ",diff[i-1].c,*(code+i));
	} 
	//----------------------��������ַ���-----------------------
	char result[100];															//���������ַ���result 
	int place=0;																//placeָ��ǰд����result����λ�ã������´�д�� 
	for(i=0;i<len;i++){															//������Ҫ������ַ�����ÿ���ַ� 
		for(j=0;j<dn;j++){														//����ǰ��Ҫ�Ƚϵ��ַ���ȷ���˵��ַ��Ĺ���������ƥ�� 
			if(str[i]==diff[j].c){
				 strcpy(&result[place],*(code+j+1));
				 place+=strlen(*(code+j+1));
			}
		}
	}
	printf("\n�������ַ���Ϊ��\n");
	puts(result);
	// ----------------------��������ַ���-----------------------
	char decode[len];															//���������ַ���������decode 
	int p,c=2*dn-1,l=0;															//pΪ���α��������ַ����ı�����c��ʾ��ʱ���ʵĹ��������Ľ�㣬��ʼ��Ϊ����㣬l��ʾ����Ľ��� 
	for(p=0;p<strlen(result);p++){												//���������ÿ���ַ� 
		if(result[p]=='0') c=HT[c].lchild;										//�����0���������� 
		else c=HT[c].rchild;													//������1�������Һ��� 
		if(HT[c].lchild==0&&HT[c].rchild==0){									//����������Һ��Ӷ���0������Ҷ�ӽ�� 
			decode[l]=diff[c-1].c;												//���Ѿ�ȷ�����ַ�д��decode�� 
			l++;																//׼��ȷ����һ�ַ� 
			decode[l]='\0';														//�ַ����Ľ�β��ֵΪ/0 
			c=2*dn-1;															//�ٽ�Cָ������ 
		}
	}
	printf("\n�����ַ�����\n");
	puts(decode);																//���������ַ��� 
	printf("\n\n������Ҫ������ַ���������0�Խ���\n");
	gets(str);																	//������һ��Ҫ�������ַ��� 
	}
	return 0; 
}
