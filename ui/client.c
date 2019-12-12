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
    char signin[6] = "signin";

    MsgCalc msgCalc;
    MsgRslt msgRslt;

    strcpy(str, log);
    fflush(stdin);
    memset(&msgCalc, 0x00, sizeof(MsgCalc));
    msgCalc.mtype = MSG_TYPE_CALC;
    strcpy(msgCalc.calc.str, str);
    msgsnd(msqid, &msgCalc, MSG_SIZE_CALC, 0);

    strcpy(str, id);
    fflush(stdin);
    memset(&msgCalc, 0x00, sizeof(MsgCalc));
    msgCalc.mtype = MSG_TYPE_CALC;
    strcpy(msgCalc.calc.str, str);
    msgsnd(msqid, &msgCalc, MSG_SIZE_CALC, 0);

    strcpy(str, pw);
    fflush(stdin);
    memset(&msgCalc, 0x00, sizeof(MsgCalc));
    msgCalc.mtype = MSG_TYPE_CALC;
    strcpy(msgCalc.calc.str, str);
    msgsnd(msqid, &msgCalc, MSG_SIZE_CALC, 0);

    // if (!strcmp(log, signin)) {
    //     memset(&msgRslt, 0x00, sizeof(MsgRslt));
    //     msgrcv(msqid, &msgRslt, MSG_SIZE_RSLT, MSG_TYPE_RSLT, 0);
    //     printf(">>> %d\n", msgRslt.rslt);
    //     printf("4");
    //     sleep(5);
    // } else {
    //     printf("5");
    //     sleep(5);
    // }
    return;
}
#endif
