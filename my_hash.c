#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <locale.h>

#define True 	(1)
#define False	(0)

#define Max_strLen (50)
#define MAX_COURSES (200)
#define Max_hashTableSize (100)
#define MaxBlock (4654)

typedef enum{
	STUDENT_ID, 
	COURSE_ID, 
	COURSE_NAME
}BlockType;

typedef struct{
	char student_id[11];
	char course_id[5];
	char course_name[Max_strLen];
}Record;

typedef struct{
    char courseName[50];
    char courseID[5];
    unsigned numStudents;
    struct Student{
        char studentName[50];
        char studentID[10];
    }student[100];
}Course;

typedef struct{
    Course courses[MAX_COURSES];
    int numCourses;
}CourseList;

typedef struct Node{
	Record data;
	struct Node* next;
}Node;

Node* HashTable[Max_hashTableSize];
CourseList courseLists;

unsigned check_flag = True;
Record check_record[100];
unsigned index_check = 0;

void MyHash(int block_num, BlockType type);

void init_hashTable(){
	int i = 0;
	for(i=0; i<Max_hashTableSize; i++){
		HashTable[i] = NULL;
	}
}

void init_check_record(){
	int i = 0;
	for(i=0; i<index_check; i++){
		check_record[i].student_id[0] = '\0';
		check_record[i].course_id[0] = '\0';
		check_record[i].course_name[0] = '\0';
	}
	index_check = 0;
}

void init_courseLists(){
    courseLists.numCourses = 0;
}

void printLine(int n){
	puts("");
	int i = 0;
	for(i=1; i<=n; i++){
		printf("-");
	}
	puts("\n");
}

void addCourse(const Record record){
    int existingIndex = -1;
	int i = 0;
    for(i=0; i<courseLists.numCourses; i++){
        if(strcmp(courseLists.courses[i].courseName, record.course_name) == 0){
        	if(strcmp(courseLists.courses[i].courseID, record.course_id) == 0){
        		existingIndex = i;	
        		break;
			}
        }
    }

    if(existingIndex != -1){
        // 該課程已存在，檢查學生是否重複
        Course* existingCourse = &(courseLists.courses[existingIndex]);
		int i = 0;
        for(i=0; i<existingCourse->numStudents; i++) {
            if(strcmp(existingCourse->student[i].studentID, record.student_id) == 0){
                // 學生已存在，不新增重複的學生資料
                return;
            }
        }

        // 新增學生資料至現有課程
        strcpy(existingCourse->student[existingCourse->numStudents].studentID, record.student_id);
        existingCourse->numStudents++;
    }else{
        // 該課程不存在，建立新的課程
        Course* newCourse = &(courseLists.courses[courseLists.numCourses]);
        strcpy(newCourse->courseName, record.course_name);
        strcpy(newCourse->courseID, record.course_id);
        newCourse->numStudents = 0;

        // 新增學生資料至新課程
        strcpy(newCourse->student[newCourse->numStudents].studentID, record.student_id);
        newCourse->numStudents++;

        courseLists.numCourses++;
    }
}

void printCourseInfo(const char *target_courseName){
	unsigned first = True;
	int i=0;
    for(i=0; i<courseLists.numCourses; i++){
        const Course* course = &(courseLists.courses[i]);

        if(strcmp(course->courseName, target_courseName) == 0){
        	if(first){
        		printf("課程名稱: %s - %s", course->courseName, course->courseID);
        		printLine(50);
			}
			first = False;
            
            printf("Number of Students: %u\n", course->numStudents);
            int j=0;
            for(j=0; j<course->numStudents; j++){
                const struct Student* student = &(course->student[j]);
                printf("學生ID: %-10s\n", student->studentID);
            }

            puts("");
        }
    }
}

//void freeCourseLists() {
//    for (int i = 0; i < courseLists.numCourses; i++) {
//        Course* course = &(courseLists.courses[i]);
//
//        // 釋放學生記憶體
//        for (int j = 0; j < course->numStudents; j++) {
//            free(course->student[j].studentName);
//        }
//
//        // 釋放課程記憶體
//        free(course->student);
//    }
//}

unsigned hash1(const char key[]){
	unsigned value = 0;
	int i = 0;
	for(i=0; key[i]!='\0'; i++){
		value = 31 * value + key[i];		
	}
	return value%Max_hashTableSize;
}

void insertRecord(const Record *record, BlockType type){
	unsigned index = 0;
	
	switch(type){
		case STUDENT_ID:
			index = hash1(record->student_id);
			break;
		case COURSE_ID:
			index = hash1(record->course_id);
			break;
		case COURSE_NAME:
			index = hash1(record->course_name);
			break;
	}
	
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->data = *record;
	newNode->next = NULL;
	
	if(HashTable[index] == NULL){
		HashTable[index] = newNode;
	}else{
		Node *cur = HashTable[index];
		while(cur->next != NULL){
			cur = cur->next;
		}
		cur->next = newNode;
	}
}

