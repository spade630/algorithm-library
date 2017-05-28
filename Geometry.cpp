double eps = 1e-10;

class Point {
public:
  double x, y;

  Point(double x = 0, double y = 0) : x(x), y(y) {}

  Point operator + (const Point p) {
    return Point(x + p.x, y + p.y);
  }
  Point operator - (const Point p) {
    return Point(x - p.x, y - p.y);
  }
  Point operator * (const double a) {
    return Point(x * a, y * a);
  }
  Point operator / (const double a) {
    return Point(x / a, y / a);
  }

  bool operator < (const Point& p) const {
    return x != p.x ? x < p.x : y < p.y;
  }
  bool operator == (const Point& p) const {
    return fabs(x - p.x) < eps && fabs(y - p.y) < eps;
  }

  double abs() {
    return sqrt(norm());
  }
  double norm() {
    return x * x + y * y;
  }

};

typedef Point Vector;

struct Segment {
  Point p1, p2;
  Segment(Point p1, Point p2) : p1(p1), p2(p2) {}
};

typedef Segment Line;

// 等価判定
bool equals(const double& a, const double& b) {
  return fabs(a - b) < eps;
}

// 内積
double dot(const Vector& a, const Vector& b){
  return a.x * b.x + a.y * b.y;
}

// 外積
double cross(const Vector& a, const Vector& b){
  return a.x * b.y - a.y * b.x;
}

// ccw
// p0: 基準点
// p1, p2: 線分p0p1、p0p2となる点
// 反時計回り: 1
// 時計回り:  -1
int ccw(Point p0, Point p1, Point p2){
  Vector a = p1 - p0;
  Vector b = p2 - p0;
  if(cross(a, b) > eps) return 1;
  if(cross(a, b) < -eps) return -1;
  if(dot(a, b) < -eps) return 2;
  if(a.norm() < b.norm()) return -2;

  return 0;
}

// 射影
Point project(Segment s, Point p){
  Vector base = s.p2 - s.p1;
  double r = dot(p - s.p1, base) / norm(base);
  return s.p1 + base * r;
}

// 直行判定(ベクトル)
bool isOrthogonal(Vector a, Vector b){
  return equals(dot(a, b), 0.0);
}

// 直行判定(点4つ)
bool isOrthogonal(Point a1, Point a2, Point b1, Point b2){
  return isOrthogonal(a1 - a2, b1 - b2);
}

// 直行判定(直線2本)
bool isOrthogonal(Segment s1, Segment s2){
  return equals(dot(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
}

// 平行判定(ベクトル)
bool isParallel(const Vector& a, const Vector& b){
  return equals(cross(a, b), 0.0);
}

// 平行判定(点4つ)
bool isParallel(Point a1, Point a2, Point b1, Point b2){
  return isParallel(a1 - a2, b1 - b2);
}

// 直行判定(直線2本)
bool isParallel(Segment s1, Segment s2){
  return equals(cross(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
}

double norm(Vector v) {
    return v.x * v.x + v.y * v.y;
}

double abs(Vector v) {
    return sqrt(norm(v));
}

// 直線と点の距離
double getDistanceLP(Line l, Point p){
    return abs(cross(l.p2 - l.p1, p - l.p1) / abs(l.p2 - l.p1));
}

// 線分と点の距離
double getDistanceSP(Segment s, Point p){
    if(dot(s.p2 - s.p1, p - s.p1) < 0.0)
        return abs(p - s.p1);
    if(dot(s.p1 - s.p2, p - s.p2) < 0.0)
        return abs(p - s.p2);
    return getDistanceLP(s, p);
}

class Circle {
  Point c;
  double r;
  Circle(Point c = Point(), double r = 0.0) : c(c), r(r) {}
};

class Triangle {
public:
  Point p1, p2, p3; // 頂点
  Vector v1, v2, v3; // 辺のベクトル
  double e1, e2, e3; // 辺の大きさ
  double a1, a2, a3; // 角度(ラジアン)
  
  Triangle(Point a, Point b, Point c) : p1(a), p2(b), p3(c) {
    v1 = p3 - p2; v2 = p3 - p1; v3 = p2 - p1;
    e1 = v1.abs(); e2 = v2.abs(); e3 = v3.abs();
    a1 = law_of_cosines(e1, e2, e3); a2 = law_of_cosines(e2, e1, e3);
    a3 = law_of_cosines(e3, e2, e1);
  }
  
  // 余弦定理(返り値:ラジアン角度)
  double law_of_cosines(const double& a, const double& b, const double& c) { 
    return acos((b * b + c * c - a * a) / (2.0 * b * c));
  }
  
  // 外接円の半径
  double calc_radius_circumcenter() {
    return e1 / (2.0 * sin(a1));
  }
  // 外心のベクトル
  Vector calc_vec_circumcenter() {
    return (v1 * sin(2.0 * a1) + v2 * sin(2.0 * a2) + v3 * sin(2.0 * a3))
           / (sin(2.0 * a1) + sin(2.0 * a2) + sin(2.0 * a3));
  }
  
  // 外心の座標
  Point calc_p_circumcenter() {
    return Point((p1.x * sin(2.0 * a1) + p2.x * sin(2.0 * a2) + p3.x * sin(2.0 * a3))
                 / (sin(2.0 * a1) + sin(2.0 * a2) + sin(2.0 * a3)),
                 (p1.y * sin(2.0 * a1) + p2.y * sin(2.0 * a2) + p3.y * sin(2.0 * a3))
                 / (sin(2.0 * a1) + sin(2.0 * a2) + sin(2.0 * a3)));
  }
};
