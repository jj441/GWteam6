#include "ui_func.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef __SIGNIN_UI_C__
#define __SIGNIN_UI_C__

void SigninUi() {
    struct User user;
    system("clear");
    printf(
        "┌─────────────────────────────────────────────────────────────────────"
        "┐\n"
        "│                                                                     "
        "│\n"
        "│                                 로그인                            "
        "  │\n"
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
}

#endif
