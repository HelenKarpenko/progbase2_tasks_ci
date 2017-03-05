#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../include/university.h"
#include "../include/list.h"
#include "../include/teacher.h"
#define throw(MSG) assert(0 && MSG)

struct Teacher {
        char *name;
        int year;
        double score;
        List *listOfStudents;
};


Teacher *Teacher_new(void){
        Teacher *newTeacher = (Teacher *)malloc(sizeof(Teacher));
        if(newTeacher == NULL) {
                printf("Teacher_new: Can not alloc memory for new teacher\n");
                return NULL;
        }
        newTeacher->name = NULL;
        newTeacher->year = 0;
        newTeacher->score = 0.0;
        newTeacher->listOfStudents = List_new();
        return newTeacher;
}

void Teacher_free(Teacher **self){
        if(self != NULL) {
                if((*self)->name != NULL) {
                        free((*self)->name);
                }
                if((*self)->listOfStudents != NULL) {
                        List_free(&(*self)->listOfStudents,NULL);
                }
                free(*self);
                *self = NULL;
        }
}

char *Teacher_getName(Teacher *self){
        if(self == NULL) throw("Teacher_getName: teacher = null\n");
        return self->name;
}

int Teacher_getYear(Teacher *self){
        if(self == NULL) throw("Teacher_getYear: teacher = null\n");
        return self->year;
}

double Teacher_getScore(Teacher *self){
        if(self == NULL) throw("Teacher_getScore: teacher = null\n");
        return self->score;
}

List *Teacher_getListOfStudents(Teacher *self){
        if(self == NULL) throw("Teacher_getListOfStudents: teacher = null\n");
        return self->listOfStudents;
}

Teacher *Teacher_create(char *name, int year, double score, List *listOfStudents){
        Teacher *newTeacher = Teacher_new();
        if(newTeacher == NULL) {
                return 0;
        }
        if(name == NULL || strlen(name) == 0) {
                strcpy(newTeacher->name,"Unknown teacher");
        }else{
                strcpy(newTeacher->name, name);
        }
        newTeacher->year = year;
        newTeacher->score = score;
        if(listOfStudents != NULL)
                Teacher_addStudentsFromList(newTeacher,listOfStudents);
        return newTeacher;

}
void Teacher_addStudent(Teacher * self,Student * student){
        if(self == NULL || student == NULL) throw("Teacher_addStudent: teacher = null || student == NULL\n");
        List_addLast(self->listOfStudents, student);
}
void Teacher_addStudentsFromList(Teacher *self, List *list){
        int len = List_getLength(list);
        for(int i = 0; i < len; i++) {
                Teacher_addStudent(self, (Student *)List_getDataAt(list,i));
        }
}
int Teacher_containsStudent(Teacher *self, Student *student){
        if(self == NULL || student == NULL) throw("Teacher_containsStudent: teacher = null || student == NULL\n");
        int len = List_getLength(self->listOfStudents);
        for(int i = 0; i < len; i++) {
                if(List_getDataAt(self->listOfStudents,i) == student) {
                        return 1;
                }
        }
        return 0;
}
