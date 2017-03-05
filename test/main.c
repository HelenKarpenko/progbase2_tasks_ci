#include <stdio.h>
#include <stdlib.h>

#include <check.h>
#include "../include/university.h"


START_TEST(university_getListOfStudentsFromCSVStr_LenOfStr_0){
        char str[] = "";
        List *listOfStudents = List_new();
        listOfStudents = University_getListOfStudentsFromCSVStr(listOfStudents, str);
        ck_assert_int_eq(List_getLength(listOfStudents), 0);
        List_free(&listOfStudents,Student_free);
}
END_TEST

START_TEST(university_getListOfStudentsFromCSVStr_LenOfStr_OneLine){
        char *str = "\"Lena\",1999,4.1\n\"VITA\",1980,-33";
        List *listOfStudents = List_new();
        University_getListOfStudentsFromCSVStr(listOfStudents, str);
        ck_assert_int_eq(List_getLength(listOfStudents), 2);
        Student *student = (Student *)List_getDataAt(listOfStudents, 0);
        ck_assert_str_eq(Student_getName(student),"Lena");
        ck_assert_int_eq(Student_getYear(student),1999);
        ck_assert_double_eq(Student_getScore(student),4.1);
        student = (Student *)List_getDataAt(listOfStudents, 1);
        ck_assert_str_eq(Student_getName(student),"VITA");
        ck_assert_int_eq(Student_getYear(student),1980);
        ck_assert_double_eq(Student_getScore(student),-33);
        List_free(&listOfStudents, Student_free);
}
END_TEST

START_TEST(university_getListOfStudentsFromCSVStr){
        char *str = "\"Lena,1999,4.1\n\"VITA\",1980,-33";
        List *listOfStudents = List_new();
        University_getListOfStudentsFromCSVStr(listOfStudents, str);
        ck_assert_int_eq(List_getLength(listOfStudents), 2);
        Student *student = (Student *)List_getDataAt(listOfStudents, 0);
        ck_assert_str_eq(Student_getName(student),"Lena,1999,4.1");
        student = (Student *)List_getDataAt(listOfStudents, 1);
        ck_assert_str_eq(Student_getName(student),"VITA");
        ck_assert_int_ne(Student_getYear(student),190);
        ck_assert_double_eq(Student_getScore(student),-33);
        List_free(&listOfStudents, Student_free);
}
END_TEST

START_TEST(university_getStrFromListOfStudents_LenOfStud_0){
        List *listOfStudents = List_new();
        char *str = University_getStrFromListOfStudents(listOfStudents);
        ck_assert_str_eq(str, "");
        free(str);
        List_free(&listOfStudents, Student_free);
}
END_TEST

START_TEST(university_getStrFromListOfStudents_LenOfStud_1){
        List *listOfStudents = List_new();
        Student *stud = Student_create("Ira", 1985, 6.3);
        List_addLast(listOfStudents, stud);
        char *str = University_getStrFromListOfStudents(listOfStudents);
        ck_assert_str_eq(str, "\"Ira\",1985,6.3\n");
        free(str);
        List_free(&listOfStudents, Student_free);
}
END_TEST

START_TEST(university_getStrFromListOfStudents_LenOfStud_3){
        List *listOfStudents = List_new();
        Student *stud1 = Student_create("Ira", 1985, 6.3);
        Student *stud2 = Student_create("Bika", 1999, 7.8);
        Student *stud3 = Student_create("Alex", 1976, 1.9);
        List_addLast(listOfStudents, stud1);
        List_addLast(listOfStudents, stud2);
        List_addLast(listOfStudents, stud3);
        char *str = University_getStrFromListOfStudents(listOfStudents);
        ck_assert_str_eq(str, "\"Ira\",1985,6.3\n\"Bika\",1999,7.8\n\"Alex\",1976,1.9\n");
        free(str);
        List_free(&listOfStudents, Student_free);
}
END_TEST
/////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(university_setListOfStudentToTeacher_countOfStud_0){
        Teacher *teacher = Teacher_new();
        List *listOfStudents = List_new();
        teacher = University_setListOfStudentToTeacher(teacher, listOfStudents);
        ck_assert_int_eq(List_getLength(Teacher_getListOfStudents(teacher)), 0);
        List_free(&listOfStudents, Student_free);
        Teacher_free(&teacher);
}
END_TEST

