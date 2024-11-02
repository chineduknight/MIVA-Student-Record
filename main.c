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
    printf("\n1. Add Student");
    printf("\n2. Modify Student");
    printf("\n3. Remove Student");
    printf("\n4. Display All Students");
    printf("\n5. Search Student by Roll Number");
    printf("\n6. Save Records to File");
    printf("\n7. Load Records from File");
    printf("\n8. Calculate Average Marks");
    printf("\n9. Sort Students by Marks");
    printf("\n10. Exit\n");

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
      remove_student(&records, &student_count);
      break;
    case 4:
      display_students(records, student_count);
      break;
    case 5:
      search_student(records, student_count);
      break;
    case 6:
      save_records_to_file(records, student_count);
      break;
    case 7:
      load_records_from_file(&records, &student_count);
      break;
    case 8:
      calculate_average_marks(records, student_count);
      break;
    case 9:
    {
      int order;
      printf("Enter 1 to sort by ascending order or 0 to sort by descending order: ");
      if (scanf("%d", &order) != 1 || (order != 0 && order != 1))
      {
        printf("Invalid choice. Defaulting to descending order.\n");
        order = 0;
      }
      getchar(); // Consume newline character left by scanf
      sort_students_by_marks(records, student_count, order);
      display_students(records, student_count);
      break;
    }
    case 10:
      free(records);
      printf("Exiting the Student Record System. Goodbye, %s!\n", user_name);
      return 0;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }
}
