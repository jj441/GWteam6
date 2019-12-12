#include "ui_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFF_SIZE 1024

void adware_ui();
void adware_ui_intro();
void adware_remove();

void RemoveAdware() {
    FILE *file;

    char str[BUFF_SIZE];
    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];
    char buf[BUFF_SIZE];
    int count = 0;
    int adwarecount = 9;
    int adwareTF = 0;

    system("clear");
    adware_ui_intro();
    system("clear");
    adware_ui();
    move_cur(2, 5);
    printf("진행하려면 루트 비밀번호를 입력해주세요.");
    clearline(2, 5);
    fflush(stdout);
    file = popen("sudo find / -type f 2>/dev/null", "r");
    FILE *fp1 = fopen("./adrmlist.txt", "w");
    while (fgets(str, 1024, file) != NULL) {
        clearline(2, 5);
        printf("파일 경로 : ");
        for (int i = 0; i < 60; i++) {
            if (str[i] == '\0')
                break;
            printf("%c", str[i]);
        }

        FILE *fp = fopen("./adwareList.txt", "r");
        while (fgets(str1, sizeof(str1), fp) != NULL) {
            char *ptr = strstr(str, str1);
            if (ptr != NULL) {
                sleep(1);
                move_cur(2, adwarecount);
                printf("adware : %s|\n", str);
                fprintf(fp1, "%s", str);
                fflush(stdout);
                adwarecount++;
                adwareTF = 1;
            }
        }

        fclose(fp);

        clearline(2, 7);
        printf("검사한 파일의 개수 : %d", count);
        fflush(stdout);

        count++;
    }
    fclose(fp1);
    move_cur(65, 7);
    printf("검사 완료");
    fflush(stdout);
    pclose(file);

    move_cur(2, adwarecount);
    if (adwareTF == 0) {
        printf("아무 것도 검출되지 않았습니다.");
    } else if (adwareTF == 1) {
        printf("애드웨어를 삭제하시려면 Y를 누르세요.\n");
    }

    int num = getch();
    if (num == 49)
        return;
    else if (num == 121) {
        char str[1024];
        FILE *fp2 = fopen("./adrmlist.txt", "r");
        while (fscanf(fp2, "%s", str) > 0) {
            move_cur(2, adwarecount + 1);
            printf("%s", str);
            int result = remove(str);
            if (result == 0) {
                printf(" : file delete complete\n");
            } else if (result == -1) {
                printf(" : file delete fail\n");
            }
            sleep(1);
            adwarecount++;
        }
        move_cur(2, adwarecount);
        printf("All adware deleted!");
        int num = getch();
        if (num == 49)
            return;
    } else {
        return;
    }
}

void adware_ui() {
    printf("┌──────────────────────────────────────────────────────────────"
           "───────"
           "──"
           "───┐\n"
           "│                               애드웨어 삭제           "
           "         "
           "     "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                              "
           "       "
           "     │\n"
           "│                                                                  "
           "        │\n"
           "│                                 "
           "                                 1 나가기│\n"
           "└──────────────────────────────────────────────────────────────────"
           "────────┘\n");
}

void adware_ui_intro() {
    adware_ui();
    move_cur(19, 4);
    printf("..............@@@@@@@@@@@..............");
    move_cur(19, 5);
    printf("..............@@@@@@@@@@@..............");
    move_cur(19, 6);
    printf("...............@@@@@@@@@...............");
    move_cur(19, 7);
    printf(".................@@@@@.................");
    move_cur(19, 8);
    printf("................. @@@ .................");
    move_cur(19, 9);
    printf(".......@..........@@@..........@.......");
    move_cur(19, 10);
    printf(".......@@@...................@@@.......");
    move_cur(19, 11);
    printf(".......@@@@@ ............. @@@@@.......");
    move_cur(19, 12);
    printf(".......@@@@@@@...........@@@@@@@.......");
    move_cur(19, 13);
    printf(".......@@@@@@@...........@@@@@@@.......");
    move_cur(19, 14);
    printf(".......@@@@@@@...........@@@@@@@.......");
    move_cur(19, 15);
    printf(".......@@@@@ ............. @@@@@.......");
    move_cur(19, 16);
    printf(".......@@@...................@@@.......");
    move_cur(19, 17);
    printf(".......@..........@@@..........@.......");
    move_cur(19, 18);
    printf("...............@@@@@@@@@...............");
    move_cur(19, 19);
    printf("..............@@@@@@@@@@@..............");
    move_cur(19, 20);
    printf("..............@@@@@@@@@@@..............");
    move_cur(19, 21);
    printf(".............@@@@@@@@@@@@@ ............\n");
    sleep(2);
}