START_TEST(university_setListOfStudentToTeacher_countOfStud_3){
        Teacher *teacher = Teacher_new();
        List *listOfStudents = List_new();
        Student *stud1 = Student_create("Ira", 1985, 6.3);
        Student *stud2 = Student_create("Bika", 1999, 7.8);
        Student *stud3 = Student_create("Alex", 1976, 1.9);
        List_addLast(listOfStudents, stud1);
        List_addLast(listOfStudents, stud2);
        List_addLast(listOfStudents, stud3);
        teacher = University_setListOfStudentToTeacher(teacher, listOfStudents);
        ck_assert_int_eq(List_getLength(Teacher_getListOfStudents(teacher)), 3);
        List_free(&listOfStudents, Student_free);
        Teacher_free(&teacher);
}
END_TEST

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(university_listFromIntersectionOfTeacher_listsWithTheSameStud){
        Teacher *teacher1 = Teacher_new();
        Teacher *teacher2 = Teacher_new();
        List *list1 = List_new();
        List *list2 = List_new();
        List *listResult = NULL;
        Student *stud1 = Student_create("Ira", 1985, 6.3);
        Student *stud2 = Student_create("Bika", 1999, 7.8);
        Student *stud3 = Student_create("Alex", 1976, 1.9);
        List_addLast(list1, stud1);
        List_addLast(list1, stud2);
        List_addLast(list1, stud3);

        List_addLast(list2, stud1);
        List_addLast(list2, stud2);
        List_addLast(list2, stud3);

        University_setListOfStudentToTeacher(teacher1, list1);
        University_setListOfStudentToTeacher(teacher2, list2);

        listResult = University_listFromIntersectionOfTeacher(teacher1, teacher2);
        ck_assert_int_eq(List_getLength(listResult), 3);

        List_free(&list1, Student_free);
        List_free(&list2, NULL);
        List_free(&listResult, NULL);
        Teacher_free(&teacher1);
        Teacher_free(&teacher2);
}
END_TEST

START_TEST(university_listFromIntersectionOfTeacher_listsIsEmpty){
        Teacher *teacher1 = Teacher_new();
        Teacher *teacher2 = Teacher_new();
        List *list1 = List_new();
        List *list2 = List_new();
        List *listResult = NULL;
        University_setListOfStudentToTeacher(teacher1, list1);
        University_setListOfStudentToTeacher(teacher2, list2);
        listResult = University_listFromIntersectionOfTeacher(teacher1, teacher2);
        ck_assert_int_eq(List_getLength(listResult), 0);

        List_free(&list1, Student_free);
        List_free(&list2, Student_free);
        List_free(&listResult, Student_free);
        Teacher_free(&teacher1);
        Teacher_free(&teacher2);
}
END_TEST

START_TEST(university_listFromIntersectionOfTeacher_listsWithDiferStud){
        Teacher *teacher1 = Teacher_new();
        Teacher *teacher2 = Teacher_new();
        List *list1 = List_new();
        List *list2 = List_new();
        List *listResult = NULL;
        Student *stud1 = Student_create("Ira", 1985, 6.3);
        Student *stud2 = Student_create("Bika", 1999, 7.8);
        Student *stud3 = Student_create("Alex", 1976, 1.9);
        List_addLast(list1, stud1);
        List_addLast(list1, stud2);
        List_addLast(list1, stud3);

        Student *stud4 = Student_create("Dan", 1885, 4.3);
        Student *stud5 = Student_create("Noga", 1990, 9.2);
        Student *stud6 = Student_create("Dupa", 1967, 6.4);
        List_addLast(list2, stud4);
        List_addLast(list2, stud5);
        List_addLast(list2, stud6);

        University_setListOfStudentToTeacher(teacher1, list1);
        University_setListOfStudentToTeacher(teacher2, list2);

        listResult = University_listFromIntersectionOfTeacher(teacher1, teacher2);
        ck_assert_int_eq(List_getLength(listResult), 0);

        List_free(&list1, Student_free);
        List_free(&list2, Student_free);
        List_free(&listResult, Student_free);
        Teacher_free(&teacher1);
        Teacher_free(&teacher2);
}
END_TEST

