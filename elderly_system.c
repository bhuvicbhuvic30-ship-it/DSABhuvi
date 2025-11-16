/*
 Elderly Helping System (Linked List implementation in C)
 - Add, display, search, edit, delete elderly records
 - Save/load records to/from a file for persistence
 - Uses dynamic memory and safe string handling
Compile:
    gcc elderly_system.c -o elderly_system
Run:
    ./elderly_system
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME 50
#define MAX_ADDR 120
#define MAX_NEED 100
#define MAX_CONTACT 30
#define DATA_FILE "elderly_data.txt"

typedef struct Elder {
    int id;
    char name[MAX_NAME];
    int age;
    char address[MAX_ADDR];
    char need[MAX_NEED];
    char contact[MAX_CONTACT];
    struct Elder *next;
} Elder;

Elder *head = NULL;
int nextID = 1000;

/* ---------- Utility functions ---------- */

void strip_newline(char *s) {
    size_t n = strlen(s);
    if (n == 0) return;
    if (s[n-1] == '\n') s[n-1] = '\0';
}

/* Read a line from stdin into buffer (safe) */
void read_line(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    strip_newline(buffer);
}

/* Convert string to lowercase for case-insensitive comparisons */
void str_to_lower(char *out, const char *in) {
    size_t i;
    for (i = 0; in[i] && i < strlen(in); ++i) out[i] = (char)tolower((unsigned char)in[i]);
    out[i] = '\0';
}

/* ---------- Linked list operations ---------- */

Elder* create_elder_node(const char *name, int age, const char *address, const char *need, const char *contact) {
    Elder *p = (Elder*)malloc(sizeof(Elder));
    if (!p) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    p->id = nextID++;
    strncpy(p->name, name, MAX_NAME-1); p->name[MAX_NAME-1] = '\0';
    p->age = age;
    strncpy(p->address, address, MAX_ADDR-1); p->address[MAX_ADDR-1] = '\0';
    strncpy(p->need, need, MAX_NEED-1); p->need[MAX_NEED-1] = '\0';
    strncpy(p->contact, contact, MAX_CONTACT-1); p->contact[MAX_CONTACT-1] = '\0';
    p->next = NULL;
    return p;
}

void add_elder() {
    char name[MAX_NAME], address[MAX_ADDR], need[MAX_NEED], contact[MAX_CONTACT];
    char age_str[10];
    int age = 0;

    printf("\n--- Add New Elderly Record ---\n");
    read_line("Name: ", name, sizeof(name));
    read_line("Age: ", age_str, sizeof(age_str));
    age = atoi(age_str);
    read_line("Address: ", address, sizeof(address));
    read_line("Need / Remarks: ", need, sizeof(need));
    read_line("Contact (phone): ", contact, sizeof(contact));

    Elder *node = create_elder_node(name, age, address, need, contact);
    /* Insert at head for simplicity */
    node->next = head;
    head = node;

    printf("Record added with ID: %d\n\n", node->id);
}

void display_elder(const Elder *e) {
    if (!e) return;
    printf("ID: %d\n", e->id);
    printf("Name: %s\n", e->name);
    printf("Age: %d\n", e->age);
    printf("Address: %s\n", e->address);
    printf("Need/Remarks: %s\n", e->need);
    printf("Contact: %s\n", e->contact);
    printf("------------------------------------\n");
}

void display_all() {
    if (!head) {
        printf("\nNo records found.\n\n");
        return;
    }
    printf("\n--- All Elderly Records ---\n");
    Elder *cur = head;
    while (cur) {
        display_elder(cur);
        cur = cur->next;
    }
    printf("\n");
}

Elder* find_by_id(int id) {
    Elder *cur = head;
    while (cur) {
        if (cur->id == id) return cur;
        cur = cur->next;
    }
    return NULL;
}

void search_by_id() {
    char idstr[16];
    read_line("\nEnter ID to search: ", idstr, sizeof(idstr));
    int id = atoi(idstr);
    Elder *res = find_by_id(id);
    if (res) {
        printf("\nRecord found:\n");
        display_elder(res);
    } else {
        printf("\nNo record with ID %d found.\n", id);
    }
}

void search_by_name() {
    char q[MAX_NAME], qlow[MAX_NAME], tmp_low[MAX_NAME];
    read_line("\nEnter name (or part of it) to search: ", q, sizeof(q));
    if (strlen(q) == 0) {
        printf("Empty query.\n");
        return;
    }
    str_to_lower(qlow, q);

    Elder *cur = head;
    int found = 0;
    printf("\nSearch results:\n");
    while (cur) {
        str_to_lower(tmp_low, cur->name);
        if (strstr(tmp_low, qlow)) {
            display_elder(cur);
            found++;
        }
        cur = cur->next;
    }
    if (!found) printf("No records match '%s'.\n", q);
}

