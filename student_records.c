// student_records.c
#include "student_records.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSING_MARKS 40
void add_student(StudentRecord **records, int *student_count)
{
  int roll_number;
  printf("Enter roll number: ");
  scanf("%d", &roll_number);
  getchar();

  // Check if roll number is unique
  for (int i = 0; i < *student_count; i++)
  {
    if ((*records)[i].roll_number == roll_number)
    {
      printf("\nError: Roll number %d already exists. Please enter a unique roll number.\n\n", roll_number);
      return;
    }
  }

  *student_count += 1;
  *records = realloc(*records, (*student_count) * sizeof(StudentRecord));
  if (*records == NULL)
  {
    printf("Memory allocation failed.\n");
    exit(1);
  }

  (*records)[*student_count - 1].roll_number = roll_number;
  printf("Enter student name: ");
  fgets((*records)[*student_count - 1].name, 50, stdin);
  (*records)[*student_count - 1].name[strcspn((*records)[*student_count - 1].name, "\n")] = 0;
  printf("Enter marks: ");
  scanf("%d", &(*records)[*student_count - 1].marks);
  getchar(); // Consume newline character

  if ((*records)[*student_count - 1].marks >= PASSING_MARKS)
  {
    printf("%s has passed.\n", (*records)[*student_count - 1].name);
  }
  else
  {
    printf("%s has failed.\n", (*records)[*student_count - 1].name);
  }
}

void modify_student(StudentRecord *records, int student_count)
{
  int roll_number;
  printf("Enter roll number of student to modify: ");
  scanf("%d", &roll_number);
  getchar();

  for (int i = 0; i < student_count; i++)
  {
    if (records[i].roll_number == roll_number)
    {
      printf("Enter new name: ");
      fgets(records[i].name, 50, stdin);
      records[i].name[strcspn(records[i].name, "\n")] = 0;
      printf("Enter new marks: ");
      scanf("%d", &records[i].marks);
      getchar();
      return;
    }
  }
  printf("Student with roll number %d not found.\n", roll_number);
}

void display_students(const StudentRecord *records, int student_count)
{
  if (student_count == 0)
  {
    printf("No student data available.\n");
    return;
  }
  for (int i = 0; i < student_count; i++)
  {
    printf("Name: %s, Roll Number: %d, Marks: %d\n", records[i].name, records[i].roll_number, records[i].marks);
  }
}

void search_student(const StudentRecord *records, int student_count)
{
  int roll_number;
  printf("Enter roll number to search: ");
  scanf("%d", &roll_number);
  getchar();

  for (int i = 0; i < student_count; i++)
  {
    if (records[i].roll_number == roll_number)
    {
      printf("Name: %s, Roll Number: %d, Marks: %d\n", records[i].name, records[i].roll_number, records[i].marks);
      return;
    }
  }
  printf("Student with roll number %d not found.\n", roll_number);
}

void save_records_to_file(const StudentRecord *records, int student_count)
{
  FILE *file = fopen("student_records.txt", "w");
  if (file == NULL)
  {
    printf("Unable to open file for writing.\n");
    return;
  }
  for (int i = 0; i < student_count; i++)
  {
    fprintf(file, "%s,%d,%d\n", records[i].name, records[i].roll_number, records[i].marks);
  }
  fclose(file);
  printf("Records saved successfully.\n");
}

void load_records_from_file(StudentRecord **records, int *student_count)
{
  FILE *file = fopen("student_records.txt", "r");
  if (file == NULL)
  {
    printf("Unable to open file for reading.\n");
    return;
  }
  *student_count = 0;
  *records = NULL;
  char line[100];
  while (fgets(line, sizeof(line), file))
  {
    StudentRecord temp;
    if (sscanf(line, "%49[^,],%d,%d", temp.name, &temp.roll_number, &temp.marks) == 3)
    {
      *student_count += 1;
      *records = realloc(*records, (*student_count) * sizeof(StudentRecord));
      if (*records == NULL)
      {
        printf("Memory allocation failed.\n");
        exit(1);
      }
      (*records)[*student_count - 1] = temp;
    }
  }
  fclose(file);
  printf("Records loaded successfully.\n");
}

void calculate_average_marks(const StudentRecord *records, int student_count)
{
  if (student_count == 0)
  {
    printf("No students to calculate average marks.\n");
    return;
  }
  int total_marks = 0;
  for (int i = 0; i < student_count; i++)
  {
    total_marks += records[i].marks;
  }
  printf("Average Marks: %.2f\n", (double)total_marks / student_count);
}

void sort_students_by_marks(StudentRecord *records, int student_count)
{
  for (int i = 0; i < student_count - 1; i++)
  {
    for (int j = i + 1; j < student_count; j++)
    {
      if (records[i].marks < records[j].marks)
      {
        StudentRecord temp = records[i];
        records[i] = records[j];
        records[j] = temp;
      }
    }
  }
  printf("Students sorted by marks in descending order.\n");
}
