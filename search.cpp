#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define str_len (100)

typedef struct {
	wchar_t student_id[str_len];
	wchar_t course_id[str_len];
	wchar_t course_name[str_len];
} Line;

Line target;
Line line;
Line title;
FILE *block_file;
char block[str_len];

int main(void) {
	
	setlocale(LC_ALL, ""); // 設置本地化環境
	int option = -1;
	
	
	while(option != 0) {
		
		int i = 1;
		
		char path[str_len] = {0};
		char blockname[str_len] = {0};
		
		printf("請輸入1、2、3或0。\n");
		printf("(1) 輸入學號以顯示該學號之學生的選課清單。\n");
		printf("(2) 輸入課號以顯示該課號之課程的學生清單。\n");
		printf("(3) 輸入課名以顯示該課名之課程的學生清單。\n");
		printf("(0) 離開。\n\n");
		printf("你的選擇: ");
		scanf("%d", &option);
		printf("\n");
		
		switch(option) {
			
			case 1:
				printf("請輸入預查詢的學號: ");
				scanf("%ls", &target.student_id);
				printf("\n結果如下:\n");
				
				wcstombs(block, target.student_id, str_len);
				strcpy(path, ".\\Block_by_student_id\\");
				strcat(path, block);  
				strcat(path, ".csv");
				
				block_file = fopen(path, "r, ccs=UTF-8"); 
				
				if(block_file == NULL) {
					printf("找不到資料!\n");
				} else {
					while (fwscanf(block_file, L"%[^,]%*lc", &line.student_id) == 1) {
						wprintf(L"%ls,", line.student_id);
					    fwscanf(block_file, L"%[^,]%*lc", &line.course_id);
					    wprintf(L"%ls,", line.course_id);
					    fwscanf(block_file, L"%[^\n]%*lc", &line.course_name);
					    wprintf(L"%ls\n", line.course_name);
					}
				
					while(1) {
						strcpy(path, ".\\Block_by_student_id\\");
						
						char s[3] = {0};
						itoa(i, s, 10);
				
						strcat(path, block);
				    	strcat(path, "(");
				    	strcat(path,  s);
				    	strcat(path, ")");
				    	strcat(path, ".csv");
				    	
				    	block_file = fopen(path, "r, ccs=UTF-8");
				    	
				    	if(block_file == NULL) {
				    		break;
						} else {
							// 標頭另外讀取 
							fwscanf(block_file, L"%[^,]%*lc", &title.student_id); 
							fwscanf(block_file, L"%[^,]%*lc", &title.course_id); 
							fwscanf(block_file, L"%[^\n]%*lc", &title.course_name); 
							while (fwscanf(block_file, L"%[^,]%*lc", &line.student_id) == 1) {
								wprintf(L"%ls,", line.student_id);
							    fwscanf(block_file, L"%[^,]%*lc", &line.course_id);
							    wprintf(L"%ls,", line.course_id);
							    fwscanf(block_file, L"%[^\n]%*lc", &line.course_name);
							    wprintf(L"%ls\n", line.course_name);
							}
						}
						
						i++;
					}
				}
				
				break;
			case 2:
				printf("請輸入預查詢的課號: ");
				scanf("%ls", &target.course_id);
				printf("\n結果如下:\n");
				
				wcstombs(block, target.course_id, str_len);
				strcpy(path, ".\\Block_by_course_id\\");
				strcat(path, block);  
				strcat(path, ".csv");
				
				block_file = fopen(path, "r, ccs=UTF-8"); 
				
				if(block_file == NULL) {
					printf("找不到資料!\n");
				} else {
					while (fwscanf(block_file, L"%[^,]%*lc", &line.student_id) == 1) {
						wprintf(L"%ls,", line.student_id);
					    fwscanf(block_file, L"%[^,]%*lc", &line.course_id);
					    wprintf(L"%ls,", line.course_id);
					    fwscanf(block_file, L"%[^\n]%*lc", &line.course_name);
					    wprintf(L"%ls\n", line.course_name);
					}
				
					while(1) {
						strcpy(path, ".\\Block_by_course_id\\");
						
						char s[3] = {0};
						itoa(i, s, 10);
				
						strcat(path, block);
				    	strcat(path, "(");
				    	strcat(path,  s);
				    	strcat(path, ")");
				    	strcat(path, ".csv");
				    	
				    	block_file = fopen(path, "r, ccs=UTF-8");
				    	
				    	if(block_file == NULL) {
				    		break;
						} else {
							// 標頭另外讀取 
							fwscanf(block_file, L"%[^,]%*lc", &title.student_id); 
							fwscanf(block_file, L"%[^,]%*lc", &title.course_id); 
							fwscanf(block_file, L"%[^\n]%*lc", &title.course_name); 
							while (fwscanf(block_file, L"%[^,]%*lc", &line.student_id) == 1) {
								wprintf(L"%ls,", line.student_id);
							    fwscanf(block_file, L"%[^,]%*lc", &line.course_id);
							    wprintf(L"%ls,", line.course_id);
							    fwscanf(block_file, L"%[^\n]%*lc", &line.course_name);
							    wprintf(L"%ls\n", line.course_name);
							}
						}
						
						i++;
					}
				}
				
				break;
			case 3:
				printf("請輸入預查詢的課名: ");
				scanf("%ls", &target.course_name);
				printf("\n結果如下:\n");
				
				wcstombs(block, target.course_name, str_len);
				strcpy(path, ".\\Block_by_course_name\\");
				strcat(path, block);  
				strcat(path, ".csv");
				
				block_file = fopen(path, "r, ccs=UTF-8"); 
				
				if(block_file == NULL) {
					printf("找不到資料!\n");
				} else {
					while (fwscanf(block_file, L"%[^,]%*lc", &line.student_id) == 1) {
						wprintf(L"%ls,", line.student_id);
					    fwscanf(block_file, L"%[^,]%*lc", &line.course_id);
					    wprintf(L"%ls,", line.course_id);
					    fwscanf(block_file, L"%[^\n]%*lc", &line.course_name);
					    wprintf(L"%ls\n", line.course_name);
					}
				
					while(1) {
						strcpy(path, ".\\Block_by_course_name\\");
						
						char s[3] = {0};
						itoa(i, s, 10);
				
						strcat(path, block);
				    	strcat(path, "(");
				    	strcat(path,  s);
				    	strcat(path, ")");
				    	strcat(path, ".csv");
				    	
				    	block_file = fopen(path, "r, ccs=UTF-8");
				    	
				    	if(block_file == NULL) {
				    		break;
						} else {
							// 標頭另外讀取 
							fwscanf(block_file, L"%[^,]%*lc", &title.student_id); 
							fwscanf(block_file, L"%[^,]%*lc", &title.course_id); 
							fwscanf(block_file, L"%[^\n]%*lc", &title.course_name); 
							while (fwscanf(block_file, L"%[^,]%*lc", &line.student_id) == 1) {
								wprintf(L"%ls,", line.student_id);
							    fwscanf(block_file, L"%[^,]%*lc", &line.course_id);
							    wprintf(L"%ls,", line.course_id);
							    fwscanf(block_file, L"%[^\n]%*lc", &line.course_name);
							    wprintf(L"%ls\n", line.course_name);
							}
						}
						
						i++;
					}
				}
				break;
			case 0:
				printf("離開。\n");
				break;
			default:
				printf("無效的輸入。\n");
				break;
		}
		
		printf("----------------------------------------------------------\n\n");
	}
	 
}
