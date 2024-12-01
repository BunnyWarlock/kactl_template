/**
 * Author: Stjepan Glavina
 * License: Unlicense
 * Source: https://github.com/stjepang/snippets/blob/master/min_rotation.cpp
 * Description: Finds the lexicographically smallest rotation of a string.
 * Time: O(N)
 * Usage:
 *  rotate(v.begin(), v.begin()+minRotation(v), v.end());
 * Status: Stress-tested
 */

// Fenwick tree code insert plz

vector<int> LIS(vector<int>& arr){
    int n = arr.size();
    int ind[n];
    iota(ind, ind+n, 0);
    sort(ind, ind+n, [&](int a, int b){
        if (arr[a] == arr[b])
            return a > b;
        return arr[a] < arr[b];
    });

    vector<int> ans(n);
    FT<int> temp(n, [](int a, int b){ return max(a, b); }, 0);
    for (auto& i: ind){
        ans[i] = temp.query(i) + 1;
        temp.update(i, ans[i]);
    }
    return ans;
}
