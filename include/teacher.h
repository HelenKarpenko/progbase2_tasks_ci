#ifndef TEACHER_H
#define TEACHER_H
#include "list.h"
#include "student.h"
typedef struct Teacher Teacher;

Teacher *Teacher_new(void);
void Teacher_free(Teacher **self);
char *Teacher_getName(Teacher *self);
int Teacher_getYear(Teacher *self);
double Teacher_getScore(Teacher *self);
List *Teacher_getListOfStudents(Teacher *self);
Teacher *Teacher_create(char *name, int year, double score, List *listOfStudents);
void Teacher_addStudentsFromList(Teacher *self, List *list);
void Teacher_addStudent(Teacher *self,Student *student);
int Teacher_containsStudent(Teacher *self,Student *student);

#endif
