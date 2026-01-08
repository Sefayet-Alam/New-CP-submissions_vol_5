#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// VVI
#define fast                      \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

#define ll long long
#define SZ(a) (int)a.size()
#define UNIQUE(a) (a).erase(unique(all(a)), (a).end())
#define mp make_pair
#define mem(a, b) memset(a, b, sizeof(a))
#define all(x) x.begin(), x.end()

// Printings & debugging
#define nn '\n'
#define Setpre(n) cout << fixed << setprecision(n)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define debug printf("I am here\n")

/// INLINE FUNCTIONS
inline ll GCD(ll a, ll b) { return b == 0 ? a : GCD(b, a % b); }
inline ll LCM(ll a, ll b) { return a * b / GCD(a, b); }
inline double logb(ll base, ll num) { return (double)log(num) / (double)log(base); }

/// Data structures
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pll> vpll;
typedef vector<vl> vvl;
template <typename T>
using PQ = priority_queue<T>;
template <typename T>
using QP = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R>
using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R>
using ordered_multimap = tree<T, R, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
namespace io
{
    template <typename First, typename Second>
    ostream &operator<<(ostream &os, const pair<First, Second> &p) { return os << p.first << " " << p.second; }
    template <typename First, typename Second>
    ostream &operator<<(ostream &os, const map<First, Second> &mp)
    {
        for (auto it : mp)
        {
            os << it << endl;
        }
        return os;
    }
    template <typename First>
    ostream &operator<<(ostream &os, const vector<First> &v)
    {
        bool space = false;
        for (First x : v)
        {
            if (space)
                os << " ";
            space = true;
            os << x;
        }
        return os;
    }
    template <typename First>
    ostream &operator<<(ostream &os, const set<First> &st)
    {
        bool space = false;
        for (First x : st)
        {
            if (space)
                os << " ";
            space = true;
            os << x;
        }
        return os;
    }
    template <typename First>
    ostream &operator<<(ostream &os, const multiset<First> &st)
    {
        bool space = false;
        for (First x : st)
        {
            if (space)
                os << " ";
            space = true;
            os << x;
        }
        return os;
    }
    template <typename First, typename Second>
    istream &operator>>(istream &is, pair<First, Second> &p) { return is >> p.first >> p.second; }
    template <typename First>
    istream &operator>>(istream &is, vector<First> &v)
    {
        for (First &x : v)
        {
            is >> x;
        }
        return is;
    }

    long long fastread()
    {
        char c;
        long long d = 1, x = 0;
        do
            c = getchar();
        while (c == ' ' || c == '\n');
        if (c == '-')
            c = getchar(), d = -1;
        while (isdigit(c))
        {
            x = x * 10 + c - '0';
            c = getchar();
        }
        return d * x;
    }
    static bool sep = false;
    using std::to_string;
    string to_string(bool x) { return (x ? "true" : "false"); }
    string to_string(const string &s) { return "\"" + s + "\""; }
    string to_string(const char *s) { return "\"" + string(s) + "\""; }
    string to_string(const char &c)
    {
        string s;
        s += c;
        return "\'" + s + "\'";
    }
    template <typename Type>
    string to_string(vector<Type>);
    template <typename First, typename Second>
    string to_string(pair<First, Second>);
    template <typename Collection>
    string to_string(Collection);
    template <typename First, typename Second>
    string to_string(pair<First, Second> p) { return "{" + to_string(p.first) + ", " + to_string(p.second) + "}"; }
    template <typename Type>
    string to_string(vector<Type> v)
    {
        bool sep = false;
        string s = "[";
        for (Type x : v)
        {
            if (sep)
                s += ", ";
            sep = true;
            s += to_string(x);
        }
        s += "]";
        return s;
    }
    template <typename Collection>
    string to_string(Collection collection)
    {
        bool sep = false;
        string s = "{";
        for (auto x : collection)
        {
            if (sep)
                s += ", ";
            sep = true;
            s += to_string(x);
        }
        s += "}";
        return s;
    }
    void print()
    {
        cerr << endl;
        sep = false;
    }
    template <typename First, typename... Other>
    void print(First first, Other... other)
    {
        if (sep)
            cerr << " | ";
        sep = true;
        cerr << to_string(first);
        print(other...);
    }
}
using namespace io;

