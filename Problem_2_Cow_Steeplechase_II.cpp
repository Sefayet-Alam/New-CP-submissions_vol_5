#include <bits/stdc++.h>

using namespace std;

long long sweep_line_x;

struct Segment {
    long long a, b;
    long long x, y;
    long long idx;
};

// Move coordinate function above operator< to avoid error
double coordinate(Segment a) {
    if (a.a == a.x) { return a.b; }
    return a.b + (a.y - a.b) * (sweep_line_x - a.a) / (a.x - a.a);
}

bool operator<(Segment a, Segment b) {
    return a.idx != b.idx && (coordinate(a) <= coordinate(b));
}

bool operator==(Segment a, Segment b) { return a.idx == b.idx; }

int sign(long long x) {
    if (x == 0) {
        return 0;
    } else {
        return x < 0 ? -1 : +1;
    }
}

struct Point {
    long long x, y, segment_idx;
    bool operator<(const Point &other) {
        return x == other.x ? y < other.y : x < other.x;
    }
};
int operator*(Point p1, Point p2) { return sign(p1.x * p2.y - p1.y * p2.x); }

Point operator-(Point p1, Point p2) {
    return {p1.x - p2.x, p1.y - p2.y};
}

bool intersect(Segment a, Segment b) {
    Point p1 = {a.a, a.b}, q1 = {a.x, a.y}, p2 = {b.a, b.b}, q2 = {b.x, b.y};
    return ((q2 - p1) * (q1 - p1)) * ((q1 - p1) * (p2 - p1)) >= 0 &&
           ((q1 - p2) * (q2 - p2)) * ((q2 - p2) * (p1 - p2)) >= 0;
}

long long orientation(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

int main() {
    int n;
    cin >> n;
    vector<Segment> segments;
    vector<Point> events;

    for (int i = 0; i < n; i++) {
        int a, b, x, y;
        cin >> a >> b >> x >> y;
        segments.push_back({a, b, x, y, i});
        events.push_back({a, b, i});
        events.push_back({x, y, i});
    }

    sort(events.begin(), events.end());

    set<Segment> active_segments;
    int first_segment, second_segment;

    for (int i = 0; i < 2 * n; i++) {
        first_segment = events[i].segment_idx;
        sweep_line_x = events[i].x;
        auto it = active_segments.find(segments[first_segment]);

        if (it != active_segments.end()) {
            auto after = next(it), before = it;
            if (before != active_segments.begin() && after != active_segments.end()) {
                before--;
                if (intersect(segments[before->idx], segments[after->idx])) {
                    first_segment = before->idx;
                    second_segment = after->idx;
                    break;
                }
            }
            active_segments.erase(it);
        } else {
            it = active_segments.lower_bound(segments[first_segment]);
            if (it != active_segments.end() && intersect(segments[first_segment], *it)) {
                second_segment = it->idx;
                break;
            }
            if (it != active_segments.begin()) {
                it--;
                if (intersect(segments[it->idx], segments[first_segment])) {
                    second_segment = it->idx;
                    break;
                }
            }
            active_segments.insert(segments[first_segment]);
        }
    }

    if (first_segment > second_segment) { swap(first_segment, second_segment); }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (i != second_segment && intersect(segments[i], segments[second_segment])) {
            ans++;
        }
    }

    cout << (ans > 1 ? second_segment + 1 : first_segment + 1) << endl;
}
