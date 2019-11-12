#include "signin_ui.c"
#include "signup_ui.c"
#include "ui_func.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef __FIRST_UI_C__
#define __FIRST_UI_C__

void FirstUi() {
    int num;
    system("clear");
    printf("┌──────────────────────────────────────────────────────────────────"
           "───┐\n"
           "│                                                                  "
           "   │\n"
           "│                                                                  "
           "   │\n"
           "│                    \x1b[32m오클린\x1b[0m에 오신 것을 환영합니다! "
           "       "
           "         "
           "  │\n"
           "│                  진행하려면 다음 숫자를 눌러주세요.              "
           "   │\n"
           "│                                                                  "
           "   │\n"
           "│                            1.회원가입                            "
           "   │\n"
           "│                            2.로그인                              "
           "   │\n"
           "│                            3.프로그램 종료                       "
           "   │\n"
           "│                                                                  "
           "   │\n"
           "│                                                                  "
           "   │\n"
           "└────────────────────────────────────────────────────────────────"
           "─────┘\n");
    num = getch();
    system("clear");
    switch (num) {
    case 49: // 1.회원가입을 눌렀을 경우
        SignupUi();
        FirstUi();
        break;
    case 50: // 2.로그인을 눌렀을 경우
        SigninUi();
        FirstUi();
        break;
    case 51: // 3.프로그램 종료를 눌렀을 경우
        exit(0);
    default:
        FirstUi();
    }
}

#endif
