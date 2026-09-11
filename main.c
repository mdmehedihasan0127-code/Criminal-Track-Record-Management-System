#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- File name constants ---------- */
#define LOGIN_FILE  "login.txt"
#define CASES_FILE  "cases.txt"
#define TEMP_FILE   "cases_tmp.dat"

/* ---------- Field size limits ---------- */
#define MAX_FIELD   100

/* ---------- Struct for one criminal case ---------- */
typedef struct {
    int  caseID;
    char caseTitle[MAX_FIELD];
    char victimName[MAX_FIELD];
    char suspectName[MAX_FIELD];
    int  suspectAge;
    char address[MAX_FIELD];
    char crimeType[MAX_FIELD];
    char location[MAX_FIELD];
    char fingerprintID[MAX_FIELD];
    char dnaID[MAX_FIELD];
    char hairColor[MAX_FIELD];
    char eyeColor[MAX_FIELD];
    char witnessName[MAX_FIELD];
    char witnessContact[MAX_FIELD];
    char status[MAX_FIELD];   /* "Open", "Closed", or "Pending" */
} CriminalCase;

void printLine() {
    printf("============================================================\n");
}

void printDash() {
    printf("------------------------------------------------------------\n");
}

void pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar();
}

void clearScreen() {
    system("cls");
}


int getValidInt(const char *prompt) {
    char buf[50];
    int  val;
    while (1) {
        printf("%s", prompt);
        if (fgets(buf, sizeof(buf), stdin) && sscanf(buf, "%d", &val) == 1)
            return val;
        printf("  [!] Please enter a valid number.\n");
    }
}


int getValidIntRange(const char *prompt, int min, int max) {
    int val;
    while (1) {
        val = getValidInt(prompt);
        if (val >= min && val <= max) return val;
        printf("  [!] Please enter a number between %d and %d.\n", min, max);
    }
}


void getString(const char *prompt, char *dest, int len) {
    while (1) {
        printf("%s", prompt);
        if (fgets(dest, len, stdin)) {
            dest[strcspn(dest, "\n")] = '\0';
            if (strlen(dest) > 0) return;
        }
        printf("  [!] Input cannot be empty. Please try again.\n");
    }
}

/*
 * validateStatus - converts numeric choice 1/2/3 to status string.
 * Returns 1 on success, 0 on invalid choice.
 */
int validateStatus(int choice, char *dest) {
    switch (choice) {
        case 1: strncpy(dest, "Open",    MAX_FIELD - 1); dest[MAX_FIELD-1]='\0'; return 1;
        case 2: strncpy(dest, "Closed",  MAX_FIELD - 1); dest[MAX_FIELD-1]='\0'; return 1;
        case 3: strncpy(dest, "Pending", MAX_FIELD - 1); dest[MAX_FIELD-1]='\0'; return 1;
        default: return 0;
    }
}


void selectStatus(char *dest) {
    printf("\n  Status Options:\n");
    printf("    [1] Open\n");
    printf("    [2] Closed\n");
    printf("    [3] Pending\n");
    while (1) {
        int choice = getValidInt("  Select Status (1-3): ");
        if (validateStatus(choice, dest)) return;
        printf("  [!] Please select 1, 2, or 3.\n");
    }
}


