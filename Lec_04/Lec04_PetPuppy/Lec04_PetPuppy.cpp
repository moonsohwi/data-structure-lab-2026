// Lec04_PetPuppy.cpp
// 실습: Pet & Puppy 클래스 (상속)
// Pet: 이름/나이/종류 저장 및 반환
// Puppy: Pet 상속 + 견종(breed) 추가

#include <stdio.h>
#include <string.h>

const int MAX_NAME = 50;

// ── Pet 클래스 ──────────────────────────────────────────────
class Pet {
protected:
    char name[MAX_NAME];
    int  age;
    char type[MAX_NAME];
public:
    Pet(const char* n, int a, const char* t) {
        strcpy(name, n);
        age = a;
        strcpy(type, t);
    }
    const char* getName() { return name; }
    int         getAge()  { return age;  }
    const char* getType() { return type; }

    virtual void display() {
        printf("이름: %s, 나이: %d, 종류: %s\n", name, age, type);
    }
};

// ── Puppy 클래스 (Pet 상속) ─────────────────────────────────
class Puppy : public Pet {
private:
    char breed[MAX_NAME];   // 견종
public:
    Puppy(const char* n, int a, const char* t, const char* b)
        : Pet(n, a, t) {
        strcpy(breed, b);
    }
    const char* getBreed() { return breed; }

    void display() {
        printf("이름: %s, 나이: %d, 종류: %s, 견종: %s\n",
            name, age, type, breed);
    }
};

int main() {
    Pet   cat("나비", 3, "고양이");
    cat.display();
    printf("이름: %s, 나이: %d, 종류: %s\n",
        cat.getName(), cat.getAge(), cat.getType());

    printf("\n");

    Puppy dog("초코", 2, "강아지", "골든 리트리버");
    dog.display();
    printf("이름: %s, 견종: %s\n", dog.getName(), dog.getBreed());

    return 0;
}
