clear %�ͷ�ϵͳ�ڴ�
clc   %���������������

%% �����ȶ������
num = 1000;
seed = 0; %��������,��֤�����ȶ��������
rand('seed',seed); 
Data = round(rand(1,num)*1);%�������01���أ���ΪǶ�������
%Data=randi([0 1],100);%�������01���أ���ΪǶ�������
%% ����Lenaͼ������ֱ��ͼ
origin_I = double(imread('Lena.tiff')); %����Lenaͼ��
hist_ori_I = tabulate(origin_I(:)); %��Lenaͼ���������ֵ����ͳ��
subplot(111); %��������
bar(hist_ori_I(:,2),0.1); %����hist_ori_I��ֱ��ͼ
% 2�������hist_ori_I�ڶ��е���ֵ��0.1��ʾ������Ŀ��
title('ԭʼֱ��ͼ'); %���ñ��� 
%% Ѱ�ҷ�ֵ��
[m,n] = size(hist_ori_I); %��ȡ����hist_ori_I����ֵ����ֵ
PK = 0;
num_PK = 0; %��¼��ֵ�����صĸ����������Ƕ�����ݸ���
for i=1:m   
    if num_PK < hist_ori_I(i,2)       
        PK = hist_ori_I(i,1);
        num_PK = hist_ori_I(i,2);
    end    
end
%% Ѱ����ֵ��
% �����ͷ�ֵ�㲻����ʱ�������ͷ�ֵ��֮���ͼ����������һ����λ
for i=PK+1:m
    if hist_ori_I(i,2)==0 %�ҷ�ֵ��PK����ĵ�һ����� 
        Z = hist_ori_I(i,1);
        break;
    end
end
%% Ƕ�뺯��  
[stego_I,emD] = Embed(origin_I,Data,PK,Z);
hist_stego_I = tabulate(stego_I(:)); %��Lenaͼ���������ֵ����ͳ��
figure; %���´�һ������
subplot(111); %��������
bar(hist_stego_I(:,2),0.1); %����hist_stego_I��ֱ��ͼ
title('����ֱ��ͼ'); %���ñ��� 
%% ��ȡ���� 
[recover_I,exD] = Extract(stego_I,num,PK,Z);
%% ͼ��Ա�
figure;
subplot(221);imshow(origin_I,[]);title('ԭʼͼ��');
subplot(222);imshow(stego_I,[]);title('����ͼ��');
subplot(223);imshow(recover_I,[]);title('�ָ�ͼ��');
%% �жϽ���Ƿ���ȷ
isequal(emD,exD)
isequal(origin_I,recover_I)
psnrvalue = PSNR(origin_I,stego_I) %��PSNRֵ