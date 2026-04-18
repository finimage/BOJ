#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define x first
#define y second
#define MOD 1000000007
using namespace std;
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
ll n, m, q;
ll arr[2501];
ll Max[200001], Min[200001];
ll a1, a2;
 
void find(ll ind) {
    if (ind > n) ind -= n;
    if (Min[ind] == 0) {
        cout << "? " << ind << endl;
        cin >> Min[ind] >> Max[ind];
        Min[ind + n] = Min[ind];
        Max[ind + n] = Max[ind];
    }
}
 
bool check(ll ind) {
    if (a1 == 0 && Min[ind] == 1) {
        ll le = ind, ri = ind + 99, mid;
        while (le <= ri) {
            mid = (le + ri) / 2;
            find(mid);
            if (Min[mid] == 1) {
                a1 = mid;
                le = mid + 1;
            }
            else ri = mid - 1;
        }
    }
    if (a2 == 0 && Max[ind] == n) {
        ll le = ind, ri = ind + 99, mid;
        while (le <= ri) {
            mid = (le + ri) / 2;
            find(mid);
            if (Max[mid] == n) {
                a2 = mid;
                le = mid + 1;
            }
            else ri = mid - 1;
        }
    }
    if (a1 * a2) return 1;
    return 0;
}
 
void ifa1(ll k1, ll k2) {
    ll le = k1, ri = k2, mid;
    while (le <= ri) {
        mid = (le + ri) / 2;
        find(mid);
        if (check(mid)) return;
        find(mid + 1);
        if (check(mid + 1)) return;
        if (Max[mid] == n || Max[mid + 1] == n) break;
        if (Max[mid] < Max[mid + 1]) le = mid + 1;
        else ri = mid - 1;
    }
}
 
void ifa2(ll k1, ll k2) {
    ll le = k1, ri = k2, mid;
    while (le <= ri) {
        mid = (le + ri) / 2;
        find(mid);
        if (check(mid)) return;
        find(mid + 1);
        if (check(mid + 1)) return;
        if (Max[mid] == 1 || Max[mid + 1] == 1) break;
        if (Max[mid] > Max[mid + 1]) le = mid + 1;
        else ri = mid - 1;
    }
}
 
void st4() {
    ll i;
    find(1);
    if (check(1)) return;
    find(2);
    if (check(2)) return;
    if (a1) {
        ifa1(a1 + 1, n);
        return;
    }
    if (a2) {
        ifa2(a2 + 1, n);
        return;
    }
    if (Min[1] < Min[2]) {
        ll le = 1, ri = n, mid;
        while (le <= ri) {
            mid = (le + ri) / 2;
            find(mid);
            if (check(mid)) return;
            find(mid + 1);
            if (check(mid + 1)) return;
            if (Min[mid] > Min[mid + 1]) break;
            if (Min[mid + 1] < Min[1]) ri = mid;
            else if (Min[mid] > Min[1]) le = mid + 1;
            if (a1) {
                ifa1(le, a1 - 1);
                return;
            }
            if (a2) {
                ifa2(a2 + 1, ri);
                return;
            }
        }
        ll lle = mid + 1, rri = ri;
        ri = mid;
        if (a2 == 0) {
            while (le <= ri) {
                mid = (le + ri) / 2;
                find(mid);
                if (check(mid)) return;
                find(mid + 1);
                if (check(mid + 1)) return;
                if (a2) break;
                if (Max[mid] < Max[mid + 1]) le = mid + 1;
                else ri = mid - 1;
            }
        }
        le = lle; ri = rri;
        if (a1 == 0) {
            while (le <= ri) {
                mid = (le + ri) / 2;
                find(mid);
                if (check(mid)) return;
                find(mid + 1);
                if (check(mid + 1)) return;
                if (a1) break;
                if (Max[mid] > Max[mid + 1]) le = mid + 1;
                else ri = mid - 1;
            }
        }
    }
    else {
        ll le = 1, ri = 100000, mid;
        while (le <= ri) {
            mid = (le + ri) / 2;
            find(mid);
            if (check(mid)) return;
            find(mid + 1);
            if (check(mid + 1)) return;
            if (Min[mid] < Min[mid + 1]) break;
            if (Min[mid + 1] > Min[1]) ri = mid;
            else if (Min[mid] < Min[1]) le = mid + 1;
            if (a1) {
                ifa1(a1 + 1, ri);
                return;
            }
            if (a2) {
                ifa2(le, a2 - 1);
                return;
            }
        }
        ll lle = mid + 1, rri = ri;
        ri = mid;
        if (a1 == 0) {
            while (le <= ri) {
                mid = (le + ri) / 2;
                find(mid);
                if (check(mid)) return;
                find(mid + 1);
                if (check(mid + 1)) return;
                if (a1) break;
                if (Max[mid] > Max[mid + 1]) le = mid + 1;
                else ri = mid - 1;
            }
        }
        le = lle; ri = rri;
        if (a2 == 0) {
            while (le <= ri) {
                mid = (le + ri) / 2;
                find(mid);
                if (check(mid)) return;
                find(mid + 1);
                if (check(mid + 1)) return;
                if (a2) break;
                if (Max[mid] < Max[mid + 1]) le = mid + 1;
                else ri = mid - 1;
            }
        }
    }
}
 
