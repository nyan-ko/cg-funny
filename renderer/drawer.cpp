#include <iostream>

#include "objmodel.h"

#include "drawer.h"

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    if (x0 > x1) {
        std::swap(x0, x1);
    }
    if (y0 > y1) {
        std::swap(y0, y1);
    }

    int x = x0;
    int y = y0;
    bool transpose = false;

    int dx = x1 - x0;
    int dy = y1 - y0;
    int p = 2 * dy - dx;

    if (dy > dx) {
        std::swap(x, y);
        std::swap(x0, y0);
        std::swap(x1, y1);
        std::swap(dx, dy);
        transpose = true;
    }

    while (x <= x1) {
        if (transpose) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }

        if (p < 0) {
            p += 2 * dy;
        } else {
            p += 2 * dy - 2 * dx;
            y++;
        }

        x++;
    }
}

bool contain(int x0, int y0, int x1, int y1, int x2, int y2, int a, int b) {
    // A to B vector, v0
    int abx = x1 - x0;
    int aby = y1 - y0;
    // A to C vector, v1
    int acx = x2 - x0;
    int acy = y2 - y0;
    // A to P vector, v2
    int pax = a - x0;
    int pay = b - y0;

    int d00 = abx * abx + aby * aby;
    int d01 = abx * acx + aby * acy;
    int d11 = acx * acx + acy * acy;
    int d02 = abx * pax + aby * pay;
    int d12 = acx * pax + acy * pay;
    double denom = d00 * d11 - d01 * d01;

// cache this
    double u = (d02 * d11 - d12 * d01) / denom;
    double v = (d00 * d12 - d02 * d01) / denom;
    double w = 1.0f - u - v;
    return u >= 0 && v >= 0 && w >= 0;
}

void triangle(int x0, int y0, int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color) {
    int ax = std::min(x0, std::min(x1, x2));
    int ay = std::min(y0, std::min(y1, y2));
    int bx = std::max(x0, std::max(x1, x2));
    int by = std::max(y0, std::max(y1, y2));

    for (int i = ax; i < bx; i++) {
        for (int j = ay; j < by; j++) {
            if (contain(x0, y0, x1, y1, x2, y2, i, j)) {
                image.set(i, j, color);
            }
        }
    }
}

