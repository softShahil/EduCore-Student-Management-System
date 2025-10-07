#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for student
typedef struct {
    int id;
    char name[100];
    char course[50];
    char address[200];
} Student;

// Structure for Admin
typedef struct {
    char username[50];
    char password[20];
} Admin;

// Function prototypes
void adminRegister();
int adminLogin();
void addStudent();
void viewStudents();
void updateStudent();
void deleteStudent();
void studentRegister();
int studentLogin();
void studentAddData();
int checkStudentExists(int id);
void logout();

int main() {
    int choice, userType;

    do {
        printf("\n=== Welcome To Student Record Management System ===\n");
        printf("Users menu:\n1. Admin\n");
        printf("2. Student\n");
        printf("3. Exit\n");
        printf("Enter your user type: ");
        scanf("%d", &userType);

        if (userType == 1) {
            do {
                printf("\nAdmin Menu:\n");
                printf("1. Register\n2. Login\n3. Exit\nEnter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                case 1:
                    adminRegister();
                    break;
                case 2:
                    if (adminLogin()) {
                        do {
                            printf("\nAdmin Menu:\n");
                            printf("\t1. Add Student\n\t2. View Students\n\t3. Update Student\n\t4. Delete Student\n\t5. Logout\nEnter your choice: ");
                            scanf("%d", &choice);

                            switch (choice) {
                            case 1:
                                addStudent();
                                break;
                            case 2:
                                viewStudents();
                                break;
                            case 3:
                                updateStudent();
                                break;
                            case 4:
                                deleteStudent();
                                break;
                            case 5:
                                logout();
                                break;
                            default:
                                printf("Invalid choice!\n");
                            }
                        } while (choice != 5);
                    }
                    break;
                case 3:
                    logout();
                    break;
                default:
                    printf("Invalid Choice! Pleas try again\n");
                }
            } while (choice != 3);
        }
        else if (userType == 2) {
            do {
                printf("\n1. Register\n2. Login\n3. Logout\nEnter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                case 1:
                    studentRegister();
                    break;
                case 2:
                    if (studentLogin()) {
                        studentAddData();
                    }
                    break;
                case 3:
                    logout();
                    break;
                default:
                    printf("Invalid Choice! Pleas try again\n");
                }
            } while (choice != 3);
        }
        else if (userType == 3) {
            printf("Exiting...\n");
            break;
        }
        else {
            printf("Invalid user type!\n");
        }
    } while (userType != 3);

    return 0;
}

// Admin Registration
void adminRegister() {
    Admin admin;
    FILE *file = fopen("admins.txt", "a");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n-----ADMIN REGISTRATION-----\n\nEnter username: ");
    scanf("%s", admin.username);
    printf("Enter password: ");
    scanf("%s", admin.password);

    fprintf(file, "%s %s\n", admin.username, admin.password);
    fclose(file);

    printf("\n------Admin registered successfully!-----\n");
}

// Admin Login
int adminLogin() {
    Admin admin;
    char username[50], password[20];
    FILE *file = fopen("admins.txt", "r");

    if (file == NULL) {
        printf("No admins found! Please register first.\n");
        return 0;
    }

    printf("\n----ADMIN LOGIN-----\n\nEnter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    while (fscanf(file, "%s %s\n", admin.username, admin.password) != EOF) {
        if (strcmp(admin.username, username) == 0 && strcmp(admin.password, password) == 0) {
            fclose(file);
            printf("\n-----Login successful!------\n");
            return 1;
        }
    }

    fclose(file);
    printf("Invalid credentials!\n");
    return 0;
}

// Add Student
void addStudent() {
    Student student;
    FILE *file = fopen("students.txt", "a");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n-----ADD STUDENT DATA-------\n\nEnter Student ID: ");
    scanf("%d", &student.id);
    printf("Enter Name: ");
    scanf(" %[^\n]s", student.name);
    printf("Enter Course: ");
    scanf(" %[^\n]s", student.course);
    printf("Enter Address: ");
    scanf(" %[^\n]s", student.address);

    fprintf(file, "%d, %s, %s, %s\n", student.id, student.name, student.course, student.address);
    fclose(file);

    printf("\n------Student added successfully!------\n");
}

// View Students
void viewStudents() {
    Student student;
    FILE *file = fopen("students.txt", "r");

    if (file == NULL) {
        printf("No students found!\n");
        return;
    }

    printf("\n-------Student Records--------\n");
    printf("\nID\tName\t\tCourse\t\tAddress\n");
    printf("--------------------------------------------------\n");

    // Use the corrected format string
    while (fscanf(file, "%d,%49[^,],%49[^,],%99[^\n]", &student.id, student.name, student.course, student.address) == 4) {
        printf("%d\t%-15s\t%-15s\t%s\n", student.id, student.name, student.course, student.address);
    }

    fclose(file);
}

