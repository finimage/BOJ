#include<iostream>
#include<algorithm>
using namespace std;

int arr[51], ans[51];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, i, le, ri, dif = 0; cin >> n;
    for (i = 0; i < n; i++) cin >> arr[i];
    sort(arr, arr + n);
    ans[0] = arr[0], ans[n] = arr[0], le = 0, ri = n;
    for (i = 1; i < n; i++) {
        if (arr[i] - ans[le] >= arr[i] - ans[ri]) {
            dif = max(dif, arr[i] - ans[le]);
            le++;
            ans[le] = arr[i];
        }
        else {
            dif = max(dif, arr[i] - ans[ri]);
            ri--;
            ans[ri] = arr[i];
        }
    }
    le = 0, ri = n;
    for (i = 1; i < n - 1; i++) {
        if (arr[i + 1] - ans[ri] > dif) {
            ri--;
            ans[ri] = arr[i];
        }
        else if (arr[i] - ans[le] <= dif && arr[i + 1] - ans[ri] <= dif) {
            le++;
            ans[le] = arr[i];
        }
    }
    ans[ri - 1] = arr[n - 1];
    for (i = 0; i < n; i++) cout << ans[i] << ' ';
}
