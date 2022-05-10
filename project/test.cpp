#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <externalpolyhedronautomata.h>

TEST_CASE("Determinant") {
    Point a(0, 0, 0);
    Vector vec1(a, 1, 2, 3);
    Vector vec2(a, 4, 5, 6);
    Vector vec3(a, 7, 8, 9);
    CHECK(Determinant(vec1, vec2, vec3) == 0);
    vec1 = Vector(a, -2, 2, 10);
    vec2 = Vector(a, -4, 2, 57);
    vec3 = Vector(a, 7, 3, 9);
    CHECK(Determinant(vec1, vec2, vec3) == 916);
    vec1 = Vector(a, -2, 2, 10);
    vec2 = Vector(Point(1, 1, 1), -4, 2, 57);
    vec3 = Vector(Point(2, -3, 1), 7, 3, 9);
    CHECK(Determinant(vec1, vec2, vec3) == 916);
}

bool Contains(const Point& point, const std::vector<Plane>& faces, const std::set<Point>& face_points) {
    for (Point point_inside : face_points) {
        for (int i = 0; i < faces.size(); ++i) {
            if (!IsInSameHalfSpace(point, point_inside, faces[i])) {
                return false;
            }
        }
    }
    return true;
}

TEST_CASE("Contains") {
    std::vector<Plane> faces;
    Point a(0, 0, 0);
    Point x(10, 0, 0);
    Point y(0, 10, 0);
    Point z(0, 0, 10);
    faces.emplace_back(a, x, y);
    faces.emplace_back(a, x, z);
    faces.emplace_back(a, y, z);
    faces.emplace_back(x, y, z);
    Point point_inside_1(1, 1, 1);
    Point point_inside_2(2, 2, 2);
    std::set<Point> face_points;
    for (int i = 0; i < faces.size(); ++i) {
        face_points.insert(faces[i].first_vec_.Start());
        face_points.insert(faces[i].first_vec_.End());
        face_points.insert(faces[i].second_vec_.End());
    }
    CHECK(Contains(point_inside_1, faces, face_points));
    CHECK(Contains(point_inside_2, faces, face_points));
    Point point_not_inside_1(10, 1, 1);
    Point point_not_inside_2(-1, -1, -1);
    CHECK_FALSE(Contains(point_not_inside_1, faces, face_points));
    CHECK_FALSE(Contains(point_not_inside_2, faces, face_points));
}

TEST_CASE("IsInSameHalfSpace") {
    Point x(10, 0, 0);
    Point y(0, 10, 0);
    Point z(0, 0, 10);
    Plane plane(x, y, z);
    Point up1(10, 10, 10);
    Point up2(10, 0, 1);
    Point down1(1, 1, 1);
    Point down2(-1, 1, 0);
    CHECK(IsInSameHalfSpace(up1, up2, plane));
    CHECK(IsInSameHalfSpace(down1, down2, plane));
    CHECK_FALSE(IsInSameHalfSpace(down1, up1, plane));
    CHECK_FALSE(IsInSameHalfSpace(down2, up2, plane));
    CHECK(IsInSameHalfSpace(down2, x, plane));
    CHECK(IsInSameHalfSpace(up2, x, plane));
}

bool IsConvex(const std::set<Point>& points, const std::vector<Plane>& faces) {
    for (int i = 0; i < faces.size(); ++i) {
        Point point_inside = faces[i].first_vec_.Start();
        for (const auto& point : points) {
            if (!IsInSameHalfSpace(point, point_inside, faces[0])) {
                return false;
            }
        }
    }
    return true;
}

void GenerateRandomPoints(std::set<Point>& points, int count) {
    for (int i = 0; i < count; ++i) {
        int x = std::rand();
        int y = std::rand();
        int z = std::rand();
        points.emplace(x, y, z);
    }
}

TEST_CASE("main test") {
    SUBCASE("count = 100") {
        int count = 100;    
        std::set<Point> points;
        GenerateRandomPoints(points, count);
        ExternalPolyhedronAutomata polyhedron(points);
        auto faces = polyhedron.GetFaces();
        points = polyhedron.GetPoints();
        CHECK(IsConvex(points, faces));
        std::set<Point> face_points;
        for (int i = 0; i < faces.size(); ++i) {
            face_points.insert(faces[i].first_vec_.Start());
            face_points.insert(faces[i].first_vec_.End());
            face_points.insert(faces[i].second_vec_.End());
        }
        for (const auto& point : points) {
            CHECK(Contains(point, faces, face_points));
        }
    }
    SUBCASE("count = 1000") {
        int count = 1000;    
        std::set<Point> points;
        GenerateRandomPoints(points, count);
        ExternalPolyhedronAutomata polyhedron(points);
        auto faces = polyhedron.GetFaces();
        points = polyhedron.GetPoints();
        CHECK(IsConvex(points, faces));
        std::set<Point> face_points;
        for (int i = 0; i < faces.size(); ++i) {
            face_points.insert(faces[i].first_vec_.Start());
            face_points.insert(faces[i].first_vec_.End());
            face_points.insert(faces[i].second_vec_.End());
        }
        for (const auto& point : points) {
            CHECK(Contains(point, faces, face_points));
        }
    }
    SUBCASE("count = 10000") {
        int count = 10000;    
        std::set<Point> points;
        GenerateRandomPoints(points, count);
        ExternalPolyhedronAutomata polyhedron(points);
        auto faces = polyhedron.GetFaces();
        points = polyhedron.GetPoints();
        CHECK(IsConvex(points, faces));
        std::set<Point> face_points;
        for (int i = 0; i < faces.size(); ++i) {
            face_points.insert(faces[i].first_vec_.Start());
            face_points.insert(faces[i].first_vec_.End());
            face_points.insert(faces[i].second_vec_.End());
        }
        for (const auto& point : points) {
            CHECK(Contains(point, faces, face_points));
        }
    }
}


