// Lec04_MusicService.cpp
// 실습: MusicStreamingService 클래스
// - 음악(제목/아티스트/앨범/발매년도) 추가
// - 제목으로 검색 / 아티스트로 검색

#include <stdio.h>
#include <string.h>

const int MAX_MUSIC = 100;
const int MAX_STR   = 100;

struct Music {
    char title[MAX_STR];
    char artist[MAX_STR];
    char album[MAX_STR];
    int  year;
};

class MusicStreamingService {
private:
    Music musicList[MAX_MUSIC];
    int   count;
public:
    MusicStreamingService() { count = 0; }

    // 음악 추가
    void addMusic(const char* title, const char* artist,
                  const char* album, int year) {
        if (count >= MAX_MUSIC) { printf("목록이 가득 찼습니다.\n"); return; }
        strcpy(musicList[count].title,  title);
        strcpy(musicList[count].artist, artist);
        strcpy(musicList[count].album,  album);
        musicList[count].year = year;
        count++;
        printf("추가됨: %s - %s\n", title, artist);
    }

    // 제목으로 검색
    void searchByTitle(const char* title) {
        printf("=== 제목 검색: \"%s\" ===\n", title);
        bool found = false;
        for (int i = 0; i < count; i++)
            if (strcmp(musicList[i].title, title) == 0) {
                printf("  [%s] %s / %s (%d)\n",
                    musicList[i].title, musicList[i].artist,
                    musicList[i].album, musicList[i].year);
                found = true;
            }
        if (!found) printf("  검색 결과 없음\n");
    }

    // 아티스트로 검색
    void searchByArtist(const char* artist) {
        printf("=== 아티스트 검색: \"%s\" ===\n", artist);
        bool found = false;
        for (int i = 0; i < count; i++)
            if (strcmp(musicList[i].artist, artist) == 0) {
                printf("  [%s] %s / %s (%d)\n",
                    musicList[i].title, musicList[i].artist,
                    musicList[i].album, musicList[i].year);
                found = true;
            }
        if (!found) printf("  검색 결과 없음\n");
    }

    void displayAll() {
        printf("=== 전체 음악 목록 (%d곡) ===\n", count);
        for (int i = 0; i < count; i++)
            printf("  %s - %s [%s] %d년\n",
                musicList[i].title, musicList[i].artist,
                musicList[i].album, musicList[i].year);
    }
};

int main() {
    MusicStreamingService svc;

    svc.addMusic("Blueming",  "아이유", "LILAC", 2019);
    svc.addMusic("LILAC",     "아이유", "LILAC", 2021);
    svc.addMusic("Celebrity", "아이유", "LILAC", 2021);
    svc.addMusic("Dynamite",  "BTS",    "BE",    2020);

    printf("\n");
    svc.displayAll();

    printf("\n");
    svc.searchByTitle("LILAC");

    printf("\n");
    svc.searchByArtist("아이유");

    printf("\n");
    svc.searchByArtist("EXO");

    return 0;
}
