//
//将保留字数组新增
//struct、union、signed、unsigned、_Bool、short include scanf、printf const、enum、extern、_Bool
//​​标识符增加
//
//支持以下划线开头的标识符
//​​
//浮点数识别
//
//科学计数法
//
//允许正负号开头的数字（如 - 123、 + 45.6）
//
//​​预处理指令处理​​（这个没做好）
//
//​​新增运算符分类​​
//
//指针运算符： * 、 & 
//
//结构体成员访问符.
//
//增强关系运算符处理
//
//​​不支持的字符
//
//未定义字符
//
//支持结构体 / 联合体类型声明
//
//识别unsigned、signed
//
//
//添加文件关闭操作（fclose(fp)）
//
//缓冲区大小
//
//使用ungetc防止字符读取越界




#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>   //添加头文件

FILE* fp;
char cbuffer;
/* 扩展保留字数组（新增struct/union等），包含带下划线关键字 */
const char* key[28] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "return", "void", "_Bool", "struct", "union",    //新增struct union  结构体
    "include", "scanf", "printf", "signed", "unsigned","header.h"  //新增预处理和IO相关保留字
};
int atype, id = 4; /* 原始全局变量声明 */

int search(char searchchar[], int wordtype);
char alphaprocess(char buffer);
char digitprocess(char buffer);
char otherprocess(char buffer);

int main() {                                    // 返回值改为int
    if ((fp = fopen("example.c", "r")) == NULL)   /* 只读方式打开一个文件 */
        printf("error");
    else {
        cbuffer = fgetc(fp);  /* fgetc( )函数：从磁盘文件读取一个字符 */
        while (cbuffer != EOF) {
            if (cbuffer == ' ' || cbuffer == '\n')   /* 掠过空格和回车符 */
                cbuffer = fgetc(fp);

            else if (isdigit(cbuffer) || (cbuffer == '.' && isdigit(fgetc(fp))) || ((cbuffer == '-' || cbuffer == '+') && id == 4))
            {  //新增：正负号开头数字
               // ungetc(fgetc(fp), fp);  
                cbuffer = digitprocess(cbuffer);
            }
            else if (isalpha(cbuffer) || cbuffer == '_') // 原isalpha扩展下划线
                cbuffer = alphaprocess(cbuffer);
            else
                cbuffer = otherprocess(cbuffer);
        }
        fclose(fp);  // 添加文件关闭操作防止资源泄漏
    }
    return 0;
}

char alphaprocess(char buffer) {
    int atype;   /* 保留字数组中的位置 */
    int i = -1;
    char alphatp[40];  // 扩展缓冲长度适应长标识符
    while ((isalpha(buffer)) || (isdigit(buffer)) || buffer == '_') {  // 修改：增加下划线支持
        alphatp[++i] = buffer;
        buffer = fgetc(fp);  // 持续读取下一个字符
    }
    alphatp[i + 1] = '\0';
    atype = search(alphatp, 1); /* 对此单词调用search函数判断类型 */
    if (atype != 0) {
        printf("“%s” , (1,%d)\n", alphatp, atype - 1);
        id = 1;
    }
    else {
        printf("(%s ,2)\n", alphatp);
        id = 2;
    }
    return buffer;  // 返回最后一个非字母数字字符
}

int search(char searchchar[], int wordtype) {  // 原函数未修改，判断是保留字还是标识符
    int i = 0;
    int p = 0;
    switch (wordtype) {
    case 1:
        for (i = 0; i < 28; i++) {  // 扩大循环范围
            if (strcmp(key[i], searchchar) == 0) {
                p = i + 1;
                break;
            }
        }
        return p;
    }
    return 0;
}

/* 增强数字处理函数：支持小数点和科学计数法 */
char digitprocess(char buffer) {     //处理数字字符
    int i = -1, isFloat = 0, hasExp = 0;
    char digittp[40];
    // 处理首字符负号
    if (buffer == '-' || buffer == '+') {  //新增正负号处理
        digittp[++i] = buffer;
        buffer = fgetc(fp);
    }
    // 处理数字主体
    while (1) {
        if (isdigit(buffer)) {
            digittp[++i] = buffer;
        }
        else if (buffer == '.' && !isFloat && !hasExp) {
            isFloat = 1;
            digittp[++i] = buffer;
        }
        else if ((buffer == 'e' || buffer == 'E') && !hasExp) {  //新增科学计数法
            hasExp = 1;
            digittp[++i] = buffer;
            char next = fgetc(fp);
            if (next == '+' || next == '-')
            {
                digittp[++i] = next;
                buffer = fgetc(fp);
                continue;
            }
            else {
                buffer = next;
                continue;
            }
        }
        else break;
        buffer = fgetc(fp);
    }
    digittp[i + 1] = '\0';
    ungetc(buffer, fp); // 回退多读的非数字字符
    printf("(“%s” ,3)\n", digittp);
    id = 3;
    return buffer;
}

