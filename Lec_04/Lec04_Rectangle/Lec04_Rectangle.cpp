// Lec04_Rectangle.cpp
// 실습: Rectangle 클래스 - 가로/세로 저장, 넓이·둘레 계산, 정사각형 판별

#include <stdio.h>

class Rectangle {
private:
    double width;
    double height;
public:
    Rectangle(double w = 0, double h = 0) {
        width  = w;
        height = h;
    }
    double area()      { return width * height; }
    double perimeter() { return 2 * (width + height); }
    bool   isSquare()  { return width == height; }

    void display() {
        printf("가로: %.2f, 세로: %.2f\n", width, height);
        printf("  넓이: %.2f\n", area());
        printf("  둘레: %.2f\n", perimeter());
        printf("  정사각형: %s\n", isSquare() ? "Yes" : "No");
    }
};

int main() {
    Rectangle r1(5.0, 3.0);
    r1.display();

    Rectangle r2(4.0, 4.0);
    r2.display();

    return 0;
}
