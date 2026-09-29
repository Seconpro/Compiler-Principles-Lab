



//
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
///* 分析栈 */
//char A[20];
///* 剩余串 */
//char B[20];
///* 终结符 */
//char v1[6] = { 'i','+','*','(',')','#' };
///* 非终结符 */
//char v2[5] = { 'E','G','T','S','F' };
//
//int j = 0, b = 0, top = 0, l, k = 1;
//
//typedef struct type
//{
//    char origin;
//    char array[5];
//    int length;
//}type;
//
//type e, t, g, g1, s, s1, f, f1;
//type C[5][6];
//
//void print()
//{
//    int a;
//    for (a = 0; a <= top + 1; a++)
//        printf("%c", A[a]);
//    printf("\t\t");
//}
//
//void print1()
//{
//    int j;
//    for (j = 0; j < b; j++)
//        printf(" ");
//    for (j = b; j <= l; j++)
//        printf("%c", B[j]);
//    printf("\t\t\t");
//}
//
//int main()
//{
//    e.origin = 'E';
//    strcpy(e.array, "TG");
//    e.length = 2;
//
//    t.origin = 'T';
//    strcpy(t.array, "FS");
//    t.length = 2;
//
//    g.origin = 'G';
//    strcpy(g.array, "+TG");
//    g.length = 3;
//
//    g1.origin = 'G';
//    g1.array[0] = '^';
//    g1.length = 1;
//
//    s.origin = 'S';
//    strcpy(s.array, "*FS");
//    s.length = 3;
//
//    s1.origin = 'S';
//    s1.array[0] = '^';
//    s1.length = 1;
//
//    f.origin = 'F';
//    strcpy(f.array, "(E)");
//    f.length = 3;
//
//    f1.origin = 'F';
//    f1.array[0] = 'i';
//    f1.length = 1;
//
//    for (int m = 0; m < 5; m++)
//        for (int n = 0; n < 6; n++)
//            C[m][n].origin = 'N';
//
//    C[0][0] = e;
//    C[0][3] = e;
//
//    C[1][1] = g;
//    C[1][4] = g1;
//    C[1][5] = g1;
//
//    C[2][0] = t;
//    C[2][3] = t;
//
//    C[3][2] = s;
//    C[3][1] = s1;
//    C[3][4] = s1;
//    C[3][5] = s1;
//
//    C[4][0] = f1;
//    C[4][3] = f;
//
//    char choice;
//    do {
//        j = 0; b = 0; top = 0; k = 1;
//        memset(A, 0, sizeof(A));
//        memset(B, 0, sizeof(B));
//
//        printf("请输入要进行LL(1)分析的符号串：");
//        char ch;
//        do {
//            scanf("%c", &ch);
//            if (ch == '\n') continue;
//            B[j] = ch;
//            j++;
//        } while (ch != '#');
//        l = j - 1;
//
//        //// 新增：括号匹配校验
//        //int paren_count = 0;
//        //for (int i = 0; i <= l; i++) {
//        //    if (B[i] == '(') paren_count++;
//        //    if (B[i] == ')') {
//        //        if (--paren_count < 0) {
//        //            printf("错误：存在不匹配的右括号\n");
//        //            exit(1);
//        //        }
//        //    }
//        //}
//        //if (paren_count > 0) {
//        //    printf("错误：存在未闭合的左括号\n");
//        //    exit(1);
//        //}
//
//        ch = B[0];
//        A[top] = '#';
//        A[++top] = 'E';
//
//        printf("步骤\t分析栈\t\t剩余字符\t\t所用产生式\n");
//        int finish = 0;
//        do {
//            char x = A[top--];
//            printf("%d\t", k++);
//            print();
//            print1();
//
//            int flag = 0;
//            for (int j = 0; j < 6; j++) {
//                if (x == v1[j]) {
//                    flag = 1;
//                    break;
//                }
//            }
//
//            if (flag) {
//                if (x == '#') {
//                    finish = 1;
//                    printf("acc!\n");
//                    break;
//                }
//                if (x == ch) {
//                    printf("%c匹配\n", ch);
//
//                    // 新增：连续运算符检测
//                    if (strchr("+*", x) && strchr("+*", B[b + 1])) {
//                        printf("错误：存在连续运算符%c%c\n", x, B[b + 1]);
//                        exit(1);
//                    }
//
//                    ch = B[++b];
//                }
//                else {
//                    // 修改：括号不匹配错误
//                    if (x == '(' || x == ')') {
//                        printf("错误：括号不匹配，期望'%c'但找到'%c'\n", x, ch);
//                    }
//                    else {
//                        printf("报错！需要%c，不能处理%c\n", x, ch);
//                    }
//                    exit(1);
//                }
//            }
//            else {
//                int m, n;
//                for (m = 0; m < 5; m++)
//                    if (x == v2[m]) break;
//                for (n = 0; n < 6; n++)
//                    if (ch == v1[n]) break;
//
//                type cha = C[m][n];
//                if (cha.origin == 'N') {
//                    // 新增：运算符优先级错误检测
//                    if ((x == 'T' || x == 'F') && strchr("+*)", ch)) {
//                        printf("错误：运算符'%c'前缺少操作数\n", ch);
//                    }
//                    else if ((x == 'G' || x == 'S') && strchr("+*", ch)) {
//                        printf("错误：运算符'%c'优先级错误\n", ch);
//                    }
//                    else {
//                        printf("无可用产生式%c遇%c\n", x, ch);
//                    }
//                    exit(1);
//                }
//
//                printf("%c→%s\n", cha.origin, cha.array);
//                for (int j = cha.length - 1; j >= 0; j--) {
//                    if (cha.array[j] != '^')
//                        A[++top] = cha.array[j];
//                }
//            }
//        } while (!finish);
//
//        printf("继续分析？(Y/N): ");
//        scanf(" %c", &choice);
//        getchar();
//    } while (choice == 'Y' || choice == 'y');
//
//    return 0;
//}




