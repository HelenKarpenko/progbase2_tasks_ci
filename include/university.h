#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include "../include/list.h"
#include "../include/teacher.h"

// Формування списку студентів із CSV строки.
List *University_getListOfStudentsFromCSVStr(List *listOfStudents, char *csv);

// Формування CSV строки із списку студентів.
char *University_getStrFromListOfStudents(List *listOfStudents);

// Прикріплення списку студентів до викладача.
Teacher *University_setListOfStudentToTeacher(Teacher *self, List *listOfStud);

// Функція, що приймає двох викладачів і в результаті створює список зі студентами, що прив'язані до обох викладачів.
List *University_listFromIntersectionOfTeacher(Teacher *teacher1, Teacher *teacher2);



#endif
