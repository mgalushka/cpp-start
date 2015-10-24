#include "Nearest.h"

using namespace std;

namespace nearest {

    // to print Point to cout
    std::ostream& operator<<(std::ostream &o, const nearest::Point& p) {
        o << "(" << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;
        return o;
    }

    vector<Point> nearestN(const vector<Point>& points, int N) {
        if (points.size() == 0) {
            vector<Point> empty;
            return empty;
        }
        return nearestN(points, N, points[0], INFINITY);
    }

    vector<Point> nearestN(const vector<Point>& points,
                           int N,
                           const Point& reference,
                           double distanceThreshold) {

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
                return reference.dist(p1) < reference.dist(p2);
            });

        auto sz = min(static_cast<int>(temp.size()), N);
        temp.resize(sz);
        return temp;
    }
}
