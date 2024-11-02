// student_records.c
#include "student_records.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tinyfiledialogs.h"
// https://github.com/native-toolkit/libtinyfiledialogs
// here is the github link for tinyfiledialogs

#define PASSING_MARKS 40

void add_student(StudentRecord **records, int *student_count)
{
  int roll_number;
  while (1)
  {
    printf("Enter roll number (or type -1 to Return to main menu): ");
    if (scanf("%d", &roll_number) != 1)
    {
      printf("Invalid input. Roll number must be a number. Try again.\n");
      while (getchar() != '\n')
        ; // Clear input buffer
      continue;
    }
    if (roll_number == -1)
    {
      return;
    }
    if (roll_number < 0)
    {
      printf("Invalid roll number. Roll number must be positive. Try again.\n");
      continue;
    }
    getchar(); // Consume newline character
    // Check if roll number is unique
    int is_unique = 1;
    for (int i = 0; i < *student_count; i++)
    {
      if ((*records)[i].roll_number == roll_number)
      {
        printf("Error: Roll number %d already exists. Please enter a unique roll number.\n", roll_number);
        is_unique = 0;
        break;
      }
    }
    if (is_unique)
    {
      break;
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

  // Validate student name
  while (1)
  {
    printf("Enter student name: ");
    fgets((*records)[*student_count - 1].name, 50, stdin);
    (*records)[*student_count - 1].name[strcspn((*records)[*student_count - 1].name, "\n")] = 0;
    int valid_name = 1;
    for (int i = 0; i < strlen((*records)[*student_count - 1].name); i++)
    {
      if (!isalpha((*records)[*student_count - 1].name[i]) && (*records)[*student_count - 1].name[i] != ' ')
      {
        valid_name = 0;
        break;
      }
    }
    if (valid_name && strlen((*records)[*student_count - 1].name) > 0)
    {
      break;
    }
    else
    {
      printf("Invalid name. Name should only contain alphabets and spaces. Try again.\n");
    }
  }

  // Validate marks
  while (1)
  {
    printf("Enter marks (0-100): ");
    if (scanf("%d", &(*records)[*student_count - 1].marks) != 1)
    {
      printf("Invalid input. Marks must be a number. Try again.\n");
      while (getchar() != '\n')
        ; // Clear input buffer
      continue;
    }
    if ((*records)[*student_count - 1].marks < 0 || (*records)[*student_count - 1].marks > 100)
    {
      printf("Invalid marks. Marks must be between 0 and 100. Try again.\n");
    }
    else
    {
      break;
    }
  }
  getchar(); // Consume newline character

  if ((*records)[*student_count - 1].marks >= PASSING_MARKS)
  {
    printf("%s has passed.\n", (*records)[*student_count - 1].name);
  }
  else
  {
    printf("%s has failed.\n", (*records)[*student_count - 1].name);
  }

  // Prompt to add another record or return to main menu
  char choice;
  while (1)
  {
    printf("Do you want to add another student? (y/n): ");
    choice = getchar();
    getchar(); // Consume newline character
    if (choice == 'y' || choice == 'Y')
    {
      add_student(records, student_count);
      return;
    }
    else if (choice == 'n' || choice == 'N')
    {
      return;
    }
    else
    {
      printf("Invalid choice. Please enter 'y' or 'n'.\n");
    }
  }
}

void modify_student(StudentRecord *records, int student_count)
{
  int roll_number;
  printf("Enter roll number of student to modify: ");
  if (scanf("%d", &roll_number) != 1)
  {
    printf("Invalid input. Roll number must be a number.\n");
    while (getchar() != '\n')
      ; // Clear input buffer
    return;
  }
  getchar();

  for (int i = 0; i < student_count; i++)
  {
    if (records[i].roll_number == roll_number)
    {
      // Validate student name
      while (1)
      {
        printf("Enter new name: ");
        fgets(records[i].name, 50, stdin);
        records[i].name[strcspn(records[i].name, "\n")] = 0;
        int valid_name = 1;
        for (int j = 0; j < strlen(records[i].name); j++)
        {
          if (!isalpha(records[i].name[j]) && records[i].name[j] != ' ')
          {
            valid_name = 0;
            break;
          }
        }
        if (valid_name && strlen(records[i].name) > 0)
        {
          break;
        }
        else
        {
          printf("Invalid name. Name should only contain alphabets and spaces. Try again.\n");
        }
      }

      // Validate marks
      while (1)
      {
        printf("Enter new marks (0-100): ");
        if (scanf("%d", &records[i].marks) != 1)
        {
          printf("Invalid input. Marks must be a number. Try again.\n");
          while (getchar() != '\n')
            ; // Clear input buffer
          continue;
        }
        if (records[i].marks < 0 || records[i].marks > 100)
        {
          printf("Invalid marks. Marks must be between 0 and 100. Try again.\n");
        }
        else
        {
          break;
        }
      }
      getchar(); // Consume newline character
      printf("Student record updated successfully.");
      return;
    }
  }
  printf("Student with roll number %d not found.\n", roll_number);
}

void remove_student(StudentRecord **records, int *student_count)
{
  int roll_number;
  printf("Enter roll number of student to remove: ");
  if (scanf("%d", &roll_number) != 1)
  {
    printf("Invalid input. Roll number must be a number.\n");
    while (getchar() != '\n')
      ; // Clear input buffer
    return;
  }
  getchar(); // Clear newline character from buffer after scanf

  // Loop to find the student with the specified roll number
  for (int i = 0; i < *student_count; i++)
  {
    if ((*records)[i].roll_number == roll_number)
    {
      // Shift records to remove the student
      for (int j = i; j < *student_count - 1; j++)
      {
        (*records)[j] = (*records)[j + 1];
      }
      (*student_count)--;

      // Resize the array only if there are still students left
      if (*student_count > 0)
      {
        *records = realloc(*records, (*student_count) * sizeof(StudentRecord));
        if (*records == NULL)
        {
          printf("Memory reallocation failed.\n");
          exit(1);
        }
      }
      else
      {
        free(*records); // Free memory if there are no students left
        *records = NULL;
      }

      printf("Student with roll number %d removed successfully.\n", roll_number);
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
  printf("%-20s %-15s %-10s\n", "Name", "Roll Number", "Marks");
  printf("%-20s %-15s %-10s\n", "-------------------", "-------------", "---------");
  for (int i = 0; i < student_count; i++)
  {
    printf("%-20s %-15d %-10d\n", records[i].name, records[i].roll_number, records[i].marks);
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

void save_records_to_file22(const StudentRecord *records, int student_count)
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
  printf("Records saved successfully to 'student_records.txt'.\n");
}
void load_records_from_file(StudentRecord **records, int *student_count)
{
  const char *file_name = tinyfd_openFileDialog("Select a file to load records", "", 0, NULL, NULL, 0);
  if (file_name == NULL)
  {
    printf("No file selected. Operation cancelled.\n");
    return;
  }

  // Check if file has .txt extension
  const char *extension = strrchr(file_name, '.');
  if (!extension || strcmp(extension, ".txt") != 0)
  {
    printf("Invalid file format selected. Please select a .txt file.\n");
    return;
  }

  FILE *file = fopen(file_name, "r");
  if (file == NULL)
  {
    printf("Unable to open file '%s' for reading. Please check if the file exists and is accessible.\n", file_name);
    return;
  }

  *student_count = 0;
  *records = NULL;
  char line[100];
  int invalid_count = 0;
  int duplicate_count = 0;

  while (fgets(line, sizeof(line), file))
  {
    StudentRecord temp;
    if (sscanf(line, "%49[^,],%d,%d", temp.name, &temp.roll_number, &temp.marks) == 3)
    {
      // Check for duplicate roll number
      int is_duplicate = 0;
      for (int i = 0; i < *student_count; i++)
      {
        if ((*records)[i].roll_number == temp.roll_number)
        {
          is_duplicate = 1;
          duplicate_count++;
          break;
        }
      }
      if (is_duplicate)
      {
        continue;
      }

      *student_count += 1;
      *records = realloc(*records, (*student_count) * sizeof(StudentRecord));
      if (*records == NULL)
      {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
      }
      (*records)[*student_count - 1] = temp;
    }
    else
    {
      invalid_count++;
    }
  }
  fclose(file);
  if (*student_count == 0)
  {
    printf("No valid records were loaded from the file '%s'.\n", file_name);
  }
  else
  {
    printf("Records loaded successfully from '%s'.\n", file_name);
  }
  if (invalid_count > 0)
  {
    printf("%d invalid entries were skipped during the loading process.\n", invalid_count);
  }
  if (duplicate_count > 0)
  {
    printf("%d duplicate entries were skipped during the loading process.\n", duplicate_count);
  }
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

void sort_students_by_marks(StudentRecord *records, int student_count, int ascending)
{
  for (int i = 0; i < student_count - 1; i++)
  {
    for (int j = i + 1; j < student_count; j++)
    {
      int condition = ascending ? (records[i].marks > records[j].marks) : (records[i].marks < records[j].marks);
      if (condition)
      {
        StudentRecord temp = records[i];
        records[i] = records[j];
        records[j] = temp;
      }
    }
  }

  if (ascending)
  {
    printf("Students sorted by marks in ascending order.\n");
  }
  else
  {
    printf("Students sorted by marks in descending order.\n");
  }
}
