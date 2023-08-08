#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char firstName[20][50] = {
   "Prateek", "Garv", "Harshit", "Sindhu", "Arjun",
    "Buddhi", "Ishaan", "Kavya", "Mira", "Neha",
    "Pranav", "Rahul", "Riya", "Anuska", "Divya",
    "Shreya", "Siddharth", "Tanvi", "Varun", "Zara"
};

char lastName[20][50] = {
        "Tomar", "Chopra", "Desai", "Gupta", "Joshi",
    "Kumar", "Mehta", "Sethia", "Rao", "Sharma",
    "Pandit", "Gupta", "Verma", "Ratoliya", "Bhatt",
    "Chauhan", "Dubey", "Malhotra", "Reddy", "Srivastava"
};

char hostels[5][50] = {"BH-1", "BH-2", "BH-3", "BH-4", "BH-5"};
char courses[5][20] = {"BTech", "MTech", "MS", "PhD", "MBA"};

struct DateOfBirth
{
    int day;
    int month;
    int year;
};

struct Student
{
    char first_name[50];
    char last_name[50];
    char hostel[50];
    char course[20];
    int room_number;
    struct DateOfBirth dob;
};

void registerStudent(struct Student new_student)
{
    FILE *database = fopen("database.txt", "a");

    if (database == NULL)
    {
        printf("Sorry! File couldn't be opened\n");
        return;
    }


    fprintf(database, "%s %s %s %d-%d-%d %d %s \n", new_student.first_name, new_student.last_name, new_student.course, new_student.dob.day, new_student.dob.month, new_student.dob.year, new_student.room_number, new_student.hostel);

    fclose(database);
}



void registration()
{
    for (int i = 0; i < 100; i++)
    {
        struct Student *newStudent = malloc(sizeof(struct Student));

        // Generate random indexes for first and last names
        int firstNameIndex = rand() % 20;
        int lastNameIndex = rand() % 20;

        // Assign the randomly chosen names and other details to newStudent's fields
        strcpy(newStudent->first_name, firstName[firstNameIndex]);
        strcpy(newStudent->last_name, lastName[lastNameIndex]);
        strcpy(newStudent->hostel, hostels[rand() % 5]);
        strcpy(newStudent->course, courses[rand() % 5]);
        newStudent->room_number = rand() % 1000 + 100;
        newStudent->dob.day = rand() % 30 + 1;
        newStudent->dob.month = rand() % 12 + 1;
        newStudent->dob.year = rand() % 30 + 1982;

        registerStudent(*newStudent);

        free(newStudent); // Don't forget to free the allocated memory
    }
    printf("Student registration successfull!!\n");
}


    




void searchStudent(char first_name[], char last_name[])
{
       FILE *database = fopen("database.txt", "r");
    if (database == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), database) != NULL)
    {
        struct Student student;
        char first_name_buf[50];
        char last_name_buf[50];

        int scanned_items = sscanf(line, "%49s %49s %19s %d-%d-%d %d %49s",
                   first_name_buf, last_name_buf,
                   student.course,
                   &student.dob.day, &student.dob.month, &student.dob.year,
                   &student.room_number, student.hostel);

        if (scanned_items != 8)
        {
            printf("Invalid data format in the database.\n");
            break;
        }

        if (strcmp(first_name, first_name_buf) == 0 && strcmp(last_name, last_name_buf) == 0)
        {
            found = 1;
            printf("Student found:\n");
            printf("First Name: %s\n", first_name_buf);
            printf("Last Name: %s\n", last_name_buf);
            printf("Course: %s\n", student.course);
            printf("Date of Birth: %d-%d-%d\n", student.dob.day, student.dob.month, student.dob.year);
            printf("Room Number: %d\n", student.room_number);
            printf("Hostel: %s\n", student.hostel);
            break;
        }
    }

    if (!found)
    {
        printf("Student not found!\n");
    }

    fclose(database);
}

void updateStudent()
{
    FILE *database = fopen("database", "r+");
    if (database == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char first_name[50], last_name[50], new_course[20];
    printf("Enter first name of the student you want to update: ");
    scanf("%s", first_name);
    printf("Enter last name of the student you want to update: ");
    scanf("%s", last_name);
    printf("Enter new course: ");
    scanf("%s", new_course);

    char line[256];
    int found = 0;
    long int pos;

    while (fgets(line, sizeof(line), database) != NULL)
    {
        struct Student student;
        char first_name_buf[50], last_name_buf[50];

        int scanned_items = sscanf(line, "%49s %49s %19s %d-%d-%d %d %49s",
                  first_name_buf, last_name_buf,
                  student.course,
                  &student.dob.day, &student.dob.month, &student.dob.year,
                  &student.room_number, student.hostel);
    if (scanned_items != 8)
        {
            printf("Invalid data format in the database.\n");
            break;
        }

        if (strcmp(first_name, first_name_buf) == 0 && strcmp(last_name, last_name_buf) == 0)
        {
            found = 1;
            pos = ftell(database) - strlen(line); // Save the current position for later overwrite
            fseek(database, pos, SEEK_SET);       // Move the file pointer to the position to overwrite
            fprintf(database, "%s %s %s %d-%d-%d %d %s \n", first_name_buf, last_name_buf, new_course, student.dob.day, student.dob.month, student.dob.year, student.room_number, student.hostel);
            break;
        }
    
    else
    {
        printf("Student's course updated successfully!\n");
    }

    fclose(database);
}}
void deleteStudent(char *firstname,char *lastName)
{
    FILE *database = fopen("database","r");
    FILE *databaseUpdated = fopen("database_temp","a");

    char line[256];
    while (fgets(line,sizeof(line),database))
    {
        struct Student newStudent;
        sscanf(line,"%s %s %s %d-%d-%d %d %s",newStudent.first_name, newStudent.last_name, newStudent.course, &newStudent.dob.day, &newStudent.dob.month, &newStudent.dob.year, &newStudent.room_number, newStudent.hostel);
        if (strcmp(newStudent.first_name,firstname)!=0 && strcmp(newStudent.last_name,lastName)!=0)
        {   
            fprintf(databaseUpdated, "%s %s %s %d-%d-%d %d %s \n", newStudent.first_name, newStudent.last_name, newStudent.course, newStudent.dob.day, newStudent.dob.month, newStudent.dob.year, newStudent.room_number, newStudent.hostel);
        }
    }
    
    
    printf("Deleted Successfully!! \n");
    fclose(database);
    fclose(databaseUpdated);
    remove("database");
    rename("database_temp","database");

    
}

int main()
{
    
    
    
    int choice;
    do{
    printf("* * * * * * Welcome To The Server * * * * * *\n");
    printf("Menu:\n");
    printf("0 - Registration\n");
    printf("1 - Search\n");
    printf("2 - Update\n");
    printf("3 - Delete\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 0:
        printf("Selected: Registration\n");
        registration();
        break;
    case 1:
        printf("Selected: Search\n");
        char first_name[50], last_name[50];
        printf("Enter first name: ");
        scanf("%s", first_name);
        printf("Enter last name: ");
        scanf("%s", last_name);
        searchStudent(first_name, last_name);
        break;
    case 2:
        printf("Selected: Update\n");
        updateStudent();
        break;
    case 3:
        printf("Selected: Delete\n");
        printf("Enter first name: ");
        scanf("%s", first_name);
        printf("Enter last name: ");
        scanf("%s", last_name);
        deleteStudent(first_name, last_name);
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
}while(choice!= -1);
    return 0;
}