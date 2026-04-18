#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll ans, n;
vector<ll> arr, mmax, mmin, oth;

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int T, test_case;
	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
	    ll i; cin >> n;
	    ll Max = 0, Min = 1e9 + 1, mmax = 0, mmin = 0, maxcnt = 0, mincnt = 0;
	    arr.clear();
	    arr.resize(n + 1);
	    for (i = 1; i <= n; i++) {
	        cin >> arr[i];
	        if (Max < arr[i]) {
	            Max = arr[i];
	            mmax = i;
	            maxcnt = 1;
	        }
	        else if (Max == arr[i]) maxcnt++;
	        if (Min > arr[i]) {
	            Min = arr[i];
	            mmin = i;
	            mincnt = 1;
	        }
	        else if (Min == arr[i]) mincnt++;
	    }
	    if (Min == Max) {
	        cout << "Case #" << test_case+1 << '\n';
		    cout << 0 << '\n';
		    continue;
	    }
	    if (abs(mincnt - maxcnt) <= 1 && mincnt + maxcnt == n) {
	        cout << "Case #" << test_case+1 << '\n';
		    cout << 0 << '\n';
		    continue;
	    }
	    int tftf = 0;
	    if (maxcnt >= n / 2) {
	        ll le = 1, ri = 1, cnt[3] = {0,0,0};
	        while (le <= ri && ri <= n) {
	            if (arr[ri] == Max) {
	                cnt[0]++;
	                if (maxcnt - cnt[0] < n / 2) {
	                    while (le <= ri) {
	                        if (arr[le] == Max) {
	                            cnt[0]--;
	                            le++;
	                            break;
	                        }
	                        else if (arr[le] == Min) cnt[1]--;
	                        else cnt[2]--;
	                        le++;
	                    }
	                }
	            }
	            else if (arr[ri] == Min) {
	                cnt[1]++;
	            }
	            else {
	                cnt[2]++;
	            }
	            if (abs((mincnt + cnt[2] + cnt[0]) - (maxcnt - cnt[0])) <= 1) {
	                if (cnt[1] > 0 && (maxcnt - cnt[0]) + mincnt + cnt[2] + cnt[0] == n) {
	                    cout << "Case #" << test_case+1 << '\n';
	                    cout << 1 << '\n';
	                    cout << 1 << ' ' << le << ' ' << ri << '\n';
	                    tftf = 1;
	                }
	            }
                ri++;
	            if (tftf) break;
	        }
	    }
	    if (tftf) continue;
	    if (mincnt >= n / 2) {
	        ll le = 1, ri = 1, cnt[3] = {0,0,0};
	        while (le <= ri && ri <= n) {
	            if (arr[ri] == Min) {
	                cnt[0]++;
	                if (mincnt - cnt[0] < n / 2) {
	                    while (le <= ri) {
	                        if (arr[le] == Min) {
	                            cnt[0]--;
	                            le++;
	                            break;
	                        }
	                        else if (arr[le] == Max) cnt[1]--;
	                        else cnt[2]--;
	                        le++;
	                    }
	                }
	            }
	            else if (arr[ri] == Max) {
	                cnt[1]++;
	            }
	            else {
	                cnt[2]++;
	            }
	            if (abs((maxcnt + cnt[2] + cnt[0]) - (mincnt - cnt[0])) <= 1) {
	                if (cnt[1] > 0 && (mincnt - cnt[0]) + maxcnt + cnt[2] + cnt[0] == n) {
	                    cout << "Case #" << test_case+1 << '\n';
	                    cout << 1 << '\n';
	                    cout << 2 << ' ' << le << ' ' << ri << '\n';
	                    tftf = 1;
	                }
	            }
                ri++;
	            if (tftf) break;
	        }
	    }
	    if (tftf) continue;
		cout << "Case #" << test_case+1 << '\n';
		cout << 2 << '\n';
		if (mmin < mmax) {
		    if (mmax <= n / 2) {
		        cout << 2 << ' ' << mmax << ' ' << n << '\n';
		        cout << 1 << ' ' << 1 << ' ' << n / 2 << '\n';
		    }
		    else if (mmin <= n / 2) {
		        cout << 2 << ' ' << n / 2 + 1 << ' ' << n << '\n';
		        cout << 1 << ' ' << 1 << ' ' << n / 2 << '\n';
		    }
		    else {
		        cout << 1 << ' ' << 1 << ' ' << mmin << '\n';
		        cout << 2 << ' ' << n / 2 + 1 << ' ' << n << '\n';
		    }
		}
		else {
		    if (mmin <= n / 2) {
		        cout << 1 << ' ' << mmin << ' ' << n << '\n';
		        cout << 2 << ' ' << 1 << ' ' << n / 2 << '\n';
		    }
		    else if (mmax <= n / 2) {
		        cout << 1 << ' ' << n / 2 + 1 << ' ' << n << '\n';
		        cout << 2 << ' ' << 1 << ' ' << n / 2 << '\n';
		    }
		    else {
		        cout << 2 << ' ' << 1 << ' ' << mmax << '\n';
		        cout << 1 << ' ' << n / 2 + 1 << ' ' << n << '\n';
		    }
		}
	}

	return 0;
}
