#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3  // ������ �������� �ִ� ����

// ������ �������� ��Ÿ���� ����ü
typedef struct {
    int pagenumber;
    int arrivaltime;  // �������� ���� �ð�
} frame;

// ������ ������ ��Ÿ���� ����ü
typedef struct {
    int pagenumber;
} pagereference;

// ������ ��ü �˰����� �����ϴ� �Լ�
void fifo(int[], int, int);

int main() {
    int n;  // ������ ������ ����
    printf("������ ������ ������ �Է��ϼ���: ");
    scanf("%d", &n);

    // ������ ���� ���� �迭 �Ҵ�
    pagereference* pageReferences = (pagereference*)malloc(n * sizeof(pagereference));

    // ������ ���� �Է�
    printf("������ ������ �Է��ϼ���:\n");
    for (int i = 0; i < n; ++i) {
        printf("���� %d: ", i + 1);
        scanf("%d", &pageReferences[i].pagenumber);
    }

    int numframe;  // ������ �������� ����
    printf("������ �������� ������ �Է��ϼ���: ");
    scanf("%d", &numframe);

    // ������ ��ü �˰��� ����
    fifo(pageReferences, n, numframe);

    // ���� �迭 ����
    free(pageReferences);

    return 0;
}

void fifo(int pageReferences[], int n, int numFrames) {
    frame* frames = (frame*)malloc(numFrames * sizeof(frame));  // ������ ������ �迭 ���� �Ҵ�
    int frameCount = 0;                                        // ���� ������ ������ ����
    int pageFaults = 0;                                        // ������ ���� Ƚ��

    printf("FIFO\n");
    printf("+------+-----+-----+\n");
    printf("| Time | str | P.f | Memory\n");
    printf("+------+-----+-----+\n");

    for (int i = 0; i < n; ++i) {
        // �������� �̹� �޸𸮿� �����ϴ��� Ȯ��
        int pageExists = 0;
        for (int j = 0; j < frameCount; ++j) {
            if (frames[j].pagenumber == pageReferences[i]) {
                pageExists = 1;
                break;
            }
        }

        if (!pageExists) {
            // ������ ���� �߻�
            printf("| %4d | %3d |  F  | ", i + 1, pageReferences[i]);

            if (frameCount < numFrames) {
                // ������ �����ӿ� ������ ���� ���
                frames[frameCount].pagenumber = pageReferences[i];
                frames[frameCount].arrivaltime = i;  // ���� �ð����� ����
                ++frameCount;
            }
            else {
                // ������ ��ü �ʿ�
                int oldestIndex = 0;
                for (int j = 1; j < frameCount; ++j) {
                    if (frames[j].arrivaltime < frames[oldestIndex].arrivaltime) {
                        oldestIndex = j;
                    }
                }

                // ���� ������ ������ ��ü
                frames[oldestIndex].pagenumber = pageReferences[i];
                frames[oldestIndex].arrivaltime = i;  // ���� �ð����� ������Ʈ
            }

            ++pageFaults;

            // ���� ������ ������ ���
            for (int j = 0; j < frameCount; ++j) {
                printf("%d ", frames[j].pagenumber);
            }

            printf("\n");
        }
        else {
            // �������� �̹� �޸𸮿� �ִ� ���
            printf("| %4d | %3d |     | ", i + 1, pageReferences[i]);

            // ���� ������ ������ ���
            for (int j = 0; j < frameCount; ++j) {
                printf("%d ", frames[j].pagenumber);
            }

            printf("\n");
        }
    }

    printf("+------+-----+-----+\n");
    printf("\n��ü ������ ���� Ƚ��: %d\n", pageFaults);

    // ���� �迭 ����
    free(frames);
}