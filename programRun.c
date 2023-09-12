#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <tlhelp32.h>
#include <tchar.h>
#include "painted_ggshell.h"

typedef struct run{ // 全局结构体变量(主要用于命令字符存储)
    char command[256];
}cmd;

cmd namespace;

int check_shutDown()
{
    int key = 0;
    while(!kbhit())
    {
        if(kbhit()){
            if(getch()){
                key = 1;
            }else{
                if(key == 1) return key; break;
            }
        }
    }
}

void query_method(char data[])
{
    DWORD dwPID;  
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  
    PROCESSENTRY32 processEntry;  
    processEntry.dwSize = sizeof(PROCESSENTRY32);  
  
    if (!Process32First(hSnapShot, &processEntry)) {  
        printf("Failed\n\n");  
    }  
  
    do {  
        if (!strcmp(processEntry.szExeFile, data)) {   
            dwPID = processEntry.th32ProcessID;  
            printf("\n进程 %s PID为 %u\n\n", processEntry.szExeFile, dwPID);  
            break;  
        }  
    } while (Process32Next(hSnapShot, &processEntry));  
  
    CloseHandle(hSnapShot);  
    system("pause");
}

int IsProcessExists(const char* processName) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hSnapshot, &pe32)) {
        CloseHandle(hSnapshot);
        return 0;
    }

    do {
        if (strcmp(pe32.szExeFile, processName) == 0) {
            CloseHandle(hSnapshot);
            return 1;
        }
    } while (Process32Next(hSnapshot, &pe32));

    CloseHandle(hSnapshot);
    return 0;
}

void compare_time_result()
{
    char* timeStr;
    time_t time1, time2;
    struct tm* timeinfo;
    int hour, minute, second;
    int alltime,alltime2;
    time1 = time(NULL); // 获取当前时间
    timeinfo=localtime(&time1);
    printf("请输入时间 格式:00/00/00 时/分/秒:\n");
    scanf("%s", &timeStr);
    if(strlen((char*)&timeStr)!=8){
        printf("error(时间格式错误)\n\n");
    }
    else{
       hour=atoi((char*)&timeStr); // 将输入的字符串转化成时分秒
       minute=atoi((char*)(&timeStr)+3);
       second=atoi((char*)(&timeStr)+6);
       alltime=hour*360+minute*60+second; // 将输入的时间转换成总秒数
       alltime2=timeinfo->tm_hour*360+timeinfo->tm_min*60+timeinfo->tm_sec; // 将当0前时间转换成总秒数
        if(alltime>=alltime2){
            printf("距离目标时间还剩%d秒\n",alltime-alltime2);
        }else{
            printf("距离目标时间已经过了%d秒\n",alltime2-alltime);
        }
    }
}

void sonMenu_options(char input)  
{  
    char* SYstime();  
    char *Text;
    if(input == 1)  
    {  
        char* timeStr = SYstime();    
        printf("\n系统时间为: %s\n\n", timeStr);    
        free(timeStr);  
    }else if(input == 2){
        compare_time_result();
    }
} 

void sonMenu()
{
    //void sonMenu_options(char);
    char input;
    system("cls");
    system("TITLE 子级菜单");
    int i;
    char *Text[] = {
        "系统时间\n\n",
        "对较时间\n\n",
        "退出子级菜单\n\n"
    };
    for(i=0; i<sizeof(Text) / sizeof(Text[0]); i++){
        Sleep(750);
        printf("%d.%s",(i + 1),Text[i]);
    }
    printf("请键入您所需要的操作:");
    scanf("%d",&input);
    sonMenu_options(input);
}

void fristTitle() {  
    int i, j;  
    char *Str[] = {  
        "星驰所向,\n路途何归?\n风雪潇窣,\n遥遥不得.\n"  
    };  
    int key = 0;  
    while (!kbhit()) {  
        for (j = 0; j < sizeof(Str) / sizeof(Str[0]); j++) {  
            for (i = 0; i < strlen(Str[j]); i++) {  
                if (kbhit()) {  
                    if (getch()) {  
                        key = 1;  
                        system("cls");  
                        printf("%s\n", Str[0]);  
                        system("cls");  
                        printf("%s\n", Str[0]);  
                    }  
                } else {  
                    if (key == 1) {  
                        break;  
                    }  
                    Sleep(220);  
                    printf("%c", *(((char *)Str[j]) + i));  
                }  
            }  
            if (key == 1) {  
                break;  
            }  
            printf("\n");  
        }  
        if (key == 1) {  
            break;  
        }  
        printf("--作者QQ: 1065722706\n--协作QQ:2694898194\n");  
        Sleep(1000);  
        if(key == 0) {
            break; 
        }
    }  
}

char* SYstime()  
{    
    time_t rawtime;    
    struct tm *timeinfo;    
    char timeStr[50];    
    
    time(&rawtime);    
    timeinfo = localtime(&rawtime);    
    
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);    
    
    return strdup(timeStr);  // 使用strdup复制字符串，避免返回局部变量  
}

