#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "../include/university.h"
#include "../include/student.h"
#include "../include/list.h"
#include "../include/teacher.h"
#define throw(MSG) assert(0 && MSG)
enum Fields {
        nameField = 0,
        yearField=1,
        scoreField=2,
};
//1.1
Student *getStudentFromCSVStr(char *str);
char *University_getLineFromStr(char *str, char **out);
char *getNextField(char *str, char **ptr);
Student *getStudentFromCSVStr(char *str);

//1.2
char *University_getStrFromStudent(Student *student);
int getLenOfLine(Student *student);


//1.1 Формування списку студентів із CSV строки.
List *University_getListOfStudentsFromCSVStr(List *listOfStudents, char *csv){
        char *str = csv;
        while(*str != '\0') {
                char *buffer = University_getLineFromStr(str, &str);
                Student *student = getStudentFromCSVStr(buffer);
                List_addLast(listOfStudents, student);
                free(buffer);
        }
        return listOfStudents;
}

//1.2 Формування CSV строки із списку студентів.
char *University_getStrFromListOfStudents(List *listOfStudents){
        if(listOfStudents == NULL) throw("University_getStrFromListOfStudents: listOfStudents = NULL");
        int countOfStudents = List_getLength(listOfStudents);
        char *array[countOfStudents];
        int len = 0;
        for(int i = 0; i < countOfStudents; i++) {
                array[i] = University_getStrFromStudent((Student *)List_getDataAt(listOfStudents,i));
                len += strlen(array[i])+1;
        }
        len++;
        char *str = (char *)malloc(sizeof(char) * len);
        str[0] = '\0';
        for(int i = 0; i < countOfStudents; i++) {
                strcat(str, array[i]);
                strcat(str, "\n");
                free(array[i]);
        }
        return str;
}

//1.3 Прикріплення списку студентів до викладача.
Teacher *University_setListOfStudentToTeacher(Teacher *self, List *listOfStud){
        if(self == NULL) throw("University_setListOfStudentToTeacher: teacher = null\n");
        Teacher_addStudentsFromList(self, listOfStud);
        return self;
}

//1.4 Функція, що приймає двох викладачів і в результаті створює список зі студентами, що прив'язані до обох викладачів.
List *University_listFromIntersectionOfTeacher(Teacher *teacher1, Teacher *teacher2){
        if(teacher1 == NULL || teacher2 == NULL) throw("University_listFromIntersectionOfTeacher: teacher = null\n");
        List *listResult = List_new();
        List *list1 = Teacher_getListOfStudents(teacher1);
        List *list2 = Teacher_getListOfStudents(teacher2);
        int len1 = List_getLength(list1);
        int len2 = List_getLength(list2);
        for(int i = 0; i < len1; i++) {
                Student * s  =(Student *)List_getDataAt(Teacher_getListOfStudents(teacher1),i);
                if(Teacher_containsStudent(teacher2, s)) {
                        List_addLast(listResult, s);

                }
        }
        return listResult;
}


char *University_getLineFromStr(char *str, char **out){
        int len = 1;
        for(int i = 0; str[i] != '\0' && str[i] != '\n'; i++) {
                len++;
        }
        char *buffer = (char *)malloc(sizeof(char) * (len+1));
        int i = 0;
        for(; i<len; i++) {
                buffer[i] = str[i];
        }
        buffer[i] = '\0';
        *out =strlen(buffer)+str;
        return buffer;
}

char * University_getStrFromStudent(Student *student){
        if(student == NULL) throw("University_getStrFromStudent: NO student");
        char *str = (char *)malloc(sizeof(char) *getLenOfLine(student));
        sprintf(str, "\"%s\",%.4d,%1.1f",Student_getName(student), Student_getYear(student), Student_getScore(student));
        return str;
}

int getLenOfLine(Student *student){
        int commaLen = 1;
        int yearlen = 4;
        int score = 3;
        int len = 0;
        len = strlen(Student_getName(student))+2 + commaLen + yearlen + commaLen + score+1 /*for "name"*/;
        return len;
}

Student *getStudentFromCSVStr(char *str){
        if(str == NULL) throw("getStudentFromCSVStr: str = null\n");
        char *name = NULL;
        char *year = NULL;
        char *score = NULL;
        name = getNextField(str, &str);
        year = getNextField(str, &str);
        score = getNextField(str, &str);
        Student *stud = Student_create(name, atoi(year), atof(score));
        free(name);
        free(year);
        free(score);
        return stud;
}

char *getNextField(char *str, char **ptr){
        char *field = NULL;
        if(*str=='\n'|| *str=='\0') {
                field=(char *)malloc(sizeof(char)*(strlen("NO DATA")+1));
                strcpy(field,"NO DATA");
                return field;
        }
        for(; *str != '\0' && *str != '\n' && !(isalnum(*str)) && *str != '\"' && *str!='-' && *str!='+' && *str!='.'; str++) {
        }

        if(*str == '\"') {
                str++;
                int len = 0;
                while(str[len] != '\0' && str[len] != '\"' && str[len] != '\n') {
                        len++;
                }
                field = (char *)malloc(sizeof(char) * (len+1));
                for(int i = 0; i < len; i++) {
                        field[i] = str[i];
                }                field[len] = '\0';

                *ptr = str + strlen(field)+1;
        }else{
                int len = 0;
                while((str[len]!='\0' && str[len]!='\n'&& str[len]!=',') ||isalnum(str[len])) {
                        len++;
                }
                field = (char *)malloc(sizeof(char) * (len+1));
                for(int i = 0; i < len; i++) {
                        field[i] = str[i];
                }
                str++;
                field[len] = '\0';
                *ptr = str + strlen(field);
        }
        return field;
}
