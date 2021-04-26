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
#define eps2 1e-10
#define eps3 1e-10
#define maxint 1
#define pi acos(-1)
#define a 1
double F(double x, double y, double z) {
	return y;
}
double simp_x(double l, double r, double Fl, double Fr, double y, double z) {
	double mid = (l+r)/2;
	double Fmid = F(mid, y, z);
	double eps =fabs(Fl+Fr-2*Fmid)*(r-l);
	if (eps < eps1 && r-l < maxint) return (Fl + Fr + Fmid * 4.0)/6.0*(r-l);
		else return simp_x(l, mid, Fl, Fmid, y, z)+simp_x(mid, r, Fmid, Fr, y, z);
}
double low_x(double y, double z) {
	return 0;
}
double up_x(double y, double z) {
	return sqrt(a*a-y*y);
}
double simp_y(double l, double r, double Fl, double Fr, double z) {
	double mid = (l+r)/2;
	double Fmid = simp_x(low_x(mid,z), up_x(mid,z), F(low_x(mid,z),mid,z), F(up_x(mid, z),mid, z), mid , z);
	double eps =fabs(Fl+Fr-2*Fmid)*(r-l);
	if (eps < eps2 && r-l < maxint) return (Fl + Fr + Fmid * 4.0)/6.0*(r-l);
		else return simp_y(l, mid, Fl, Fmid, z)+simp_y(mid, r, Fmid, Fr, z);
}
double low_y(double z) {
	return 0;
}
double up_y(double z) {
	return a*cos(z);
}
double simp_z(double l, double r, double Fl, double Fr) {
	double mid = (l+r)/2;
	double yl = low_y(mid), yr = up_y(mid);
	double yFl = simp_x(low_x(yl,mid),up_x(yl,mid),F(low_x(yl,mid),yl,mid),F(up_x(yl,mid),yl,mid), yl, mid);
	double yFr = simp_x(low_x(yr,mid),up_x(yr,mid),F(low_x(yr,mid),yr,mid),F(up_x(yr,mid),yr,mid), yl, mid);
	
	double Fmid = simp_y(low_y(mid), up_y(mid), yFl, yFr, mid);
	double eps =fabs(Fl+Fr-2*Fmid)*(r-l);
	if (eps < eps3 && r-l < maxint) return (Fl + Fr + Fmid * 4.0)/6.0*(r-l);
		else return simp_z(l, mid, Fl, Fmid)+simp_z(mid, r, Fmid, Fr);
}
signed main() {
	//lowerbound and upperpound of y
	double zl = 0, zr = pi/2;
	
	double yl = low_y(zl), yr = up_y(zl);
	double yFl = simp_x(low_x(yl,zl),up_x(yl,zl),F(low_x(yl,zl),yl,zl),F(up_x(yl,zl),yl,zl), yl, zl);
	double yFr = simp_x(low_x(yr,zl),up_x(yr,zl),F(low_x(yr,zl),yr,zl),F(up_x(yr,zl),yr,zl), yl, zl);
	double zFl = simp_y(yl, yr, yFl, yFr, zl);

	yl = low_y(zr), yr = up_y(zr);
	yFl = simp_x(low_x(yl,zr),up_x(yl,zr),F(low_x(yl,zr),yl,zr),F(up_x(yl,zr),yl,zr), yl, zr);
	yFr = simp_x(low_x(yr,zr),up_x(yr,zr),F(low_x(yr,zr),yr,zr),F(up_x(yr,zr),yr,zr), yl, zr);
	double zFr = simp_y(yl, yr, yFl, yFr, zr);
	
	printf("%.12Lf",4*simp_z(zl, zr, zFl, zFr));
	return 0;
}
