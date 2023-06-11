#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define str_len (100)

typedef struct Line {
	wchar_t student_id[str_len];
	wchar_t course_id[str_len];
	wchar_t course_name[str_len];
	
	Line *nextLink;
	Line *preLink;
} Line;

Line target;
Line line;
Line title;
FILE *block_file;
char block[str_len];
Line idTable[str_len];
Line *newNode;
Line *cur;
unsigned idTableSize = 0;

void checkId(Line x);
void printIdTable();

int main(void) {
	
	setlocale(LC_ALL, ""); // 設置本地化環境
	int option = -1;
	
	
	while(option != 0) {
		
		int i = 1;
		
		char path[str_len] = {0};
		char blockname[str_len] = {0};
		
		idTableSize = 0;
		
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
					// 標頭另外讀取 
					fwscanf(block_file, L"%[^,]%*lc", &title.student_id); 
					fwscanf(block_file, L"%[^,]%*lc", &title.course_id); 
					fwscanf(block_file, L"%[^\n]%*lc", &title.course_name);
					while (fwscanf(block_file, L"%[^,]%*lc", &line.student_id) == 1) {
					    fwscanf(block_file, L"%[^,]%*lc", &line.course_id);
					    fwscanf(block_file, L"%[^\n]%*lc", &line.course_name);
					    checkId(line);
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
							    fwscanf(block_file, L"%[^,]%*lc", &line.course_id);
							    fwscanf(block_file, L"%[^\n]%*lc", &line.course_name);
							    checkId(line);
							}
						}
						
						i++;
					}
					
					printIdTable();
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

void checkId(Line x) {
	
	newNode = (Line*) malloc(sizeof(Line));
	wcscpy(newNode->student_id, x.student_id);
	wcscpy(newNode->course_id, x.course_id);
	wcscpy(newNode->course_name, x.course_name);
	newNode->nextLink = NULL;
	
	if(idTableSize == 0) {  // 第一筆資料。 
		idTableSize++;

		idTable[idTableSize].nextLink = newNode;
		idTable[idTableSize].preLink = newNode;
		wcscpy(idTable[idTableSize].course_id, x.course_id);
	} else {
		
		for(int i = 1; i <= idTableSize; i++) { 
			if(wcscmp(idTable[i].course_id, x.course_id) == 0) {  // 該課號已被加入過。 
				idTable[i].preLink->nextLink = newNode;
				idTable[i].preLink = newNode;
				return;
			}
		}
		
		idTableSize++;
				
		idTable[idTableSize].nextLink = newNode;
		idTable[idTableSize].preLink = newNode;
		wcscpy(idTable[idTableSize].course_id, x.course_id);
	}
}

void printIdTable() {
	for(int i = 1; i <= idTableSize; i++) {
		printf("\n課程代碼-");
		wprintf(L"%ls\n-----------------------------------------------\n", idTable[i].course_id);
		cur = &idTable[i];
		cur = cur->nextLink;  // 標投不印。 
		while(cur) {
			wprintf(L"%ls,", cur->student_id);
			wprintf(L"%ls,", cur->course_id);
			wprintf(L"%ls\n", cur->course_name);
			cur = cur->nextLink;
		}
	}
}
