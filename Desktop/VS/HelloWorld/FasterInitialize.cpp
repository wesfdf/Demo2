#include <iostream>
#include <vector>

const int N = 100;  // limit for lattice points

struct Vector {
    int x, y, z, w;
};

// Returns the greatest common divisor of two integers using Euclidean algorithm
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Finds the least common multiple of two integers
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main() {
    Vector v1 = { 2, 3, 4, 5 };  // vectors spanning the plane
    Vector v2 = { 5, 4, 3, 2 };

    // Find the least common multiple of the components of v1 and v2
    int l = lcm(lcm(v1.x, v1.y), lcm(v1.z, v1.w));
    l = lcm(l, lcm(v2.x, v2.y));
    l = lcm(l, lcm(v2.z, v2.w));

    // Divide all components of v1 and v2 by their gcd
    int g = gcd(v1.x, v1.y);
    g = gcd(g, gcd(v1.z, v1.w));
    v1 = { v1.x / g, v1.y / g, v1.z / g, v1.w / g };
    g = gcd(v2.x, v2.y);
    g = gcd(g, gcd(v2.z, v2.w));
    v2 = { v2.x / g, v2.y / g, v2.z / g, v2.w / g };

    // Print the integer lattice points along the plane
    for (int i = 0; i <= l; i++) {
        int x = v1.x * i;
        int y = v1.y * i;
        int z = v1.z * i;
        int w = v1.w * i;
        for (int j = 0; j <= l; j++) {
            int x2 = x + v2.x * j;
            int y2 = y + v2.y * j;
            int z2 = z + v2.z * j;
            int w2 = w + v2.w * j;
            if (x2 >= -N && x2 <= N && y2 >= -N && y2 <= N && z2 >= -N && z2 <= N && w2 >= -N && w2 <= N) {
                std::cout << "(" << x2 << ", " << y2 << ", " << z2 << ", " << w2 << ")\n";
            }
        }
    }

    return 0;
}