void selectStatusUpdate(char *dest) {
    char buf[20];
    printf("\n  Status Options:\n");
    printf("    [1] Open\n");
    printf("    [2] Closed\n");
    printf("    [3] Pending\n");
    printf("    (Press Enter to keep current: %s)\n", dest);
    printf("  Select Status (1-3) or Enter to skip: ");

    if (fgets(buf, sizeof(buf), stdin)) {
        buf[strcspn(buf, "\n")] = '\0';
        if (strlen(buf) == 0) return; /* keep existing */
        int choice = atoi(buf);
        if (validateStatus(choice, dest)) return;
        printf("  [!] Invalid choice. Keeping current status: %s\n", dest);
    }
}
int writeCase(FILE *fp, const CriminalCase *c) {
    return fprintf(fp,
        "%d|%s|%s|%s|%d|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n",
        c->caseID,
        c->caseTitle,
        c->victimName,
        c->suspectName,
        c->suspectAge,
        c->address,
        c->crimeType,
        c->location,
        c->fingerprintID,
        c->dnaID,
        c->hairColor,
        c->eyeColor,
        c->witnessName,
        c->witnessContact,
        c->status
    ) > 0;
}
int readCase(FILE *fp, CriminalCase *c) {
    char line[1600];

    if (fgets(line, sizeof(line), fp) == NULL)
        return 0;

    line[strcspn(line, "\n")] = '\0';

    char *token;

    token = strtok(line, "|");
    if (token == NULL) return 0;
    c->caseID = atoi(token);

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strncpy(c->caseTitle, token, MAX_FIELD - 1);
    c->caseTitle[MAX_FIELD - 1] = '\0';

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strncpy(c->victimName, token, MAX_FIELD - 1);
    c->victimName[MAX_FIELD - 1] = '\0';

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strncpy(c->suspectName, token, MAX_FIELD - 1);
    c->suspectName[MAX_FIELD - 1] = '\0';

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    c->suspectAge = atoi(token);

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strncpy(c->address, token, MAX_FIELD - 1);
    c->address[MAX_FIELD - 1] = '\0';

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strncpy(c->crimeType, token, MAX_FIELD - 1);
    c->crimeType[MAX_FIELD - 1] = '\0';

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strncpy(c->location, token, MAX_FIELD - 1);
    c->location[MAX_FIELD - 1] = '\0';

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strncpy(c->fingerprintID, token, MAX_FIELD - 1);
    c->fingerprintID[MAX_FIELD - 1] = '\0';

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strncpy(c->dnaID, token, MAX_FIELD - 1);
    c->dnaID[MAX_FIELD - 1] = '\0';

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strncpy(c->hairColor, token, MAX_FIELD - 1);
    c->hairColor[MAX_FIELD - 1] = '\0';

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strncpy(c->eyeColor, token, MAX_FIELD - 1);
    c->eyeColor[MAX_FIELD - 1] = '\0';

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strncpy(c->witnessName, token, MAX_FIELD - 1);
    c->witnessName[MAX_FIELD - 1] = '\0';

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strncpy(c->witnessContact, token, MAX_FIELD - 1);
    c->witnessContact[MAX_FIELD - 1] = '\0';

    token = strtok(NULL, "|");
    if (token == NULL) return 0;
    strncpy(c->status, token, MAX_FIELD - 1);
    c->status[MAX_FIELD - 1] = '\0';

    return 1;
}
int getNextCaseID() {
    FILE *fp = fopen(CASES_FILE, "r");

    if (fp == NULL)
        return 1001;

    CriminalCase c;
    int maxID = 1000;

    while (readCase(fp, &c)) {
        if (c.caseID > maxID)
            maxID = c.caseID;
    }

    fclose(fp);

    return maxID + 1;
}
void printCaseDetailed(const CriminalCase *c) {
    printLine();
    printf("  CASE #%d\n", c->caseID);
    printLine();

    /* Section 1: Case & Person Information */
    printf("  CASE & PERSON INFORMATION\n");
    printDash();
    printf("  Case ID             : %d\n",  c->caseID);
    printf("  Case Title          : %s\n",  c->caseTitle);
    printf("  Victim Name         : %s\n",  c->victimName);
    printf("  Suspect Name        : %s\n",  c->suspectName);
    printf("  Suspect Age         : %d\n",  c->suspectAge);
    printf("  Residential Address : %s\n",  c->address);
    printf("\n");

    /* Section 2: Crime Information */
    printf("  CRIME INFORMATION\n");
    printDash();
    printf("  Crime Type          : %s\n",  c->crimeType);
    printf("  Location            : %s\n",  c->location);
    printf("  Status              : %s\n",  c->status);
    printf("\n");

    /* Section 3: Investigation & Evidence */
    printf("  INVESTIGATION & EVIDENCE INFORMATION\n");
    printDash();
    printf("  Fingerprint ID      : %s\n",  c->fingerprintID);
    printf("  DNA Profile ID      : %s\n",  c->dnaID);
    printf("  Hair Color          : %s\n",  c->hairColor);
    printf("  Eye Color           : %s\n",  c->eyeColor);
    printf("\n");

    /* Section 4: Witness Information */
    printf("  WITNESS INFORMATION\n");
    printDash();
    printf("  Witness Name        : %s\n",  c->witnessName);
    printf("  Witness Contact     : %s\n",  c->witnessContact);
    printf("\n");

    printf("                  END OF CASE #%d\n", c->caseID);
    printLine();
}


/* ============================================================
 *  LOGIN SYSTEM
 * ============================================================ */