// 
#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 分析栈：用于存储语法分析过程中的符号 */
char A[20];
/* 输入缓冲区：存储待分析的符号串 */
char B[20];
/* 终结符集合：i, +, *, (, ), # */
char v1[6] = { 'i','+','*','(',')','#' };
/* 非终结符集合：E, G, T, S, F */
char v2[5] = { 'E','G','T','S','F' };

/* 全局变量定义 */
int j = 0;        // 输入缓冲区写入位置指针
int b = 0;        // 输入缓冲区读取位置指针
int top = 0;      // 分析栈栈顶指针
int l;            // 输入符号串有效长度
int k = 1;        // 分析步骤计数器

/* 产生式结构体定义 */
typedef struct type {
    char origin;    // 产生式左部符号
    char array[5];  // 产生式右部符号序列
    int length;     // 产生式右部长度
} type;

/* 产生式实例化 */
type e, t, g, g1, s, s1, f, f1;      // 文法产生式
type C[5][6];                        // LL(1)预测分析表

/* 打印分析栈当前状态 */
void print() {
   // printf("分析栈: ");
    for (int a = 0; a <= top + 1; a++)
        printf("%c", A[a]);
    printf("\t\t");
}

/* 打印剩余输入符号串 */
void print1() {
   // printf("剩余串: ");
    // 通过空格对齐已处理部分
    for (int j = 0; j < b; j++) printf(" ");
    // 打印尚未处理的输入部分
    for (int j = b; j <= l; j++)
        printf("%c", B[j]);
    printf("\t\t\t");
}

