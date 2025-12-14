#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int id;
    char name[40];
    char disease[40];
    int cabin;
    char phone[15];
    int age;
    struct node *next;
};

struct node *head = NULL;
int nextID = 1;

/* ---------- FUNCTION DECLARATIONS ---------- */
void loadFromFile();
void saveToFile();
void addPatient();
void displayPatients();
void searchPatient();
void editPatient();
void deletePatient();
void freeAll();

/* ---------- SAFE INPUT ---------- */
void readLine(char *buf, int size) {
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = 0;
}

/* ---------- MAIN ---------- */
int main() {
    int choice;
    loadFromFile();

    do {
        printf("\n\n===== HOSPITAL MANAGEMENT SYSTEM =====\n");
        printf("1. Add Patient\n");
        printf("2. View All Patients\n");
        printf("3. Search Patient\n");
        printf("4. Edit Patient\n");
        printf("5. Delete Patient\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addPatient(); break;
            case 2: displayPatients(); break;
            case 3: searchPatient(); break;
            case 4: editPatient(); break;
            case 5: deletePatient(); break;
            case 6:
                saveToFile();
                freeAll();
                printf("Data saved. Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}

/* ---------- ADD PATIENT ---------- */
void addPatient() {
    struct node *newNode = malloc(sizeof(struct node));

    newNode->id = nextID++;

    printf("Enter Name: ");
    readLine(newNode->name, 40);

    printf("Enter Disease: ");
    readLine(newNode->disease, 40);

    printf("Enter Cabin Number: ");
    scanf("%d", &newNode->cabin);

    printf("Enter Phone Number: ");
    scanf("%s", newNode->phone);

    printf("Enter Age: ");
    scanf("%d", &newNode->age);
    getchar();

    newNode->next = head;
    head = newNode;

    printf("Patient added successfully! (ID: %d)\n", newNode->id);
}

/* ---------- DISPLAY ---------- */
void displayPatients() {
    struct node *temp = head;

    if (!temp) {
        printf("No patient records found.\n");
        return;
    }

    while (temp) {
        printf("\n----------------------------------");
        printf("\nID      : %d", temp->id);
        printf("\nName    : %s", temp->name);
        printf("\nDisease : %s", temp->disease);
        printf("\nCabin   : %d", temp->cabin);
        printf("\nPhone   : %s", temp->phone);
        printf("\nAge     : %d", temp->age);
        printf("\n----------------------------------");
        temp = temp->next;
    }
}

/* ---------- SEARCH ---------- */
void searchPatient() {
    int id;
    printf("Enter Patient ID: ");
    scanf("%d", &id);

    struct node *temp = head;
    while (temp) {
        if (temp->id == id) {
            printf("\nPatient Found:\n");
            printf("Name: %s\nDisease: %s\nCabin: %d\nPhone: %s\nAge: %d\n",
                   temp->name, temp->disease, temp->cabin, temp->phone, temp->age);
            return;
        }
        temp = temp->next;
    }
    printf("Patient not found.\n");
}

/* ---------- EDIT ---------- */
void editPatient() {
    int id;
    printf("Enter Patient ID to edit: ");
    scanf("%d", &id);
    getchar();

    struct node *temp = head;
    while (temp) {
        if (temp->id == id) {
            printf("Enter New Name: ");
            readLine(temp->name, 40);

            printf("Enter New Disease: ");
            readLine(temp->disease, 40);

            printf("Enter New Cabin Number: ");
            scanf("%d", &temp->cabin);

            printf("Enter New Phone: ");
            scanf("%s", temp->phone);

            printf("Enter New Age: ");
            scanf("%d", &temp->age);
            getchar();

            printf("Patient updated successfully.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Patient ID not found.\n");
}

/* ---------- DELETE ---------- */
void deletePatient() {
    int id;
    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    struct node *temp = head, *prev = NULL;

    while (temp) {
        if (temp->id == id) {
            if (!prev)
                head = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            printf("Patient deleted successfully.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Patient not found.\n");
}

/* ---------- FILE HANDLING ---------- */
void saveToFile() {
    FILE *fp = fopen("patients.dat", "wb");
    struct node *temp = head;

    while (temp) {
        fwrite(temp, sizeof(struct node), 1, fp);
        temp = temp->next;
    }
    fclose(fp);
}

void loadFromFile() {
    FILE *fp = fopen("patients.dat", "rb");
    if (!fp) return;

    struct node tempNode;
    while (fread(&tempNode, sizeof(struct node), 1, fp)) {
        struct node *newNode = malloc(sizeof(struct node));
        *newNode = tempNode;
        newNode->next = head;
        head = newNode;

        if (newNode->id >= nextID)
            nextID = newNode->id + 1;
    }
    fclose(fp);
}

/* ---------- FREE MEMORY ---------- */
void freeAll() {
    struct node *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
