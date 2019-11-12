#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#define ENTER_KEY 10
#define TAB_KEY 9

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

        buf[cnt++] = (char)key; // 버퍼에 글자 저장하고 카운트 1 증가
        printf("%c", (char)key);

        if (cnt == size - 1) // 최대 크기를 넘어가면 종료
            break;
    }

    buf[cnt] = '\0'; // 문자열로 만들기 위해 널 문자 마무리
} // 키보드에 입력받은 문자를 id에 넣음

int get_pw(char *buf, int size) {
    int cnt = 0, key; // 입력 받은 글자 수와 키

    while (1) {
        key = getch();                          // 한 글자 입력받음
        if (key == ENTER_KEY || key == TAB_KEY) // 엔터 또는 탭 키면 종료
            break;

        buf[cnt++] = (char)key; // 버퍼에 글자 저장하고 카운트 1 증가
        putchar('*');           // 화면에 별 표시

        if (cnt == size - 1) // 최대 크기를 넘어가면 종료
            break;
    }

    buf[cnt] = '\0'; // 문자열로 만들기 위해 널 문자 마무리
} // 키보드에 입력받은 문자를 passwd에 넣음

#endif