int readCredentials(char *storedUser, char *storedPass) {
    FILE *fp = fopen(LOGIN_FILE, "r");
    if (fp == NULL) {
        printf("\n  [ERROR] '%s' not found. Cannot load credentials.\n", LOGIN_FILE);
        printf("  Please create '%s' with format:  username|password\n", LOGIN_FILE);
        return 0;
    }

    char line_buf[200];
    if (fgets(line_buf, sizeof(line_buf), fp) == NULL) {
        printf("\n  [ERROR] '%s' is empty or unreadable.\n", LOGIN_FILE);
        fclose(fp);
        return 0;
    }
    fclose(fp);

    line_buf[strcspn(line_buf, "\n")] = '\0';

    char *pipe_pos = strchr(line_buf, '|');
    if (pipe_pos == NULL) {
        printf("\n  [ERROR] '%s' has wrong format. Expected: username|password\n", LOGIN_FILE);
        return 0;
    }

    int userLen = (int)(pipe_pos - line_buf);
    strncpy(storedUser, line_buf, userLen);
    storedUser[userLen] = '\0';
    strncpy(storedPass, pipe_pos + 1, MAX_FIELD - 1);
    storedPass[MAX_FIELD - 1] = '\0';

    return 1;
}

int login() {
    char storedUser[MAX_FIELD];
    char storedPass[MAX_FIELD];

    if (!readCredentials(storedUser, storedPass)) {
        pauseScreen();
        return 0;
    }

    char inputUser[MAX_FIELD];
    char inputPass[MAX_FIELD];
    int  attemptsLeft = 3;

    while (attemptsLeft > 0) {
        clearScreen();
        printLine();
        printf("                    ADMIN LOGIN\n");
        printLine();
        printf("\n");

        printf("  Username : ");
        fgets(inputUser, sizeof(inputUser), stdin);
        inputUser[strcspn(inputUser, "\n")] = '\0';

        printf("  Password : ");
        fgets(inputPass, sizeof(inputPass), stdin);
        inputPass[strcspn(inputPass, "\n")] = '\0';

        if (strcmp(inputUser, storedUser) == 0 &&
            strcmp(inputPass, storedPass) == 0) {
            printf("\n  [SUCCESS] Login successful! Welcome, %s.\n", storedUser);
            pauseScreen();
            return 1;
        }

        attemptsLeft--;
        if (attemptsLeft > 0)
            printf("\n  [FAILED] Invalid credentials! %d attempt(s) remaining.\n", attemptsLeft);
        else
            printf("\n  [FAILED] Invalid credentials! No attempts remaining.\n");
        pauseScreen();
    }

    return 0;
}


/* ============================================================
 *  FEATURE 1: ADD NEW CASE RECORD
 * ============================================================ */
void addCase() {
    clearScreen();
    printLine();
    printf("                ADD NEW CASE RECORD\n");
    printLine();

    CriminalCase c;
    memset(&c, 0, sizeof(CriminalCase));

    c.caseID = getNextCaseID();
    printf("\n  Auto-generated Case ID: %d\n", c.caseID);

    /* ---- SECTION 1: Case & Person Information ---- */
    printf("\n");
    printLine();
    printf("  CASE & PERSON INFORMATION\n");
    printDash();

    getString("  Case Title          : ", c.caseTitle,   MAX_FIELD);
    getString("  Victim Name         : ", c.victimName,  MAX_FIELD);
    getString("  Suspect Name        : ", c.suspectName, MAX_FIELD);

    /* Age must be a positive integer */
    while (1) {
        c.suspectAge = getValidInt("  Suspect Age         : ");
        if (c.suspectAge > 0) break;
        printf("  [!] Age must be a positive number.\n");
    }

    getString("  Residential Address : ", c.address,    MAX_FIELD);
    getString("  Crime Type          : ", c.crimeType,  MAX_FIELD);
    getString("  Location            : ", c.location,   MAX_FIELD);

    /* ---- SECTION 2: Investigation & Evidence Information ---- */
    printf("\n");
    printLine();
    printf("  INVESTIGATION & EVIDENCE INFORMATION\n");
    printDash();

    getString("  Fingerprint ID      : ", c.fingerprintID,  MAX_FIELD);
    getString("  DNA Profile ID      : ", c.dnaID,          MAX_FIELD);
    getString("  Hair Color          : ", c.hairColor,      MAX_FIELD);
    getString("  Eye Color           : ", c.eyeColor,       MAX_FIELD);
    getString("  Witness Name        : ", c.witnessName,    MAX_FIELD);
    getString("  Witness Contact     : ", c.witnessContact, MAX_FIELD);

    /* Numbered status selection (1=Open, 2=Closed, 3=Pending) */
    selectStatus(c.status);

    /* Open binary file in append mode and write struct using fwrite() */
    FILE *fp = fopen(CASES_FILE, "a");
    if (fp == NULL) {
        printf("\n  [ERROR] Cannot open '%s' for writing.\n", CASES_FILE);
        pauseScreen();
        return;
    }

    if (!writeCase(fp, &c)) {
        printf("\n  [ERROR] Failed to write case record to file.\n");
        fclose(fp);
        pauseScreen();
        return;
    }
    fclose(fp);

    printf("\n  [SUCCESS] Case #%d added and saved successfully.\n", c.caseID);
    pauseScreen();
}


