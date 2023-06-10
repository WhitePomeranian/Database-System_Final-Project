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
	
	setlocale(LC_ALL, ""); // �]�m���a������
	int option = -1;
	
	
	while(option != 0) {
		
		int i = 1;
		
		char path[str_len] = {0};
		char blockname[str_len] = {0};
		
		printf("�п�J1�B2�B3��0�C\n");
		printf("(1) ��J�Ǹ��H��ܸӾǸ����ǥͪ���ҲM��C\n");
		printf("(2) ��J�Ҹ��H��ܸӽҸ����ҵ{���ǥͲM��C\n");
		printf("(3) ��J�ҦW�H��ܸӽҦW���ҵ{���ǥͲM��C\n");
		printf("(0) ���}�C\n\n");
		printf("�A�����: ");
		scanf("%d", &option);
		printf("\n");
		
		switch(option) {
			
			case 1:
				printf("�п�J�w�d�ߪ��Ǹ�: ");
				scanf("%ls", &target.student_id);
				printf("\n���G�p�U:\n");
				
				wcstombs(block, target.student_id, str_len);
				strcpy(path, ".\\Block_by_student_id\\");
				strcat(path, block);  
				strcat(path, ".csv");
				
				block_file = fopen(path, "r, ccs=UTF-8"); 
				
				if(block_file == NULL) {
					printf("�䤣����!\n");
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
							// ���Y�t�~Ū�� 
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
				printf("�п�J�w�d�ߪ��Ҹ�: ");
				scanf("%ls", &target.course_id);
				printf("\n���G�p�U:\n");
				
				wcstombs(block, target.course_id, str_len);
				strcpy(path, ".\\Block_by_course_id\\");
				strcat(path, block);  
				strcat(path, ".csv");
				
				block_file = fopen(path, "r, ccs=UTF-8"); 
				
				if(block_file == NULL) {
					printf("�䤣����!\n");
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
							// ���Y�t�~Ū�� 
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
				printf("�п�J�w�d�ߪ��ҦW: ");
				scanf("%ls", &target.course_name);
				printf("\n���G�p�U:\n");
				
				wcstombs(block, target.course_name, str_len);
				strcpy(path, ".\\Block_by_course_name\\");
				strcat(path, block);  
				strcat(path, ".csv");
				
				block_file = fopen(path, "r, ccs=UTF-8"); 
				
				if(block_file == NULL) {
					printf("�䤣����!\n");
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
							// ���Y�t�~Ū�� 
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
				printf("���}�C\n");
				break;
			default:
				printf("�L�Ī���J�C\n");
				break;
		}
		
		printf("----------------------------------------------------------\n\n");
	}
	 
}
