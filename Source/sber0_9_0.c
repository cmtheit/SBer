/**
 * @file sb0_9_0.c
 * @author 程闽     
 * @address: e-mail:cmtheit@outlook.com | QQ:2905432378
 * @brief  这是最初始的版本 of SBer。
 * @version 0.9.0
 * @date 2022-05-20
 * 
 * @copyright Be free!
 * 
 */

#include<stdio.h>
#include<time.h>


int main(int argc, char**argv){
    if(argc == 1){
        printf("Please input your thought.");
        return 0;
    }
    time_t n = time(NULL);
    struct tm * now = localtime(&n);
    FILE * l = fopen("C:\\Users\\cmthe\\Desktop\\随笔.txt", "a");
    char buffer[30] = {0};
    strftime(buffer, 30, "\n\n%Y年%m月%d日%H:%M:%S\n", now);
    fprintf(l, buffer);
    fprintf(l, argv[1]);
    fclose(l);
    return 0;
}