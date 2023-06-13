#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <windows.h>

void deleteFolderContents(const char *folderPath){
    char searchPath[MAX_PATH];
    WIN32_FIND_DATA findData;
    HANDLE hFind;

    snprintf(searchPath, sizeof(searchPath), "%s\\*", folderPath);

    hFind = FindFirstFile(searchPath, &findData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0) {
                continue;
            }

            snprintf(searchPath, sizeof(searchPath), "%s\\%s", folderPath, findData.cFileName);

            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {                
                deleteFolderContents(searchPath);
                RemoveDirectory(searchPath);
            } else {
                DeleteFile(searchPath);
            }
        } while (FindNextFile(hFind, &findData) != 0);

        FindClose(hFind);
    }
}

#define str_len (100)
#define Max_strLen (50)
#define True 	(1)
#define False	(0)

typedef struct{
	wchar_t student_id[str_len];
	wchar_t course_id[str_len];
	wchar_t course_name[str_len];
}Line;
 
void Read(const char*);
void Write(void);

Line title;
Line line;

unsigned newBlock_flag = False;
unsigned block_num = 0;

int main(void){
	// 設置本地化環境
    setlocale(LC_ALL, ""); 
    
	mkdir("Block");
	deleteFolderContents("Block");
	
    Read("DB_students_tc_utf8.csv");
    return 0;
}

void Read(const char* filename){
    FILE *fptr = fopen(filename, "r, ccs=UTF-8");
    
    if(fptr == NULL){
        printf("找不到檔案 \'%s\' !\n", filename);
        return;
    }
    
    // 標頭另外讀取 
	fwscanf(fptr, L"%[^,]%*lc", &title.student_id); 
	fwscanf(fptr, L"%[^,]%*lc", &title.course_id); 
	fwscanf(fptr, L"%[^\n]%*lc", &title.course_name); 
    
	int counter = 0, numOfRecord = 0;
    
	while(fwscanf(fptr, L"%[^,]%*lc", &line.student_id)){ 
        fwscanf(fptr, L"%[^,]%*lc", &line.course_id);
        fwscanf(fptr, L"%[^\n]%*lc", &line.course_name);
        
        counter++;
        
        wprintf(L"%7d: %-10ls, %-4ls, %ls\n", counter, line.student_id, line.course_id, line.course_name);
		
		if(numOfRecord < 100){
			numOfRecord++;
			newBlock_flag = False;
		}else{
			numOfRecord = 1;
			newBlock_flag = True;
		}
		
		Write();
    }
    
    fclose(fptr);
}

void Write(){
	char path[Max_strLen] = ".\\Block\\block_";
	
	if(newBlock_flag){
		block_num++;
	}
	
	char n[10];
	itoa(block_num, n, 10);
	
	strcat(path, n);
	strcat(path, ".txt");
	
	FILE *fptr = fopen(path, "a");
	
	char studentID[str_len];
	char courseID[str_len];
	char courseName[str_len];
	
	wcstombs(studentID, line.student_id, str_len);
	wcstombs(courseID, line.course_id, str_len);
	wcstombs(courseName, line.course_name, str_len);
	
	fprintf(fptr, "%s,%s,%s\n", studentID, courseID, courseName);
	
	fclose(fptr);
}
