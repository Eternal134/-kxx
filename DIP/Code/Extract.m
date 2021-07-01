function [recover_I,exD] = Extract(stego_I,num,PK,Z)
% ����˵����������ͼ������ȡ��Ϣ
% ���룺stego_I������ͼ��,num���������ݸ�����,PK����ֵ�㣩,Z����ֵ�㣩
% �����recover_I���ظ�ͼ��,exD����ȡ���������ݣ�

[m,n] = size(stego_I); %ͳ��ͼ���������
recover_I = stego_I;
exD = zeros();
%% ���ݷ�ֵ��PK����ֵ��Z��ȡ��Ϣ
t = 0; %��������ȡ��Ϣ�ĸ���
for i=1:m
    for j=1:n
        if t >= num %������Ϣ����ȡ����
            break;
        end
        if recover_I(i,j)>PK+1 && recover_I(i,j)<=Z %����ֵ��PK+1����ֵ��Z֮�����������ƽ��
            recover_I(i,j) = recover_I(i,j) - 1;
        elseif recover_I(i,j)==PK %��ȡ0
            recover_I(i,j) = recover_I(i,j);
            t = t+1;
            exD(t) = 0;
        elseif recover_I(i,j)==PK+1 %��ȡ1
            recover_I(i,j) = recover_I(i,j)-1;
            t = t+1;
            exD(t) = 1;   
        end
    end
end