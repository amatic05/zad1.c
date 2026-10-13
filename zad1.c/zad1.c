
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Student {
    char name[30];
    char lastname[30];
    int points;
} Student;

int main(void) {

    FILE* fp = fopen("studenti.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char buffer[50] = { 0 };
    int br = 0;

    // Brojanje redaka, odnosno studenata
    while (fgets(buffer, 50, fp) != NULL) {
        br++;
    }

    printf("Broj studenata: %d\n", br);

    // Provjera ima li studenata
    if (br == 0) {
        printf("Datoteka je prazna!\n");
        fclose(fp);
        return 1;
    }

    // Dinamicka alokacija memorije
    Student* students = malloc(br * sizeof(Student));

    if (students == NULL) {
        printf("Greska pri alokaciji memorije\n");
        fclose(fp);
        return 1;
    }

    // Povratak na pocetak datoteke
    rewind(fp);

    // Ucitavanje podataka u niz struktura
    for (int i = 0; i < br; i++) {
        if (fscanf(fp, "%29s %29s %d",
            students[i].name,
            students[i].lastname,
            &students[i].points) != 3) {

            printf("Greska pri citanju datoteke\n");
            free(students);
            fclose(fp);
            return 1;
        }
    }

    // Pronalaženje maksimalnog broja bodova
    int maxPoints = students[0].points;

    for (int i = 1; i < br; i++) {
        if (students[i].points > maxPoints) {
            maxPoints = students[i].points;
        }
    }

    // Ispis studenata i relativnih bodova
    printf("\nIme\tPrezime\tBodovi\tRelativni bodovi\n");

    for (int i = 0; i < br; i++) {

        float relativepoints = 0;

        if (maxPoints > 0) {
            relativepoints =
                (float)students[i].points / maxPoints * 100;
        }

        printf("%s\t%s\t%d\t%.2f%%\n",
            students[i].name,
            students[i].lastname,
            students[i].points,
            relativepoints);
    }

    // Oslobadanje memorije i zatvaranje datoteke
    free(students);
    fclose(fp);

    return 0;
}
