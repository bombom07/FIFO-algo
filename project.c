#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3  // 페이지 프레임의 최대 개수

// 페이지 프레임을 나타내는 구조체
typedef struct {
    int pagenumber;
    int arrivaltime;  // 페이지가 들어온 시간
} frame;

// 페이지 참조를 나타내는 구조체
typedef struct {
    int pagenumber;
} pagereference;

// 페이지 교체 알고리즘을 수행하는 함수
void fifo(int[], int, int);

int main() {
    int n;  // 페이지 참조의 개수
    printf("페이지 참조의 개수를 입력하세요: ");
    scanf("%d", &n);

    // 페이지 참조 동적 배열 할당
    pagereference* pageReferences = (pagereference*)malloc(n * sizeof(pagereference));

    // 페이지 참조 입력
    printf("페이지 참조를 입력하세요:\n");
    for (int i = 0; i < n; ++i) {
        printf("참조 %d: ", i + 1);
        scanf("%d", &pageReferences[i].pagenumber);
    }

    int numframe;  // 페이지 프레임의 개수
    printf("페이지 프레임의 개수를 입력하세요: ");
    scanf("%d", &numframe);

    // 페이지 교체 알고리즘 수행
    fifo(pageReferences, n, numframe);

    // 동적 배열 해제
    free(pageReferences);

    return 0;
}

void fifo(int pageReferences[], int n, int numFrames) {
    frame* frames = (frame*)malloc(numFrames * sizeof(frame));  // 페이지 프레임 배열 동적 할당
    int frameCount = 0;                                        // 현재 페이지 프레임 개수
    int pageFaults = 0;                                        // 페이지 부재 횟수

    printf("FIFO\n");
    printf("+------+-----+-----+\n");
    printf("| Time | str | P.f | Memory\n");
    printf("+------+-----+-----+\n");

    for (int i = 0; i < n; ++i) {
        // 페이지가 이미 메모리에 존재하는지 확인
        int pageExists = 0;
        for (int j = 0; j < frameCount; ++j) {
            if (frames[j].pagenumber == pageReferences[i]) {
                pageExists = 1;
                break;
            }
        }

        if (!pageExists) {
            // 페이지 부재 발생
            printf("| %4d | %3d |  F  | ", i + 1, pageReferences[i]);

            if (frameCount < numFrames) {
                // 페이지 프레임에 여유가 있을 경우
                frames[frameCount].pagenumber = pageReferences[i];
                frames[frameCount].arrivaltime = i;  // 현재 시간으로 설정
                ++frameCount;
            }
            else {
                // 페이지 교체 필요
                int oldestIndex = 0;
                for (int j = 1; j < frameCount; ++j) {
                    if (frames[j].arrivaltime < frames[oldestIndex].arrivaltime) {
                        oldestIndex = j;
                    }
                }

                // 가장 오래된 페이지 교체
                frames[oldestIndex].pagenumber = pageReferences[i];
                frames[oldestIndex].arrivaltime = i;  // 현재 시간으로 업데이트
            }

            ++pageFaults;

            // 현재 페이지 프레임 출력
            for (int j = 0; j < frameCount; ++j) {
                printf("%d ", frames[j].pagenumber);
            }

            printf("\n");
        }
        else {
            // 페이지가 이미 메모리에 있는 경우
            printf("| %4d | %3d |     | ", i + 1, pageReferences[i]);

            // 현재 페이지 프레임 출력
            for (int j = 0; j < frameCount; ++j) {
                printf("%d ", frames[j].pagenumber);
            }

            printf("\n");
        }
    }

    printf("+------+-----+-----+\n");
    printf("\n전체 페이지 부재 횟수: %d\n", pageFaults);

    // 동적 배열 해제
    free(frames);
}