/* ============================================================
 *  FEATURE 2: VIEW ALL CASE RECORDS
 * ============================================================ */
void viewCases() {
    clearScreen();
    printLine();
    printf("               VIEW ALL CASE RECORDS\n");
    printLine();

    FILE *fp = fopen(CASES_FILE, "r");
    if (fp == NULL) {
        printf("\n  [INFO] No records found. '%s' does not exist yet.\n", CASES_FILE);
        pauseScreen();
        return;
    }

    CriminalCase c;
    int count = 0;

    printf("\n");

    /* Read each binary struct using fread() and display as a full block */
    while (readCase(fp, &c)) {
        count++;
        printCaseDetailed(&c);
        printf("\n");
    }
    fclose(fp);

    if (count == 0)
        printf("  [INFO] No records found in '%s'.\n", CASES_FILE);
    else
        printf("  Total Records Found: %d\n", count);

    pauseScreen();
}


/* ============================================================
 *  FEATURE 3: SEARCH CASE BY ID
 *  - Reads records using fread() via readCase()
 *  - Result displayed in four labelled sections
 * ============================================================ */
void searchCase() {
    clearScreen();
    printLine();
    printf("               SEARCH CASE BY ID\n");
    printLine();

    int searchID = getValidInt("\n  Enter Case ID to search: ");

   FILE *fp = fopen(CASES_FILE, "r");
    if (fp == NULL) {
        printf("\n  [INFO] '%s' not found. No records exist yet.\n", CASES_FILE);
        pauseScreen();
        return;
    }

    CriminalCase c;
    int found = 0;

    /* Scan binary records using fread() until matching ID found */
    while (readCase(fp, &c)) {
        if (c.caseID == searchID) {
            printf("\n  [FOUND] Case record:\n\n");
            printCaseDetailed(&c);
            found = 1;
            break; /* IDs are unique - stop after first match */
        }
    }
    fclose(fp);

    if (!found)
        printf("\n  [NOT FOUND] No case with ID %d exists.\n", searchID);

    pauseScreen();
}


/* ============================================================
 *  FEATURE 4: UPDATE CASE RECORD
 * ============================================================ */
