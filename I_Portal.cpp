#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fast                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

#define ll long long
#define nn '\n'
#define Setpre(n) cout << fixed << setprecision(n)

const double EPS = 1e-9;

// given 2 teleporter positions  x1,y1 and x2,y2
// find 2 points with maxm distance

struct pt {
    double x, y;
};

double distSq(pt p1, pt p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

double dist(pt p1, pt p2) {
    return sqrt(distSq(p1, p2));
}

double eval_path(pt a, pt b, pt p1, pt p2) {
    double d1 = dist(a, b);
    double d2 = dist(b, p1) + dist(a, p2);
    double d3 = dist(b, p2) + dist(a, p1);
    return min({d1, d2, d3});
}

void solve_quad(double a, double b, double c, vector<double>& roots) {
    if (abs(a) < EPS) {
        if (abs(b) > EPS) roots.push_back(-c / b);
        return;
    }
    double delta = b * b - 4 * a * c;
    if (delta >= -EPS) {
        if (delta < 0) delta = 0;
        double sqrt_delta = sqrt(delta);
        roots.push_back((-b + sqrt_delta) / (2 * a));
        roots.push_back((-b - sqrt_delta) / (2 * a));
    }
}

void find_crit_pts(pt anchor, pt start, pt end, pt p1, pt p2, vector<pt>& cands) {
    pt v = {end.x - start.x, end.y - start.y};

    {
        double const_d = dist(anchor, p2);
        double l_a = 2 * (v.x * (start.x - anchor.x) + v.y * (start.y - anchor.y)) - 2 * (v.x * (start.x - p1.x) + v.y * (start.y - p1.y));
        double l_b = distSq(start, anchor) - distSq(start, p1) - const_d * const_d;
        double q_a = v.x * v.x + v.y * v.y;
        double q_b = 2 * (v.x * (start.x - p1.x) + v.y * (start.y - p1.y));
        double q_c = distSq(start, p1);
        
        vector<double> roots;
        solve_quad(l_a * l_a - 4 * const_d * const_d * q_a, 2 * l_a * l_b - 4 * const_d * const_d * q_b, l_b * l_b - 4 * const_d * const_d * q_c, roots);
        for(double t : roots) {
            if (t >= -EPS && t <= 1.0 + EPS) {
                cands.push_back({start.x + t * v.x, start.y + t * v.y});
            }
        }
    }

    {
        double const_d = dist(anchor, p1);
        double l_a = 2 * (v.x * (start.x - anchor.x) + v.y * (start.y - anchor.y)) - 2 * (v.x * (start.x - p2.x) + v.y * (start.y - p2.y));
        double l_b = distSq(start, anchor) - distSq(start, p2) - const_d * const_d;
        double q_a = v.x * v.x + v.y * v.y;
        double q_b = 2 * (v.x * (start.x - p2.x) + v.y * (start.y - p2.y));
        double q_c = distSq(start, p2);
        
        vector<double> roots;
        solve_quad(l_a * l_a - 4 * const_d * const_d * q_a, 2 * l_a * l_b - 4 * const_d * const_d * q_b, l_b * l_b - 4 * const_d * const_d * q_c, roots);
        for(double t : roots) {
            if (t >= -EPS && t <= 1.0 + EPS) {
                cands.push_back({start.x + t * v.x, start.y + t * v.y});
            }
        }
    }
}

void solve(int tno) {
    cout << "Case #" << tno << ": " << nn;
    double W, H;
    pt p1, p2;
    cin >> W >> H >> p1.x >> p1.y >> p2.x >> p2.y;

    vector<pt> critics;
    critics.push_back({0, 0}); critics.push_back({W, 0});
    critics.push_back({0, H}); critics.push_back({W, H});
    vector<pt> portals = {p1, p2};
    for(const auto& p : portals) {
        if(p.x >= -EPS && p.x <= W + EPS) { critics.push_back({p.x, 0}); critics.push_back({p.x, H}); }
        if(p.y >= -EPS && p.y <= H + EPS) { critics.push_back({0, p.y}); critics.push_back({W, p.y}); }
    }
    for(auto& p : critics) {
        p.x = max(0.0, min(W, p.x));
        p.y = max(0.0, min(H, p.y));
    }
    
    double max_d = -1.0;
    pt ans_a, ans_b;

    vector<pair<pt, pt>> edges = { {{0,0}, {W,0}}, {{W,0}, {W,H}}, {{W,H}, {0,H}}, {{0,H}, {0,0}} };

    for(const auto& pa : critics) {
        vector<pt> cands = critics;
        for (const auto& edge : edges) {
            find_crit_pts(pa, edge.first, edge.second, p1, p2, cands);
        }
        for(auto& p : cands) {
            p.x = max(0.0, min(W, p.x));
            p.y = max(0.0, min(H, p.y));
        }

        for(const auto& pb : cands) {
            double d = eval_path(pa, pb, p1, p2);
            if (d > max_d) {
                max_d = d;
                ans_a = pa;
                ans_b = pb;
            }
        }
    }

    Setpre(8) << ans_a.x << " " << ans_a.y << nn;
    Setpre(8) << ans_b.x << " " << ans_b.y << nn;
}

int main() {
    fast;
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve(i);
    }
    return 0;
}