function [stego_I,emD] = Embed(origin_I,Data,PK,Z)
% ����˵�������ݷ�ֵ�����ֵ��Ƕ����Ϣ
% ���룺origin_I��ԭʼͼ��,Data���������ݣ�,PK����ֵ�㣩,Z����ֵ�㣩
% �����stego_I������ͼ��,emD��Ƕ���������Ϣ��

[m,n] = size(origin_I); %ͳ��ͼ���������
num = numel(Data); %������Ϣ����
stego_I = origin_I;
%% ���ݷ�ֵ��PK����ֵ��ZǶ����Ϣ
t = 0; %������Ƕ����Ϣ�ĸ���
for i=1:m
    for j=1:n
        if t >= num %������Ϣ��Ƕ��
            break;
        end
        if stego_I(i,j)>PK && stego_I(i,j)<Z %����ֵ��PK����ֵ��Z֮�����������ƽ��
            stego_I(i,j) = stego_I(i,j) + 1;
        elseif stego_I(i,j)==PK
            t = t+1;
            stego_I(i,j) = stego_I(i,j) + Data(t);
        end
    end
end
%% ͳ��Ƕ���������Ϣ
emD = Data(1:t);
end