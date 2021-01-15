#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<ll, ll>
#define ff first
#define ss second
#define pb push_back
#define fastio ios::sync_with_stdio(false); cin.tie(NULL);
#define PI 2*acos(0.0)
#define eps 1e-11
#define DEBUG(x) cerr << #x << " = " << x << endl
//#pragma comment(linker, "/stack:200000000")
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

const int MAX = 2e5 + 5, MOD = 1e9 + 7;
const ll inf = 1e18 + 5;

typedef double doubleType;
bool eq(doubleType a, doubleType b) { return fabs( a - b ) < eps; } //use fabsl for long double
int sgn(doubleType value) {
  if (eq(value, 0)) return 0; //colinear
  if (value + eps < 0) return -1; //right or cw
  return +1; //left or ccw
}

struct point {
  doubleType x, y;
  point() {}
  point(doubleType x, doubleType y) : x(x), y(y) {}
};

point operator + (const point &p, const point &q) { return point(p.x + q.x, p.y + q.y); }
point operator - (const point &p, const point &q) { return point(p.x - q.x, p.y - q.y); }
point operator * (const point &p, doubleType v) { return point(p.x * v, p.y * v); }
point operator / (const point &p, doubleType v) { return point(p.x / v, p.y / v); }
bool operator == (const point &p, const point &q) { return (eq(p.x, q.x) && eq(p.y, q.y)); }
bool operator != (const point &p, const point &q) { return !(eq(p.x, q.x) && eq(p.y, q.y)); }
bool operator < (const point &p, const point &q) { return fabs(p.x - q.x) > eps ? (p.x < q.x) : (p.y < q.y); }
bool operator > (const point &p, const point &q) { return fabs(p.x - q.x) > eps ? (p.x > q.x) : (p.y > q.y); }
ostream& operator << (ostream& os, const point p) { return os << "(" << p.x << ", " << p.y << ")"; }

doubleType dot(point p, point q) { return (p.x * q.x + p.y * q.y); }
doubleType cross(point p, point q) { return (p.x * q.y - q.x * p.y); }
doubleType norm(point p) { return sqrt( dot(p, p) ); }
doubleType sqlen(point p) { return dot(p, p); }
doubleType sqdist(point p, point q) { return dot(q - p, q - p); }

int orientation(point p, point q, point r) { return sgn(cross(q - p, r - p)); }

point unitVector(point p) { return p / norm(p); }
point scale(point p, doubleType factor, point reference = point(0, 0)) { return reference + (p - reference) * factor; }
point translate(point p, point v) { return p + v; }
point rotate(point p, doubleType theta, point axis = point(0, 0)) {
  p = p - axis;
  return axis + point(p.x * cos(theta) - p.y * sin(theta), p.x * sin(theta) + p.y * cos(theta));
}
point perp(point p) { return point(-p.y, p.x); }
bool isPerpendicular(point p, point q) { return eq(dot(p, q), 0); }

doubleType angle(point p, point q) { return acos( max((doubleType) - 1.0, min((doubleType)1.0, dot(p, q) / (norm(p) * norm(q)))) ); } //range[0 to PI]
doubleType signedAngle(point p, point q, point r) { // between pq w.r.t pr in range[-PI to PI]
  if ( orientation(p, q, r) >= 0 ) return angle(q - p, r - p);
  return -angle(q - p, r - p);
}
doubleType polarAngle(point p) { return atan2(p.y, p.x); }
doubleType orientedAngle(point p, point q, point r) { // between pq w.r.t pr in range[0 to 2*PI]
  if ( orientation(p, q, r) >= 0 ) return angle(q - p, r - p);
  return 2 * PI - angle(q - p, r - p);
}

bool pointInAngle(point p, point q, point r, point P) {
  if ( !orientation(p, q, r) ) return false;
  if ( orientation(p, q, r) < 0 ) swap(q, r);
  return orientation(p, q, P) >= 0 && orientation(p, r, P) <= 0;
}

bool isConvex(vector<point> &P) {
  bool bame = false, dane = false;
  int n = (int)P.size();
  for (int i = 0; i < n; i++) {
    int dir = orientation(P[i], P[(i + 1) % n], P[(i + 2) % n]);
    if (dir == 1) bame = true;
    else if (dir == -1) dane = true;
  }
  if (bame && dane) return false;
  return true;
}

doubleType triangleArea(point a, point b, point c) {
  doubleType ret = ( (a.x * b.y) + (b.x * c.y) + (c.x * a.y) ) - ( (a.x * c.y) + (c.x * b.y) + (b.x * a.y) );
  return fabs(ret) / 2;
}

doubleType polygonArea(vector<point> &P) {
  doubleType ret = 0;
  int n = (int)P.size();
  for (int i = 0; i < n; i++) {
    ret += cross(P[i], P[(i + 1) % n]);
  }
  return fabs(ret) / 2;
}

void polarSort(vector<point> &P) {
  point pivot = P[0];
  for (int i = 0; i < P.size(); i++) {
    if (P[i] < pivot) pivot = P[i];
  }
  sort(P.begin(), P.end(), [pivot] (const point & a, const point & b) {
    int dir = orientation(pivot, a, b);
    if (!dir) return sqlen(a - pivot) < sqlen(b - pivot);
    return dir > 0;
  });

  int idx = (int)P.size() - 1;
  while (idx - 1 > 0 && !orientation(pivot, P[idx - 1], P[idx]) ) idx--;
  if (idx > 1) reverse(P.begin() + idx, P.end());
}

vector<point> convexHull(vector<point> &P) {
  polarSort(P);
  vector<point> hull;
  for (int i = 0; i < P.size(); i++) {
    int sz = (int)hull.size();
    // use < 0 to include colinears
    while ( sz >= 2 && orientation(hull[sz - 2], hull[sz - 1], P[i]) <= 0 ) hull.pop_back(), sz--;
    hull.pb(P[i]);
  }
  return hull;
}

doubleType closestPair(vector<point> &P) { // returns sqdist
  sort(P.begin(), P.end());
  set<point>st;
  doubleType best = inf;
  int left = 0;
  for (int i = 0; i < P.size(); i++) {
    doubleType dis = sqrt(best);
    while (P[i].x - P[left].x >= best) {
      st.erase(point(P[left].y, P[left].x));
      left++;
    }

    auto it1 = st.lower_bound(point(P[i].y - dis, P[i].x));
    auto it2 = st.upper_bound(point(P[i].y + dis, P[i].x));

    for (auto it = it1; it != it2; it++) {
      point cur = *it;
      swap(cur.x, cur.y);
      best = min(best, sqdist(cur, P[i]));
    }
    st.insert( point(P[i].y, P[i].x) );
  }
  return best;
}

doubleType maxTriArea(vector<point> &P) {
  int a = 0, b = 1, c = 2;
  doubleType area = triangleArea(v[a], v[b], v[c]);
  n = v.size();
  for (; a < n; a++) {
    if (a == b) b = (b + 1) % n;
    if (b == c) c = (c + 1) % n;
    while (1) {
      while ( sgn(triangleArea(v[a], v[b], v[c]) - triangleArea(v[a], v[b], v[(c + 1) % n])) <= 0 ) {
        c = (c + 1) % n;
      }
      if ( sgn(triangleArea(v[a], v[b], v[c]) - triangleArea(v[a], v[(b + 1) % n], v[c])) <= 0 ) {
        b = (b + 1) % n;
      } else break;
    }
    if ( sgn(area - triangleArea(v[a], v[b], v[c])) < 0 ) area = triangleArea(v[a], v[b], v[c]);
  }
  return area;
}

int arr[MAX];
int main() {

  fastio;

}