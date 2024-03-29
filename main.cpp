#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int step = 1;

double f(double x, double y) {
    return -2*x*x - x*y - 4*y*y + 20*x + 12*y - 4;
}

pair<double, double> findNextPair(double x, double y, double delta) {
    vector<double> fxy_vec;
    vector<pair<double, double>> xy_vec;

    fxy_vec.push_back(f(x, y));
    fxy_vec.push_back(f(x + delta, y + delta));
    fxy_vec.push_back(f(x + delta, y - delta));
    fxy_vec.push_back(f(x - delta, y + delta));
    fxy_vec.push_back(f(x - delta, y - delta));

    xy_vec.emplace_back(x, y);
    xy_vec.emplace_back(x + delta, y + delta);
    xy_vec.emplace_back(x + delta, y - delta);
    xy_vec.emplace_back(x - delta, y + delta);
    xy_vec.emplace_back(x - delta, y - delta);

    cout << "f(" << xy_vec[0].first << "," << xy_vec[0].second << ") = " << fxy_vec[0] << endl;
    cout << "f(" << xy_vec[1].first << "," << xy_vec[1].second << ") = " << fxy_vec[1] << endl;
    cout << "f(" << xy_vec[2].first << "," << xy_vec[2].second << ") = " << fxy_vec[2] << endl;
    cout << "f(" << xy_vec[3].first << "," << xy_vec[3].second << ") = " << fxy_vec[3] << endl;
    cout << "f(" << xy_vec[4].first << "," << xy_vec[4].second << ") = " << fxy_vec[4] << endl;

    int pos = distance(fxy_vec.begin(),max_element(fxy_vec.begin(), fxy_vec.end()));;

    cout << "\nf_max(" << xy_vec[pos].first << ", " << xy_vec[pos].second << ") = " << fxy_vec[pos] << endl;

    return make_pair(xy_vec[pos].first, xy_vec[pos].second);
}

pair<double, double> updateValues(double x, double y, double delta) {
    cout << endl << "=============================================================================================" << endl;
    cout << "Крок №" << step << ":" << endl << endl;

    cout << "del = " << delta << " > 0.01" << endl << endl;

    pair<double, double> nextPair = findNextPair(x, y, delta);

    step++;
    return nextPair;
}

int main() {
    double x = 0, y = 0, delta = 0.5;

    std::cout << fixed << setprecision(4);

    while (true) {
        pair<double, double> nextPair = updateValues(x, y, delta);

        if (f(x, y) == f(nextPair.first, nextPair.second)) {
            if (delta < 0.01) {
                return 0;
            } else {
                delta /= 2;
            }
        } else {
            x = nextPair.first;
            y = nextPair.second;
        }
    }
}