char otherprocess(char buffer) {
    char ch[20];
    ch[0] = buffer;
    ch[1] = '\0';


    // 新增：处理++和--运算符
    if (ch[0] == '+' || ch[0] == '-') {
        char next = fgetc(fp);
        if (next == ch[0]) {          // 检测双字符运算符
            ch[1] = next;            // 组合成++或--
            ch[2] = '\0';
            printf("(%s ,4)\n", ch);  // 类型4为运算符
            buffer = fgetc(fp);      // 移动文件指针
            return buffer;
        }
        else {
            ungetc(next, fp);        // 回退单字符
            printf("(%s ,4)\n", ch); // 单目+或-
        }
        buffer = fgetc(fp);
        return buffer;
    }

    // 新增：处理%和格式说明符（如%d）
    if (ch[0] == '%') {
        char next = fgetc(fp);
        if (isalpha(next)) {          // 格式说明符识别
            printf("(“%%%c” ,8)\n", next); // 类型8为格式符
            buffer = fgetc(fp);       // 移动指针
        }
        else {
            ungetc(next, fp);         // 回退非字母字符
            printf("(“%%” ,4)\n");    // 取模运算符
        }
        buffer = fgetc(fp);
        return buffer;
    }

    // 新增：冒号和双引号识别为分隔符
    if (ch[0] == ':' || ch[0] == '"') {
        printf("(%s ,5)\n", ch);     // 类型5为分隔符
        buffer = fgetc(fp);
        return buffer;
    }
  

    /* 预处理指令处理 */
    if (ch[0] == '#') {
        printf("(“#” ,6)\n");  //类型6为预处理符号
        buffer = fgetc(fp);
        char directive[20];
        int i = 0;
        while (isalpha(buffer) || buffer == '_') {  // 支持带下划线的指令
            directive[i++] = buffer;
            buffer = fgetc(fp);
        }
        directive[i] = '\0';
        int dtype = search(directive, 1);
        if (dtype != 0)
            printf("“%s” , (1,%d)\n", directive, dtype - 1);
        else
            printf("(%s ,2)\n", directive);
        // 处理头文件内容（如<stdio.h>）
        if (strcmp(directive, "include") == 0) {
            while (buffer != '>' && buffer != '"' && buffer != EOF) {  // 跳过路径内容
                buffer = fgetc(fp);
            }
            if (buffer == '>' || buffer == '"') {
                printf("(“%c” ,5)\n", buffer);  // 将<>和""视为分隔符
                buffer = fgetc(fp);
            }
        }
        return buffer;
    }

    // 结构体成员访问符 
    if (ch[0] == '.') {
        printf("(“.” ,9)\n");  //类型9为成员访问符
        buffer = fgetc(fp);
        id = 9;
        return buffer;
    }

    // 指针运算符处理  
    if (ch[0] == '*' || ch[0] == '&') {
        printf("(“%s” ,7)\n", ch);  //类型7为指针运算符
        buffer = fgetc(fp);
        id = 7;
        return buffer;
    }

    /* 原代码中的分隔符处理 */
    if (ch[0] == ',' || ch[0] == ';' || ch[0] == '{' || ch[0] == '}' || ch[0] == '(' || ch[0] == ')') {
        printf("(%s ,5)\n", ch);
        buffer = fgetc(fp);
        id = 4;
        return buffer;
    }

    // 处理关系运算符
    if (ch[0] == '=' || ch[0] == '!' || ch[0] == '<' || ch[0] == '>') {
        char next = fgetc(fp);
        if (next == '=') {
            ch[1] = next;
            ch[2] = '\0';
            printf("(%s ,4)\n", ch);  //类型4为运算符
        }
        else {
            printf("(%s ,4)\n", ch);
            buffer = next;
        }
        buffer = fgetc(fp);
        id = 4;
        return buffer;
    }

    /* 错误字符分类处理 */  //新增注释
    switch (ch[0]) {
    case '@': case '$':
    //case '^': case '%': case '~':
        printf("不支持的字符: %c\n", ch[0]);
        break;
    default:
        printf("未定义字符: %c\n", ch[0]);  // 保留原始描述
    }
    buffer = fgetc(fp);
    return buffer;
}
















