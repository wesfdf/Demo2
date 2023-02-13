
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <numeric>

struct Point {
    std::vector<double> y;
    double Pot;
};


std::vector<Point> latticeTesseract;
std::vector<Point> lattice;

std::vector<std::vector<double>> basis = {{std::sqrt(2.0) / 2.0, 1 / 2.0, 0.0, -1 / 2.0},
                                          {0.0, 1 / 2.0, sqrt(2.0) / 2.0, 1 / 2.0},
                                          {std::sqrt(2.0), -1 / 2.0, 0.0, 1 / 2.0},
                                          {0.0, 1 / 2.0, -std::sqrt(2.0), 1 / 2.0} };

/*std::vector<std::vector<double>> basis = {{std::sqrt(2.0) / 2.0, 0.0, std::sqrt(2.0), 0.0},
                                          {1 / 2.0, 1 / 2.0, -1 / 2.0, 1 / 2.0},
                                          {0.0, sqrt(2.0) / 2.0, 0.0, -std::sqrt(2.0)},
                                          {-1 / 2.0, 1 / 2.0, 1 / 2.0, 1 / 2.0} };*/

std::vector<double> multiplyMatrix(std::vector<int>& x, std::vector<std::vector<double>>& matrix) {
    std::vector<double> newX(4);
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) {
            newX[j] += matrix[j][k] * x[k];
        }
    }
    return newX;
}


bool hullCalculated = false;
std::vector<int> x;


bool isInsidePolygon(const Point& p, const std::vector<Point>& hull) {
    int n = hull.size();
    int intersections = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if ((hull[i].y[2] > p.y[2]) != (hull[j].y[2] > p.y[2])) {
            double slope = (hull[j].y[3] - hull[i].y[3]) / (hull[j].y[2] - hull[i].y[2]);
            double intercept = hull[i].y[3] - slope * hull[i].y[2];
            if (p.y[3] < slope * p.y[2] + intercept) {
                intersections++;
            }
        }
    }
    return intersections % 2 == 1;
}


void addPointLattice1(int N, std::vector<Point>& lat, const std::vector<Point>& hull) {
    for (int i = -N; i < N; i++) {
        for (int j = -N; j < N; j++) {
            for (int k = -N; k < N; k++) {
                for (int l = -N; l < N; l++) {
                    x = { i, j, k, l };
                    Point p;
                    p.y = multiplyMatrix(x, basis);
                    p.Pot = 0.0;
                    if (p.y[0] >= 0 && p.y[0] <= 20 && p.y[1] >= 0 && p.y[1] <= 20) {
                        if (isInsidePolygon(p, hull)) {//isInsidePolygon(p,hull)//p.y[2]*p.y[2]+p.y[3] * p.y[3]<1
                            lat.push_back(p);
                        }
                    }
                }
            }
        }
    }
}

/*void addHalfSpace(int N) {
    int halfSpace = N / 2;
    for (int i = 0; i < lattice.size(); i++) {
        if (lattice[i].x[0] > halfSpace) {
            lattice.erase(lattice.begin() + i);
            i--;
        }
    }
}*/

/*
void addPointLattice0(int N, std::vector<Point>& lat) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                for (int l = 0; l < N; l++) {
                    x = { i, j, k, l };
                    Point p;
                    p.y = multiplyMatrix(x, basis);
                    p.Pot = 0.0;
                    lat.push_back(p);
                }
            }
        }
    }
}


int orientation(const Point& p, const Point& q, const Point& r) {
    double val = (q.y[3] - p.y[3]) * (r.y[2] - q.y[2]) -
        (q.y[2] - p.y[2]) * (r.y[3] - q.y[3]);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

std::vector<Point> convexHull(std::vector<Point>& points) {
    int n = points.size();
    if (n < 3) return points;

    std::vector<Point> hull; //hull lieber keinen Point

    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].y[2] < points[l].y[2]) l = i;

    int p = l, q;
    do {
        hull.push_back(points[p]);
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (orientation(points[p], points[i], points[q]) == 2) q = i;
        }
        p = q;
    } while (p != l);

    //centerHullAroundCenter(hull);

    return hull;
}*/
void multiplyHullByConstant(std::vector<Point>& hull, double Ep) {
    for (Point& p : hull) {
        p.y[0] *= Ep;
        p.y[1] *= Ep;
        p.y[2] *= Ep;
        p.y[3] *= Ep;
    }
}