/* Points tO CONSIDER
    # RTE? -> check array bounds and constraints
    -> check if u are dividing smth by 0
    #TLE? -> thinks about binary search/ dp / optimization techniques
    # WA?
    -> overflow,reset global variables
    -> Check corner cases
    -> use Setpre for precision problems

    #Can't Get an idea?
    -> think from different/simpler approaches
    -> Think in reverse?
    -> Read the problem statement again
    -> Check the constraints again
    -> Ignore unnecessary information, and use it to draw the problem in new ways.
    -> Characterize the problem: Suppose I did find such a solution, what would it look like? what characteristics it would have? Can we toy around with such a solution so that it remains optimal?
    -> Randomly guessing: Guess and try to prove false
    -> Finding invariants: Check which properties don't change
    -> Solving subtasks of the original problem and then trying to extend/generalize your solution.
    -> bruteforce to find pattern
    -> Making obvious lower and upper bounds, and proving they are constructible.
    -> Fixing a parameter and then trying to maximise the result with respect to that fixed parameter.
    -> Maybe take a deep breath and take a break
    -> STRESS TESTING !!!!!!
*/

// CONSTANTS
#define md 10000007

const double EPS = 1e-9;
const ll N = 2e5 + 10;
const ll M = 1e9 + 7;
const double inf = 1e100;
const double eps = 1e-9;
const double PI = acos((double)-1.0);
int sign(double x) { return (x > eps) - (x < -eps); }
struct PT
{
    double x, y;
    PT() { x = 0, y = 0; }
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    PT operator+(const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator-(const PT &a) const { return PT(x - a.x, y - a.y); }
    PT operator*(const double a) const { return PT(x * a, y * a); }
    friend PT operator*(const double &a, const PT &b) { return PT(a * b.x, a * b.y); }
    PT operator/(const double a) const { return PT(x / a, y / a); }
    bool operator==(PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
    bool operator!=(PT a) const { return !(*this == a); }
    bool operator<(PT a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator>(PT a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
    double norm() { return sqrt(x * x + y * y); }
    double norm2() { return x * x + y * y; }
    PT perp() { return PT(-y, x); }
    double arg() { return atan2(y, x); }
    PT truncate(double r)
    { // returns a vector with norm r and having same direction
        double k = norm();
        if (!sign(k))
            return *this;
        r /= k;
        return PT(x * r, y * r);
    }
};
inline double dot(PT a, PT b) { return a.x * b.x + a.y * b.y; }
inline double dist2(PT a, PT b) { return dot(a - b, a - b); }
inline double dist(PT a, PT b) { return sqrt(dot(a - b, a - b)); }
inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
inline double cross2(PT a, PT b, PT c) { return cross(b - a, c - a); }
inline int orientation(PT a, PT b, PT c) { return sign(cross(b - a, c - a)); }
PT perp(PT a) { return PT(-a.y, a.x); }
PT rotateccw90(PT a) { return PT(-a.y, a.x); }
PT rotatecw90(PT a) { return PT(a.y, -a.x); }
PT rotateccw(PT a, double t) { return PT(a.x * cos(t) - a.y * sin(t), a.x * sin(t) + a.y * cos(t)); }
PT rotatecw(PT a, double t) { return PT(a.x * cos(t) + a.y * sin(t), -a.x * sin(t) + a.y * cos(t)); }
double SQ(double x) { return x * x; }
double rad_to_deg(double r) { return (r * 180.0 / PI); }
double deg_to_rad(double d) { return (d * PI / 180.0); }
double get_angle(PT a, PT b)
{
    double costheta = dot(a, b) / a.norm() / b.norm();
    return acos(max((double)-1.0, min((double)1.0, costheta)));
}
bool is_point_in_angle(PT b, PT a, PT c, PT p)
{ // does point p lie in angle <bac
    assert(orientation(a, b, c) != 0);
    if (orientation(a, c, b) < 0)
        swap(b, c);
    return orientation(a, c, p) >= 0 && orientation(a, b, p) <= 0;
}
bool half(PT p)
{
    return p.y > 0.0 || (p.y == 0.0 && p.x < 0.0);
}
void polar_sort(vector<PT> &v)
{ // sort points in counterclockwise
    sort(v.begin(), v.end(), [](PT a, PT b)
         { return make_tuple(half(a), 0.0, a.norm2()) < make_tuple(half(b), cross(a, b), b.norm2()); });
}
struct line
{
    PT a, b; // goes through points a and b
    PT v;
    double c; // line form: direction vec [cross] (x, y) = c
    line() {}
    // direction vector v and offset c
    line(PT v, double c) : v(v), c(c)
    {
        auto p = get_points();
        a = p.first;
        b = p.second;
    }
    // equation ax + by + c = 0
    line(double _a, double _b, double _c) : v({_b, -_a}), c(-_c)
    {
        auto p = get_points();
        a = p.first;
        b = p.second;
    }
    // goes through points p and q
    line(PT p, PT q) : v(q - p), c(cross(v, p)), a(p), b(q) {}
    pair<PT, PT> get_points()
    { // extract any two points from this line
        PT p, q;
        double a = -v.y, b = v.x; // ax + by = c
        if (sign(a) == 0)
        {
            p = PT(0, c / b);
            q = PT(1, c / b);
        }
        else if (sign(b) == 0)
        {
            p = PT(c / a, 0);
            q = PT(c / a, 1);
        }
        else
        {
            p = PT(0, c / b);
            q = PT(1, (c - a) / b);
        }
        return {p, q};
    }
    // ax + by + c = 0
    array<double, 3> get_abc()
    {
        double a = -v.y, b = v.x;
        return {a, b, c};
    }
    // 1 if on the left, -1 if on the right, 0 if on the line
    int side(PT p) { return sign(cross(v, p) - c); }
    // line that is perpendicular to this and goes through point p
    line perpendicular_through(PT p) { return {p, p + perp(v)}; }
    // translate the line by vector t i.e. shifting it by vector t
    line translate(PT t) { return {v, c + cross(v, t)}; }
    // compare two points by their orthogonal projection on this line
    // a projection point comes before another if it comes first according to vector v
    bool cmp_by_projection(PT p, PT q) { return dot(v, p) < dot(v, q); }
    line shift_left(double d)
    {
        PT z = v.perp().truncate(d);
        return line(a + z, b + z);
    }
};
// find a point from a through b with distance d
PT point_along_line(PT a, PT b, double d)
{
    return a + (((b - a) / (b - a).norm()) * d);
}
// projection point c onto line through a and b  assuming a != b
PT project_from_point_to_line(PT a, PT b, PT c)
{
    return a + (b - a) * dot(c - a, b - a) / (b - a).norm2();
}
// reflection point c onto line through a and b  assuming a != b
PT reflection_from_point_to_line(PT a, PT b, PT c)
{
    PT p = project_from_point_to_line(a, b, c);
    return point_along_line(c, p, 2.0 * dist(c, p));
}
// minimum distance from point c to line through a and b
double dist_from_point_to_line(PT a, PT b, PT c)
{
    return fabs(cross(b - a, c - a) / (b - a).norm());
}
// returns true if  point p is on line segment ab
bool is_point_on_seg(PT a, PT b, PT p)
{
    if (fabs(cross(p - b, a - b)) < eps)
    {
        if (p.x < min(a.x, b.x) || p.x > max(a.x, b.x))
            return false;
        if (p.y < min(a.y, b.y) || p.y > max(a.y, b.y))
            return false;
        return true;
    }
    return false;
}
// minimum distance point from point c to segment ab that lies on segment ab
PT project_from_point_to_seg(PT a, PT b, PT c)
{
    double r = dist2(a, b);
    if (fabs(r) < eps)
        return a;
    r = dot(c - a, b - a) / r;
    if (r < 0)
        return a;
    if (r > 1)
        return b;
    return a + (b - a) * r;
}
// minimum distance from point c to segment ab
double dist_from_point_to_seg(PT a, PT b, PT c)
{
    return dist(c, project_from_point_to_seg(a, b, c));
}
// 0 if not parallel, 1 if parallel, 2 if collinear
int is_parallel(PT a, PT b, PT c, PT d)
{
    double k = fabs(cross(b - a, d - c));
    if (k < eps)
    {
        if (fabs(cross(a - b, a - c)) < eps && fabs(cross(c - d, c - a)) < eps)
            return 2;
        else
            return 1;
    }
    else
        return 0;
}
// check if two lines are same
bool are_lines_same(PT a, PT b, PT c, PT d)
{
    if (fabs(cross(a - c, c - d)) < eps && fabs(cross(b - c, c - d)) < eps)
        return true;
    return false;
}
// bisector vector of <abc
PT angle_bisector(PT &a, PT &b, PT &c)
{
    PT p = a - b, q = c - b;
    return p + q * sqrt(dot(p, p) / dot(q, q));
}
// 1 if point is ccw to the line, 2 if point is cw to the line, 3 if point is on the line
int point_line_relation(PT a, PT b, PT p)
{
    int c = sign(cross(p - a, b - a));
    if (c < 0)
        return 1;
    if (c > 0)
        return 2;
    return 3;
}
// intersection point between ab and cd assuming unique intersection exists
bool line_line_intersection(PT a, PT b, PT c, PT d, PT &ans)
{
    double a1 = a.y - b.y, b1 = b.x - a.x, c1 = cross(a, b);
    double a2 = c.y - d.y, b2 = d.x - c.x, c2 = cross(c, d);
    double det = a1 * b2 - a2 * b1;
    if (det == 0)
        return 0;
    ans = PT((b1 * c2 - b2 * c1) / det, (c1 * a2 - a1 * c2) / det);
    return 1;
}
// intersection point between segment ab and segment cd assuming unique intersection exists
bool seg_seg_intersection(PT a, PT b, PT c, PT d, PT &ans)
{
    double oa = cross2(c, d, a), ob = cross2(c, d, b);
    double oc = cross2(a, b, c), od = cross2(a, b, d);
    if (oa * ob < 0 && oc * od < 0)
    {
        ans = (a * ob - b * oa) / (ob - oa);
        return 1;
    }
    else
        return 0;
}
// intersection point between segment ab and segment cd assuming unique intersection may not exists
// se.size()==0 means no intersection
// se.size()==1 means one intersection
// se.size()==2 means range intersection
set<PT> seg_seg_intersection_inside(PT a, PT b, PT c, PT d)
{
    PT ans;
    if (seg_seg_intersection(a, b, c, d, ans))
        return {ans};
    set<PT> se;
    if (is_point_on_seg(c, d, a))
        se.insert(a);
    if (is_point_on_seg(c, d, b))
        se.insert(b);
    if (is_point_on_seg(a, b, c))
        se.insert(c);
    if (is_point_on_seg(a, b, d))
        se.insert(d);
    return se;
}
// intersection  between segment ab and line cd
// 0 if do not intersect, 1 if proper intersect, 2 if segment intersect
int seg_line_relation(PT a, PT b, PT c, PT d)
{
    double p = cross2(c, d, a);
    double q = cross2(c, d, b);
    if (sign(p) == 0 && sign(q) == 0)
        return 2;
    else if (p * q < 0)
        return 1;
    else
        return 0;
}
// intersection between segament ab and line cd assuming unique intersection exists
bool seg_line_intersection(PT a, PT b, PT c, PT d, PT &ans)
{
    bool k = seg_line_relation(a, b, c, d);
    assert(k != 2);
    if (k)
        line_line_intersection(a, b, c, d, ans);
    return k;
}
// minimum distance from segment ab to segment cd
double dist_from_seg_to_seg(PT a, PT b, PT c, PT d)
{
    PT dummy;
    if (seg_seg_intersection(a, b, c, d, dummy))
        return 0.0;
    else
        return min({dist_from_point_to_seg(a, b, c), dist_from_point_to_seg(a, b, d),
                    dist_from_point_to_seg(c, d, a), dist_from_point_to_seg(c, d, b)});
}
// minimum distance from point c to ray (starting point a and direction vector b)
double dist_from_point_to_ray(PT a, PT b, PT c)
{
    b = a + b;
    double r = dot(c - a, b - a);
    if (r < 0.0)
        return dist(c, a);
    return dist_from_point_to_line(a, b, c);
}
// starting point as and direction vector ad
bool ray_ray_intersection(PT as, PT ad, PT bs, PT bd)
{
    double dx = bs.x - as.x, dy = bs.y - as.y;
    double det = bd.x * ad.y - bd.y * ad.x;
    if (fabs(det) < eps)
        return 0;
    double u = (dy * bd.x - dx * bd.y) / det;
    double v = (dy * ad.x - dx * ad.y) / det;
    if (sign(u) >= 0 && sign(v) >= 0)
        return 1;
    else
        return 0;
}
double ray_ray_distance(PT as, PT ad, PT bs, PT bd)
{
    if (ray_ray_intersection(as, ad, bs, bd))
        return 0.0;
    double ans = dist_from_point_to_ray(as, ad, bs);
    ans = min(ans, dist_from_point_to_ray(bs, bd, as));
    return ans;
}
struct circle
{
    PT p;
    double r;
    circle() {}
    circle(PT _p, double _r) : p(_p), r(_r) {};
    // center (x, y) and radius r
    circle(double x, double y, double _r) : p(PT(x, y)), r(_r) {};
    // circumcircle of a triangle
    // the three points must be unique
    circle(PT a, PT b, PT c)
    {
        b = (a + b) * 0.5;
        c = (a + c) * 0.5;
        line_line_intersection(b, b + rotatecw90(a - b), c, c + rotatecw90(a - c), p);
        r = dist(a, p);
    }
    // inscribed circle of a triangle
    circle(PT a, PT b, PT c, bool t)
    {
        line u, v;
        double m = atan2(b.y - a.y, b.x - a.x), n = atan2(c.y - a.y, c.x - a.x);
        u.a = a;
        u.b = u.a + (PT(cos((n + m) / 2.0), sin((n + m) / 2.0)));
        v.a = b;
        m = atan2(a.y - b.y, a.x - b.x), n = atan2(c.y - b.y, c.x - b.x);
        v.b = v.a + (PT(cos((n + m) / 2.0), sin((n + m) / 2.0)));
        line_line_intersection(u.a, u.b, v.a, v.b, p);
        r = dist_from_point_to_seg(a, b, p);
    }
    bool operator==(circle v) { return p == v.p && sign(r - v.r) == 0; }
    double area() { return PI * r * r; }
    double circumference() { return 2.0 * PI * r; }
};
// 0 if outside, 1 if on circumference, 2 if inside circle
int circle_point_relation(PT p, double r, PT b)
{
    double d = dist(p, b);
    if (sign(d - r) < 0)
        return 2;
    if (sign(d - r) == 0)
        return 1;
    return 0;
}
// 0 if outside, 1 if on circumference, 2 if inside circle
int circle_line_relation(PT p, double r, PT a, PT b)
{
    double d = dist_from_point_to_line(a, b, p);
    if (sign(d - r) < 0)
        return 2;
    if (sign(d - r) == 0)
        return 1;
    return 0;
}
// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<PT> circle_line_intersection(PT c, double r, PT a, PT b)
{
    vector<PT> ret;
    b = b - a;
    a = a - c;
    double A = dot(b, b), B = dot(a, b);
    double C = dot(a, a) - r * r, D = B * B - A * C;
    if (D < -eps)
        return ret;
    ret.push_back(c + a + b * (-B + sqrt(D + eps)) / A);
    if (D > eps)
        ret.push_back(c + a + b * (-B - sqrt(D)) / A);
    return ret;
}
int main()
{
    fast;
    ll t;
    // setIO();
    // ll tno=1;;
    t = 1;
    double r, x1, y1, x2, y2;
    cin >> r >> x1 >> y1 >> x2 >> y2;
    PT ctr(x1, y1);
    circle c(ctr, r);
    PT p(x2, y2);
    auto a = circle_line_intersection(ctr, r, ctr, p);
    PT p1 = a[0];
    PT p2 = a[1];
    if(dist(ctr,p)>=r){
        Setpre(8)<<ctr.x<<" "<<ctr.y<<" "<<r<<nn;
    }
    else if(p==ctr){
        double rad=r/2.00;
        PT ans(ctr.x+rad,ctr.y);
        Setpre(8) << ans.x << " " << ans.y << " " << rad << nn;
    }
    else if (dist(p1, p) > dist(p2, p))
    {
        PT ans((p1.x + p.x) / 2.00, (p1.y + p.y) / 2.00);
        double rad = dist(p1, p) / 2.00;
        Setpre(8) << ans.x << " " << ans.y << " " << rad << nn;
    }
    else
    {
        PT ans((p2.x + p.x) / 2.00, (p2.y + p.y) / 2.00);
        double rad = dist(p2, p) / 2.00;
        Setpre(8) << ans.x << " " << ans.y << " " << rad << nn;
    }
    return 0;
}
