// student_records.h
#ifndef STUDENT_RECORDS_H
#define STUDENT_RECORDS_H

typedef struct
{
  char name[50];
  int roll_number;
  int marks;
} StudentRecord;

void add_student(StudentRecord **records, int *student_count);
void modify_student(StudentRecord *records, int student_count);
void remove_student(StudentRecord **records, int *student_count);
void display_students(const StudentRecord *records, int student_count);
void search_student(const StudentRecord *records, int student_count);
void save_records_to_file(const StudentRecord *records, int student_count);
void load_records_from_file(StudentRecord **records, int *student_count);
void calculate_average_marks(const StudentRecord *records, int student_count);
void sort_students_by_marks(StudentRecord *records, int student_count, int order);

#endif
