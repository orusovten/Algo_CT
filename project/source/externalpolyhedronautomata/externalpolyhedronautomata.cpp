#include <iostream>
#include <externalpolyhedronautomata/externalpolyhedronautomata.h>

bool operator==(const Point& first, const Point& second) {
  return first.x_ == second.x_ && first.y_ == second.y_ &&
         first.z_ == second.z_;
}

bool operator!=(const Point& first, const Point& second) {
  return !(first == second);
}

bool operator<(const Point& first, const Point& second) {
  return first.z_ < second.z_ ||
         (first.z_ == second.z_ && first.y_ < second.y_) ||
         (first.z_ == second.z_ && first.y_ == second.y_ &&
          first.x_ < second.x_);
}

std::ostream& operator<< (std::ostream& out, const Point& point) {
  out << point.x_ << " " << point.y_ << " " << point.z_;
  return out;
}

Vector& Vector::operator*=(int64_t n) {
    len_x_ *= n;
    len_y_ *= n;
    len_z_ *= n;
    return *this;
}

void Vector::SwapEnds() {  // чтобы ребра были равны, если направлены в
    // разные стороны, но концы совпадают
    if (Start().z_ > End().z_ ||
        (Start().z_ == End().z_ && Start().y_ > End().y_) ||
        (Start().z_ == End().z_ && Start().y_ == End().y_ &&
         Start().x_ > End().x_)) {
      x_ += len_x_;
      y_ += len_y_;
      z_ += len_z_;
      len_x_ *= -1;
      len_y_ *= -1;
      len_z_ *= -1;
    }
}

int64_t Determinant(const Vector& first, const Vector& second, const Vector& third) {
  return first.len_x_ * second.len_y_ * third.len_z_ +
         first.len_y_ * second.len_z_ * third.len_x_ +
         first.len_z_ * second.len_x_ * third.len_y_ -
         first.len_z_ * second.len_y_ * third.len_x_ -
         first.len_y_ * second.len_x_ * third.len_z_ -
         first.len_x_ * second.len_z_ * third.len_y_;
}

bool VectorComparator::operator()(const Vector& first, const Vector& second) const {
    return ((first.Start() < second.Start()) ||
            (first.Start() == second.Start() && first.End() < second.End()));
}


// гарантируется, что у векторов общее начало
Vector VectorMultiply(const Vector& first, const Vector& second) {
  int64_t len_x = first.len_y_ * second.len_z_ - second.len_y_ * first.len_z_;
  int64_t len_y = second.len_x_ * first.len_z_ - first.len_x_ * second.len_z_;
  int64_t len_z = first.len_x_ * second.len_y_ - second.len_x_ * first.len_y_;
  return Vector(first.Start(), len_x, len_y, len_z);
}

int64_t ScalarMultiply(const Vector& first, const Vector& second) {
  return first.len_x_ * second.len_x_ + first.len_y_ * second.len_y_ +
         first.len_z_ * second.len_z_;
}

Plane::Plane(const Point& first, const Point& second, const Point& third): 
      first_vec_(first, second), second_vec_(first, third)
{}

std::ostream& operator<<(std::ostream& out, const Plane& plane) {
  out << plane.first_vec_.Start() << " " << plane.first_vec_.End() << " " << plane.second_vec_.End();
  return out;
}

Vector Plane::Complement(
    const Vector& vec) const {  // гарантируется, что vec - ребро грани
  Point first = first_vec_.Start();
  Point second = first_vec_.End();
  Point third = second_vec_.End();
  if (vec.Start() == first) {
    if (vec.End() == second) {
      return Vector(first, third);
    }
    return Vector(first, second);
  }
  if (vec.Start() == second) {
    if (vec.End() == first) {
      return Vector(second, third);
    }
    return Vector(second, first);
  }
  if (vec.End() == first) {
    return Vector(third, second);
  }
  return Vector(third, first);
}

bool operator== (const Plane& left, const Plane& right) {
  std::set<Point> left_points;
  std::set<Point> right_points;
  left_points.insert(left.first_vec_.Start());
  left_points.insert(left.first_vec_.End());
  left_points.insert(left.second_vec_.Start());
  left_points.insert(left.second_vec_.End());
  right_points.insert(right.first_vec_.Start());
  right_points.insert(right.first_vec_.End());
  right_points.insert(right.second_vec_.Start());
  right_points.insert(right.second_vec_.End());
  return left_points == right_points;
}

std::vector<Plane> ExternalPolyhedronAutomata::GetFaces() const {
  return faces_;
}

std::set<Point> ExternalPolyhedronAutomata::GetPoints() const {
  return points_;
}

bool IsFirstMoreNearForBeingSecondOrThirdPoint(const Point& first,
                                               const Point& second,
                                               const Plane& plane) {
  Vector normal = VectorMultiply(plane.first_vec_, plane.second_vec_);
  Vector first_normal = VectorMultiply(Vector(first, plane.first_vec_.Start()),
                                       Vector(first, plane.first_vec_.End()));
  Vector second_normal =
      VectorMultiply(Vector(second, plane.first_vec_.Start()),
                     Vector(second, plane.first_vec_.End()));
  int64_t first_scalar_multiply = ScalarMultiply(first_normal, normal);
  first_scalar_multiply = std::abs(first_scalar_multiply);
  int64_t second_scalar_multiply = ScalarMultiply(second_normal, normal);
  second_scalar_multiply = std::abs(second_scalar_multiply);
  return first_scalar_multiply * second_normal.Len() >
         second_scalar_multiply * first_normal.Len();
}

