#pragma once

#include <vector>

namespace cpp {

struct Point {
  double x;
  double y;
  double z;
};

// Return N closest points to origin, IN ORDER
std::vector<Point> nearestN(const std::vector<Point>& points,
                            int N);


// Return N closest points to a reference point, in order, AND all
// within maximum distance threshold
std::vector<Point> nearestN(const std::vector<Point>& points,
                            int N,
                            const Point& reference,
                            double distanceThreshold);

}
