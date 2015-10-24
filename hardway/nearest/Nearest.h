#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

namespace nearest {

struct Point {
    double x;
    double y;
    double z;

    bool operator==(const Point& rhp) const {
        return x == rhp.x && y == rhp.y && z == rhp.z;
    }

    std::ostream& operator<<(std::ostream &o) const {
        return o << "(" << x << ", " << y << ", " << z << ")\n";
    }

    double dist_square(const Point& other) const {
        double xs = (x - other.x) * (x - other.x);
        double ys = (y - other.y) * (y - other.y);
        double zs = (z - other.z) * (z - other.z);
        return xs + ys + zs;
    }

    double dist(const Point& other) const {
        return sqrt(dist_square(other));
    }

};

// Return N closest points to origin in order
std::vector<Point> nearestN(const std::vector<Point>& points,
                            int N);


// Return N closest points to a reference point, in order - all
// within maximum distance threshold
std::vector<Point> nearestN(const std::vector<Point>& points,
                            int N,
                            const Point& reference,
                            double distanceThreshold);

}
