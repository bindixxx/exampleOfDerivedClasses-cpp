#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Triangle {
protected:
    double a, b, c;

public:
    Triangle(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}

    bool exists() const {
        return (a + b > c) && (a + c > b) && (b + c > a);
    }

    double perimeter() const {
        return a + b + c;
    }

    double area() const {
        double s = perimeter() / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    double angleA() const {
        return acos((b * b + c * c - a * a) / (2 * b * c)) * 180 / M_PI;
    }

    double angleB() const {
        return acos((a * a + c * c - b * b) / (2 * a * c)) * 180 / M_PI;
    }

    double angleC() const {
        return acos((a * a + b * b - c * c) / (2 * a * b)) * 180 / M_PI;
    }

    virtual void printInfo() const {
        if (!exists()) {
            cout << "Triangle does not exist." << endl;
            return;
        }
        cout << "Sides: a=" << a << ", b=" << b << ", c=" << c << endl;
        cout << "Angles: A=" << angleA() << ", B=" << angleB() << ", C=" << angleC() << endl;
        cout << "Perimeter: " << perimeter() << endl;
        cout << "Area: " << area() << endl;
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(double side) : Triangle(side, side, side) {}

    bool isEquilateral() const {
        return (a == b) && (b == c);
    }

    void printInfo() const override {
        if (!exists()) {
            cout << "Equilateral triangle does not exist." << endl;
            return;
        }
        cout << "Equilateral Triangle with side=" << a << endl;
        cout << "Perimeter: " << perimeter() << endl;
        cout << "Area: " << area() << endl;
    }
};

int main() {
    int K, L;
    cout << "Enter the number of triangles (K): ";
    cin >> K;
    cout << "Enter the number of equilateral triangles (L): ";
    cin >> L;

    vector<Triangle> triangles;
    vector<EquilateralTriangle> equilateralTriangles;

    // Ввод обычных треугольников
    for (int i = 0; i < K; ++i) {
        double a, b, c;
        cout << "Enter sides of triangle " << i + 1 << ": ";
        cin >> a >> b >> c;
        Triangle t(a, b, c);
        triangles.push_back(t);
    }

    // Ввод равносторонних треугольников
    for (int i = 0; i < L; ++i) {
        double side;
        cout << "Enter side of equilateral triangle " << i + 1 << ": ";
        cin >> side;
        EquilateralTriangle et(side);
        equilateralTriangles.push_back(et);
    }

    // Вычисление средней площади для K треугольников
    double totalArea = 0;
    int validTriangles = 0;
    for (const auto& triangle : triangles) {
        if (triangle.exists()) {
            totalArea += triangle.area();
            ++validTriangles;
        }
    }
    if (validTriangles > 0) {
        cout << "Average area of " << validTriangles << " triangles: " << totalArea / validTriangles << endl;
    } else {
        cout << "No valid triangles found." << endl;
    }

    // Нахождение наибольшего равностороннего треугольника
    EquilateralTriangle* largestEquilateral = nullptr;
    double maxArea = 0;
    for (auto& et : equilateralTriangles) {
        if (et.exists() && et.area() > maxArea) {
            largestEquilateral = &et;
            maxArea = et.area();
        }
    }

    if (largestEquilateral) {
        cout << "Largest equilateral triangle:" << endl;
        largestEquilateral->printInfo();
    } else {
        cout << "No valid equilateral triangles found." << endl;
    }

    return 0;
}
