// Polynomial.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
using namespace std;

class Polynomial {
private:
    vector<double> coeffs; // coeffs[i] = x^i 의 계수

public:
    Polynomial() {}
    Polynomial(vector<double> c) : coeffs(c) {}

    // 두 다항식 덧셈
    Polynomial operator+(const Polynomial& other) const {
        int maxSize = max(coeffs.size(), other.coeffs.size());
        vector<double> result(maxSize, 0.0);
        for (int i = 0; i < (int)coeffs.size(); i++)
            result[i] += coeffs[i];
        for (int i = 0; i < (int)other.coeffs.size(); i++)
            result[i] += other.coeffs[i];
        return Polynomial(result);
    }

    // 특정 x값에서 다항식 계산
    double evaluate(double x) const {
        double result = 0.0, power = 1.0;
        for (double c : coeffs) {
            result += c * power;
            power *= x;
        }
        return result;
    }

    // 출력
    void print() const {
        bool first = true;
        for (int i = (int)coeffs.size() - 1; i >= 0; i--) {
            if (coeffs[i] == 0.0) continue;
            if (!first && coeffs[i] > 0) cout << " + ";
            if (i == 0) cout << coeffs[i];
            else if (i == 1) cout << coeffs[i] << "x";
            else cout << coeffs[i] << "x^" << i;
            first = false;
        }
        cout << endl;
    }
};

int main() {
    // p1 = 3x^2 + 2x + 1
    Polynomial p1({ 1.0, 2.0, 3.0 });
    // p2 = x^2 + 4x + 5
    Polynomial p2({ 5.0, 4.0, 1.0 });

    cout << "p1 = "; p1.print();
    cout << "p2 = "; p2.print();

    Polynomial sum = p1 + p2;
    cout << "p1 + p2 = "; sum.print();

    cout << "p1(2) = " << p1.evaluate(2.0) << endl;

    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
