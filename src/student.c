#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../include/student.h"
#define throw(MSG) assert(0 && MSG)
#define STUDENT_NAME "UNKNOWN"
struct Student {
        char *name;
        int year;
        double score;
};

Student *Student_new(void){
        Student *newStudent = (Student *)malloc(sizeof(Student));
        if(newStudent == NULL) {
                printf("Student_new: Can not alloc memory for new student\n");
                return NULL;
        }
        newStudent->name = NULL;
        newStudent->year = 0;
        newStudent->score = 0.0;
        return newStudent;
}

void Student_free(void *self){
        Student *student = (Student *)self;
        if(student != NULL) {
                if(student->name != NULL) {
                        free(student->name);
                }
                free(student);
        }
}

Student *Student_setName(Student *self, char *name){
        if(self == NULL) throw("Student_setName: Student = NULL\n");

        if(self->name != NULL) free(self->name);
        if(name == NULL || strlen(name) == 0) {
                name = "Unknown student";
        }
        self->name = (char *)malloc(sizeof(char) * (strlen(name)+1));
        strcpy(self->name, name);

        return self;
}

Student *Student_setYear(Student *self, int year){
        if(self == NULL) throw("Student_setYear: Student = NULL\n");
        self->year = year;
        return self;
}

Student *Student_setScore(Student *self, double score){
        if(self == NULL) throw("Student_setScore: Student = NULL\n");
        self->score = score;
        return self;
}

Student *Student_create(char *name, int year, double score){
        Student *newStudent = Student_new();
        if(newStudent == NULL) {
                printf("Student_create: student = NULL\n");
                return 0;
        }
        newStudent = Student_setName(newStudent, name);
        newStudent = Student_setYear(newStudent, year);
        newStudent = Student_setScore(newStudent, score);
        return newStudent;
}

char *Student_getName(Student *self){
        if(self == NULL) throw("Student_getName: student = null\n");
        return self->name;
}

int Student_getYear(Student *self){
        if(self == NULL) throw("Student_getYear: student = null\n");
        return self->year;
}

double Student_getScore(Student *self){
        if(self == NULL) throw("Student_getScore: student = null\n");
        return self->score;
}
