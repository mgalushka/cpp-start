#include "Nearest.h"

using namespace std;

namespace cpp {

    struct ByDistance {
        const Point& origin;

        bool operator()(const Point& lp, const Point& rp) {
            double xs = (lp.x - rp.x) * (lp.x - rp.x);
            double ys = (lp.y - rp.y) * (lp.y - rp.y);
            double zs = (lp.z - rp.z) * (lp.z - rp.z);
            return sqrt(xs + ys + zs);
        }
    };

    vector<Point> nearestN(const vector<Point>& points, int N) {
        vector<Point> temp(points);
        ByDistance distance = {points[0]};
        sort(temp.begin(), temp.end(), distance);

        vector<Point> result(N);
        copy_n(temp.begin(), N, result.begin());
        return result;
    }

    vector<Point> nearestN(const vector<Point>& points,
                           int N,
                           const Point& reference,
                           double distanceThreshold) {
        vector<Point> ret;
        return ret;
    }
}

int main() {

}
