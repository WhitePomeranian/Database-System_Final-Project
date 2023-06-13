#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_FILES 6000
#define MAX_FILENAME 255

int main() {
    DIR *dir;
    struct dirent *ent;
    char *folder_path = "C:\\Users\\ASUS\\Desktop\\test\\Block_by_course_id"; // 資料夾的路徑
    char file_names[MAX_FILES][MAX_FILENAME];
    char number_str[10];
    int file_count = 0;
    int number[MAX_FILES];

    // 開啟資料夾
    dir = opendir(folder_path);
    if (dir == NULL) {
        printf("無法開啟資料夾\n");
        return 1;
    }

    // 遍歷資料夾中的檔案
    while ((ent = readdir(dir)) != NULL) {
        // 確保檔案名稱以 ".csv" 結尾
        if (strstr(ent->d_name, ".csv") != NULL) {
            strcpy(file_names[file_count], ent->d_name);
            char *paren = strchr(file_names[file_count], '.');
            if (paren != NULL)
			{
        		// 計算左括號的索引位置
       			 int index = paren - file_names[file_count];
        
        		// 提取數字部分
       			strncpy(number_str, file_names[file_count], index);
        		number_str[index] = '\0';  // 添加結束符號
        
        		// 將數字部分轉換為數字型別
        		number[file_count] = atoi(number_str);
        	}
            file_count++;
        }
    }
    printf("%d\n",file_count);

    // 關閉資料夾
    closedir(dir);

    // 印出陣列中的檔案名稱
    for (int i = 0; i < file_count; i++) {
        printf("%d\n", number[i]);
    }

    return 0;
}

