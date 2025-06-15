#include <stdio.h>

/* 判斷是否為閏年 */
int is_leap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

/* 回傳某年某月的天數 */
int month_days(int y, int m) {
    static const int mdays[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m == 2 && is_leap(y)) return 29;
    return mdays[m];
}

/* 驗證年月日是否合理 */
int validate_date(int y, int m, int d) {
    if (m < 1 || m > 12) return 0;
    if (d < 1 || d > month_days(y, m)) return 0;
    return 1;
}

/* 計算前一天 */
void yesterday(int *y, int *m, int *d) {
    if (!validate_date(*y, *m, *d)) {
        printf("錯誤：%04d-%02d-%02d，不做計算。\n", *y, *m, *d);
        return;
    }
    if (*d > 1) {
        (*d)--;
    } else {
        if (*m > 1) {
            (*m)--;
        } else {
            *m = 12;
            (*y)--;
        }
        *d = month_days(*y, *m);
    }
}

/* 計算後一天 */
void tomorrow(int *y, int *m, int *d) {
    if (!validate_date(*y, *m, *d)) {
        printf("錯誤：%04d-%02d-%02d，不做計算。\n", *y, *m, *d);
        return;
    }
    int md = month_days(*y, *m);
    if (*d < md) {
        (*d)++;
    } else {
        *d = 1;
        if (*m < 12) {
            (*m)++;
        } else {
            *m = 1;
            (*y)++;
        }
    }
}

int main(void) {
    int y, m, d;
    /* 指標指向 y, m, d */
    int *py = &y, *pm = &m, *pd = &d;
    char choice;

    do {
        /* 1. 提示並讀入日期 */
        printf("請輸入日期（yyyy mm dd）：");
        if (scanf("%d %d %d", py, pm, pd) != 3) {
            printf("輸入格式錯誤，程式結束。\n");
            break;
        }

        /* 2. 檢查日期是否合法 */
        if (!validate_date(y, m, d)) {
            printf("錯誤：%d-%d-%d 不合理！\n", y, m, d);
        } else {
            /* 暫存原始日期 */
            int tmp_y = y, tmp_m = m, tmp_d = d;
 
            /* 3. 計算並顯示前一天 */
            yesterday(py, pm, pd);
            printf("前一天：%d-%d-%d\n", *py, *pm, *pd);

            /* 4. 還原並計算後一天 */
            *py = tmp_y;  *pm = tmp_m;  *pd = tmp_d;
            tomorrow(py, pm, pd);
            printf("後一天：%d-%d-%d\n", *py, *pm, *pd);
        }

        /* 5. 清空緩衝區 */
        while (getchar() != '\n');

        /* 6. 詢問是否退出 */
        printf("按 'q' 再 Enter 結束，其他鍵繼續：");
        choice = getchar();
        while (getchar() != '\n');
    } while (choice != 'q');

    printf("程式已結束。\n");
    return 0;
}
