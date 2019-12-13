#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define ENTER_KEY 10
#define TAB_KEY 9
#define BACKSPACE_KEY 127

#ifndef __UI_FUNC_H__
#define __UI_FUNC_H__

struct User {
    char id[16];
    char passwd[16];
};

int getch() {
    int c;
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr); // 현재 터미널 설정 읽음
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO); // CANONICAL과 ECHO 끔
    newattr.c_cc[VMIN] = 1;  // 최소 입력 문자 수를 1로 설정
    newattr.c_cc[VTIME] = 0; // 최소 읽기 대기 시간을 0으로 설정
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr); // 터미널에 설정 입력
    c = getchar();                              // 키보드 입력 읽음
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); // 원래의 설정으로 복구
    return c;
} // 키보드에 입력받은 문자를 바로 반환

void move_cur(int x, int y) {
    printf("\033[%dd\033[%dG", y, x);
} // 커서를 해당 위치로 이동

int get_id(char *buf, int size) {
    int cnt = 0, key; // 입력 받은 글자 수와 키

    while (1) {
        key = getch();                          // 한 글자 입력받음
        if (key == ENTER_KEY || key == TAB_KEY) // 엔터 또는 탭 키면 종료
            break;
        if (key == BACKSPACE_KEY) {
            if (cnt == 0) // 아무 문자도 없을 때는 진행
                continue;
            if (cnt > 0) {
                move_cur(30, 9);
                cnt = cnt - 1;
                buf[cnt] = '\0';
                printf("%s", buf);
                printf(" \b");
                continue;
            } // 문자가 있을 경우 처음으로 커서를 옮기고 해당 문자를
              // NULL문자로 만든 후 새로 출력함.
        }

        buf[cnt++] = (char)key; // 버퍼에 글자 저장하고 카운트 1 증가
        printf("%c", (char)key);

        if (cnt == size - 1) {
            move_cur(9, 15);
            printf("아이디의 최대 길이는 14자 입니다. 다시 입력해 주세요.");
            move_cur(30, 9);
            printf("                  ");
            move_cur(30, 9);
            cnt = 0;
            continue;
        } // 처음으로 돌아가 다시 입력받음
    }

    buf[cnt] = '\0'; // 문자열로 만들기 위해 널 문자 마무리
    return *buf;
} // 키보드에 입력받은 문자를 id에 넣음

int get_pw(char *buf, int size) {
    int cnt = 0, key; // 입력 받은 글자 수와 키

    while (1) {
        key = getch();                          // 한 글자 입력받음
        if (key == ENTER_KEY || key == TAB_KEY) // 엔터 또는 탭 키면 종료
            break;
        if (key == BACKSPACE_KEY) {
            if (cnt == 0) // 아무 문자도 없을 때는 진행
                continue;
            if (cnt > 0) {
                move_cur(30, 13);
                cnt = cnt - 1;
                buf[cnt] = '\0';
                for (int j = 0; j < cnt; j++)
                    printf("*");
                printf(" \b");
                continue;
            } // 문자가 있을 경우 처음으로 커서를 옮기고 해당 문자를
              // NULL문자로 만든 후 새로 출력함.
        }
        buf[cnt++] = (char)key; // 버퍼에 글자 저장하고 카운트 1 증가
        printf("*");            // 화면에 별 표시

        if (cnt == size - 1) {
            move_cur(9, 15);
            printf("비밀번호의 최대 길이는 14자 입니다. 다시 입력해 주세요.");
            move_cur(30, 13);
            printf("                  ");
            move_cur(30, 13);
            cnt = 0;
            continue;
        } // 처음으로 돌아가 다시 입력받음
    }

    buf[cnt] = '\0'; // 문자열로 만들기 위해 널 문자 마무리

    return *buf;
} // 키보드에 입력받은 문자를 passwd에 넣음

int kbhit() { // 키 버퍼에 값이 있는 지 확인
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

void clearline(int x, int y) { // 해당 라인 출력 초기화
    move_cur(x, y);
    printf("                                                                   "
           "       ");
    move_cur(x, y);
}

#endif
