#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>   // 提供pow(幂运算)和fmod(浮点取余)函数
#define MAX 100      // 定义最大字符长度

char ex[MAX];  // 存储转换后的逆波兰式（后缀表达式）
char str[MAX];  // 存储用户输入的原表达式

/* 获取运算符优先级 */
int get_priority(char op) {
    switch (op) {
    case '@': return 4;   // 单目运算符'-'用@表示，最高优先级
    case '^': return 4;   // 乘方运算符，右结合性
    case '*': case '/': case '%': return 2;  // 乘除取余
    case '+': case '-': return 1;           // 加减
    case '(': return 0;   // 左括号优先级最低
    default: return -1;   // 其他字符
    }
}

/* 中缀表达式转后缀表达式（逆波兰式） */
void trans() {
    char stack[MAX];       // 运算符栈
    int top = 0, t = 0;    // top: 栈顶指针，t: 逆波兰式索引
    int i = 0;             // 原表达式索引
    char ch = str[i++];    // 读取第一个字符

    while (ch != '#') {    // '#'为表达式结束符
        switch (ch) {
        case '@':  // 处理单目减（例如-5中的-）
            // 栈顶运算符优先级>=当前运算符则出栈1
            while (top != 0 && get_priority(stack[top]) >= get_priority('@')) {
                ex[t++] = stack[top--];
            }
            stack[++top] = ch;  // 当前运算符入栈
            break;
        case '^':  // 处理乘方（右结合性）
            // 右结合运算符需栈顶优先级>当前才出栈
            while (top != 0 && get_priority(stack[top]) > get_priority('^')) {
                ex[t++] = stack[top--];
            }
            stack[++top] = ch;
            break;
        case '%':  // 处理取余运算
            while (top != 0 && get_priority(stack[top]) >= get_priority('%')) {
                ex[t++] = stack[top--];
            }
            stack[++top] = ch;
            break;
        case '(':   // 左括号直接入栈
            stack[++top] = ch;
            break;
        case ')':   // 右括号：弹出栈元素直到遇到左括号
            while (stack[top] != '(') {
                ex[t++] = stack[top--];
            }
            top--;  // 弹出左括号但不加入逆波兰式
            break;
        case '+': case '-':  // 处理加减（可能为双目或单目）
        case '*': case '/':  // 处理乘除
            // 栈顶优先级>=当前运算符则持续出栈
            while (top != 0 && get_priority(stack[top]) >= get_priority(ch)) {
                ex[t++] = stack[top--];
            }
            stack[++top] = ch;  // 当前运算符入栈
            break;
        case ' ':  // 忽略空格
            break;
        default:  // 处理数字
            while (isdigit(ch)) {  // 拼接多位数
                ex[t++] = ch;
                ch = str[i++];
            }
            i--;         // 回退一个字符（非数字字符）
            ex[t++] = '&';  // 数字结束标记，用于后续计算区分
        }
        ch = str[i++];  // 读取下一个字符
    }

    // 将栈内剩余运算符弹出
    while (top != 0) {
        if (stack[top] != '(') {
            ex[t++] = stack[top--];
        }
        else {  // 存在未匹配左括号则报错
            printf("括号不匹配错误");
            exit(0);
        }
    }
    ex[t] = '#';  // 结束逆波兰式

    // 打印转换结果
    printf("\n原表达式:\t");
    for (int j = 0; str[j] != '#'; j++)
        printf("%c", str[j]);
    printf("\n后缀表达式:\t");
    for (int j = 0; ex[j] != '#'; j++)
        printf("%c", ex[j]);
}

/* 计算逆波兰式的值 */
void calculate() {
    float stack[MAX];  // 操作数栈
    int top = 0;       // 栈顶指针
    int t = 0;         // 逆波兰式索引
    char ch = ex[t++]; // 读取第一个字符

    while (ch != '#') {
        switch (ch) {
        case '@':  // 单目取反：栈顶元素取负
            stack[top] = -stack[top];
            break;
        case '^': {  // 乘方运算：a^b
            float b = stack[top];
            float a = stack[top - 1];
            stack[--top] = pow(a, b);  // 计算结果存入栈
            break;
        }
        case '%': {  // 取余运算：a%b
            float b = stack[top];
            float a = stack[top - 1];
            if (b != 0) {
                stack[--top] = fmod(a, b);  // 使用fmod处理浮点取余
            }
            else {
                printf("\n取余除零错误!");
                exit(0);
            }
            break;
        }
        case '+':  // 加法
            stack[top - 1] += stack[top];
            top--;
            break;
        case '-':  // 减法
            stack[top - 1] -= stack[top];
            top--;
            break;
        case '*':  // 乘法
            stack[top - 1] *= stack[top];
            top--;
            break;
        case '/':  // 除法
            if (stack[top] != 0) {
                stack[top - 1] /= stack[top];
                top--;
            }
            else {
                printf("\n除零错误!");
                exit(0);
            }
            break;
        case '&':  // 数字分隔符，无需处理
            break;
        default:   // 处理数字
            float num = 0;
            while (isdigit(ch)) {  // 转换字符为浮点数
                num = num * 10 + (ch - '0');
                ch = ex[t++];
            }
            t--;            // 回退非数字字符
            stack[++top] = num;  // 数字压栈
        }
        ch = ex[t++];  // 读取下一个字符
    }
    printf("\n计算结果:\t%.02f\n", stack[top]);  // 输出结果，保留两位小数
}

/* 主函数 */
int main() {
    while (1) {
        memset(str, 0, sizeof(str));  // 清空输入缓冲区
        memset(ex, 0, sizeof(ex));

        printf("\n请输入表达式（输入exit#退出）:\n");
        int i = 0;
        do {  // 读取用户输入，直到遇到#或MAX长度
            scanf("%c", &str[i]);
            if (i == 4 && strncmp(str, "exit", 4) == 0) {  // 检测退出命令
                str[i] = '#';
                break;
            }
            if (str[i] == '#') break;
        } while (++i < MAX - 1);
        str[i] = '#';  // 添加结束符

        if (strncmp(str, "exit", 4) == 0) {  // 退出程序
            printf("程序已退出\n");
            break;
        }

        trans();       // 转换中缀为后缀表达式
        calculate();   // 计算后缀表达式

        // 清空输入缓冲区剩余字符
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    return 0;
}




