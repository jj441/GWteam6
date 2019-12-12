#include "client.c"
#include "ui_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef __SIGNUP_UI_C__
#define __SIGNUP_UI_C__

void SignupUi() {
    char id[16];
    char pw[16];
    char signup[6] = "signup";
    system("clear");
    printf(
        "┌──────────────────────────────────────────────────────────────"
        "─────────"
        "───┐\n"
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
        "│                                  회원가입                        "
        "      "
        "  │\n"
        "│                                                              "
        "       "
        "     │\n"
        "│                           ┌───────────────────┐                  "
        "      "
        "  │\n"
        "│                   아이디  │                   │                   "
        "     "
        "  │\n"
        "│                           └───────────────────┘                   "
        "     "
        "  │\n"
        "│                                                              "
        "       "
        "     │\n"
        "│                           ┌───────────────────┐                  "
        "       "
        " │\n"
        "│                 비밀번호  │                   │                   "
        "       "
        "│\n"
        "│                           └───────────────────┘                  "
        "      "
        "  │\n"
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

        "└──────────────────────────────────────────────────────────────"
        "───────"
        "─────┘\n");

    move_cur(30, 9);
    get_id(id, 16);
    move_cur(30, 13);
    get_pw(pw, 16);
    client(id, pw, signup);
    move_cur(9, 17);
    printf("회원가입이 완료되었습니다. 3초 후 초기화면으로 돌아갑니다.");
    fflush(stdout);
    sleep(3);
}

#endif
