#include "mymsg.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#ifndef __CLIENT_C__
#define __CLIENT_C__

void client(char *id, char *pw, char *log) {
    key_t mykey = ftok("mykey", 1);
    int msqid = msgget(mykey, IPC_CREAT);
    char str[16];

    MsgCalc msgCalc;
    MsgRslt msgRslt;

    strcpy(str, log); // 회원가입, 로그인 인지 구별
    fflush(stdin);
    memset(&msgCalc, 0x00, sizeof(MsgCalc));
    msgCalc.mtype = MSG_TYPE_CALC;
    strcpy(msgCalc.calc.str, str);
    msgsnd(msqid, &msgCalc, MSG_SIZE_CALC, 0);

    strcpy(str, id); // id 문자열 복사
    fflush(stdin);
    memset(&msgCalc, 0x00, sizeof(MsgCalc));
    msgCalc.mtype = MSG_TYPE_CALC;
    strcpy(msgCalc.calc.str, str);
    msgsnd(msqid, &msgCalc, MSG_SIZE_CALC, 0); // id 문자열 전송

    strcpy(str, pw); // pw 문자열 복사
    fflush(stdin);
    memset(&msgCalc, 0x00, sizeof(MsgCalc));
    msgCalc.mtype = MSG_TYPE_CALC;
    strcpy(msgCalc.calc.str, str);
    msgsnd(msqid, &msgCalc, MSG_SIZE_CALC, 0); // pw 문자열 전송

    return;
}
#endif
