%��ߵ������pos09
clear;
clc;
%ɾ���������ݣ��ٽ������
%��ߵ������pos09
figure (1);
x=[
];
y=[
];
p=polyfit(x,y,3); % ��ϳ��Ķ��κ�����ϵ��
ye=y-polyval(p,x); % �������
ye2s=sum(ye.^2); % ����ƽ����
fprintf('����ƽ����=%d\n',ye2s);
xx=linspace(min(x),max(x)); % ��ͼ�õ��ĵ�ĺ�����
yy=polyval(p,xx); % ������ߵ�������
plot(x,y,'o',xx,yy); % ��ͼ��ԭʼ����+�������
legend('ԭʼ����','�������'); % ͼʾ
syms m;
f(m) = p(1)*m^3 + p(2)*m^2 + p(3)*m^1 + p(4);%��Ϻ���
f(m)