void findRecord(unsigned block_num, const char target[], BlockType type){
	unsigned index = hash1(target);

	Node *cur = HashTable[index];
	while(cur != NULL){
		switch(type){
			case STUDENT_ID:
				if(strcmp(cur->data.student_id, target) == 0){
					printf("In Block%-5d: %-11s %5s %s\n", block_num, cur->data.student_id, cur->data.course_id, cur->data.course_name);
				}
				break;
			case COURSE_ID:
				if(strcmp(cur->data.course_id, target) == 0){
					printf("In Block%-5d: %-11s %5s %s\n", block_num, cur->data.student_id, cur->data.course_id, cur->data.course_name);
				}
				break;
			case COURSE_NAME:
				printCourseInfo(target);
//				return NULL;
		}
		cur = cur->next;
		
//		if(!isDupl(cur->data) || index_check == 0){
//			check_record[index_check] = cur->data;
//			index_check++;
//			
//			
//		}else{
//			
//		}
	}
	
//	return NULL;
}

void printHashTable(){
	int i = 0;
    for(i=0; i<Max_hashTableSize; i++){
        printf("Index %d:\n", i);
        
		Node *cur = HashTable[i];
        while (cur != NULL) {
            printf("%-10s %-5s %s\n", cur->data.student_id, cur->data.course_id, cur->data.course_name);
            cur = cur->next;
        }
        puts("");
    }
}

int main(void){
	// 設置本地化環境
	setlocale(LC_ALL, "");
    
    int choose = 0;
    char target[Max_strLen];
    
    do{
    	puts("請輸入(0)、(1)、(2)或(3)");
		puts("(1) 輸入「學號」以顯示該學號之學生的選課清單");
		puts("(2) 輸入「課號」以顯示該課號之課程的學生清單");
		puts("(3) 輸入「課名」以顯示該課名之課程的學生清單");
		puts("(0) 結束程式\n");
		
		printf("你的選擇: ");
		scanf("%d", &choose);
		fflush(stdin);
		
		printLine(65);
		
		switch(choose){
			case 1:
				target[0] = '\0';
				
				printf("請輸入學生學號: ");
				scanf("%s", target);
				fflush(stdin);
				unsigned block_num=0;
				for(block_num=0; block_num<MaxBlock; block_num++){
					init_hashTable();
					init_courseLists();
					
					MyHash(block_num, STUDENT_ID);
					
					findRecord(block_num, target, STUDENT_ID);
//					do{
//						foundRecord = findRecord(target, STUDENT_ID);
//						if(foundRecord != NULL){
//							printf("In Block%-5d: %-11s %5s %s\n", block_num, foundRecord->student_id, foundRecord->course_id, foundRecord->course_name);
//						}else{
//							init_check_record();
//						}
//					}while(foundRecord != NULL);
				}
				printLine(65);
				break;
			case 2:
				target[0] = '\0';
				
				printf("請輸入課程代號: ");
				scanf("%s", target);
				fflush(stdin);
				for(block_num=0; block_num<MaxBlock; block_num++){
					init_hashTable();
					init_courseLists();
					
					MyHash(block_num, COURSE_ID);
//					printHashTable();
//					puts("");
					findRecord(block_num, target, COURSE_ID);
					
//					do{
//						foundRecord = findRecord(target, COURSE_ID);
//						if(foundRecord != NULL){
//							printf("In Block%-5d: %-11s %5s %s\n", block_num, foundRecord->student_id, foundRecord->course_id, foundRecord->course_name);
//						}else{
//							init_check_record();
//						}
//					}while(foundRecord != NULL);
				}
				printLine(65);
				break;
			case 3:
				target[0] = '\0';
				
				printf("請輸入課程名稱: ");
				scanf("%s", target);
				fflush(stdin);
				for(block_num=0; block_num<MaxBlock; block_num++){
					init_hashTable();
					init_courseLists();
					
					MyHash(block_num, STUDENT_ID);
					printCourseInfo(target);
				}
				printLine(65);
				break;
			case 0:
				puts("\n\n結束!");
				break;
			default:
				puts("請勿輸入(0)~(4)以外的字元!");
				printLine(65);
		}
	}while(choose != 0);
	int i = 0;
	for(i=0; i<Max_hashTableSize; i++){
        Node *cur = HashTable[i];
        while(cur != NULL){
            Node *temp = cur;
            cur = cur->next;
            free(temp);
        }
    }
    
	return 0;
}

void MyHash(int block_num, BlockType type){
	char line[256];
	char path[Max_strLen] = ".\\Block\\block_";
		
	char n[10];
	itoa(block_num, n, 10);
		
	strcat(path, n);
	strcat(path, ".txt");
		
	FILE *fptr = fopen(path, "r");
	int i = 0;
	for(i=0; i<100; i++){
//		printf("%d ", i);
		line[0] = '\0';
	    fgets(line, sizeof(line), fptr);
		
		Record record;
		sscanf(line, "%[^,],%[^,],%[^\n]", record.student_id, record.course_id, record.course_name);
		
		insertRecord(&record, type);
		addCourse(record);
	}
//	puts("");
		
	fclose(fptr);
}