void edit_elder() {
    char idstr[16];
    read_line("\nEnter ID to edit: ", idstr, sizeof(idstr));
    int id = atoi(idstr);
    Elder *e = find_by_id(id);
    if (!e) {
        printf("No record with ID %d.\n", id);
        return;
    }

    printf("\nEditing record (leave blank to keep current value)\n");
    char tmp[MAX_ADDR];
    printf("Current name: %s\n", e->name);
    read_line("New name: ", tmp, sizeof(tmp));
    if (strlen(tmp) > 0) strncpy(e->name, tmp, MAX_NAME-1);

    printf("Current age: %d\n", e->age);
    read_line("New age: ", tmp, sizeof(tmp));
    if (strlen(tmp) > 0) e->age = atoi(tmp);

    printf("Current address: %s\n", e->address);
    read_line("New address: ", tmp, sizeof(tmp));
    if (strlen(tmp) > 0) strncpy(e->address, tmp, MAX_ADDR-1);

    printf("Current need: %s\n", e->need);
    read_line("New need: ", tmp, sizeof(tmp));
    if (strlen(tmp) > 0) strncpy(e->need, tmp, MAX_NEED-1);

    printf("Current contact: %s\n", e->contact);
    read_line("New contact: ", tmp, sizeof(tmp));
    if (strlen(tmp) > 0) strncpy(e->contact, tmp, MAX_CONTACT-1);

    printf("Record updated.\n");
}

void delete_elder() {
    char idstr[16];
    read_line("\nEnter ID to delete: ", idstr, sizeof(idstr));
    int id = atoi(idstr);
    Elder *cur = head, *prev = NULL;
    while (cur) {
        if (cur->id == id) {
            if (prev) prev->next = cur->next;
            else head = cur->next;
            free(cur);
            printf("Record with ID %d deleted.\n", id);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("No record with ID %d found.\n", id);
}

/* ---------- File persistence ---------- */

void save_to_file() {
    FILE *fp = fopen(DATA_FILE, "w");
    if (!fp) {
        perror("Error opening file for writing");
        return;
    }
    /* First line stores nextID to preserve continuity */
    fprintf(fp, "%d\n", nextID);
    Elder *cur = head;
    while (cur) {
        /* Use a simple pipe-separated format; escape pipes not handled (keep data simple) */
        fprintf(fp, "%d|%s|%d|%s|%s|%s\n",
                cur->id,
                cur->name,
                cur->age,
                cur->address,
                cur->need,
                cur->contact);
        cur = cur->next;
    }
    fclose(fp);
    printf("Data saved to '%s'.\n", DATA_FILE);
}

void free_list() {
    Elder *cur = head;
    while (cur) {
        Elder *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    head = NULL;
}

/* Load file; replaces current list */
void load_from_file() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        /* No file yet is not an error */
        // perror("Warning: could not open data file for reading");
        printf("No saved data file found ('%s'). Starting fresh.\n", DATA_FILE);
        return;
    }
    free_list();

    char line[1024];
    if (fgets(line, sizeof(line), fp) != NULL) {
        /* first line should be nextID */
        nextID = atoi(line);
        if (nextID <= 0) nextID = 1000;
    }

    while (fgets(line, sizeof(line), fp)) {
        strip_newline(line);
        if (strlen(line) == 0) continue;
        /* expected format: id|name|age|address|need|contact */
        char *parts[6];
        char *p = strtok(line, "|");
        int idx = 0;
        while (p && idx < 6) {
            parts[idx++] = p;
            p = strtok(NULL, "|");
        }
        if (idx == 6) {
            Elder *node = (Elder*)malloc(sizeof(Elder));
            if (!node) { fprintf(stderr, "Memory error\n"); break; }
            node->id = atoi(parts[0]);
            strncpy(node->name, parts[1], MAX_NAME-1); node->name[MAX_NAME-1] = '\0';
            node->age = atoi(parts[2]);
            strncpy(node->address, parts[3], MAX_ADDR-1); node->address[MAX_ADDR-1] = '\0';
            strncpy(node->need, parts[4], MAX_NEED-1); node->need[MAX_NEED-1] = '\0';
            strncpy(node->contact, parts[5], MAX_CONTACT-1); node->contact[MAX_CONTACT-1] = '\0';
            node->next = head;
            head = node;
        }
    }
    fclose(fp);
    printf("Data loaded from '%s'.\n", DATA_FILE);
}

/* ---------- Menu & main ---------- */

void print_menu() {
    printf("\n====== Elderly Helping System ======\n");
    printf("1. Add new elderly record\n");
    printf("2. Display all records\n");
    printf("3. Search by ID\n");
    printf("4. Search by name\n");
    printf("5. Edit a record\n");
    printf("6. Delete a record\n");
    printf("7. Save to file\n");
    printf("8. Load from file\n");
    printf("9. Exit\n");
    printf("Choose an option (1-9): ");
}

int main() {
    char choice[8];
    /* Attempt to load existing data on startup */
    load_from_file();

    while (1) {
        print_menu();
        if (fgets(choice, sizeof(choice), stdin) == NULL) {
            printf("\nInput error. Exiting.\n");
            break;
        }
        int opt = atoi(choice);
        switch (opt) {
            case 1: add_elder(); break;
            case 2: display_all(); break;
            case 3: search_by_id(); break;
            case 4: search_by_name(); break;
            case 5: edit_elder(); break;
            case 6: delete_elder(); break;
            case 7: save_to_file(); break;
            case 8: load_from_file(); break;
            case 9:
                printf("Do you want to save before exit? (y/n): ");
                if (fgets(choice, sizeof(choice), stdin)) {
                    if (choice[0] == 'y' || choice[0] == 'Y') save_to_file();
                }
                free_list();
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid option. Please choose 1..9\n");
        }
    }

    free_list();
    return 0;
}
