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
        // �ӽҵ{�w�s�b�A�ˬd�ǥͬO�_����
        Course* existingCourse = &(courseLists.courses[existingIndex]);
		int i = 0;
        for(i=0; i<existingCourse->numStudents; i++) {
            if(strcmp(existingCourse->student[i].studentID, record.student_id) == 0){
                // �ǥͤw�s�b�A���s�W���ƪ��ǥ͸��
                return;
            }
        }

        // �s�W�ǥ͸�Ʀܲ{���ҵ{
        strcpy(existingCourse->student[existingCourse->numStudents].studentID, record.student_id);
        existingCourse->numStudents++;
    }else{
        // �ӽҵ{���s�b�A�إ߷s���ҵ{
        Course* newCourse = &(courseLists.courses[courseLists.numCourses]);
        strcpy(newCourse->courseName, record.course_name);
        strcpy(newCourse->courseID, record.course_id);
        newCourse->numStudents = 0;

        // �s�W�ǥ͸�Ʀܷs�ҵ{
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
        		printf("�ҵ{�W��: %s - %s", course->courseName, course->courseID);
        		printLine(50);
			}
			first = False;
            
            printf("Number of Students: %u\n", course->numStudents);
            int j=0;
            for(j=0; j<course->numStudents; j++){
                const struct Student* student = &(course->student[j]);
                printf("�ǥ�ID: %-10s\n", student->studentID);
            }

            puts("");
        }
    }
}

//void freeCourseLists() {
//    for (int i = 0; i < courseLists.numCourses; i++) {
//        Course* course = &(courseLists.courses[i]);
//
//        // ����ǥͰO����
//        for (int j = 0; j < course->numStudents; j++) {
//            free(course->student[j].studentName);
//        }
//
//        // ����ҵ{�O����
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
	// �]�m���a������
	setlocale(LC_ALL, "");
    
    int choose = 0;
    char target[Max_strLen];
    
    do{
    	puts("�п�J(0)�B(1)�B(2)��(3)");
		puts("(1) ��J�u�Ǹ��v�H��ܸӾǸ����ǥͪ���ҲM��");
		puts("(2) ��J�u�Ҹ��v�H��ܸӽҸ����ҵ{���ǥͲM��");
		puts("(3) ��J�u�ҦW�v�H��ܸӽҦW���ҵ{���ǥͲM��");
		puts("(0) �����{��\n");
		
		printf("�A�����: ");
		scanf("%d", &choose);
		fflush(stdin);
		
		printLine(65);
		
		switch(choose){
			case 1:
				target[0] = '\0';
				
				printf("�п�J�ǥ;Ǹ�: ");
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
				
				printf("�п�J�ҵ{�N��: ");
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
				
				printf("�п�J�ҵ{�W��: ");
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
				puts("\n\n����!");
				break;
			default:
				puts("�Фſ�J(0)~(4)�H�~���r��!");
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
