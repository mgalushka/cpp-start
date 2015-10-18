#include "Nearest.h"

using namespace std;

namespace cpp {

    struct ByDistance {
        const Point& origin;
        const double distanceThreshold;

        bool operator()(const Point& lp, const Point& rp) {
            double ld = dist(origin, lp);
            double rd = dist(origin, rp);
            if (ld <= distanceThreshold && ld <= distanceThreshold) {
                return ld - rd;
            }
            if (ld > distanceThreshold && ld <= distanceThreshold) {
                return -1;
            }
            if (ld <= distanceThreshold && ld > distanceThreshold) {
                return 1;
            }
            return 0;
        }

        double dist(const Point& lp, const Point& rp){
            double xs = (lp.x - rp.x) * (lp.x - rp.x);
            double ys = (lp.y - rp.y) * (lp.y - rp.y);
            double zs = (lp.z - rp.z) * (lp.z - rp.z);
            return sqrt(xs + ys + zs);
        }
    };

    vector<Point> nearestN(const vector<Point>& points, int N) {
        return nearestN(points, N, points[0], INFINITY);
    }

    vector<Point> nearestN(const vector<Point>& points,
                           int N,
                           const Point& reference,
                           double distanceThreshold) {


        vector<Point> temp(points);
        ByDistance distance = {reference, distanceThreshold};
        sort(temp.begin(), temp.end(), distance);

        vector<Point> result(N);
        copy_n(temp.begin(), N, result.begin());
        return result;
    }
}

int main() {

}