void solve() {
    ll i, a, b, ans1 = 100, ans2 = 100; cin >> n >> m >> q;
    if (n == 101 && m == 100) {
        ll aa = 1, bb = n;
        for (i = 1; i <= 100; i++) {
            cout << "? " << i << endl;
            cin >> a >> b;
            if (aa == 1 && a != 1) {
                ans1 = i - 1;
                if (ans1 == 0) ans1 = 101;
            }
            if (bb == n && b != n) {
                ans2 = i - 1;
                if (ans2 == 0) ans2 = 101;
            }
            aa = a;
            bb = b;
        }
        cout << "! " << ans1 << ' ' << ans2 << endl;
    }
    else if (n == 8000 && m == 100) {
        ll aa, bb;
        for (i = 1; i <= 80; i++) {
            cout << "? " << (i - 1) * 100 + 1 << endl;
            cin >> a >> b;
            if (a == 1) aa = (i - 1) * 100 + 1;
            if (b == n) bb = (i - 1) * 100 + 1;
        }
        ll le = aa, ri = aa + 99, mid;
        while (le <= ri) {
            mid = (le + ri) / 2;
            cout << "? " << mid << endl;
            cin >> a >> b;
            if (a != 1) ri = mid - 1;
            else {
                le = mid + 1;
                ans1 = mid;
            }
        }
        le = bb; ri = bb + 99;
        while (le <= ri) {
            mid = (le + ri) / 2;
            cout << "? " << mid << endl;
            cin >> a >> b;
            if (b != n) ri = mid - 1;
            else {
                le = mid + 1;
                ans2 = mid;
            }
        }
        cout << "! " << ans1 << ' ' << ans2 << endl;
    }
    else if (n == 2500 && m == 1) {/*st3*/
        ans1 = ans2 = 0;
        cout << "? " << 1 << endl;
        cin >> arr[1] >> a;
        cout << "? " << 2 << endl;
        cin >> arr[2] >> a;
        if (arr[1] == n) ans2 = 1;
        if (arr[2] == n) ans2 = 2;
        if (arr[1] == 1) ans1 = 1;
        if (arr[2] == 1) ans1 = 2;
        if (ans1 && ans2) {
            ll good = 1;
        }
        else if (arr[1] < arr[2]) {
            ll tf = 0, ck1 = 2451, ck2 = 2451;
            for (i = 51; i <= n; i += 50) {
                cout << "? " << i << endl;
                cin >> arr[i] >> a;
                if (arr[i] == n) ans2 = i;
                if (arr[i] == 1) ans1 = i;
                if (!tf && arr[i - 50] > arr[i]) {
                    tf = 1;
                    ck1 = i - 50;
                }
                else if (tf == 1 && arr[i - 50] < arr[i]) {
                    tf = 2;
                    ck2 = i - 50;
                }
            }
            if (tf == 1) {
                if (ck1 == 1) {//case1
                    ll le = 1, ri = 50, llr, lrr;
                    while (le + 3 <= ri) {//n
                        llr = (le * 2 + ri) / 3;
                        if (arr[llr] == 0) {
                            cout << "? " << llr << endl;
                            cin >> arr[llr] >> a;
                        }
                        if (arr[llr] == n) {
                            ans2 = llr;
                            break;
                        }
                        lrr = (le + ri * 2) / 3;
                        if (arr[lrr] == 0) {
                            cout << "? " << lrr << endl;
                            cin >> arr[lrr] >> a;
                        }
                        if (arr[lrr] == n) {
                            ans2 = lrr;
                            break;
                        }
                        if (arr[llr] > arr[lrr]) ri = lrr;
                        else le = llr;
                    }
                    if (ans2 == 0) {
                        for (i = le; i <= ri; i++) {
                            if (arr[i] == 0) {
                                cout << "? " << i << endl;
                                cin >> arr[i] >> a;
                            }
                            if (arr[i] == n) ans2 = i;
                        }
                    }
                    if (arr[ck2 + 1] == 0) {
                        cout << "? " << ck2 + 1 << endl;
                        cin >> arr[ck2 + 1] >> a;
                    }
                    if (arr[ck2 + 1] == 1) ans1 = ck2 + 1;
                    if (ans1) {
                        ll good = 1;
                    }
                    else if (arr[ck2] > arr[ck2 + 1]) {
                        le = ck2; ri = ck2 + 49;
                        while (le + 3 <= ri) {//1
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == 1) {
                                ans1 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == 1) {
                                ans1 = lrr;
                                break;
                            }
                            if (arr[llr] < arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans1 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == 1) ans1 = i;
                            }
                        }
                    }
                    else {
                        le = ck2 - 50; ri = ck2 - 1;
                        while (le + 3 <= ri) {//1
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == 1) {
                                ans1 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == 1) {
                                ans1 = lrr;
                                break;
                            }
                            if (arr[llr] < arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans1 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == 1) ans1 = i;
                            }
                        }
                    }
                }
                else {//case2
                    //n
                    if (arr[ck1 + 1] == 0) {
                        cout << "? " << ck1 + 1 << endl;
                        cin >> arr[ck1 + 1] >> a;
                    }
                    if (arr[ck1 + 1] == n) ans2 = ck1 + 1;
                    if (ans2) {
                        ll good = 1;
                    }
                    else if (arr[ck1] < arr[ck1 + 1]) {
                        ll le = ck1, ri = ck1 + 49, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == n) {
                                ans2 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == n) {
                                ans2 = lrr;
                                break;
                            }
                            if (arr[llr] > arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans2 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == n) ans2 = i;
                            }
                        }
                    }
                    else {
                        ll le = ck1 - 50, ri = ck1 - 1, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == n) {
                                ans2 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == n) {
                                ans2 = lrr;
                                break;
                            }
                            if (arr[llr] > arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans2 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == n) ans2 = i;
                            }
                        }
                    }
                    //1
                    if (arr[ck2 + 1] == 0) {
                        cout << "? " << ck2 + 1 << endl;
                        cin >> arr[ck2 + 1] >> a;
                    }
                    if (arr[ck2 + 1] == 1) ans1 = ck2 + 1;
                    if (ans1) {
                        ll good = 1;
                    }
                    else if (arr[ck2] > arr[ck2 + 1]) {
                        ll le = ck2, ri = ck2 + 49, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == 1) {
                                ans1 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == 1) {
                                ans1 = lrr;
                                break;
                            }
                            if (arr[llr] < arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans1 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == 1) ans1 = i;
                            }
                        }
                    }
                    else {
                        ll le = ck2 - 50, ri = ck2 - 1, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == 1) {
                                ans1 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == 1) {
                                ans1 = lrr;
                                break;
                            }
                            if (arr[llr] < arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans1 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == 1) ans1 = i;
                            }
                        }
                    }
                }
            }
            else if (tf == 2) {
                if (ck1 + 50 == ck2) {
                    if (arr[ck1 + 1] == 0) {
                        cout << "? " << ck1 + 1 << endl;
                        cin >> arr[ck1 + 1] >> a;
                    }
                    if (arr[ck1 + 1] == n) ans2 = ck1 + 1;
                    if (arr[ck2 - 1] == 0) {
                        cout << "? " << ck2 - 1 << endl;
                        cin >> arr[ck2 - 1] >> a;
                    }
                    if (arr[ck2 - 1] == 1) ans1 = ck2 - 1;
                    if (arr[ck1] < arr[ck1 + 1] && arr[ck2 - 1] < arr[ck2]) {//case3
                        //3
                        if (ans1 == 0) ans1 = ck2 - 2;
                        if (ans2 == 0) ans2 = ck2 - 2;
                        for (i = ck1 + 2; i < ck2 - 2; i++) {
                            if (arr[i] == 0) {
                                cout << "? " << i << endl;
                                cin >> arr[i] >> a;
                            }
                            if (arr[i] == 1) ans1 = i;
                            if (arr[i] == n) ans2 = i;
                        }
                    }
                    else {//case4
                        //n
                        if (ans2) {
                            ll good = 1;
                        }
                        else if (arr[ck1] < arr[ck1 + 1]) {
                            ll le = ck1, ri = ck1 + 49, llr, lrr;
                            while (le + 3 <= ri) {
                                llr = (le * 2 + ri) / 3;
                                if (arr[llr] == 0) {
                                    cout << "? " << llr << endl;
                                    cin >> arr[llr] >> a;
                                }
                                if (arr[llr] == n) {
                                    ans2 = llr;
                                    break;
                                }
                                lrr = (le + ri * 2) / 3;
                                if (arr[lrr] == 0) {
                                    cout << "? " << lrr << endl;
                                    cin >> arr[lrr] >> a;
                                }
                                if (arr[lrr] == n) {
                                    ans2 = lrr;
                                    break;
                                }
                                if (arr[llr] > arr[lrr]) ri = lrr;
                                else le = llr;
                            }
                            if (ans2 == 0) {
                                for (i = le; i <= ri; i++) {
                                    if (arr[i] == 0) {
                                        cout << "? " << i << endl;
                                        cin >> arr[i] >> a;
                                    }
                                    if (arr[i] == n) ans2 = i;
                                }
                            }
                        }
                        else {
                            ll le = ck1 - 50, ri = ck1 - 1, llr, lrr;
                            while (le + 3 <= ri) {
                                llr = (le * 2 + ri) / 3;
                                if (arr[llr] == 0) {
                                    cout << "? " << llr << endl;
                                    cin >> arr[llr] >> a;
                                }
                                if (arr[llr] == n) {
                                    ans2 = llr;
                                    break;
                                }
                                lrr = (le + ri * 2) / 3;
                                if (arr[lrr] == 0) {
                                    cout << "? " << lrr << endl;
                                    cin >> arr[lrr] >> a;
                                }
                                if (arr[lrr] == n) {
                                    ans2 = lrr;
                                    break;
                                }
                                if (arr[llr] > arr[lrr]) ri = lrr;
                                else le = llr;
                            }
                            if (ans2 == 0) {
                                for (i = le; i <= ri; i++) {
                                    if (arr[i] == 0) {
                                        cout << "? " << i << endl;
                                        cin >> arr[i] >> a;
                                    }
                                    if (arr[i] == n) ans2 = i;
                                }
                            }
                        }
                        //1
                        if (ans1) {
                            ll good = 1;
                        }
                        else if (arr[ck2 - 1] < arr[ck2]) {
                            ll le = ck2 - 50, ri = ck2 - 1, llr, lrr;
                            while (le + 3 <= ri) {
                                llr = (le * 2 + ri) / 3;
                                if (arr[llr] == 0) {
                                    cout << "? " << llr << endl;
                                    cin >> arr[llr] >> a;
                                }
                                if (arr[llr] == 1) {
                                    ans1 = llr;
                                    break;
                                }
                                lrr = (le + ri * 2) / 3;
                                if (arr[lrr] == 0) {
                                    cout << "? " << lrr << endl;
                                    cin >> arr[lrr] >> a;
                                }
                                if (arr[lrr] == 1) {
                                    ans1 = lrr;
                                    break;
                                }
                                if (arr[llr] < arr[lrr]) ri = lrr;
                                else le = llr;
                            }
                            if (ans1 == 0) {
                                for (i = le; i <= ri; i++) {
                                    if (arr[i] == 0) {
                                        cout << "? " << i << endl;
                                        cin >> arr[i] >> a;
                                    }
                                    if (arr[i] == 1) ans1 = i;
                                }
                            }
                        }
                        else {
                            ll le = ck2, ri = ck2 + 49, llr, lrr;
                            while (le + 3 <= ri) {
                                llr = (le * 2 + ri) / 3;
                                if (arr[llr] == 0) {
                                    cout << "? " << llr << endl;
                                    cin >> arr[llr] >> a;
                                }
                                if (arr[llr] == 1) {
                                    ans1 = llr;
                                    break;
                                }
                                lrr = (le + ri * 2) / 3;
                                if (arr[lrr] == 0) {
                                    cout << "? " << lrr << endl;
                                    cin >> arr[lrr] >> a;
                                }
                                if (arr[lrr] == 1) {
                                    ans1 = lrr;
                                    break;
                                }
                                if (arr[llr] < arr[lrr]) ri = lrr;
                                else le = llr;
                            }
                            if (ans1 == 0) {
                                for (i = le; i <= ri; i++) {
                                    if (arr[i] == 0) {
                                        cout << "? " << i << endl;
                                        cin >> arr[i] >> a;
                                    }
                                    if (arr[i] == 1) ans1 = i;
                                }
                            }
                        }
                    }
                }
                else {//case5
                    if (arr[ck1 + 1] == 0) {
                        cout << "? " << ck1 + 1 << endl;
                        cin >> arr[ck1 + 1] >> a;
                    }
                    if (arr[ck1 + 1] == n) ans2 = ck1 + 1;
                    if (arr[ck2 - 1] == 0) {
                        cout << "? " << ck2 - 1 << endl;
                        cin >> arr[ck2 - 1] >> a;
                    }
                    if (arr[ck2 - 1] == 1) ans1 = ck2 - 1;
                    //n
                    if (ans2) {
                        ll good = 1;
                    }
                    else if (arr[ck1] < arr[ck1 + 1]) {
                        ll le = ck1, ri = ck1 + 49, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == n) {
                                ans2 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == n) {
                                ans2 = lrr;
                                break;
                            }
                            if (arr[llr] > arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans2 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == n) ans2 = i;
                            }
                        }
                    }
                    else {
                        ll le = ck1 - 50, ri = ck1 - 1, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == n) {
                                ans2 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == n) {
                                ans2 = lrr;
                                break;
                            }
                            if (arr[llr] > arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans2 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == n) ans2 = i;
                            }
                        }
                    }
                    //1
                    if (ans1) {
                        ll good = 1;
                    }
                    else if (arr[ck2 - 1] < arr[ck2]) {
                        ll le = ck2 - 50, ri = ck2 - 1, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == 1) {
                                ans1 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == 1) {
                                ans1 = lrr;
                                break;
                            }
                            if (arr[llr] < arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans1 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == 1) ans1 = i;
                            }
                        }
                    }
                    else {
                        ll le = ck2, ri = ck2 + 49, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == 1) {
                                ans1 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == 1) {
                                ans1 = lrr;
                                break;
                            }
                            if (arr[llr] < arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans1 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == 1) ans1 = i;
                            }
                        }
                    }
                }
            }
            else {
                if (arr[2452] == 0) {
                    cout << "? " << 2452 << endl;
                    cin >> arr[2452] >> a;
                }
                if (arr[2451] < arr[2452]) {//case6
                    if (ans1 == 0) ans1 = 2500;
                    if (ans2 == 0) ans2 = 2500;
                    for (i = 2453; i < 2500; i++) {
                        if (arr[i] == 0) {
                            cout << "? " << i << endl;
                            cin >> arr[i] >> a;
                        }
                        if (arr[i] == n) ans2 = i;
                        else if (arr[i] == 1) ans1 = i;
                    }
                }
                else {//case7
                    ll le = ck1 - 50, ri = ck1 - 1, llr, lrr;
                    while (le + 3 <= ri) {
                        llr = (le * 2 + ri) / 3;
                        if (arr[llr] == 0) {
                            cout << "? " << llr << endl;
                            cin >> arr[llr] >> a;
                        }
                        if (arr[llr] == n) {
                            ans2 = llr;
                            break;
                        }
                        lrr = (le + ri * 2) / 3;
                        if (arr[lrr] == 0) {
                            cout << "? " << lrr << endl;
                            cin >> arr[lrr] >> a;
                        }
                        if (arr[lrr] == n) {
                            ans2 = lrr;
                            break;
                        }
                        if (arr[llr] > arr[lrr]) ri = lrr;
                        else le = llr;
                    }
                    if (ans2 == 0) {
                        for (i = le; i <= ri; i++) {
                            if (arr[i] == 0) {
                                cout << "? " << i << endl;
                                cin >> arr[i] >> a;
                            }
                            if (arr[i] == n) ans2 = i;
                        }
                    }
                    le = ck2; ri = ck2 + 49;
                    while (le + 3 <= ri) {
                        llr = (le * 2 + ri) / 3;
                        if (arr[llr] == 0) {
                            cout << "? " << llr << endl;
                            cin >> arr[llr] >> a;
                        }
                        if (arr[llr] == 1) {
                            ans1 = llr;
                            break;
                        }
                        lrr = (le + ri * 2) / 3;
                        if (arr[lrr] == 0) {
                            cout << "? " << lrr << endl;
                            cin >> arr[lrr] >> a;
                        }
                        if (arr[lrr] == 1) {
                            ans1 = lrr;
                            break;
                        }
                        if (arr[llr] < arr[lrr]) ri = lrr;
                        else le = llr;
                    }
                    if (ans1 == 0) {
                        for (i = le; i <= ri; i++) {
                            if (arr[i] == 0) {
                                cout << "? " << i << endl;
                                cin >> arr[i] >> a;
                            }
                            if (arr[i] == 1) ans1 = i;
                        }
                    }
                }
            }
        }
        else {
            ll tf = 0, ck1 = 2451, ck2 = 2451;
            for (i = 51; i <= n; i += 50) {
                cout << "? " << i << endl;
                cin >> arr[i] >> a;
                if (arr[i] == n) ans2 = i;
                if (arr[i] == 1) ans1 = i;
                if (!tf && arr[i - 50] < arr[i]) {
                    tf = 1;
                    ck1 = i - 50;
                }
                else if (tf == 1 && arr[i - 50] > arr[i]) {
                    tf = 2;
                    ck2 = i - 50;
                }
            }
            if (tf == 1) {
                if (ck1 == 1) {//case8
                    ll le = 1, ri = 50, llr, lrr;
                    while (le + 3 <= ri) {//1
                        llr = (le * 2 + ri) / 3;
                        if (arr[llr] == 0) {
                            cout << "? " << llr << endl;
                            cin >> arr[llr] >> a;
                        }
                        if (arr[llr] == 1) {
                            ans1 = llr;
                            break;
                        }
                        lrr = (le + ri * 2) / 3;
                        if (arr[lrr] == 0) {
                            cout << "? " << lrr << endl;
                            cin >> arr[lrr] >> a;
                        }
                        if (arr[lrr] == 1) {
                            ans1 = lrr;
                            break;
                        }
                        if (arr[llr] < arr[lrr]) ri = lrr;
                        else le = llr;
                    }
                    if (ans1 == 0) {
                        for (i = le; i <= ri; i++) {
                            if (arr[i] == 0) {
                                cout << "? " << i << endl;
                                cin >> arr[i] >> a;
                            }
                            if (arr[i] == 1) ans1 = i;
                        }
                    }
                    if (arr[2452] == 0) {
                        cout << "? " << 2452 << endl;
                        cin >> arr[2452] >> a;
                    }
                    if (arr[2452] == n) ans2 = 2452;
                    if (ans2) {
                        ll good = 1;
                    }
                    else if (arr[2451] < arr[2452]) {
                        le = 2451; ri = 2500;
                        while (le + 3 <= ri) {//n
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == n) {
                                ans2 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == n) {
                                ans2 = lrr;
                                break;
                            }
                            if (arr[llr] > arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans2 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == n) ans2 = i;
                            }
                        }
                    }
                    else {
                        le = 2401; ri = 2450;
                        while (le + 3 <= ri) {//n
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == n) {
                                ans2 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == n) {
                                ans2 = lrr;
                                break;
                            }
                            if (arr[llr] > arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans2 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == n) ans2 = i;
                            }
                        }
                    }
                }
                else {//case9
                    //1
                    if (arr[ck1 + 1] == 0) {
                        cout << "? " << ck1 + 1 << endl;
                        cin >> arr[ck1 + 1] >> a;
                    }
                    if (arr[ck1 + 1] == 1) ans1 = ck1 + 1;
                    if (ans1) {
                        ll good = 1;
                    }
                    else if (arr[ck1] > arr[ck1 + 1]) {
                        ll le = ck1, ri = ck1 + 49, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == 1) {
                                ans1 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == 1) {
                                ans1 = lrr;
                                break;
                            }
                            if (arr[llr] < arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans1 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == 1) ans1 = i;
                            }
                        }
                    }
                    else {
                        ll le = ck1 - 50, ri = ck1 - 1, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == 1) {
                                ans1 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == 1) {
                                ans1 = lrr;
                                break;
                            }
                            if (arr[llr] < arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans1 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == 1) ans1 = i;
                            }
                        }
                    }
                    //n
                    if (arr[ck2 + 1] == 0) {
                        cout << "? " << ck2 + 1 << endl;
                        cin >> arr[ck2 + 1] >> a;
                    }
                    if (arr[ck2 + 1] == n) ans2 = ck2 + 1;
                    if (ans2) {
                        ll good = 1;
                    }
                    else if (arr[ck2] < arr[ck2 + 1]) {
                        ll le = ck2, ri = ck2 + 49, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == n) {
                                ans2 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == n) {
                                ans2 = lrr;
                                break;
                            }
                            if (arr[llr] > arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans2 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == n) ans2 = i;
                            }
                        }
                    }
                    else {
                        ll le = ck2 - 50, ri = ck2 - 1, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == n) {
                                ans2 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == n) {
                                ans2 = lrr;
                                break;
                            }
                            if (arr[llr] > arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans2 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == n) ans2 = i;
                            }
                        }
                    }
                }
            }
            else if (tf == 2) {
                if (ck1 + 50 == ck2) {//case10
                    if (arr[ck1 + 1] == 0) {
                        cout << "? " << ck1 + 1 << endl;
                        cin >> arr[ck1 + 1] >> a;
                    }
                    if (arr[ck1 + 1] == 1) ans1 = ck1 + 1;
                    if (arr[ck2 - 1] == 0) {
                        cout << "? " << ck2 - 1 << endl;
                        cin >> arr[ck2 - 1] >> a;
                    }
                    if (arr[ck2 - 1] == n) ans2 = ck2 - 1;
                    if (arr[ck1] > arr[ck1 + 1] && arr[ck2 - 1] > arr[ck2]) {
                        //3
                        if (ans1 == 0) ans1 = ck2 - 2;
                        if (ans2 == 0) ans2 = ck2 - 2;
                        for (i = ck1 + 2; i < ck2 - 2; i++) {
                            if (arr[i] == 0) {
                                cout << "? " << i << endl;
                                cin >> arr[i] >> a;
                            }
                            if (arr[i] == 1) ans1 = i;
                            if (arr[i] == n) ans2 = i;
                        }
                    }
                    else {//case11
                        //1
                        if (ans1) {
                            ll good = 1;
                        }
                        else if (arr[ck1] > arr[ck1 + 1]) {
                            ll le = ck1, ri = ck1 + 49, llr, lrr;
                            while (le + 3 <= ri) {
                                llr = (le * 2 + ri) / 3;
                                if (arr[llr] == 0) {
                                    cout << "? " << llr << endl;
                                    cin >> arr[llr] >> a;
                                }
                                if (arr[llr] == 1) {
                                    ans1 = llr;
                                    break;
                                }
                                lrr = (le + ri * 2) / 3;
                                if (arr[lrr] == 0) {
                                    cout << "? " << lrr << endl;
                                    cin >> arr[lrr] >> a;
                                }
                                if (arr[lrr] == 1) {
                                    ans1 = lrr;
                                    break;
                                }
                                if (arr[llr] < arr[lrr]) ri = lrr;
                                else le = llr;
                            }
                            if (ans1 == 0) {
                                for (i = le; i <= ri; i++) {
                                    if (arr[i] == 0) {
                                        cout << "? " << i << endl;
                                        cin >> arr[i] >> a;
                                    }
                                    if (arr[i] == 1) ans1 = i;
                                }
                            }
                        }
                        else {
                            ll le = ck1 - 50, ri = ck1 - 1, llr, lrr;
                            while (le + 3 <= ri) {
                                llr = (le * 2 + ri) / 3;
                                if (arr[llr] == 0) {
                                    cout << "? " << llr << endl;
                                    cin >> arr[llr] >> a;
                                }
                                if (arr[llr] == 1) {
                                    ans1 = llr;
                                    break;
                                }
                                lrr = (le + ri * 2) / 3;
                                if (arr[lrr] == 0) {
                                    cout << "? " << lrr << endl;
                                    cin >> arr[lrr] >> a;
                                }
                                if (arr[lrr] == 1) {
                                    ans1 = lrr;
                                    break;
                                }
                                if (arr[llr] < arr[lrr]) ri = lrr;
                                else le = llr;
                            }
                            if (ans1 == 0) {
                                for (i = le; i <= ri; i++) {
                                    if (arr[i] == 0) {
                                        cout << "? " << i << endl;
                                        cin >> arr[i] >> a;
                                    }
                                    if (arr[i] == 1) ans1 = i;
                                }
                            }
                        }
                        //n
                        if (ans2) {
                            ll good = 1;
                        }
                        else if (arr[ck2 - 1] > arr[ck2]) {
                            ll le = ck2 - 50, ri = ck2 - 1, llr, lrr;
                            while (le + 3 <= ri) {
                                llr = (le * 2 + ri) / 3;
                                if (arr[llr] == 0) {
                                    cout << "? " << llr << endl;
                                    cin >> arr[llr] >> a;
                                }
                                if (arr[llr] == n) {
                                    ans2 = llr;
                                    break;
                                }
                                lrr = (le + ri * 2) / 3;
                                if (arr[lrr] == 0) {
                                    cout << "? " << lrr << endl;
                                    cin >> arr[lrr] >> a;
                                }
                                if (arr[lrr] == n) {
                                    ans2 = lrr;
                                    break;
                                }
                                if (arr[llr] > arr[lrr]) ri = lrr;
                                else le = llr;
                            }
                            if (ans2 == 0) {
                                for (i = le; i <= ri; i++) {
                                    if (arr[i] == 0) {
                                        cout << "? " << i << endl;
                                        cin >> arr[i] >> a;
                                    }
                                    if (arr[i] == n) ans2 = i;
                                }
                            }
                        }
                        else {
                            ll le = ck2, ri = ck2 + 49, llr, lrr;
                            while (le + 3 <= ri) {
                                llr = (le * 2 + ri) / 3;
                                if (arr[llr] == 0) {
                                    cout << "? " << llr << endl;
                                    cin >> arr[llr] >> a;
                                }
                                if (arr[llr] == n) {
                                    ans2 = llr;
                                    break;
                                }
                                lrr = (le + ri * 2) / 3;
                                if (arr[lrr] == 0) {
                                    cout << "? " << lrr << endl;
                                    cin >> arr[lrr] >> a;
                                }
                                if (arr[lrr] == n) {
                                    ans2 = lrr;
                                    break;
                                }
                                if (arr[llr] > arr[lrr]) ri = lrr;
                                else le = llr;
                            }
                            if (ans2 == 0) {
                                for (i = le; i <= ri; i++) {
                                    if (arr[i] == 0) {
                                        cout << "? " << i << endl;
                                        cin >> arr[i] >> a;
                                    }
                                    if (arr[i] == n) ans2 = i;
                                }
                            }
                        }
                    }
                }
                else {//case12
                    if (arr[ck1 + 1] == 0) {
                        cout << "? " << ck1 + 1 << endl;
                        cin >> arr[ck1 + 1] >> a;
                    }
                    if (arr[ck1 + 1] == 1) ans1 = ck1 + 1;
                    if (arr[ck2 - 1] == 0) {
                        cout << "? " << ck2 - 1 << endl;
                        cin >> arr[ck2 - 1] >> a;
                    }
                    if (arr[ck2 - 1] == n) ans2 = ck2 - 1;
                    //1
                    if (ans1) {
                        ll good = 1;
                    }
                    else if (arr[ck1] > arr[ck1 + 1]) {
                        ll le = ck1, ri = ck1 + 49, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == 1) {
                                ans1 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == 1) {
                                ans1 = lrr;
                                break;
                            }
                            if (arr[llr] < arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans1 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == 1) ans1 = i;
                            }
                        }
                    }
                    else {
                        ll le = ck1 - 50, ri = ck1 - 1, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == 1) {
                                ans1 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == 1) {
                                ans1 = lrr;
                                break;
                            }
                            if (arr[llr] < arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans1 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == 1) ans1 = i;
                            }
                        }
                    }
                    //n
                    if (ans2) {
                        ll good = 1;
                    }
                    else if (arr[ck2 - 1] > arr[ck2]) {
                        ll le = ck2 - 50, ri = ck2 - 1, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == n) {
                                ans2 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == n) {
                                ans2 = lrr;
                                break;
                            }
                            if (arr[llr] > arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans2 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == n) ans2 = i;
                            }
                        }
                    }
                    else {
                        ll le = ck2, ri = ck2 + 49, llr, lrr;
                        while (le + 3 <= ri) {
                            llr = (le * 2 + ri) / 3;
                            if (arr[llr] == 0) {
                                cout << "? " << llr << endl;
                                cin >> arr[llr] >> a;
                            }
                            if (arr[llr] == n) {
                                ans2 = llr;
                                break;
                            }
                            lrr = (le + ri * 2) / 3;
                            if (arr[lrr] == 0) {
                                cout << "? " << lrr << endl;
                                cin >> arr[lrr] >> a;
                            }
                            if (arr[lrr] == n) {
                                ans2 = lrr;
                                break;
                            }
                            if (arr[llr] > arr[lrr]) ri = lrr;
                            else le = llr;
                        }
                        if (ans2 == 0) {
                            for (i = le; i <= ri; i++) {
                                if (arr[i] == 0) {
                                    cout << "? " << i << endl;
                                    cin >> arr[i] >> a;
                                }
                                if (arr[i] == n) ans2 = i;
                            }
                        }
                    }
                }
            }
            else {
                if (arr[2452] == 0) {
                    cout << "? " << 2452 << endl;
                    cin >> arr[2452] >> a;
                }
                if (arr[2451] > arr[2452]) {//case13
                    if (ans1 == 0) ans1 = 2500;
                    if (ans2 == 0) ans2 = 2500;
                    for (i = 2453; i < 2500; i++) {
                        if (arr[i] == 0) {
                            cout << "? " << i << endl;
                            cin >> arr[i] >> a;
                        }
                        if (arr[i] == n) ans2 = i;
                        else if (arr[i] == 1) ans1 = i;
                    }
                }
                else {//case14
                    ll le = 2401, ri = 2450, llr, lrr;
                    while (le + 3 <= ri) {
                        llr = (le * 2 + ri) / 3;
                        if (arr[llr] == 0) {
                            cout << "? " << llr << endl;
                            cin >> arr[llr] >> a;
                        }
                        if (arr[llr] == 1) {
                            ans1 = llr;
                            break;
                        }
                        lrr = (le + ri * 2) / 3;
                        if (arr[lrr] == 0) {
                            cout << "? " << lrr << endl;
                            cin >> arr[lrr] >> a;
                        }
                        if (arr[lrr] == 1) {
                            ans1 = lrr;
                            break;
                        }
                        if (arr[llr] < arr[lrr]) ri = lrr;
                        else le = llr;
                    }
                    if (ans1 == 0) {
                        for (i = le; i <= ri; i++) {
                            if (arr[i] == 0) {
                                cout << "? " << i << endl;
                                cin >> arr[i] >> a;
                            }
                            if (arr[i] == 1) ans1 = i;
                        }
                    }
                    le = 2451; ri = 2500;
                    while (le + 3 <= ri) {
                        llr = (le * 2 + ri) / 3;
                        if (arr[llr] == 0) {
                            cout << "? " << llr << endl;
                            cin >> arr[llr] >> a;
                        }
                        if (arr[llr] == n) {
                            ans2 = llr;
                            break;
                        }
                        lrr = (le + ri * 2) / 3;
                        if (arr[lrr] == 0) {
                            cout << "? " << lrr << endl;
                            cin >> arr[lrr] >> a;
                        }
                        if (arr[lrr] == n) {
                            ans2 = lrr;
                            break;
                        }
                        if (arr[llr] > arr[lrr]) ri = lrr;
                        else le = llr;
                    }
                    if (ans2 == 0) {
                        for (i = le; i <= ri; i++) {
                            if (arr[i] == 0) {
                                cout << "? " << i << endl;
                                cin >> arr[i] >> a;
                            }
                            if (arr[i] == n) ans2 = i;
                        }
                    }
                }
            }
        }
        cout << "! " << ans1 << ' ' << ans2 << endl;
    }
    else {/*st4*/
        st4();
        cout << "! " << (a1 > 100000 ? a1 - 100000 : a1) << ' ' << (a2 > 100000 ? a2 - 100000 : a2) << endl;
    }
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T = 1; //cin >> T;
    while (T--) solve();
}
