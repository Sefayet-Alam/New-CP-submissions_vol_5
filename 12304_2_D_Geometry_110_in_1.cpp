#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;
#define PI acos(-1)
struct Point
{
    double x,y;
    Point(){}
    Point(double x,double y):x(x),y(y){}
};
struct Line
{
  Point a,v;
  Line() {}
  Line(Point a,Point v):a(a), v(v) {}
};
struct Circle
{
    Point c;
    double r;
    Circle(){}
    Circle(Point c,double r):c(c),r(r){}
    Point point(double a)
    {
        return Point(c.x+cos(a)*r,c.y+sin(a)*r);
    }
};
Point operator+(Point A,Point B)
{
    return Point(A.x+B.x,A.y+B.y);
}
Point operator-(Point A,Point B)
{
    return Point(A.x-B.x,A.y-B.y);
}
Point operator*(Point A,double p)
{
    return Point(A.x*p,A.y*p);
}
Point operator/(Point A,double p)
{
    return Point(A.x/p,A.y/p);
}
bool operator<(const Point&a,const Point&b)
{
    return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
double Dot(Point A,Point B)
{
    return A.x*B.x+A.y*B.y;
}
double Length(Point A)//vector length
{
    return sqrt(Dot(A,A));
}
double fix(double x)
{
  if(x <-1e-10) x=x+PI;
  return x*180.0/PI;
}
double angle(Point v)
{
  return atan2(v.y, v.x);
}
int dcmp(double x)
{
    if(fabs(x)<1e-10)return 0;
    else return x<0?-1:1;
}
Point Normal (Point A) //Unit normal vector
{
    double L=Length(A);
    return Point(-A.y/L,A.x/L);
}
Point Rotate(Point A,double rad)
{
    return Point(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
double Cross(Point A,Point B) //Use the cross product to find the area
{
    return A.x*B.y-A.y*B.x;
}
double DistanceToLine(Point P,Point A,Point B) //Distance from point to line
{
    Point v1=B-A,v2=P-A;
    return fabs(Cross(v1,v2)/Length(v1));
}


Circle CircumscribedCircle(Point p1,Point p2,Point p3) //Find the circumscribed circle of the triangle to ensure that the three points are not collinear
{
    double Bx=p2.x-p1.x,By=p2.y-p1.y;//vector p1p2
    double Cx=p3.x-p1.x,Cy=p3.y-p1.y;//vector p1p3
    double D=2*(Bx*Cy-By*Cx); //Cross product to double the area of ​​the enclosed quadrilateral
    double cx=(Cy*(Bx*Bx+By*By)-By*(Cx*Cx+Cy*Cy))/D+p1.x;
    double cy=(Bx*(Cx*Cx+Cy*Cy)-Cx*(Bx*Bx+By*By))/D+p1.y;
    Point p=Point(cx,cy);
    return Circle(p,Length(p1-p)); //Center of circle, distance from point to point
}
Circle InscribedCircle(Point p1,Point p2,Point p3) //Find the inscribed circle of the triangle to ensure that the three points are not collinear
{
    double a=Length(p2-p3); //Find the length of the three sides
    double b=Length(p3-p1);
    double c=Length(p1-p2);
    Point p=(p1*a+p2*b+p3*c)/(a+b+c);//center of circle
    return Circle(p,DistanceToLine(p,p1,p2)); //The radius is the distance from the point to the line
}
int TangentLineThroughPoint(Circle C,Point P,double *V)
{
    Point u=C.c-P; //vector pc
    double dist=Length(u);//the distance of pc
    if(dist<C.r)return 0;//The point has no tangent line inside the circle
    else if(dcmp(dist-C.r)==0)//The point is on the circle
    {
        V[0]=fix(angle(Rotate(u,-PI/2))); //Rotate counterclockwise by PI/2
        return 1;
    }
    else
    {
        double ang=asin(C.r/dist);
        V[0]=fix(angle(Rotate(u,-ang))); //rotate clockwise
        V[1]=fix(angle(Rotate(u,+ang))); //Counterclockwise rotation
        sort(V,V+2);
        return 2;
    }
}
void cirLineIntersect(Circle C,Line L,vector<Point> &sol)
{
    double e=Dot(L.v,L.v);
    double f=Dot(L.a-C.c,L.v)*2;
    double g=Dot(L.a-C.c,L.a-C.c)-C.r*C.r;
    double dlt=f*f-4*e*g;
    if(dlt<-1e-6)return;
    if(dlt<1e-6)
    {
        double t=-f/(2*e);
        sol.push_back(L.v*t+L.a);
        return;
    }
    dlt=sqrt(dlt);
    double t1=(-f+dlt)/(2*e),t2=(-f-dlt)/(2*e);
    sol.push_back(L.v*t1+L.a);
    sol.push_back(L.v*t2+L.a);
}


void CircleThroughAPointAndTangentToALineWithRadius(Point P,Line lin,double r)
{
    vector<Point> sol;
    Point v=Normal(lin.v);
    cirLineIntersect(Circle(P,r),Line(lin.a+v*r,lin.v),sol);
    cirLineIntersect(Circle(P,r),Line(lin.a-v*r,lin.v),sol);
    sort(sol.begin(),sol.end());
    cout<<"[";
    for(int i = 0; i < sol.size(); i++)
    {
        cout<<"("<<sol[i].x<<","<<sol[i].y<<")";
        if(i != sol.size()-1)
          cout<<",";
    }
    cout<<"]"<<endl;
}
void lineLineIntersect(Line L1, Line L2, vector <Point> &sol)
{
    double t = Cross((L2.a-L1.a), L2.v) / Cross(L1.v, L2.v);
    sol.push_back(L1.a+L1.v*t);
}
void CircleTangentToTwoLinesWithRadius(Line L1, Line L2, double r)
{
    vector<Point> sol;
    Point v1=Normal(L1.v);
    Point v2=Normal(L2.v);
    lineLineIntersect(Line(L1.a+v1*r, L1.v), Line(L2.a+v2*r, L2.v), sol);
    lineLineIntersect(Line(L1.a+v1*r, L1.v), Line(L2.a-v2*r, L2.v), sol);
    lineLineIntersect(Line(L1.a-v1*r, L1.v), Line(L2.a+v2*r, L2.v), sol);
    lineLineIntersect(Line(L1.a-v1*r, L1.v), Line(L2.a-v2*r, L2.v), sol);
    sort(sol.begin(), sol.end());
    cout<<"[";
    for(int i = 0; i < sol.size(); i++)
    {
        cout<<"("<<sol[i].x<<","<<sol[i].y<<")";
        if(i != sol.size()-1)
          cout<<",";
    }
    cout<<"]"<<endl;
}
void cirCirIntersect(Circle C1, Circle C2, vector <Point> &sol)
{
    Point v = C2.c - C1.c;
    double d =Length(v);
    if(dcmp(d-C1.r-C2.r) > 0) return;
    double ct =angle(v), alf = acos((C1.r*C1.r+d*d-C2.r*C2.r)/(2*C1.r*d));
    sol.push_back(C1.point(ct+alf));
    if(dcmp(alf) > 1e-10)sol.push_back(C1.point(ct-alf));
}
void CircleTangentToTwoDisjointCirclesWithRadius(Circle C1, Circle C2, double r)
{
    vector<Point> sol;
    cirCirIntersect(Circle(C1.c, C1.r+r), Circle(C2.c, C2.r+r), sol);
    sort(sol.begin(), sol.end());
    cout<<"[";
    for(int i = 0; i < sol.size(); i++)
    {
        cout<<"("<<sol[i].x<<","<<sol[i].y<<")";
        if(i != sol.size()-1)
            cout<<",";
    }
    cout<<"]"<<endl;
}
int main()
{
    string op;
    while(cin>>op)
    {
        cout<<setiosflags(ios::fixed)<<setprecision(6);
        if(op=="CircumscribedCircle")
        {
            Point p1,p2,p3;
            cin>>p1.x>>p1.y>>p2.x>>p2.y>>p3.x>>p3.y;
            Circle result=CircumscribedCircle(p1,p2,p3);
            cout<<"("<<result.c.x<<","<<result.c.y<<","<<result.r<<")"<<endl;
        }
        if(op=="InscribedCircle")
        {
            Point p1,p2,p3;
            cin>>p1.x>>p1.y>>p2.x>>p2.y>>p3.x>>p3.y;
            Circle result=InscribedCircle(p1,p2,p3);
            cout<<"("<<result.c.x<<","<<result.c.y<<","<<result.r<<")"<<endl;
        }
        if(op=="TangentLineThroughPoint")
        {
            Circle C;Point P;
            cin>>C.c.x>>C.c.y>>C.r>>P.x>>P.y;
            double V[2];
            int count=TangentLineThroughPoint(C,P,V);
            if(count==0)
                cout<<"[]"<<endl;
            else if(count==1)
                cout<<"["<<V[0]<<"]"<<endl;
            else
                cout<<"["<<V[0]<<","<<V[1]<<"]"<<endl;
        }
        if(op=="CircleThroughAPointAndTangentToALineWithRadius")
        {
            Point P;
            double r,x1,y1,x2,y2;
            cin>>P.x>>P.y>>x1>>y1>>x2>>y2>>r;
            Line lin=Line(Point(x1,y1),Point(x2-x1,y2-y1));
            CircleThroughAPointAndTangentToALineWithRadius(P,lin,r);
        }
        if(op=="CircleTangentToTwoLinesWithRadius")
        {
            double x1,y1,x2,y2,x3,y3,x4,y4,r;
            cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4>>r;
            Line L1=Line(Point(x1,y1),Point(x2-x1,y2-y1));
            Line L2=Line(Point(x3,y3),Point(x4-x3,y4-y3));
            CircleTangentToTwoLinesWithRadius(L1,L2,r);
        }
        if(op=="CircleTangentToTwoDisjointCirclesWithRadius")
        {
            Circle C1,C2;
            double r;
            cin>>C1.c.x>>C1.c.y>>C1.r>>C2.c.x>>C2.c.y>>C2.r>>r;
            CircleTangentToTwoDisjointCirclesWithRadius(C1, C2, r);
        }
    }
    return 0;
}