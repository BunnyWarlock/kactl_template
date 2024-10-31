typedef pair<int64_t, int64_t> pll;

vector<pll> convexHull(vector<pll> pts) {
	if (pts.size() <= 1) return pts;
	sort(pts.begin(), pts.end());
	vector<pll> h(pts.size()+1);
	auto cross = [](pll p, pll a, pll b){
		return (a.first-p.first)*(b.second-p.second) -
			(a.second-p.second)*(b.first-p.first);
	}; // Returns the cross product of vectors pa and pb
	int s = 0, t = 0, i;
	for (i = 2; i--; s = --t, reverse(pts.begin(), pts.end()))
		for (pll& p : pts) {
			while (t >= s + 2 && cross(h[t-2], h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}