void updateCase() {
    clearScreen();
    printLine();
    printf("               UPDATE CASE RECORD\n");
    printLine();

    int updateID = getValidInt("\n  Enter Case ID to update: ");

    FILE *src = fopen(CASES_FILE, "r");

    if (src == NULL) {
        printf("\n  [ERROR] '%s' not found. No records to update.\n", CASES_FILE);
        pauseScreen();
        return;
    }

    FILE *tmp = fopen(TEMP_FILE, "w");
    if (tmp == NULL) {
        printf("\n  [ERROR] Cannot create temporary file '%s'.\n", TEMP_FILE);
        fclose(src);
        pauseScreen();
        return;
    }

    CriminalCase c;
    char input[MAX_FIELD];
    int found = 0;

    /* Read each binary record using fread() */
    while (readCase(src, &c)) {

        if (c.caseID == updateID) {
            found = 1;

            /* Show current record before editing */
            printf("\n");
            printLine();
            printf("  CURRENT CASE INFORMATION\n");
            printLine();
            printCaseDetailed(&c);

            printf("\n  Enter new values below.\n");
            printf("  Press ENTER to keep the current value.\n");

            /* ---- SECTION 1: Case & Person Information ---- */
            printf("\n");
            printLine();
            printf("  CASE & PERSON INFORMATION\n");
            printDash();

            printf("  Case Title          [%s]: ", c.caseTitle);
            fgets(input, MAX_FIELD, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strncpy(c.caseTitle, input, MAX_FIELD - 1);

            printf("  Victim Name         [%s]: ", c.victimName);
            fgets(input, MAX_FIELD, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strncpy(c.victimName, input, MAX_FIELD - 1);

            printf("  Suspect Name        [%s]: ", c.suspectName);
            fgets(input, MAX_FIELD, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strncpy(c.suspectName, input, MAX_FIELD - 1);

            /* Age - validate if user enters something new */
            while (1) {
                printf("  Suspect Age         [%d]: ", c.suspectAge);
                fgets(input, MAX_FIELD, stdin);
                input[strcspn(input, "\n")] = '\0';
                if (strlen(input) == 0) break; /* keep current */
                int newAge = atoi(input);
                if (newAge > 0) { c.suspectAge = newAge; break; }
                printf("  [!] Age must be a positive number.\n");
            }

            printf("  Residential Address [%s]: ", c.address);
            fgets(input, MAX_FIELD, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strncpy(c.address, input, MAX_FIELD - 1);

            printf("  Crime Type          [%s]: ", c.crimeType);
            fgets(input, MAX_FIELD, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strncpy(c.crimeType, input, MAX_FIELD - 1);

            printf("  Location            [%s]: ", c.location);
            fgets(input, MAX_FIELD, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strncpy(c.location, input, MAX_FIELD - 1);

            /* ---- SECTION 2: Investigation & Evidence ---- */
            printf("\n");
            printLine();
            printf("  INVESTIGATION & EVIDENCE INFORMATION\n");
            printDash();

            printf("  Fingerprint ID      [%s]: ", c.fingerprintID);
            fgets(input, MAX_FIELD, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strncpy(c.fingerprintID, input, MAX_FIELD - 1);

            printf("  DNA Profile ID      [%s]: ", c.dnaID);
            fgets(input, MAX_FIELD, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strncpy(c.dnaID, input, MAX_FIELD - 1);

            printf("  Hair Color          [%s]: ", c.hairColor);
            fgets(input, MAX_FIELD, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strncpy(c.hairColor, input, MAX_FIELD - 1);

            printf("  Eye Color           [%s]: ", c.eyeColor);
            fgets(input, MAX_FIELD, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strncpy(c.eyeColor, input, MAX_FIELD - 1);

            printf("  Witness Name        [%s]: ", c.witnessName);
            fgets(input, MAX_FIELD, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strncpy(c.witnessName, input, MAX_FIELD - 1);

            printf("  Witness Contact     [%s]: ", c.witnessContact);
            fgets(input, MAX_FIELD, stdin);
            input[strcspn(input, "\n")] = '\0';
            if (strlen(input) > 0) strncpy(c.witnessContact, input, MAX_FIELD - 1);

            /* Status update with numbered menu or Enter to keep */
            selectStatusUpdate(c.status);
        }

        /* Write this record (original or updated) to temp file using fwrite() */
        writeCase(tmp, &c);
    }

    fclose(src);
    fclose(tmp);

    if (!found) {
        printf("\n  [NOT FOUND] No case with ID %d exists.\n", updateID);
        remove(TEMP_FILE);
        pauseScreen();
        return;
    }

    /* Replace cases.dat with temp file */
    if (remove(CASES_FILE) != 0) {
        printf("\n  [ERROR] Could not remove old '%s'.\n", CASES_FILE);
        pauseScreen();
        return;
    }
    if (rename(TEMP_FILE, CASES_FILE) != 0) {
        printf("\n  [ERROR] Could not rename temp file to '%s'.\n", CASES_FILE);
        pauseScreen();
        return;
    }

    printf("\n  [SUCCESS] Case #%d updated successfully.\n", updateID);
    pauseScreen();
}


/* ============================================================
 *  FEATURE 5: DELETE CASE RECORD
 *  - First pass: confirm record exists using fread()
 *  - Second pass: copy all records except target using fwrite()
 *  - Confirms before deleting; replaces file atomically
 * ============================================================ */
void deleteCase() {
    clearScreen();
    printLine();
    printf("               DELETE CASE RECORD\n");
    printLine();

    int deleteID = getValidInt("\n  Enter Case ID to delete: ");

    /* First pass: confirm the record exists */
    FILE *check = fopen(CASES_FILE, "r");
    if (check == NULL) {
        printf("\n  [ERROR] '%s' not found. No records to delete.\n", CASES_FILE);
        pauseScreen();
        return;
    }

    CriminalCase c;
    int found = 0;

    while (readCase(check, &c)) {
        if (c.caseID == deleteID) {
            found = 1;
            printf("\n  Record to be deleted:\n\n");
            printCaseDetailed(&c);
            break;
        }
    }
    fclose(check);

    if (!found) {
        printf("\n  [NOT FOUND] No case with ID %d exists.\n", deleteID);
        pauseScreen();
        return;
    }

    /* Confirm before deleting */
    char confirm[10];
    getString("\n  Are you sure you want to delete this record? (yes/no): ",
              confirm, sizeof(confirm));
    if (strcmp(confirm, "yes") != 0) {
        printf("\n  [CANCELLED] Deletion cancelled.\n");
        pauseScreen();
        return;
    }


   FILE *src = fopen(CASES_FILE, "r");
   FILE *tmp = fopen(TEMP_FILE, "w");
    if (src == NULL || tmp == NULL) {
        printf("\n  [ERROR] File operation failed during delete.\n");
        if (src) fclose(src);
        if (tmp) fclose(tmp);
        pauseScreen();
        return;
    }

    /* Read each record with fread(); write all except target with fwrite() */
    while (readCase(src, &c)) {
        if (c.caseID == deleteID) continue; /* skip deleted record */
        writeCase(tmp, &c);
    }

    fclose(src);
    fclose(tmp);

    if (remove(CASES_FILE) != 0 || rename(TEMP_FILE, CASES_FILE) != 0) {
        printf("\n  [ERROR] Could not replace '%s'. Check file permissions.\n", CASES_FILE);
        pauseScreen();
        return;
    }

    printf("\n  [SUCCESS] Case #%d deleted successfully.\n", deleteID);
    pauseScreen();
}


/* ============================================================
 *  FEATURE 6: CASE STATUS REPORT
 * ============================================================ */
void caseStatusReport() {
    clearScreen();
    printLine();
    printf("               CASE STATUS REPORT\n");
    printLine();

    FILE *fp = fopen(CASES_FILE, "r");
    if (fp == NULL) {
        printf("\n  [INFO] No case records found.\n");
        pauseScreen();
        return;
    }

    CriminalCase c;
    int total = 0, openCount = 0, closedCount = 0, pendingCount = 0;

    /* Read each binary record using fread() */
    while (readCase(fp, &c)) {
        total++;
        if      (strcmp(c.status, "Open")    == 0) openCount++;
        else if (strcmp(c.status, "Closed")  == 0) closedCount++;
        else if (strcmp(c.status, "Pending") == 0) pendingCount++;
    }
    fclose(fp);

    printf("\n");
    printDash();
    printf("  Total Cases    : %d\n", total);
    printDash();
    printf("  Open Cases     : %d\n", openCount);
    printf("  Closed Cases   : %d\n", closedCount);
    printf("  Pending Cases  : %d\n", pendingCount);
    printDash();
    printf("\n");

    pauseScreen();
}


/* ============================================================
 *  MAIN MENU
 * ============================================================ */
void menu() {
    int choice;
    do {
        clearScreen();
        printLine();
        printf("          CRIMINAL TRACK RECORD SYSTEM\n");
        printf("     Bangladesh University of Business & Technology\n");
        printLine();
        printf("\n");
        printf("  [1]  Add New Case Record\n");
        printf("  [2]  View All Case Records\n");
        printf("  [3]  Search Case by ID\n");
        printf("  [4]  Update Case Record\n");
        printf("  [5]  Delete Case Record\n");
        printf("  [6]  Case Status Report\n");
        printf("  [0]  Logout\n");
        printf("\n");
        printDash();

        choice = getValidIntRange("  Select option (0-6): ", 0, 6);

        switch (choice) {
            case 1: addCase();          break;
            case 2: viewCases();        break;
            case 3: searchCase();       break;
            case 4: updateCase();       break;
            case 5: deleteCase();       break;
            case 6: caseStatusReport(); break;
            case 0:
                printf("\n  Logging out... Goodbye.\n");
                pauseScreen();
                break;
        }
    } while (choice != 0);
}


/* ============================================================
 *  MAIN ENTRY POINT
 * ============================================================ */
int main() {
    while (1) {
        if (!login()) {
            clearScreen();
            printLine();
            printf("  Too many failed login attempts. Program terminated.\n");
            printLine();
            return 1;
        }
        menu();
    }
    return 0;
}
