%最高点出现在pos09
clear;
clc;
%删除部分数据，再进行拟合
%最高点出现在pos09
figure (1);
x=[439893
439907
439920
439934
439948
439962
];
y=[3257.06
3249.45
3450.57
3467.09
3469.7
3464.57
];
p=polyfit(x,y,3); % 拟合出的二次函数的系数
ye=y-polyval(p,x); % 计算误差
ye2s=sum(ye.^2); % 误差的平方和
fprintf('误差的平方和=%d\n',ye2s);
xx=linspace(min(x),max(x)); % 绘图用到的点的横坐标
yy=polyval(p,xx); % 拟合曲线的纵坐标
plot(x,y,'o',xx,yy); % 绘图，原始数据+拟合曲线
legend('原始数据','拟合曲线'); % 图示
syms m;
f(m) = p(1)*m^3 + p(2)*m^2 + p(3)*m^1 + p(4);%拟合函数
f(m);

