#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
#include <stack>
#include <vector>

struct Point {
  int64_t x_;
  int64_t y_;
  int64_t z_;
  Point(int64_t x, int64_t y, int64_t z) : x_(x), y_(y), z_(z) {}
  Point() : x_(0), y_(0), z_{0} {}
};

bool operator==(const Point& first, const Point& second);
bool operator!=(const Point& first, const Point& second);
bool operator<(const Point& first, const Point& second);

std::ostream& operator<< (std::ostream& out, const Point& point);

struct Vector {
  int64_t x_;
  int64_t y_;
  int64_t z_;
  int64_t len_x_;
  int64_t len_y_;
  int64_t len_z_;
  std::vector<int> neigh_faces_;  // смежные грани
  Vector(const Point& point1, const Point& point2)
      : x_(point1.x_),
        y_(point1.y_),
        z_(point1.z_),
        len_x_(point2.x_ - point1.x_),
        len_y_(point2.y_ - point1.y_),
        len_z_(point2.z_ - point1.z_) {}
  Vector(const Point& point, int64_t len_x, int64_t len_y, int64_t len_z)
      : x_(point.x_),
        y_(point.y_),
        z_(point.z_),
        len_x_(len_x),
        len_y_(len_y),
        len_z_(len_z) {}
  Vector(const Vector& vec)
      : x_(vec.x_),
        y_(vec.y_),
        z_(vec.z_),
        len_x_(vec.len_x_),
        len_y_(vec.len_y_),
        len_z_(vec.len_z_),
        neigh_faces_(vec.neigh_faces_) {}
  int64_t LenInSquare() const {
    return len_x_ * len_x_ + len_y_ * len_y_ + len_z_ * len_z_;
  }
  double Len() const { return sqrt(LenInSquare()); }
  Point Start() const { return Point(x_, y_, z_); }
  Point End() const {  // returns the end of vector
    return Point(x_ + len_x_, y_ + len_y_, z_ + len_z_);
  }
  Vector& operator*=(int64_t n);
  void SwapEnds(); // чтобы ребра были равны, если направлены в
                   // разные стороны, но концы совпадают
};

int64_t Determinant(const Vector& first, const Vector& second, const Vector& third);

struct VectorComparator {
  bool operator()(const Vector& first, const Vector& second) const;
};

struct Plane {  // гарантируется, что грань есть 2 вектора с общим началом
  Vector first_vec_;
  Vector second_vec_;
  Plane(const Vector& first, const Vector& second)
      : first_vec_(first), second_vec_(second) {}
  Plane(const Point& first, const Point& second, const Point& third);
  bool IsVertex(
      const Point& point) const {  // является ли точка вершиной грани?
    return first_vec_.Start() == point || first_vec_.End() == point ||
           second_vec_.End() == point;
  }
  Vector Complement(const Vector& vec) const;  // "дополняет" вектор другим из грани с тем же началом
};

std::ostream& operator<<(std::ostream& out, const Plane& plane);

bool operator== (const Plane& left, const Plane& right);

class ExternalPolyhedronAutomata {
public:
  ExternalPolyhedronAutomata(const std::set<Point>& points);
  std::vector<Plane> GetFaces() const;
  std::set<Point> GetPoints() const;
private:
  std::set<Point> points_; // точки
  std::vector<Plane> faces_;  // грани
  Point FindFirstPoint();
  Point FindSecondPoint(const Point& first_point);
  Point FindThirdPoint(const Point& first_point,
                              const Point& second_point);
  bool IsFaceNew(const Point& point, const Vector& edge) const;
  Point FindNewFace(std::set<Point>& points, Vector& edge);
  void AddEdge(std::set<Vector, VectorComparator>& edges, Vector& edge) const;
};

bool IsInSameHalfSpace(const Point& first, const Point& second,
                       const Plane& plane);