START_TEST(university_listFromIntersectionOfTeacher){
        Teacher *teacher1 = Teacher_new();
        Teacher *teacher2 = Teacher_new();
        List *list1 = List_new();
        List *list2 = List_new();
        List *listResult = NULL;
        Student *stud1 = Student_create("Ira", 1985, 6.3);
        Student *stud2 = Student_create("Bika", 1999, 7.8);
        Student *stud3 = Student_create("Alex", 1976, 1.9);
        Student *stud4 = Student_create("Dan", 1885, 4.3);
        List_addLast(list1, stud1);
        List_addLast(list1, stud2);
        List_addLast(list1, stud3);

        List_addLast(list2, stud1);
        List_addLast(list2, stud2);
        List_addLast(list2, stud4);

        University_setListOfStudentToTeacher(teacher1, list1);
        University_setListOfStudentToTeacher(teacher2, list2);

        listResult = University_listFromIntersectionOfTeacher(teacher1, teacher2);
        ck_assert_int_eq(List_getLength(listResult), 2);

        Student_free(stud1);
        Student_free(stud2);
        Student_free(stud3);
        Student_free(stud4);
        List_free(&list1, NULL);
        List_free(&list2, NULL);
        List_free(&listResult, NULL);
        Teacher_free(&teacher1);
        Teacher_free(&teacher2);
}
END_TEST


Suite *test_suite() {
        Suite *s = suite_create("University");
        TCase *tc_sample1;

        tc_sample1 = tcase_create("University_getListOfStudentsFromCSVStr");
        tcase_add_test(tc_sample1, university_getListOfStudentsFromCSVStr_LenOfStr_0);
        tcase_add_test(tc_sample1, university_getListOfStudentsFromCSVStr_LenOfStr_OneLine);
        tcase_add_test(tc_sample1, university_getListOfStudentsFromCSVStr);

        suite_add_tcase(s, tc_sample1);

        TCase *tc_sample2;
        tc_sample2 = tcase_create("University_getStrFromListOfStudents");
        tcase_add_test(tc_sample2, university_getStrFromListOfStudents_LenOfStud_0);
        tcase_add_test(tc_sample2, university_getStrFromListOfStudents_LenOfStud_1);
        tcase_add_test(tc_sample2, university_getStrFromListOfStudents_LenOfStud_3);

        suite_add_tcase(s, tc_sample2);

        TCase *tc_sample3;
        tc_sample3 = tcase_create("University_getStrFromListOfStudents");
        tcase_add_test(tc_sample3, university_setListOfStudentToTeacher_countOfStud_0);
        tcase_add_test(tc_sample3, university_setListOfStudentToTeacher_countOfStud_3);
        suite_add_tcase(s, tc_sample3);

        TCase *tc_sample4;
        tc_sample4 = tcase_create("University_getStrFromListOfStudents");
        tcase_add_test(tc_sample4, university_listFromIntersectionOfTeacher_listsIsEmpty);
        tcase_add_test(tc_sample4, university_listFromIntersectionOfTeacher_listsWithTheSameStud);
        tcase_add_test(tc_sample4, university_listFromIntersectionOfTeacher_listsWithDiferStud);
        tcase_add_test(tc_sample4, university_listFromIntersectionOfTeacher);
        suite_add_tcase(s, tc_sample4);

        return s;
}

int main(void) {
        Suite *s = test_suite();
        SRunner *sr = srunner_create(s);
        srunner_set_fork_status(sr, CK_NOFORK); // important for debugging!

        srunner_run_all(sr, CK_VERBOSE);

        int num_tests_failed = srunner_ntests_failed(sr);
        srunner_free(sr);
        return num_tests_failed;
}
