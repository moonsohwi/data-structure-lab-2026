// Lec04_SmartHome.cpp
// 실습: SmartHome 클래스
// - 가전 ON/OFF / 밝기·온도 조절 / 타이머 / 환경 모니터링 / 자동 실행

#include <stdio.h>

class SmartHome {
private:
    bool   lightOn;
    int    brightness;    // 밝기 (0~100)
    double temperature;   // 설정 온도
    int    timerMinutes;  // 타이머 (분)
public:
    SmartHome() {
        lightOn      = false;
        brightness   = 50;
        temperature  = 22.0;
        timerMinutes = 0;
    }

    // 조명 ON/OFF
    void toggleLight() {
        lightOn = !lightOn;
        printf("조명: %s\n", lightOn ? "ON" : "OFF");
    }

    // 밝기 조절
    void setBrightness(int b) {
        if (b < 0)   b = 0;
        if (b > 100) b = 100;
        brightness = b;
        printf("밝기: %d%%\n", brightness);
    }

    // 온도 조절
    void setTemperature(double t) {
        temperature = t;
        printf("온도 설정: %.1f\n", temperature);
    }

    // 타이머 설정
    void setTimer(int minutes) {
        timerMinutes = minutes;
        printf("타이머: %d분\n", timerMinutes);
    }

    // 환경 모니터링 & 알림 (다양한 센서 활용)
    void monitorEnvironment(double curTemp, int humidity) {
        printf("현재 온도: %.1f, 습도: %d%%\n", curTemp, humidity);
        if (curTemp > 30.0) printf("  [알림] 온도 높음 -> 에어컨 ON\n");
        if (humidity  > 70) printf("  [알림] 습도 높음 -> 제습기 ON\n");
    }

    // 일정 시간마다 자동 실행
    void autoRun() {
        printf("자동 실행: 밝기 %d%%, 온도 %.1f 유지\n", brightness, temperature);
    }

    void display() {
        printf("=== SmartHome 상태 ===\n");
        printf("조명: %s | 밝기: %d%% | 온도: %.1f | 타이머: %d분\n",
            lightOn ? "ON" : "OFF", brightness, temperature, timerMinutes);
    }
};

int main() {
    SmartHome home;

    home.toggleLight();
    home.setBrightness(70);
    home.setTemperature(24.5);
    home.setTimer(30);
    home.monitorEnvironment(32.0, 75);
    home.autoRun();
    home.display();

    return 0;
}
