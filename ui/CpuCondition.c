#include "CpuCondition.h"
#include "ui_func.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PAST 0
#define PRESENT 1

typedef enum cpuInfo {
    USER,
    USER_NICE,
    SYSTEM,
    IDLE,
    IOWAIT,
    IRQ,
    SOFTIRQ,
    STEAL,
    GUEST,
    GUEST_NICE
} cpuInfo_enum;

void CpuCondition() {
    pthread_t p_thread[2];
    int thr_id;
    int status;
    char p1[] = "thread_1";
    char p2[] = "thread_2";

    cpu_ui();
    thr_id = pthread_create(&p_thread[0], NULL, cpu_usage, (void *)p1);
    if (thr_id < 0) {
        perror("thread create error : ");
        exit(0);
    }

    thr_id = pthread_create(&p_thread[1], NULL, cputemp_sensor, (void *)p2);
    if (thr_id < 0) {
        perror("thread create error : ");
        exit(0);
    }

    while (1) {
        if (kbhit() == 0) {
            continue;
        }
        if (kbhit() == 1) {
            int num = getch();
            if (num == 49) // 1, cpu 상태를 눌렀을때
                continue;
            if (num == 50) { // 2. 프로세스 상태를 눌렀을때
                pthread_cancel(p_thread[0]);
                pthread_cancel(p_thread[1]);
                break;
            }
            if (num == 51) { // 3. 나가기를 눌렀을때
                pthread_cancel(p_thread[0]);
                pthread_cancel(p_thread[1]);
                break;
            }
            if (num == 121) { // Y를 눌렀을때
                pthread_cancel(p_thread[0]);
                pthread_cancel(p_thread[1]);
                cputemp_install();
                continue;
            }
        }
    }

    return;
}

void *cpu_usage(void *data) {
    int usage[2][10][10] = {0};
    int diffUsage[10][10];
    FILE *file;
    while (1) {

        int i = 0;
        int totalUsage[10] = {0};
        char cpuId[10][4] = {0};

        file = fopen("/proc/stat", "r");
        while (1) {
            fscanf(file, "%s %d %d %d %d %d %d %d %d %d %d", cpuId[i],
                   &usage[PRESENT][i][USER], &usage[PRESENT][i][USER_NICE],
                   &usage[PRESENT][i][SYSTEM], &usage[PRESENT][i][IDLE],
                   &usage[PRESENT][i][IOWAIT], &usage[PRESENT][i][IRQ],
                   &usage[PRESENT][i][SOFTIRQ], &usage[PRESENT][i][STEAL],
                   &usage[PRESENT][i][GUEST], &usage[PRESENT][i][GUEST_NICE]);

            if (cpuId[i][0] == 'i') {
                cpuId[i][0] = '\0';
                break;
            }
            i++;
        }

        for (int num = 0; num < i; num++) {
            for (int idx = 0; idx < 10; idx++) {
                diffUsage[num][idx] =
                    usage[PRESENT][num][idx] - usage[PAST][num][idx];
                totalUsage[num] = totalUsage[num] + diffUsage[num][idx];
            }
            move_cur(2, 12 + num);
            printf("                                               ");
            move_cur(2, 12 + num);
            printf("%s %d %d %d %d %d %d %d %d %d %d\n", cpuId[num],
                   diffUsage[num][USER], diffUsage[num][USER_NICE],
                   diffUsage[num][SYSTEM], diffUsage[num][IDLE],
                   diffUsage[num][IOWAIT], diffUsage[num][IRQ],
                   diffUsage[num][SOFTIRQ], diffUsage[num][STEAL],
                   diffUsage[num][GUEST], diffUsage[num][GUEST_NICE]);
        }
        move_cur(2, 15);
        printf("Cpu usage : %f%%\n",
               100.0 * (1.0 - (diffUsage[0][IDLE] / (double)totalUsage[0])));
        fflush(stdout);
        memcpy(usage[PAST], usage[PRESENT], sizeof(int) * 100);
        fclose(file);
        sleep(1);
    }
    sleep(1);
} // cpu 사용량

