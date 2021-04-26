#include <bits/stdc++.h>
typedef long long ll;
#define double long double
inline ll read() {
    char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
    ll k = 0, kk = 1;
	if (c == '-') c = getchar() , kk = -1;
    while (c >= '0' && c <= '9') k = k * 10 + c - '0', c = getchar();
	return kk * k;
}
void write(ll x) {
	if (x < 0) x = -x, putchar('-');
	if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}
void writeln(ll x) {write(x); puts("");}
using namespace std;
#define eps1 1e-12
#define eps2 1e-9
#define maxint 1
#define pi acos(-1)
double F(double x, double y) {
	return x+y;
}
double simp_x(double l, double r, double Fl, double Fr, double y) {
	double mid = (l+r)/2;
	double Fmid = F(mid, y);
	double eps =fabs(Fl+Fr-2*Fmid)*(r-l);
	if (eps < eps1 && r-l < maxint) return (Fl + Fr + Fmid * 4.0)/6.0*(r-l);
		else return simp_x(l, mid, Fl, Fmid, y)+simp_x(mid, r, Fmid, Fr, y);
}
double low_x(double y) {
	return y*y*y*y;
}
double up_x(double y) {
	return y*y*y;
}
double simp_y(double l, double r, double Fl, double Fr) {
	double mid = (l+r)/2;
	double Fmid = simp_x(low_x(mid), up_x(mid), F(low_x(mid),mid), F(up_x(mid),mid), mid);
	double eps =fabs(Fl+Fr-2*Fmid)*(r-l);
	if (eps < eps2 && r-l < maxint) return (Fl + Fr + Fmid * 4.0)/6.0*(r-l);
		else return simp_y(l, mid, Fl, Fmid)+simp_y(mid, r, Fmid, Fr);
}
signed main() {
	//lowerbound and upperpound of y
	double yl = 0, yr = 1;
	
	double yFl = simp_x(low_x(yl),up_x(yl),F(low_x(yl),yl),F(up_x(yl),yl), yl);
	double yFr = simp_x(low_x(yr),up_x(yr),F(low_x(yr),yr),F(up_x(yr),yr), yl);
	
	printf("%.12Lf",simp_y(yl, yr, yFl, yFr));
	return 0;
}
