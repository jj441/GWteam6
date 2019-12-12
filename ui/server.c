#include "mymsg.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef __SERVER_C__
#define __SERVER_C__

void signalHandler(int signum);
int TrueOrFalse(Calc calc);

key_t mykey = 0;
int msqid = 0;

int main(int argc, char const *argv[]) {
    int fd = 0;
    char *pathname = "./logDB.txt";
    char lf = '\n';
    char dash = '-';
    ssize_t wsize = 0;
    char pw[16];
    char str[50];
    MsgCalc msgCalc;
    MsgRslt msgRslt;
    mykey = ftok("mykey", 1);
    // 키 생성
    msqid = msgget(mykey, IPC_CREAT | 0644); // 메시지 큐 생성
    signal(SIGINT, signalHandler);
    while (1) {
        memset(&msgCalc, 0x00, sizeof(MsgCalc));
        msgrcv(msqid, &msgCalc, MSG_SIZE_CALC, MSG_TYPE_CALC, 0);
        printf("Receive: %s\n", msgCalc.calc.str);
        char signup[6] = "signup";
        char signin[6] = "signin";
        char *ptr = strstr(msgCalc.calc.str, signin);
        char *ptr1 = strstr(msgCalc.calc.str, signup);
        if (ptr != NULL) {
            MsgCalc id;
            MsgCalc pw;

            memset(&msgCalc, 0x00, sizeof(MsgCalc));
            msgrcv(msqid, &msgCalc, MSG_SIZE_CALC, MSG_TYPE_CALC, 0);
            printf("Receive: %s\n", msgCalc.calc.str);
            strcpy(id.calc.str, msgCalc.calc.str);

            fd = open(pathname, O_CREAT | O_APPEND | O_RDWR, 0644);
            if (fd == -1) {
                perror("open() error!");
                exit(-1);
            }

            wsize = write(fd, (char *)id.calc.str, strlen(id.calc.str));
            if (wsize == -1) {
                perror("write() error!");
                exit(-2);
            }

            wsize = write(fd, &dash, 1);
            if (wsize == -1) {
                perror("write() error!");
                exit(-2);
            }

            memset(&msgCalc, 0x00, sizeof(MsgCalc));
            msgrcv(msqid, &msgCalc, MSG_SIZE_CALC, MSG_TYPE_CALC, 0);
            printf("Receive: %s\n", msgCalc.calc.str);
            strcpy(pw.calc.str, msgCalc.calc.str);

            wsize =
                write(fd, (char *)msgCalc.calc.str, strlen(msgCalc.calc.str));
            if (wsize == -1) {
                perror("write() error!");
                exit(-2);
            }

            wsize = write(fd, &lf, 1);
            if (wsize == -1) {
                perror("write() error!");
                exit(-2);
            }
            printf("22\n");
            FILE *fp = fopen(pathname, "r");
            printf("22\n");
            while (fgets(str, sizeof(str), fp) != NULL) {
                printf("22");
                char *ptrid = strstr(str, id.calc.str);
                char *ptrpw = strstr(str, pw.calc.str);
                if (ptrid != NULL && ptrpw != NULL) {
                    memset(&msgRslt, 0x00, sizeof(MsgRslt));
                    msgRslt.mtype = MSG_TYPE_RSLT;
                    msgRslt.rslt = 1;
                    msgsnd(msqid, &msgRslt, MSG_SIZE_RSLT, 0);
                    printf("Send: %d\n", msgRslt.rslt);
                    fflush(stdout);
                }
            }

            fclose(fp);
        }

        if (ptr1 != NULL) {

            memset(&msgCalc, 0x00, sizeof(MsgCalc));
            msgrcv(msqid, &msgCalc, MSG_SIZE_CALC, MSG_TYPE_CALC, 0);
            printf("Receive: %s\n", msgCalc.calc.str);

            fd = open(pathname, O_CREAT | O_APPEND | O_RDWR, 0644);
            if (fd == -1) {
                perror("open() error!");
                exit(-1);
            }

            wsize =
                write(fd, (char *)msgCalc.calc.str, strlen(msgCalc.calc.str));
            if (wsize == -1) {
                perror("write() error!");
                exit(-2);
            }

            wsize = write(fd, &dash, 1);
            if (wsize == -1) {
                perror("write() error!");
                exit(-2);
            }

            memset(&msgCalc, 0x00, sizeof(MsgCalc));
            msgrcv(msqid, &msgCalc, MSG_SIZE_CALC, MSG_TYPE_CALC, 0);
            printf("Receive: %s\n", msgCalc.calc.str);

            wsize =
                write(fd, (char *)msgCalc.calc.str, strlen(msgCalc.calc.str));
            if (wsize == -1) {
                perror("write() error!");
                exit(-2);
            }

            wsize = write(fd, &lf, 1);
            if (wsize == -1) {
                perror("write() error!");
                exit(-2);
            }
        }
    }
    return 0;
}
void signalHandler(int signum) {
    if (signum == SIGINT) {
        msgctl(msqid, IPC_RMID, NULL);
        exit(0);
    }
}
#endif
