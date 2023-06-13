#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define str_len (100)

typedef enum {
	STUDENT_ID, COURSE_ID, COURSE_NAME
} BlockType;

typedef struct {
	wchar_t student_id[str_len];
	wchar_t course_id[str_len];
	wchar_t course_name[str_len];
} Line;

typedef struct OverflowTable {
	char blockname[str_len];
	int blockSum;
	OverflowTable *link;
	 
	OverflowTable() {
		blockSum = 0;
		link = NULL; 
	}
	
} OverflowTable;
 
void OpenToRead(const char* filename);
void OpenToWrite(const wchar_t* wfilename, BlockType type);
unsigned CountStrLen(const wchar_t* wstr);

int counter = 1;
FILE *main_file;
FILE *block_file;
Line line;
Line title;
Line temp; 
wchar_t blockname[str_len];
OverflowTable *overflowTable = NULL;
OverflowTable *cur = overflowTable;
OverflowTable *tail = NULL;
OverflowTable *newNode = NULL;
bool flag = false;

int main() {
    setlocale(LC_ALL, ""); // 設置本地化環境
    OpenToRead("DB_students_tc_utf8.csv");
    return 0;
}

void OpenToRead(const char* filename) {
	
	// 開啟檔案
    main_file = fopen(filename, "r, ccs=UTF-8");
    
    if (main_file == NULL) {
        printf("Not Found!\n");
        return;
    }
    
    // 標頭另外讀取 
	fwscanf(main_file, L"%[^,]%*lc", &title.student_id); 
	fwscanf(main_file, L"%[^,]%*lc", &title.course_id); 
	fwscanf(main_file, L"%[^\n]%*lc", &title.course_name); 
    
    while (fwscanf(main_file, L"%[^,]%*lc", &line.student_id) == 1) { 
        wprintf(L"%ls,", line.student_id);
        fwscanf(main_file, L"%[^,]%*lc", &line.course_id);
        wprintf(L"%ls,", line.course_id);
        fwscanf(main_file, L"%[^\n]%*lc", &line.course_name);
        wprintf(L"%ls,", line.course_name);
        printf("%d\n", counter);
        counter++;
		
		wcscat(blockname, line.student_id);
		OpenToWrite(blockname, STUDENT_ID);
		blockname[0] = '\0';
		wcscat(blockname, line.course_id);

		OpenToWrite(blockname, COURSE_ID);
		blockname[0] = '\0';
		
		wcscat(blockname, line.course_name);
		OpenToWrite(blockname, COURSE_NAME);
		blockname[0] = '\0';
    }
    
    // 關閉檔案
    fclose(main_file);
}

void OpenToWrite(const wchar_t* wfilename, BlockType type) {
	char path[str_len];
	char filename[str_len];
	bool isNewBlock;
	unsigned blockSize = 0;
	wcstombs(filename, wfilename, str_len); // wchar_t字串轉成char字串。
	flag = false;
	
	if(type == STUDENT_ID) {
		strcpy(path, ".\\Block_by_student_id\\");
	} else if(type == COURSE_ID){
		strcpy(path, ".\\Block_by_course_id\\");
	} else {
		strcpy(path, ".\\Block_by_course_name\\");
	}
	
	strcat(path, filename); // path加上欲寫入的block名稱。 
	strcat(path, ".csv");
	//printf("%s",path);
	
	
	cur = overflowTable;
    if(cur) {
		while(1) {
    		if(strcmp(filename, cur->blockname) == 0) {
    			flag = true;
    			
    			if(type == STUDENT_ID) {
					strcpy(path, ".\\Block_by_student_id\\");
				} else if(type == COURSE_ID){
					strcpy(path, ".\\Block_by_course_id\\");
				} else {
					strcpy(path, ".\\Block_by_course_name\\");
				}
				
				char s[3] = {0};
				itoa(cur->blockSum, s, 10);
		
				strcat(path, filename);
		    	strcat(path, "(");
		    	strcat(path,  s);
		    	strcat(path, ")");
		    	strcat(path, ".csv");
    			break;
			} else if(cur->link) {
				cur = cur->link;
			} else {
				break;
			}	
		}
	}
	
	// 用來測試是否為新的block。 
	block_file = fopen(path, "r, ccs=UTF-8");
	if(block_file == NULL) {
		isNewBlock = true;
	} else {
		isNewBlock = false;

		while(fwscanf(block_file, L"%[^,]%*lc", &temp.student_id) == 1) {
	        fwscanf(block_file, L"%[^,]%*lc", &temp.course_id);
	        fwscanf(block_file, L"%[^\n]%*lc", &temp.course_name);
	        blockSize++;
		}
	}
	
	fclose(block_file);
  
    if(blockSize == 100) {  // block溢出 
    
    	isNewBlock = true;
    
		if(flag) {
			cur->blockSum = cur->blockSum + 1;
		} else {
			newNode = (OverflowTable*) malloc(sizeof(OverflowTable));
	    	strcpy(newNode->blockname ,filename);
	    	newNode->blockSum = 0;
	    	newNode->blockSum = newNode->blockSum + 1;
	    	newNode->link = NULL;
	    	
	    	if(tail) {
	    		tail->link = newNode;
			} else {
				overflowTable = newNode;
			}
			
			tail = newNode;
			cur = newNode;
		}
		
		
		char s[3] = {0};
		itoa(cur->blockSum, s, 10);
		
		
		if(type == STUDENT_ID) {
			strcpy(path, ".\\Block_by_student_id\\");
		} else if(type == COURSE_ID){
			strcpy(path, ".\\Block_by_course_id\\");
		} else {
			strcpy(path, ".\\Block_by_course_name\\");
		}
		
		strcat(path, filename);
    	strcat(path, "(");
    	strcat(path,  s);
    	strcat(path, ")");
    	strcat(path, ".csv");	
	} 
	
	block_file = fopen(path, "a, ccs=UTF-8");  // a模式:檔案尾端續寫，如果檔案不存在，則新建。
	
	if(isNewBlock) {  // 新建的block新增欄位標頭 。 
		fwprintf(block_file, L"%ls,", title.student_id);
		fwprintf(block_file, L"%ls,", title.course_id);
		fwprintf(block_file, L"%ls\n", title.course_name);		
	}
	
	
	fwprintf(block_file, L"%ls,", line.student_id);
	fwprintf(block_file, L"%ls,", line.course_id);
	fwprintf(block_file, L"%ls\n", line.course_name);
	
	fclose(block_file);
}

unsigned CountStrLen(const wchar_t* wstr) {
	
	int i = 0;
	
	while(wstr[i] != '\0') {
		i++;
	}
	
	return i;
}
