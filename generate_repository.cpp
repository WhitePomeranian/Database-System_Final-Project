#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define str_len (100)

typedef enum {
	DAYTIME, EVENING
} LearningMode;

typedef enum {
	STUDENT_ID, COURSE_ID, COURSE_NAME
} Block;

typedef struct {
	wchar_t student_id[str_len];
	wchar_t course_id[str_len];
	wchar_t course_name[str_len];
	LearningMode mode;
} Line;
 
void OpenToRead(const char* filename);
void OpenToWrite(const wchar_t* wfilename, Block block);
unsigned CountStrLen(const wchar_t* wstr);
FILE *main_file;
FILE *block_file;
Line line;
Line title; 
wchar_t blockname[str_len];

int main() {
    setlocale(LC_ALL, ""); // �]�m���a������
    OpenToRead("DB_students_tc_utf8.csv");
    return 0;
}

void OpenToRead(const char* filename) {
	
	// �}���ɮ�
    main_file = fopen(filename, "r, ccs=UTF-8");
    
    if (main_file == NULL) {
        printf("Not Found!\n");
        return;
    }
    
    // ���Y�t�~Ū�� 
	fwscanf(main_file, L"%[^,]%*lc", &title.student_id); 
	fwscanf(main_file, L"%[^,]%*lc", &title.course_id); 
	fwscanf(main_file, L"%[^\n]%*lc", &title.course_name); 
    
    while (!feof(main_file)) {
    	fwscanf(main_file, L"%[^,]%*lc", &line.student_id); 
        wprintf(L"%ls,", line.student_id);
        fwscanf(main_file, L"%[^,]%*lc", &line.course_id);
        wprintf(L"%ls,", line.course_id);
        fwscanf(main_file, L"%[^\n]%*lc", &line.course_name);
        wprintf(L"%ls\n", line.course_name);
        
        if(CountStrLen(line.student_id) == 8) {
        	line.mode = DAYTIME;
		} else {
			line.mode = EVENING;
		}
		
		wcscat(blockname, line.student_id);
		wcscat(blockname, L".csv");
		OpenToWrite(blockname, STUDENT_ID);
		blockname[0] = '\0';
		
		wcscat(blockname, line.course_id);
		wcscat(blockname, L".csv");
		OpenToWrite(blockname, COURSE_ID);
		blockname[0] = '\0';
		
		wcscat(blockname, line.course_name);
		wcscat(blockname, L".csv");
		OpenToWrite(blockname, COURSE_NAME);
		blockname[0] = '\0';
    }
    
    // �����ɮ�
    fclose(main_file);
}

void OpenToWrite(const wchar_t* wfilename, Block block) {
	char path[str_len];
	char filename[str_len];
	bool isNewBlock;
	wcstombs(filename, wfilename, str_len); // wchar_t�r���নchar�r��C
	
	if(block == STUDENT_ID) {
		strcpy(path, ".\\Block_student_id\\");
	} else if(block == COURSE_ID){
		strcpy(path, ".\\Block_course_id\\");
	} else {
		strcpy(path, ".\\Block_course_name\\");
	}
	
	strcat(path, filename); // path�[�W���g�J��block�W�١C 
	//printf("%s",path);
	
	// �ΨӴ��լO�_���s��block�C 
	block_file = fopen(path, "r, ccs=UTF-8");
	if(block_file == NULL) {
		isNewBlock = true;
	} else {
		isNewBlock = false;
	}
	fclose(block_file);

	block_file = fopen(path, "a, ccs=UTF-8");  // a�Ҧ�:�ɮק�����g�A�p�G�ɮפ��s�b�A�h�s�ءC  
	
	if(isNewBlock) {  // �s�ت�block�s�W�����Y �C 
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


