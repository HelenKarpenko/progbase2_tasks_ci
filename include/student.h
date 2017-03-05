#ifndef STUDENT_H
#define STUDENT_H

typedef struct Student Student;

Student *Student_new(void);
void Student_free(void *self);
Student *Student_setName(Student *self, char *name);
Student *Student_setYear(Student *self, int year);
Student *Student_setScore(Student *self, double score);
char *Student_getName(Student *self);
int Student_getYear(Student *self);
double Student_getScore(Student *self);
Student *Student_create(char *name, int year, double score);

#endif
