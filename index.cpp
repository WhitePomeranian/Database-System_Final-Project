#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_FILES 6000
#define MAX_FILENAME 255

int main() {
    DIR *dir;
    struct dirent *ent;
    char *folder_path = "C:\\Users\\ASUS\\Desktop\\test\\Block_by_course_id"; // ��Ƨ������|
    char file_names[MAX_FILES][MAX_FILENAME];
    char number_str[10];
    int file_count = 0;
    int number[MAX_FILES];

    // �}�Ҹ�Ƨ�
    dir = opendir(folder_path);
    if (dir == NULL) {
        printf("�L�k�}�Ҹ�Ƨ�\n");
        return 1;
    }

    // �M����Ƨ������ɮ�
    while ((ent = readdir(dir)) != NULL) {
        // �T�O�ɮצW�٥H ".csv" ����
        if (strstr(ent->d_name, ".csv") != NULL) {
            strcpy(file_names[file_count], ent->d_name);
            char *paren = strchr(file_names[file_count], '.');
            if (paren != NULL)
			{
        		// �p�⥪�A�������ަ�m
       			 int index = paren - file_names[file_count];
        
        		// �����Ʀr����
       			strncpy(number_str, file_names[file_count], index);
        		number_str[index] = '\0';  // �K�[�����Ÿ�
        
        		// �N�Ʀr�����ഫ���Ʀr���O
        		number[file_count] = atoi(number_str);
        	}
            file_count++;
        }
    }
    printf("%d\n",file_count);

    // ������Ƨ�
    closedir(dir);

    // �L�X�}�C�����ɮצW��
    for (int i = 0; i < file_count; i++) {
        printf("%d\n", number[i]);
    }

    return 0;
}

