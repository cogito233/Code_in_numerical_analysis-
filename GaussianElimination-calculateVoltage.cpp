#include <bits/stdc++.h>
#define eps 1e-9
using namespace std;
int n,k,np,nr,nb,ne;
double a[500][500],f[500][500],X[500];
bool flag[500];

void addEquationU(int x, int y, int dU) {//Ua-Ub=dU, 
	//cout<<x<<' '<<y<<' '<<dU<<endl;
	ne++;
	a[ne][x] = 1;
	a[ne][y] = -1;
	a[ne][k+1] = dU;
	
	a[x][ne] += -1;
	a[y][ne] += 1;
}

void addEquationR(int x, int y, int R) {//dI=(Ua-Ub)/R,Ia-=dI,Ib+=dI
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
	n = 3;//3 point
	ne = n;//numver of equation
	np=1,nr=3,nb=0;
	k = n+np+nb;//number of variable
	int P[10][3] = {
	{1,3,10}
	};
	int R[10][3] = {
	{1,2,5},
	{2,3,10},
	{2,3,10}
	};//a,b,R
	int B[10][3] = {
	//{1,2,3}
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
			cout<<"dU="<<X[R[x][0]]-X[R[x][1]]<<endl;
			cout<<"I="<<(X[R[x][0]]-X[R[x][1]])/R[x][2]<<endl;
			cout<<"P="<<(X[R[x][0]]-X[R[x][1]])*(X[R[x][0]]-X[R[x][1]])/R[x][2]<<endl;
		}else if (c == 'B') {
			cout<<"dU="<<X[B[x][0]]-X[B[x][1]]<<endl;
			cout<<"I="<<X[n+nr+x]<<endl;
			cout<<"P="<<(X[B[x][0]]-X[B[x][1]])*X[n+nr+x]<<endl;
		}
		cin>>c;
	}
}