// Update Student
void updateStudent() {
  Student student;
  int id, found = 0;

  // Open the original and temporary files
  FILE *file = fopen("students.txt", "r");
  FILE *temp = fopen("temp.txt", "w");

  if (file == NULL || temp == NULL) {
    printf("Error opening file!\n");
    if (file) fclose(file);
    if (temp) fclose(temp);
    return;
  }

  printf("\n----UPDATE STUDENT DATA-----\n\nEnter Student ID to update: ");
  scanf("%d", &id);

  // Read each student record, modify if ID matches, and write to temp file
  while (fscanf(file, "%d, %49[^,], %49[^,], %99[^\n]", &student.id, student.name, student.course, student.address) == 4) {
    if (student.id == id) {
      printf("Enter new Name: ");
      scanf(" %[^\n]", student.name); // Use %[^\n] to read the entire name
      printf("Enter new Course: ");
      scanf(" %[^\n]", student.course); // Use %[^\n] to read the entire course
      printf("Enter new Address: ");
      scanf(" %[^\n]", student.address); // Use %[^\n] to read the entire address
      found = 1;
    }
    // Write the updated or original record to the temp file
    fprintf(temp, "%d, %s, %s, %s\n", student.id, student.name, student.course, student.address);
  }

  fclose(file);
  fclose(temp);

  // Replace the old file with the updated one
  if (remove("students.txt") != 0) {
    printf("Error deleting the old file!\n");
    return;
  }
  if (rename("temp.txt", "students.txt") != 0) {
    printf("Error renaming the temporary file!\n");
    return;
  }

  if (found) {
    printf("\n-----Student updated successfully!-----\n");
  } else {
    printf("Student not found!\n");
  }
}

// Delete Student
void deleteStudent() {
  Student student;
  int id, found = 0;
  FILE *file = fopen("students.txt", "r");
  FILE *temp = fopen("temp.txt", "w");

  if (file == NULL || temp == NULL) {
    printf("Error opening file!\n");
    return;
  }

  printf("\n-----DELETE STUDENT DATA-----\n\nEnter Student ID to delete: ");
  scanf("%d", &id);

  while (fscanf(file, "%d, %49[^,], %49[^,], %99[^\n]", &student.id, student.name, student.course, student.address) != EOF) {
    if (student.id != id) {
      fprintf(temp, "%d, %s, %s, %s\n", student.id, student.name, student.course, student.address);
    } else {
      found = 1;
    }
  }

  fclose(file);
  fclose(temp);

  if (found) {
    printf("\n------Student deleted successfully!------\n");
    // Remove original file
    remove("students.txt");
    // Rename temp file to students.txt
    rename("temp.txt", "students.txt");
  } else {
    printf("Student not found!\n");
    // Remove temp file if student not found (optional)
    remove("temp.txt");
  }
}

// Student Register
void studentRegister() {
    FILE *file = fopen("student_login.txt", "a");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char username[50], password[20];

    printf("\n----STUDENT REGISTRATION----\n\nEnter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%19s", password);

    fprintf(file, "%s %s\n", username, password); 

    if (ferror(file)) {
        printf("Error writing to file.\n");
    } else {
        printf("\n-----Student registered successfully!-----\n");
    }

    fclose(file);
}

// Student Login
int studentLogin() {
    char username[50], password[20];
    char line[100]; 
    FILE *file = fopen("student_login.txt", "r");

    if (file == NULL) {
        printf("No students found! Please register first.\n");
        return 0;
    }

    printf("\n-----STUDENT LOGIN-----\n\nEnter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%19s", password);

    while (fgets(line, sizeof(line), file) != NULL) { 
        char tempUsername[50];
        char tempPassword[20];
        sscanf(line, "%s %s", tempUsername, tempPassword); // Extract username and password from line

        if (strcmp(tempUsername, username) == 0 && strcmp(tempPassword, password) == 0) {
            fclose(file);
            printf("\n------Login successful!-----\n");
            return 1;
        }
    }

    fclose(file);
    printf("Invalid credentials!\n");
    return 0;
}

// Student Add Data
void studentAddData() {
    Student student;
    FILE *file = fopen("students.txt", "a");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n----ADD YOUR DATA-----\n\nEnter your Student ID: ");
    scanf("%d", &student.id);
    printf("Enter your Name: ");
    scanf(" %[^\n]s", student.name);
    printf("Enter your Course: ");
    scanf(" %[^\n]s", student.course);
    printf("Enter your Address: ");
    scanf(" %[^\n]s", student.address);

    // Check if the student ID already exists
    if (checkStudentExists(student.id)) {
        printf("Student ID already exists. You cannot add a new record.\n");
        return;
    }

    // Write the new student data to the file
    fprintf(file, "%d, %s, %s, %s\n", student.id, student.name, student.course, student.address);

    fclose(file);
    printf("\n------Student data added successfully!-----\n");
}

// check a student with the given ID already exists
int checkStudentExists(int id) {
    FILE *file = fopen("students.txt", "r");
    Student student;

    if (file == NULL) {
        return 0; // student doesn't exist
    }

    while (fscanf(file, "%d %s %s %[^\n]", &student.id, student.name, student.course, student.address) != EOF) {
        if (student.id == id) {
            fclose(file);
            return 1; // Student found
        }
    }

    fclose(file);
    return 0; // Student not found
}

void logout() {
    printf("\nYou have been successfully logged out!\n");
}
