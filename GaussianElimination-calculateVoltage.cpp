#include <bits/stdc++.h>
#define eps 1e-9
using namespace std;
int n,k,np,nr,nb,ne;
double a[500][500],f[500][500],X[500];
bool flag[500];

void addEquationU(int x, int y, double dU) {//Ua-Ub=dU, 
	//cout<<x<<' '<<y<<' '<<dU<<endl;
	ne++;
	a[ne][x] = 1;
	a[ne][y] = -1;
	a[ne][k+1] = dU;
	
	a[x][ne] += -1;
	a[y][ne] += 1;
}

void addEquationR(int x, int y, double R) {//dI=(Ua-Ub)/R,Ia-=dI,Ib+=dI
	//cout<<x<<' '<<y<<' '<<R<<endl;
	a[x][x] -= 1.0/R;
	a[x][y] += 1.0/R;
	a[y][y] -= 1.0/R;
	a[y][x] += 1.0/R;
}

void GaussianElimination() {
	for (int i = 1; i <= k; i++) {
		int ptr = -1;
		for (int j = 1; j <= ne; j++) {
			if (!flag[j] && fabs(a[j][i])>eps &&
				(ptr == -1 || fabs(a[j][i])>fabs(a[ptr][i]))) {
					ptr = j;
				}
		}
		if (ptr != -1) {
			flag[ptr] = 1;
			f[i][i] = 1;
			for (int j = i+1; j <= k+1; j++) {
				f[i][j] = a[ptr][j]/a[ptr][i];
			}
			for (int j = 1; j < i; j++) {
				if (fabs(f[j][i])>eps) {
					for (int l = i+1; l <= k+1; l++){
						f[j][l] -= f[j][i]*f[i][l];
					}
					f[j][i] = 0;
				}
			}
			
			for (int j = 1; j <= ne; j++) {
				if (!flag[j] && fabs(a[j][i])>eps) {
					for (int l = i+1; l <= k+1; l++) {
						a[j][l] -= a[j][i]*f[i][l];
					}
					a[j][i] = 0;
				}
			}
		}
	}
	for (int i = 1; i <= k; i++) {
		int flag = 0;
		for (int j = i+1; j <= k; j++) {
			if (fabs(f[i][j])>eps) {
				flag = 1;
				X[i] = 0;
				f[j][j]=1;
				for (int l = j+1; l <= k+1; l++) {
					f[j][l] = f[i][l] / f[i][j];
				}
				for (int jhat = 1; jhat < j; jhat++) {
					if (fabs(f[jhat][j])>eps) {
						for (int l = j+1; l <= k+1; l++){
							f[jhat][l] -= f[jhat][j]*f[j][l];
						}
						f[jhat][j] = 0;
					}
				}
			}
		}
		if (!flag) X[i] = f[i][k+1];
	}
}

signed main() {
	n = 5;//3 point
	ne = n;//numver of equation
	np=1,nr=3,nb=2;
	k = n+np+nb;//number of variable
	double P[10][3] = {
	{2,3,5.68822},
	{3,4,10},
	{6,5,10}
	};
	double R[10][3] = {
	{2,1,1},
	{1,4,2},
	{1,5,1.859},
	{4,5,5},
	{2,5,10}
	};//a,b,R
	double B[10][3] = {
	//{1,2,3}
	{4,3,2.2},
	{5,3,2.8}
	};
	// input
	
	for (int i = 0; i < np; i++) {
		addEquationU(P[i][0], P[i][1], P[i][2]);
	}
	for (int i = 0; i < nr; i++) {
		addEquationR(R[i][0], R[i][1], R[i][2]);
	}
	for (int i = 0; i < nb; i++) {
		addEquationU(B[i][0], B[i][1], B[i][2]);
	}
	
	GaussianElimination();
	char c;
	int x;
	cin>>c;
	while (c!='E') {
		cin>>x;
		if (c == 'R') {
			cout<<"dU="<<X[(int)R[x][0]]-X[(int)R[x][1]]<<endl;
			cout<<"I="<<(X[(int)R[x][0]]-X[(int)R[x][1]])/R[x][2]<<endl;
			cout<<"P="<<(X[(int)R[x][0]]-X[(int)R[x][1]])*(X[(int)R[x][0]]-X[(int)R[x][1]])/R[x][2]<<endl;
		}else if (c == 'B') {
			cout<<"dU="<<X[(int)B[x][0]]-X[(int)B[x][1]]<<endl;
			cout<<"I="<<X[n+np+x+1]<<endl;
			cout<<"P="<<(X[(int)B[x][0]]-X[(int)B[x][1]])*X[n+np+x+1]<<endl;
		}
		cin>>c;
	}
}
/*
预设类：

电源(P)：电压恒定
节点(N)：没有意义，起到连接作用
电阻(R)：满足R=U/I
虚电阻：（电容和电感）(没写)
二极管(B)：压降恒定（等价于电源？）（不考虑被短路问题，如果被短路的话手动当做断路算）


// 前n个是I方程，满足基尔霍夫定律sigma(I)=0，后np+nb个方程代表由电源和二极管给出的限制
//另有np+nb个自由元，代表通过电源/二极管的电流


支持：

探测每个节点的电压
探测二极管，电阻的电流和功率

*/