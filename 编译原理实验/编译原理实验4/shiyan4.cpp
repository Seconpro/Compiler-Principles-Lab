#include <stdio.h>
#include <string.h>

// ACTION表
const char* action[10][3] = {
    {"S3","S4",NULL},   // 状态0
    {NULL,NULL,"acc"},   // 状态1
    {"S6","S7",NULL},   // 状态2
    {"S3","S4",NULL},   // 状态3
    {"r3","r3",NULL},   // 状态4
    {NULL,NULL,"r1"},   // 5
    {"S6","S7",NULL},   // 6
    {NULL,NULL,"r3"},   // 7
    {"r2","r2",NULL},   // 8
    {NULL,NULL,"r2"}    // 9
};

// GOTO表
int goto1[10][2] = {
    {1,2}, {0,0}, {0,5}, {0,8}, {0,0},
    {0,0}, {0,9}, {0,0}, {0,0}, {0,0}
};

char vt[] = { 'a','b','#' };  // 终结符
char vn[] = { 'S','B' };      // 非终结符
const char* LR[] = { "E->S","S->BB","B->aB","B->b" };  // 产生式（去除了末尾的#）

void printStacks(int a[], int top1, char b[], int top2, char input[], int cur) {
    // 打印状态栈
    for (int i = 0; i <= top1; i++) printf("%d", a[i]);
    printf("\t\t");

    // 打印符号栈
    for (int i = 0; i <= top2; i++) printf("%c", b[i]);
    printf("\t\t");

    // 打印剩余输入串
    for (int i = cur; input[i] != '\0'; i++) printf("%c", input[i]);
    printf("\t\t");
}

int main() {
    int a[100] = { 0 };  // 状态栈，初始状态0
    char b[100] = { '\0' }; // 符号栈
    char input[] = "aabb#";  // 输入字符串

    int top1 = 0;      // 状态栈顶指针
    int top2 = -1;     // 符号栈顶指针
    int cur = 0;       // 输入串当前位置
    int step = 0;      // 步骤计数器

    printf("步骤\t状态栈\t\t符号栈\t\t输入串\t\t产生式和说明\n");  // 新增列标题

    while (1) {
        step++;
        printf("%d\t", step);
        printStacks(a, top1, b, top2, input, cur);

        int s = a[top1];   // 当前状态
        char ch = input[cur]; // 当前输入符号

        // 查找ACTION表列索引
        int col = -1;
        if (ch == 'a') col = 0;
        else if (ch == 'b') col = 1;
        else if (ch == '#') col = 2;

        if (col == -1 || action[s][col] == NULL) {
            printf("\nError: 无效输入或无动作\n");
            break;
        }

        const char* act = action[s][col];

        // 移进动作
        if (act[0] == 'S') {
            int newState = act[1] - '0';
            a[++top1] = newState;  // 状态入栈
            b[++top2] = ch;        // 符号入栈
            cur++;                 // 输入指针后移
            printf("移进%s\n", act);  // 修改输出格式
        }
        // 归约动作
        else if (act[0] == 'r') {
            int prodNum = act[1] - '0';
            const char* prod = LR[prodNum];

            // 获取产生式右部长度（修改计算方式）
            int len = strlen(prod) - 3;  // 例如"S->BB"的长度是5-3=2

            // 执行归约：弹出2*len个元素
            top1 -= len;
            top2 -= len;

            // 获取新状态
            int state = a[top1];
            int col = (prod[0] == 'S') ? 0 : 1;  // 非终结符列索引

            // 更新栈
            a[++top1] = goto1[state][col];
            b[++top2] = prod[0];

            printf("%s\n", prod);  // 新增产生式输出
        }
        // 接受动作
        else if (strcmp(act, "acc") == 0) {
            printf("接受\n");
            break;
        }
    }
    return 0;
}
