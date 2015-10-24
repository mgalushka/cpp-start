#include "Nearest.h"

using namespace std;

namespace nearest {

    vector<Point> nearestN(const vector<Point>& points, int N) {
        if (points.empty() || N == 0) {
            return vector<Point>();
        }
        return nearestN(points, N, {0.0, 0.0, 0.0}, INFINITY);
    }

    vector<Point> nearestN(const vector<Point>& points,
                           int N,
                           const Point& reference,
                           double distanceThreshold) {

        assert(distanceThreshold >= 0 && N >= 0);
        vector<Point> temp;
        temp.insert(temp.begin(), points.begin(), points.end());

        // filtering vector to remove all points far then distance from reference
        temp.erase(remove_if(temp.begin(),
                             temp.end(),
                             [&reference, distanceThreshold](const Point& p){
                                return reference.dist(p) > distanceThreshold;
                             }),
                    temp.end());

        sort(temp.begin(), temp.end(),
            [&reference](const Point& p1, const Point& p2) {
                return reference.dist_square(p1) < reference.dist_square(p2);
            });

        auto sz = min(static_cast<int>(temp.size()), N);
        temp.resize(sz);
        return temp;
    }
}