void cputemp_install() {
    system("clear");
    cpu_ui();
    move_cur(10, 2);
    printf("@@@@@@@@@@@@@@@@@@--downloads--@@@@@@@@@@@@@@@\n");
    sleep(0.2);
    move_cur(10, 3);
    printf("@@@@@@@@@@@@@@@@@--------------@@@@@@@@@@@@@@@\n");
    sleep(1);
    move_cur(10, 4);
    printf("@@@@@@@@@@@@@@@@@--------------@@@@@@@@@@@@@@@\n");
    sleep(0.6);
    move_cur(10, 5);
    printf("@@@@@@@@@@@@@@@@@--------------@@@@@@@@@@@@@@@\n");
    sleep(0.6);
    move_cur(10, 6);
    printf("@@@@@@@@@@@@@@@@@--------------@@@@@@@@@@@@@@@\n");
    sleep(0.7);
    move_cur(10, 7);
    printf("@@@@@@@;---------------------------------@@@@@\n");
    sleep(0.8);
    move_cur(10, 8);
    printf("@@@@@@@@---------------------------------@@@@@\n");
    sleep(1);
    move_cur(10, 9);
    printf("@@@@@@@@@@~--------downloads-----------@@@@@@@\n");
    sleep(0.3);
    move_cur(10, 10);
    printf("@@@@@@@@@@@---------------------------@@@@@@@@\n");
    sleep(0.5);
    move_cur(10, 11);
    printf("@@@@@@@@@@@@@-----------------------@@@@@@@@@@\n");
    sleep(0.8);
    move_cur(10, 12);
    printf("@@@@@@@@@@@@@@@@@---------------@@@@@@@@@@@@@@\n");
    sleep(0.8);
    move_cur(10, 13);
    printf("@@@@@@@@@@@@@@@@@@-------------@@@@@@@@@@@@@@@\n");
    sleep(0.8);
    move_cur(10, 14);
    printf("@@@@@@@@@@@@@@@@@@@----------@@@@@@@@@@@@@@@@@\n");
    sleep(1);
    move_cur(10, 15);
    printf("@@@@@@@@@@@@@@@@@@@@---------@@@@@@@@@@@@@@@@@\n");
    sleep(0.6);
    move_cur(10, 16);
    printf("@@@@@@@@@@@@@@@@@@@@@-------@@@@@@@@@@@@@@@@@@\n");
    sleep(1.3);
    move_cur(10, 17);
    printf("@@@@@@@@@@@@@@@@@@@@@@@---@@@@@@@@@@@@@@@@@@@@\n");
    sleep(0.5);
    move_cur(10, 18);
    printf("@@@@@@@@@@@@@@@@@@@@@@@--@@@@@@@@@@@@@@@@@@@@@\n");
    sleep(0.1);
    sleep(2);
    system("clear");
    cpu_ui();
    move_cur(2, 2);
    printf("\n");
    system("sudo apt install lm-sensors");
    sleep(5);
    system("clear");
} // cpu 온도센서 설치

void *cputemp_sensor(void *data) {

    while (1) {

        char buff[256];
        FILE *fp;
        char sensor[30] = "sh: 1: sensors: not found";

        move_cur(2, 4);
        printf("cpu temperature : \n");
        fp = popen("sensors 2>&1", "r");
        int num = 5;
        while (fgets(buff, 256, fp) != NULL) {
            if (strcmp(buff, sensor)) {
                move_cur(2, num);
                printf("%s", buff);
                move_cur(2, 7);
                printf("No sensor to check temperature. Press Y to "
                       "install "
                       "sensor.");
            } else {
                move_cur(2, num);
                printf("%s", buff);
                move_cur(2, 9);
                printf("press Y to reinstall sensor.");

                num++;
            }
        }
        fflush(stdout);
        pclose(fp);
        sleep(2);
    }
    sleep(1);
} // cpu 온도센서 출력

void cpu_ui() {
    printf("┌──────────────────────────────────────────────────────────"
           "────"
           "───────"
           "──"
           "───┐\n"
           "│                                 cpu condition            "
           "    "
           "            │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "       "
           "     │\n"
           "│                                                          "
           "    "
           "    "
           "        │\n"
           "│                                 "
           "      1 cpu 상태 2 프로세스 상태 3 나가기│\n"
           "└──────────────────────────────────────────────────────────"
           "────"
           "───────"
           "─────┘\n");
} // cpu ui

/*int cpu_kbhit() {
    while (1) {
        if (kbhit() == 0) {
            continue;
        }
        if (kbhit() == 1) {
            int num = getch();
            if (num == 49) // 1, cpu 상태를 눌렀을때
                return 1;
            if (num == 50) // 2. 프로세스 상태를 눌렀을때
                return 2;
            if (num == 51) // 3. 나가기를 눌렀을때
                return 3;
            if (num == 121) {
                cputemp_install();
                continue;
            } // Y를 눌렀을때
        }
    }
}
*/
