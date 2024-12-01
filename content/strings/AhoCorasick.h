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

template<char first = 'a', int alpha = 26>
struct AhoCorasick {
	struct Node {
		// (nmatches is optional)
		int next[alpha], end = -1; // nmatches = 0;
        // next contains the next node along with the failure links of each node
        // end contains the index of the pattern which ends at that node or -1 otherwise
		Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> N;
	vector<int> backp, sizes;
    // backp contains the dictionary links of each pattern
 
	void insert(string& s, int j, vector<int>& start) {
		// assert(!s.empty());
		int n = 0;
		for (char c : s) {
			int& m = N[n].next[c - first];
			if (m == -1){
                n = m = N.size();
                N.emplace_back(-1);
                start.push_back(-1);
            }
			else n = m;
		}
		if (N[n].end == -1) start[n] = j;
		backp.push_back(N[n].end);
		N[n].end = j;
		// N[n].nmatches++;
	}
	AhoCorasick(vector<string>& pat): N(1, -1) {
        vector<int> start(1, -1);
		for(int i = 0; i < pat.size(); ++i){
            insert(pat[i], i, start);
            sizes.push_back(pat[i].size());
        }
        vector<int> back(N.size()+1);
		back[0] = N.size();
		N.emplace_back(0);
        start.push_back(-1);
 
		queue<int> q;
		for (q.push(0); !q.empty(); q.pop()) {
			int n = q.front(), prev = back[n];
			for (int i = 0; i < alpha; ++i) {
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (ed == -1) ed = y;
				else {
					back[ed] = y;
					(N[ed].end == -1 ? N[ed].end : backp[start[ed]])
						= N[y].end;
					// N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}
 
    // find(word) returns for each position the index of the longest word that ends there, or -1 if none.
    // find(x) is O(N), where N = length of x.
	vector<int> find(string& word) {
		int n = 0;
		vector<int> res; // ll count = 0;
        // count is total no. of matches
		for (char c : word) {
			n = N[n].next[c - first];
			res.push_back(N[n].end);
			// count += N[n].nmatches;
		}
		return res;
	}
 
    // findAll(-, word) finds all words (up to N*sqrt(N) many if no duplicate patterns)
    // that start at each position (shortest first).
    // findAll is O(NM).
	vector<vector<int>>findAll(string& word) {
		vector<int> r = find(word);
		vector<vector<int>> res(word.size());
		// vector<int> res(sizes.size(), 0);
        // ^ This version counts the freq of each pattern
		for (int i = 0; i < word.size(); ++i) {
			int ind = r[i];
			while (ind != -1) {
                res[i - sizes[ind] + 1].push_back(ind);
				// ++res[ind];
				ind = backp[ind];
			}
		}
		return res;
	}
};
