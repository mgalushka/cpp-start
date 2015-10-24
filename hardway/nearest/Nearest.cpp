#include "Nearest.h"

using namespace std;

namespace nearest {

    // to print Point to cout
    std::ostream& operator<<(std::ostream &o, const nearest::Point& p) {
        o << "(" << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;
        return o;
    }

    // defines sorting order for points
    struct ByDistance {
        const Point& origin;

        bool operator()(const Point& lp, const Point& rp) {
            return dist(origin, lp) < dist(origin, rp);
        }

        static double dist(const Point& lp, const Point& rp){
            double xs = (lp.x - rp.x) * (lp.x - rp.x);
            double ys = (lp.y - rp.y) * (lp.y - rp.y);
            double zs = (lp.z - rp.z) * (lp.z - rp.z);
            return sqrt(xs + ys + zs);
        }
    };

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
                             [&reference, distanceThreshold](Point& p){ return ByDistance::dist(p, reference) > distanceThreshold; }),
                   temp.end());

        ByDistance distance = {reference};
        sort(temp.begin(), temp.end(), distance);

        auto sz = min(static_cast<int>(temp.size()), N);
        temp.resize(sz);
        return temp;
    }
}
