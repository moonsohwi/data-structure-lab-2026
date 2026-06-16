// Lec07_HashTable.cpp
// 실습: HashTable - Linear Probing (선형 탐색)
// 교수님 코드 기반 (슬라이드 p.34~37)

#include <stdio.h>

const int TABLE_SIZE = 11;

class HashTable {
    int  keys[TABLE_SIZE];
    int  vals[TABLE_SIZE];
    bool occupied[TABLE_SIZE];
public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            keys[i]     = -1;
            vals[i]     = -1;
            occupied[i] = false;
        }
    }

    // 해시 함수 (p.34)
    int hashFunction(int key) { return key % TABLE_SIZE; }

    // rehash: Linear Probing (p.35)
    int rehash(int oldHash)   { return (oldHash + 1) % TABLE_SIZE; }

    // put (p.37 put 로직 기반)
    void put(int key, int data) {
        int hashVal = hashFunction(key);

        if (!occupied[hashVal]) {               // 자리가 비어있으면
            keys[hashVal]     = key;
            vals[hashVal]     = data;
            occupied[hashVal] = true;
        } else if (keys[hashVal] == key) {      // 같은 Key → replace
            vals[hashVal] = data;
        } else {                                // 충돌 → next slot 탐색
            int nextSlot = rehash(hashVal);
            while (occupied[nextSlot] && keys[nextSlot] != key)
                nextSlot = rehash(nextSlot);
            keys[nextSlot]     = key;
            vals[nextSlot]     = data;
            occupied[nextSlot] = true;
        }
    }

    // get (p.37 get 로직 기반)
    int get(int key) {
        int startSlot = hashFunction(key);
        int position  = startSlot;
        bool stop = false, found = false;
        int  result = -1;

        while (occupied[position] && !found && !stop) {
            if (keys[position] == key) {
                found  = true;
                result = vals[position];
            } else {
                position = rehash(position);
                if (position == startSlot) stop = true;
            }
        }
        return result;
    }

    void display() {
        printf("Hash Table (size=%d, h(x)=x%%%d):\n", TABLE_SIZE, TABLE_SIZE);
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (occupied[i]) printf("  [%2d] %d\n", i, keys[i]);
            else             printf("  [%2d] None\n", i);
        }
    }
};

int main() {
    HashTable ht;

    // p.34 예시: 54, 26, 93, 17, 77, 31, 44, 55, 20
    ht.put(54, 54); ht.put(26, 26); ht.put(93, 93);
    ht.put(17, 17); ht.put(77, 77); ht.put(31, 31);
    ht.put(44, 44); ht.put(55, 55); ht.put(20, 20);

    ht.display();

    printf("\nget(93) => %d\n", ht.get(93));
    printf("get(20) => %d\n",  ht.get(20));
    printf("get(99) => %d (없음)\n", ht.get(99));

    return 0;
}