bool IsInSameHalfSpace(const Point& first, const Point& second,
                       const Plane& plane) {
  Vector first_vec(plane.first_vec_.Start(), first);
  Vector second_vec(plane.first_vec_.Start(), second);
  int64_t first_determinant =
      Determinant(plane.first_vec_, plane.second_vec_, first_vec);
  int64_t second_determinant =
      Determinant(plane.first_vec_, plane.second_vec_, second_vec);
  return (first_determinant >= 0 && second_determinant >= 0) ||
         (first_determinant <= 0 && second_determinant <= 0);
}

bool IsFirstMoreNear(const Point& first, const Point& second,
                     const Plane& plane) {
  Vector normal = VectorMultiply(plane.first_vec_, plane.second_vec_);
  Vector first_normal = VectorMultiply(Vector(first, plane.first_vec_.Start()),
                                       Vector(first, plane.first_vec_.End()));
  Vector second_normal =
      VectorMultiply(Vector(second, plane.first_vec_.Start()),
                     Vector(second, plane.first_vec_.End()));
  int64_t first_scalar_multiply = ScalarMultiply(first_normal, normal);
  first_scalar_multiply = std::abs(first_scalar_multiply);
  int64_t second_scalar_multiply = ScalarMultiply(second_normal, normal);
  second_scalar_multiply = std::abs(second_scalar_multiply);
  Plane normal_plane(plane.first_vec_, normal);
  if (IsInSameHalfSpace(first, plane.second_vec_.End(), normal_plane)) {
    if (IsInSameHalfSpace(plane.second_vec_.End(), second, normal_plane)) {
      return first_scalar_multiply * second_normal.Len() <
             second_scalar_multiply * first_normal.Len();
    }
    return false;
  }
  if (IsInSameHalfSpace(plane.second_vec_.End(), second, normal_plane)) {
    return true;
  }
  return first_scalar_multiply * second_normal.Len() >
         second_scalar_multiply * first_normal.Len();
}

Point ExternalPolyhedronAutomata::FindFirstPoint() {
  Point first_point = *points_.begin();
  points_.erase(first_point);
  return first_point;
}

Point ExternalPolyhedronAutomata::FindSecondPoint(const Point& first_point) {
  Vector vec1(first_point,
              Point(first_point.x_ + 1, first_point.y_, first_point.z_));
  Vector vec2(first_point,
              Point(first_point.x_, first_point.y_ + 1, first_point.z_));
  Plane plane(vec1, vec2);
  Point second_point = *points_.begin();
  for (const auto& point : points_) {
    if (IsFirstMoreNearForBeingSecondOrThirdPoint(point, second_point, plane)) {
      second_point = point;
    }
  }
  points_.erase(second_point);
  return second_point;
}

Point ExternalPolyhedronAutomata::FindThirdPoint(const Point& first_point,
    const Point& second_point) {
  Plane plane(first_point, second_point, Point(first_point.x_ + 1, first_point.y_, first_point.z_));
  Point third_point = *points_.begin();
  for (const auto& point : points_) {
    if (IsFirstMoreNearForBeingSecondOrThirdPoint(point, third_point, plane)) {
      third_point = point;
    }
  }
  points_.insert(first_point);
  points_.insert(second_point);
  return third_point;
}

bool ExternalPolyhedronAutomata::IsFaceNew(const Point& point,
                                           const Vector& edge) const {
  return !(faces_[edge.neigh_faces_[0]].IsVertex(point));
}

Point ExternalPolyhedronAutomata::FindNewFace(
    std::set<Point>& points, Vector& edge) {
  Vector second_edge = faces_[edge.neigh_faces_[0]].Complement(edge);
  Plane plane(edge, second_edge);
  Point new_point = *points.begin();
  for (const auto& point : points) {
    if (IsFaceNew(point, edge)) {
      new_point = point;
    }
  }
  for (const auto& point : points) {
    if (IsFaceNew(point, edge) && IsFirstMoreNear(point, new_point, plane)) {
      new_point = point;
    }
  }
  return new_point;
}

void ExternalPolyhedronAutomata::AddEdge(
    std::set<Vector, VectorComparator>& edges, Vector& edge) const {
  edge.SwapEnds();
  auto ptr_to_first_edge = edges.find(edge);
  if (ptr_to_first_edge != edges.end()) {
    edge.neigh_faces_ = ptr_to_first_edge->neigh_faces_;
    edges.erase(edge);
  }
  edge.neigh_faces_.push_back(faces_.size() - 1);
  edges.insert(edge);
}

ExternalPolyhedronAutomata::ExternalPolyhedronAutomata(
    const std::set<Point>& points): points_(points) {
  Point first_point = FindFirstPoint();
  Point second_point = FindSecondPoint(first_point);
  Point third_point = FindThirdPoint(first_point, second_point);
  std::set<Vector, VectorComparator> edges;
  Vector first_edge(first_point, second_point);
  Vector second_edge(first_point, third_point);
  Plane plane(first_edge, second_edge);
  faces_.push_back(plane);
  Vector third_edge(second_point, third_point);
  AddEdge(edges, first_edge);
  AddEdge(edges, second_edge);
  AddEdge(edges, third_edge);
  while (!edges.empty()) {
    Vector edge = *edges.begin();
    if (edge.neigh_faces_.size() == 2) {  // все смежные грани уже добавлены
      edges.erase(edge);
      continue;
    }
    Point point = FindNewFace(points_, edge);
    if (IsFaceNew(point, edge)) {
      first_edge = Vector(point, edge.Start());
      second_edge = Vector(point, edge.End());
      plane = Plane(first_edge, second_edge);
      faces_.push_back(plane);
      AddEdge(edges, first_edge);
      AddEdge(edges, second_edge);
    }
    edges.erase(edge);
  }
}