void SchwerpktHull(std::vector<Point>& hull, double E0, double E1, double E2, double E3) {
    for (Point& p : hull) {
        p.y[0] += E0;
        p.y[1] += E1;
        p.y[2] += E2;
        p.y[3] += E3;
    }
}

int main() {

    std::vector<Point> hull;
    
    Point p;
    p.y = { 0,0, -0.64644660940700005, 0.14644660940699999 };
    p.Pot = 0.0;
    hull.push_back(p);
    p.y = { 0,0, -0.64644660940700005, -0.56066017177954763 };
    hull.push_back(p);
    p.y = { 0,0, -0.14644660940699999, -1.0606601717795476 };
    hull.push_back(p);
    p.y = { 0,0, 0.56066017177954763, -1.0606601717795476 };
    hull.push_back(p);
    p.y = { 0,0, 1.0606601717795474, -0.56066017177954763 };
    hull.push_back(p);
    p.y = { 0,0, 1.0606601717795474, 0.14644660940699999 };
    hull.push_back(p);
    p.y = { 0,0, 0.56066017177954763, 0.64644660940700005 };
    hull.push_back(p);
    p.y = { 0,0, -0.14644660940699999, 0.64644660940700005 };
    hull.push_back(p);


    
    /*
    Point p;
    p.y = { 0,0, -0.853453390593, -0.353453390593 };
    p.Pot = 0.0;
    hull.push_back(p);
    p.y = { 0,0, -0.353453390593, -0.853453390593 };
    hull.push_back(p);
    p.y = { 0,0, 0.353453390593, -0.853453390593 };
    hull.push_back(p);
    p.y = { 0,0, 0.853453390593, -0.353453390593 };
    hull.push_back(p);
    p.y = { 0,0, 0.853453390593, 0.353453390593 };
    hull.push_back(p);
    p.y = { 0,0, 0.353453390593, 0.853453390593 };
    hull.push_back(p);
    p.y = { 0,0, -0.353453390593, 0.853453390593 };
    hull.push_back(p);
    p.y = { 0,0, -0.853453390593, 0.353453390593 };
    hull.push_back(p);*/


    /* {-0.853453390593, -0.353453390593},
    { -0.353453390593,-0.853453390593 },
    { 0.353453390593,-0.853453390593 },
    { 0.853453390593,-0.353453390593 },
    { 0.853453390593,0.353453390593 },
    { 0.353453390593,0.853453390593 },
    { -0.353453390593,0.853453390593 },
    { -0.853453390593,0.353453390593 }*/

    //int N = 2;
    //addPointLattice0(N, latticeTesseract);
    //hull=convexHull(latticeTesseract);
    multiplyHullByConstant(hull, 1);
    SchwerpktHull(hull, 0, 0, 0.146446609407, 0.353553390593);
    int N = 20;
    addPointLattice1(N, lattice, hull);
    //addHalfSpace(N);
    std::cout << lattice.size() << std::endl;



    std::ofstream file("lattice.txt");

    for (const auto& point : lattice) {
        for (const auto& y_val : point.y) {
            file << y_val << " ";
        }
        file << std::endl;
    }

    file.close();


    std::string python_script_path = "module1.py";
    //std::string data = "1, 2, 3, 4, 5";

    std::string command = "python " + python_script_path;// +" " + data;
    system(command.c_str());

    return 0;
}