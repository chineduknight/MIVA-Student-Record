// main.c
#include "student_records.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char user_name[50];
  printf("Welcome to the Student Record System!\n");
  printf("Please enter your name: ");
  fgets(user_name, 50, stdin);
  user_name[strcspn(user_name, "\n")] = 0; // Remove trailing newline
  printf("Hello, %s!\n", user_name);

  StudentRecord *records = NULL;
  int student_count = 0;
  int choice;

  while (1)
  {
    printf("\n1. Add Student\n2. Modify Student\n3. Display All Students\n4. Search Student by Roll Number\n5. Save Records to File\n6. Load Records from File\n7. Calculate Average Marks\n8. Sort Students by Marks\n9. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Consume newline character

    switch (choice)
    {
    case 1:
      add_student(&records, &student_count);
      break;
    case 2:
      modify_student(records, student_count);
      break;
    case 3:
      display_students(records, student_count);
      break;
    case 4:
      search_student(records, student_count);
      break;
    case 5:
      save_records_to_file(records, student_count);
      break;
    case 6:
      load_records_from_file(&records, &student_count);
      break;
    case 7:
      calculate_average_marks(records, student_count);
      break;
    case 8:
      sort_students_by_marks(records, student_count);
      break;
    case 9:
      free(records);
      printf("Exiting the Student Record System. Goodbye, %s!\n", user_name);
      return 0;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }
}
