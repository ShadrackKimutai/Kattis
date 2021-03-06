#include <iostream>
#include <vector>
using namespace std;

long long BIT[5000001];
int n,k;

inline void update(int x, long long val)
{
    for(; x <= n; x += x&-x){
        BIT[x] += val;
    }
}
inline long long query(int x)
{
     long long sum = 0;
     for(; x > 0; x -= x&-x)
        sum += BIT[x];
     return sum;
}

long long sum(int i , int j){
	cerr << i << " " << j << endl;
	return query(j) - query(i-1);
}

int main(){
	cin >> n >> k;
	string s;
	cin >> s;
	vector<bool> a(n,false);
	for (int i=0;i<n;i++){
		if (s[i] == '0') update(i+1,1);
	}
	cout << "Gooz?" << endl;
	int lo = 1 , hi = k+1 , answer = n , cur;
	for (int i=k/2;i<n-k/2;i++){
		if (k % 2 == 0){ // even
			while (sum(lo,i-1) > k/2) lo++;
			while (sum(i+1,hi) < k/2) hi++;
			if (hi>n) break;
			cur = max(i-lo , hi-i);
			if (sum(lo,hi) == k+1) answer = min(answer , cur);
		}
		else { // odd
			while (sum(lo,i-1) > k/2) lo++;
			while (sum(i+1,hi) < k/2+1) hi++;
			if (hi>n) break;
			cur = max(i-lo , hi-i);
			if (sum(lo,hi) == k+1) answer = min(answer , cur);
			while (sum(lo,i-1) < k/2+1) lo--;
			while (sum(i+1,hi) > k/2) hi--;
			if (lo<1) break;
			cur = max(i-lo , hi-i);
			if (sum(lo,hi) == k+1) answer = min(answer , cur);
		}
	}
	cout << answer << endl;
	return 0;
}