int main() {
    /* 初始化产生式集合 */
    // E -> TG
    e.origin = 'E';
    strcpy(e.array, "TG");
    e.length = 2;
    // T -> FS
    t.origin = 'T';
    strcpy(t.array, "FS");
    t.length = 2;
    // G -> +TG
    g.origin = 'G';
    strcpy(g.array, "+TG");
    g.length = 3;
    // G -> ε (空产生式)
    g1.origin = 'G';
    g1.array[0] = '^';  // 用^表示空
    g1.length = 1;
    // S -> *FS
    s.origin = 'S';
    strcpy(s.array, "*FS");
    s.length = 3;
    // S -> ε
    s1.origin = 'S';
    s1.array[0] = '^';
    s1.length = 1;
    // F -> (E)
    f.origin = 'F';
    strcpy(f.array, "(E)");
    f.length = 3;
    // F -> i
    f1.origin = 'F';
    f1.array[0] = 'i';
    f1.length = 1;

    /* 初始化预测分析表（全部置空） */
    for (int m = 0; m < 5; m++)
        for (int n = 0; n < 6; n++)
            C[m][n].origin = 'N';  // N表示无效产生式

    /* 填充预测分析表 */
    // E行规则（非终结符E对应的产生式）
    C[0][0] = e;  // E遇到i时使用E->TG
    C[0][3] = e;  // E遇到(时使用E->TG
    // G行规则
    C[1][1] = g;   // G遇到+时使用G->+TG
    C[1][4] = g1;  // G遇到)时使用G->ε
    C[1][5] = g1;  // G遇到#时使用G->ε
    // T行规则
    C[2][0] = t;  // T遇到i时使用T->FS
    C[2][3] = t;  // T遇到(时使用T->FS
    // S行规则
    C[3][2] = s;   // S遇到*时使用S->*FS
    C[3][1] = s1;  // S遇到+时使用S->ε
    C[3][4] = s1;  // S遇到)时使用S->ε
    C[3][5] = s1;  // S遇到#时使用S->ε
    // F行规则
    C[4][0] = f1;  // F遇到i时使用F->i
    C[4][3] = f;   // F遇到(时使用F->(E)

    /* 主循环：支持多次分析 */
    char choice;
    do {
        // 重置分析状态
        j = 0; b = 0; top = 0; k = 1;
        memset(A, 0, sizeof(A));  // 清空分析栈
        memset(B, 0, sizeof(B));  // 清空输入缓冲区

        /* 读取输入符号串 */
        printf("请输入要进行LL(1)分析的符号串：");
        char ch;
        do {
            scanf("%c", &ch);
            if (ch == '\n') continue;  // 跳过换行符
            B[j] = ch;
            j++;
        } while (ch != '#');  // 以#作为结束标志
        l = j - 1;  // 计算有效符号长度

                //// 新增：括号匹配校验
        //int paren_count = 0;
        //for (int i = 0; i <= l; i++) {
        //    if (B[i] == '(') paren_count++;
        //    if (B[i] == ')') {
        //        if (--paren_count < 0) {
        //            printf("错误：存在不匹配的右括号\n");
        //            exit(1);
        //        }
        //    }
        //}
        //if (paren_count > 0) {
        //    printf("错误：存在未闭合的左括号\n");
        //    exit(1);
        //}

        /* 初始化分析栈 */
        ch = B[0];          // 当前待分析字符
        A[top] = '#';       // 栈底标志
        A[++top] = 'E';     // 初始非终结符

        printf("\n步骤\t分析栈\t\t剩余字符\t\t所用产生式\n");
        int finish = 0;  // 分析完成标志
        do {
            char x = A[top--];  // 弹出栈顶符号
            printf("%d\t", k++);  // 打印步骤编号
            print();             // 显示分析栈状态
            print1();            // 显示剩余输入

            /* 判断符号类型（终结符/非终结符） */
            int is_terminal = 0;
            for (int j = 0; j < 6; j++) {
                if (x == v1[j]) {
                    is_terminal = 1;
                    break;
                }
            }

            if (is_terminal) {
                /* 处理终结符 */
                if (x == '#') {  // 栈底符号与输入结束符匹配
                    finish = 1;
                    printf("acc!\n");  // 接受输入
                    break;
                }
                if (x == ch) {  // 终结符匹配成功
                    printf("%c匹配\n", ch);

                    /* 新增：连续运算符检测 */
                    if (strchr("+*", x) && strchr("+*", B[b + 1])) {
                        printf("错误：存在连续运算符%c%c\n", x, B[b + 1]);
                        exit(1);
                    }

                    ch = B[++b];  // 推进输入缓冲区指针
                }
                else {  // 终结符匹配失败
                    /* 改进的括号不匹配提示 */
                    if (x == '(' || x == ')') {
                        printf("错误：括号不匹配，期望'%c'但找到'%c'\n", x, ch);
                    }
                    else {
                        printf("报错！需要%c，不能处理%c\n", x, ch);
                    }
                    exit(1);
                }
            }
            else {
                /* 处理非终结符（查预测分析表） */
                int row = -1, col = -1;
                // 查找非终结符行号
                for (int m = 0; m < 5; m++)
                    if (x == v2[m]) { row = m; break; }
                // 查找终结符列号
                for (int n = 0; n < 6; n++)
                    if (ch == v1[n]) { col = n; break; }

                type production = C[row][col];  // 获取对应产生式
                if (production.origin == 'N') {  // 未找到合法产生式
                    /* 新增语义错误检测 */
                    if ((x == 'T' || x == 'F') && strchr("+*)", ch)) {
                        printf("错误：运算符'%c'前缺少操作数\n", ch);
                    }
                    else if ((x == 'G' || x == 'S') && strchr("+*", ch)) {
                        printf("错误：运算符'%c'优先级错误\n", ch);
                    }
                    else {
                        printf("无可用产生式%c遇%c\n", x, ch);
                    }
                    exit(1);
                }

                /* 产生式应用（逆序压栈） */
                printf("%c→%s\n", production.origin, production.array);
                for (int j = production.length - 1; j >= 0; j--) {
                    if (production.array[j] != '^')  // 跳过空产生式
                        A[++top] = production.array[j];
                }
            }
        } while (!finish);

        /* 交互控制 */
        printf("继续分析？(Y/N): ");
        scanf(" %c", &choice);  // 注意空格吸收换行符
        getchar();  // 清空输入缓冲区
    } while (choice == 'Y' || choice == 'y');

    return 0;
}