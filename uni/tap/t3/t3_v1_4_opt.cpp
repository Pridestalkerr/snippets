#include <fstream>
	
#include <iomanip>
	
#include <cmath>
	
#include <algorithm>
	
#define x first
	
#define y second
	
using namespace std;
	
 
	
ifstream fin ("cmap.in");
	
ofstream fout("cmap.out");
	
 
	
long long n,i;
	
pair< long long, long long > v[100010],a[100010],b[100010];
	
 
	
long long d(pair< long long, long long > a,pair< long long, long long > b){
	
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
	
}
	
 
	
void ic(long long st,long long mid,long long dr){
	
    long long i=st;
	
    long long j=mid+1;
	
    long long k=st-1;
	
    while (i<=mid && j<=dr)
	
        if (v[i].y<v[j].y)
	
            a[++k]=v[i++];
	
        else
	
            a[++k]=v[j++];
	
    for (;i<=mid;i++)
	
        a[++k]=v[i];
	
    for (;j<=dr;j++)
	
        a[++k]=v[j];
	
    for (i=st;i<=dr;i++)
	
        v[i]=a[i];
	
}
	
 
	
long long f(long long st,long long dr){
	
    if (dr-st==1){
	
        ic(st,st,dr);
	
        return d(v[st],v[dr]);
	
    }
	
    if (dr-st==2){
	
        ic(st,st,st+1);
	
        ic(st,st+1,dr);
	
        return min(d(v[st],v[st+1]),min(d(v[st],v[dr]),d(v[st+1],v[dr])));
	
    }
	
    long long mid=(st+dr)/2;
	
    long long sol=min(f(st,mid),f(mid+1,dr));
	
    ic(st,mid,dr);
	
    long long i,j;
	
    long long k=0;
	
    for (i=st;i<=dr;i++)
	
        if (abs(v[mid].x-v[i].x)<=sol)
	
            b[++k]=v[i];
	
    for (i=1;i<k;i++)
	
        for (j=i+1;j<=min(k,i+7);j++)
	
            sol=min(sol,d(b[i],b[j]));
	
    return sol;
	
}
	
 
	
int main(){
	
    fin>>n;
	
    for (i=1;i<=n;i++)
	
        fin>>v[i].x>>v[i].y;
	
    sort(v+1,v+n+1);
	
    fout<<setprecision(6)<<fixed<<sqrt(f(1,n));
	
    fin.close();
	
    fout.close();
	
    return 0;
	
}