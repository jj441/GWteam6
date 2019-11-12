#include "ui_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef __SIGNUP_UI_C__
#define __SIGNUP_UI_C__

void SignupUi() {
    struct User user;
    system("clear");
    printf(
        "┌─────────────────────────────────────────────────────────────────────"
        "┐\n"
        "│                                                                     "
        "│\n"
        "│                                 회원가입                            "
        "│\n"
        "│                          ┌───────────────────┐                    "
        "  │\n"
        "│                  아이디  │                   │                    "
        "  │\n"
        "│                          └───────────────────┘                    "
        "  │\n"
        "│                          ┌───────────────────┐                     "
        " │\n"
        "│                비밀번호  │                   │                      "
        "│\n"
        "│                          └───────────────────┘                      "
        "│\n"
        "│                                                                  "
        "   │\n"
        "│                                                                  "
        "   │\n"
        "└────────────────────────────────────────────────────────────────"
        "─────┘\n");
    move_cur(30, 5);
    get_id(user.id, 16);
    move_cur(30, 8);
    get_pw(user.passwd, 16);
    move_cur(0, 13);
    printf("\n회원가입이 완료되었습니다. 3초 후 초기화면으로 돌아갑니다.");
    fflush(stdout);
    sleep(3);
}

#endif