void equals(char* input)
{
    cmd *data = &namespace;
    const char* pattern = "\\.exe$";
    const char* processName = "Studentmain.exe";
    const char* processName_two = "";
    const char* command = "\"C:\\Program Files (x86)\\Mythware\\program.exe\""; // 目标程序目录
    char command_one[] = "taskkill /f /im studentmain.exe";
    char command_two[] = "shutdown -s -t 100";
    char command_three[] = "mkdir /J \"C:\\Users\\Administrator\\Desktop\" \"C:\\Program Files (x86)\\Mythware\\program.exe\""; // 创建桌面目录链接
    char command_four[101] = "taskkill /pid ";
    char *destination = "\"C:\\Program Files (x86)\\Mythware\\program.exe\""; // 判断程序是否存在
    FILE *file;
    char query_data[256]; // 键入查询值所需变量
    int exists = IsProcessExists(processName); // 获取IsProcessExists返回值
    int i,j,k; // 循环所需变量

    if(*input == '1'){
        if(exists){
            Sleep(500);
            printf("taskkill has done\n");
            for(i = 0; i <= strlen(command_one); i++) data->command[i] = command_one[i]; // 根据变量字节长度分配i的数值,并依次赋予结构体data的command数组变量值(以下类似)
            system(data->command);

            system("pause");
            exit(0);
        }else{
            Sleep(500);
            printf("\n目标进程不存在,请检查进程是否处于开启状态(或是该进程存在)\n\n");
            system("pause");
            exit(0);
            system("cls");
        }
    }else if(*input == '2'){
        Sleep(500);
        printf("关机计划已启动,按任意键取消..\n");
        Sleep(1000);
        for(j = 0; j <= strlen(command_two); j++) data->command[j] = command_two[j];
        system(data->command);
        if(check_shutDown()){
            system("shutdown -a");
            printf("\n已取消\n\n");
        }
        system("pause");
        exit(0);
        system("cls");
    }else if(*input == '3'){
        Sleep(500);
        file = fopen(destination,"r");
        printf("警告:此操作不可逆,为单向操作\n");
        Sleep(1000);
        if(file == NULL){ // error判断
            printf("启动失败,将在桌面创建一个link快捷方式,请进入目标目录找到程序文件运行.(如若桌面未创建快捷方式,请在\"win\"搜索栏内搜索\"极域\"进行操作\n");
            Sleep(540);
            for(k = 0; k <= strlen(command_three); k++) data->command[k] = command_three[k];
            system(data->command);
            system("pause");
            exit(0);
            return;
        }else{
            printf("查找目标程序成功,正在启动中...");
            Sleep(1000);
            system(command);
            system("pause");
            fclose(file);
        }
    }else if(*input == '4'){
        printf("请键入对应的进程昵称: ");
        scanf("%s", &query_data); 
        if(strstr(query_data, ".exe")){ // 判断用户键入字符串是否包含'.exe'
        }else{
            strcat(query_data,".exe");
        }
        int exists_user = IsProcessExists(query_data); // 获取IsProcessExists返回值
        if(exists_user) {
            if(strstr(query_data, ".exe")){
                query_method(query_data);
            }else{
                strcat(query_data,".exe");
                query_method(query_data);
        }
        }else{
        printf("\n目标进程不存在或不在运行\n\n");
        system("pause");
    }
        exit(0);
    }else if(*input == '5'){
        Sleep(1000);
        printf("\nsuccess\n\n");
        Sleep(1500);
        system("tasklist");
        system("pause");
        exit(1);
    }else if(*input == '6'){
        char PID[100];
        printf("请键入PID:");
        memset(PID, 0, sizeof(PID));
        scanf("%s",&PID);
        strcat(command_four, PID); // 字符串拼接
        strcat(command_four," /f");
        system(command_four);
    }else if(*input == '8'){
        sonMenu();
    }else{
        printf("\ninput invalid\n\n");
        system("pause");
        exit(0);
    }
}

// 草案,原为存储字符串字节数据(在一个组内存储多个数据段)
// char Statement_storage(){
//     int i;
//     char string;

//     char *size = (char *)malloc(sizeof(char) * 1000);

//     strcpy(string, "text");

//     for(i = 0; string != '\0'; i++) string = size[i];

//     size = (char *)realloc(string, i);
// }

int main(int argc, char **argv)
{
    /*

        选择窗口
        1.中断客户端进程
        2.注销
        3.启动目标客户端
        4.查询进程ID
        5.退出菜单(进程)

        子级菜单
        1.系统时间
        2.对较时间d
        3.退出子级菜单

    */
    // gotoxy(0,0);
    char input[114]={"0"};
    fristTitle();
    system("TITLE 选择窗口");
    printf("\n请键入您要执行的操作:\n\n1.中断目标客户端进程\n\n2.注销该计算机\n\n3.启动目标客户端进程\n\n4.查询客户端进程位置\n\n5.列出所有进程\n\n6.终止pid进程\n\n7.创建新进程\n\n8.进入子菜单\n\n");
    scanf("%c", &input);
    equals(input);
    system("pause");
    system("cls");
}