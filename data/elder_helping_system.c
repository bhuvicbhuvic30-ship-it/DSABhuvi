#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Elderly record
typedef struct Elder {
    int id;
    char name[50];
    int age;
    char address[100];
    char need[100];
    char contact[20];
    struct Elder *next;
} Elder;

Elder *head = NULL;
int nextID = 1000;

// Function prototypes
void addElder();
void displayElders();
void searchElder();
void updateElder();
void deleteElder();
void saveToFile();
void loadFromFile();

Elder* createElder(char name[], int age, char address[], char need[], char contact[]) {
    Elder *newNode = (Elder*)malloc(sizeof(Elder));
    newNode->id = nextID++;
    strcpy(newNode->name, name);
    newNode->age = age;
    strcpy(newNode->address, address);
    strcpy(newNode->need, need);
    strcpy(newNode->contact, contact);
    newNode->next = NULL;
    return newNode;
}

void addElder() {
    char name[50], address[100], need[100], contact[20];
    int age;
    printf("\nEnter Name: ");
    scanf(" %[^\n]", name);
    printf("Enter Age: ");
    scanf("%d", &age);
    printf("Enter Address: ");
    scanf(" %[^\n]", address);
    printf("Enter Type of Help Needed: ");
    scanf(" %[^\n]", need);
    printf("Enter Contact Number: ");
    scanf(" %[^\n]", contact);

    Elder *newElder = createElder(name, age, address, need, contact);

    if (head == NULL)
        head = newElder;
    else {
        Elder *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newElder;
    }
    printf("\n✅ Elder added successfully with ID %d!\n", newElder->id);
}

void displayElders() {
    if (head == NULL) {
        printf("\nNo records found.\n");
        return;
    }
    printf("\n--- List of Registered Elders ---\n");
    Elder *temp = head;
    while (temp != NULL) {
        printf("\nID: %d\nName: %s\nAge: %d\nAddress: %s\nNeed: %s\nContact: %s\n",
               temp->id, temp->name, temp->age, temp->address, temp->need, temp->contact);
        temp = temp->next;
    }
}

void searchElder() {
    int id;
    printf("\nEnter Elder ID to search: ");
    scanf("%d", &id);
    Elder *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("\nRecord Found:\nName: %s\nAge: %d\nAddress: %s\nNeed: %s\nContact: %s\n",
                   temp->name, temp->age, temp->address, temp->need, temp->contact);
            return;
        }
        temp = temp->next;
    }
    printf("\n❌ No record found for ID %d\n", id);
}

void updateElder() {
    int id;
    printf("\nEnter Elder ID to update: ");
    scanf("%d", &id);
    Elder *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Enter new Address: ");
            scanf(" %[^\n]", temp->address);
            printf("Enter new Need: ");
            scanf(" %[^\n]", temp->need);
            printf("Enter new Contact: ");
            scanf(" %[^\n]", temp->contact);
            printf("\n✅ Record updated successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("\n❌ No record found for ID %d\n", id);
}

void deleteElder() {
    int id;
    printf("\nEnter Elder ID to delete: ");
    scanf("%d", &id);
    Elder *temp = head, *prev = NULL;

    if (temp != NULL && temp->id == id) {
        head = temp->next;
        free(temp);
        printf("\n✅ Record deleted successfully.\n");
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\n❌ Record not found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("\n✅ Record deleted successfully.\n");
}

void saveToFile() {
    FILE *fp = fopen("elders_data.txt", "w");
    if (!fp) {
        printf("\nError saving data.\n");
        return;
    }
    Elder *temp = head;
    while (temp != NULL) {
        fprintf(fp, "%d|%s|%d|%s|%s|%s\n", temp->id, temp->name, temp->age, temp->address, temp->need, temp->contact);
        temp = temp->next;
    }
    fclose(fp);
    printf("\n💾 Data saved successfully.\n");
}

void loadFromFile() {
    FILE *fp = fopen("elders_data.txt", "r");
    if (!fp)
        return;

    char line[300];
    while (fgets(line, sizeof(line), fp)) {
        Elder *newElder = (Elder*)malloc(sizeof(Elder));
        sscanf(line, "%d|%[^|]|%d|%[^|]|%[^|]|%[^\n]", 
               &newElder->id, newElder->name, &newElder->age, newElder->address, newElder->need, newElder->contact);
        newElder->next = NULL;

        if (head == NULL)
            head = newElder;
        else {
            Elder *temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newElder;
        }

        if (newElder->id >= nextID)
            nextID = newElder->id + 1;
    }
    fclose(fp);
}

int main() {
    loadFromFile();
    int choice;
    printf("\n=== 🧓 Elderly Helping System ===\n");
    while (1) {
        printf("\n1. Add Elder\n2. View All\n3. Search\n4. Update\n5. Delete\n6. Save & Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addElder(); break;
            case 2: displayElders(); break;
            case 3: searchElder(); break;
            case 4: updateElder(); break;
            case 5: deleteElder(); break;
            case 6: saveToFile(); printf("\nThank you for using the system!\n"); exit(0);
            default: printf("\nInvalid choice!\n");
        }
    }
    return 0;
}
