#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_WORKS 1000  // ������������ ���������� �����
#define BUFFER_SIZE 256 // ������ ������ ��� �����

// ����������� ��������� ��� �������� �����
struct kursovie_raboti {
    char nazvanie_raboti[50];  // �������� ������
    char avtor[50];            // �����
    char opisanie[200];        // ��������
    char srok_sdachi[20];      // ���� �����
    int balli;                 // �����
};

typedef struct kursovie_raboti kursovaya_rabota_t;

// ��������� �������
void Vvod_file(kursovaya_rabota_t* db, int* size, const char* filename);
void Vivod(kursovaya_rabota_t* db, int size);
void Sortirovka_balli(kursovaya_rabota_t* db, int size);
void Vivod_file(kursovaya_rabota_t* db, int size, const char* filename);
void Dobavit_zapis(kursovaya_rabota_t* db, int* size);
void Izmenit_zapis(kursovaya_rabota_t* db, int size);
void Poisk_po_teme(kursovaya_rabota_t* db, int size, const char* tema);
char* Trim_space(char* str);
void Pokazat_menu();

// ������� �������
int main() {
    setlocale(LC_ALL, "RUS");
    kursovaya_rabota_t db[MAX_WORKS];
    int size = 0;
    char filename[] = "data.txt";  // ��� ����� ��� �������� � ���������� ������
    char choice;
    char tema[BUFFER_SIZE];

    Vvod_file(db, &size, filename);  // �������� ������ �� �����

    while (1) {
        Pokazat_menu();  // �������� ���� ������������
        printf("�������� �����: ");
        scanf(" %c", &choice);  // �������� ����� ������������

        switch (choice) {
        case '1':  // ������� ��� ������
            Vivod(db, size);
            break;
        case '2':  // �������� ����� ������
            Dobavit_zapis(db, &size);
            break;
        case '3':  // �������� ������������ ������
            Izmenit_zapis(db, size);
            break;
        case '4':  // ��������� ������ � ����
            Vivod_file(db, size, filename);
            break;
        case '5':  // ����������� �� ������
            Sortirovka_balli(db, size);
            break;
        case '6':  // ����� �� ����
            printf("������� ���� ��� ������: ");
            scanf("%255s", tema);
            Poisk_po_teme(db, size, tema);
            break;
        case '7':  // �����
            printf("����� �� ���������.\n");
            return 0;
        default:
            printf("�������� ����. ����������, �������� �������������� �������.\n");
        }
    }

    return 0;
}

// ����������� �������

void Vvod_file(kursovaya_rabota_t* db, int* size, const char* filename) {
    setlocale(LC_ALL, "RUS");
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("������ ��� �������� ����� '%s'.\n", filename);
        return;
    }

    while (fscanf(file, "%49[^;];%49[^;];%199[^;];%19[^;];%d\n",
        db[*size].nazvanie_raboti,
        db[*size].avtor,
        db[*size].opisanie,
        db[*size].srok_sdachi,
        &db[*size].balli) != EOF && *size < MAX_WORKS) {
        (*size)++;
    }

    fclose(file);
    printf("������ ��������� �� ����� '%s'.\n", filename);
}

void Vivod(kursovaya_rabota_t* db, int size) {
    setlocale(LC_ALL, "RUS");
    printf("\n������ �������� �����:\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s (�����: %s, ��������: %s, ���� �����: %s, �����: %d)\n",
            i + 1,
            db[i].nazvanie_raboti,
            db[i].avtor,
            db[i].opisanie,
            db[i].srok_sdachi,
            db[i].balli);
    }
}

void Sortirovka_balli(kursovaya_rabota_t* db, int size) {
    setlocale(LC_ALL, "RUS");
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (db[j].balli < db[j + 1].balli) {
                kursovaya_rabota_t temp = db[j];
                db[j] = db[j + 1];
                db[j + 1] = temp;
            }
        }
    }
    printf("������ ������������� �� �������� ������.\n");
}

void Vivod_file(kursovaya_rabota_t* db, int size, const char* filename) {
    setlocale(LC_ALL, "RUS");
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("������ ��� �������� ����� '%s' ��� ������.\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%s;%s;%s;%s;%d\n",
            db[i].nazvanie_raboti,
            db[i].avtor,
            db[i].opisanie,
            db[i].srok_sdachi,
            db[i].balli);
    }

    fclose(file);
    printf("������ ��������� � ���� '%s'.\n", filename);
}

void Dobavit_zapis(kursovaya_rabota_t* db, int* size) {
    setlocale(LC_ALL, "RUS");
    if (*size >= MAX_WORKS) {
        printf("���� ������ �����. ���������� �������� ����� ������.\n");
        return;
    }

    printf("������� �������� ������: ");
    scanf("%49s", db[*size].nazvanie_raboti);
    printf("������� ������ ������: ");
    scanf("%49s", db[*size].avtor);
    printf("������� �������� ������: ");
    scanf("%199s", db[*size].opisanie);
    printf("������� ���� ����� ������: ");
    scanf("%19s", db[*size].srok_sdachi);
    printf("������� ����� �� ������: ");
    scanf("%d", &db[*size].balli);

    (*size)++;
    printf("����� ������ ���������.\n");
}

void Izmenit_zapis(kursovaya_rabota_t* db, int size) {
    setlocale(LC_ALL, "RUS");
    int index;
    printf("������� ����� ������ ��� ��������� (1-%d): ", size);
    scanf("%d", &index);
    index--;  // ��������� � ������ �������

    if (index < 0 || index >= size) {
        printf("�������� ����� ������.\n");
        return;
    }

    printf("��������� ������ ����� %d.\n", index + 1);
    printf("������� �������� ������: %s\n", db[index].nazvanie_raboti);
    printf("����� �������� ������ (�������� ������, ����� �� ������): ");
    scanf("%49s", db[index].nazvanie_raboti);
    printf("����� ����� (�������� ������, ����� �� ������): ");
    scanf("%49s", db[index].avtor);
    printf("����� �������� (�������� ������, ����� �� ������): ");
    scanf("%199s", db[index].opisanie);
    printf("����� ���� ����� (�������� ������, ����� �� ������): ");
    scanf("%19s", db[index].srok_sdachi);
    printf("����� ����� (������� -1, ����� �� ������): ");
    scanf("%d", &db[index].balli);

    printf("������ ����� %d ���������.\n", index + 1);
}

void Poisk_po_teme(kursovaya_rabota_t* db, int size, const char* tema) {
    setlocale(LC_ALL, "RUS");
    int found = 0;
    printf("���������� ������ �� ���� '%s':\n", tema);
    for (int i = 0; i < size; i++) {
        if (strstr(db[i].nazvanie_raboti, tema)) {
            printf("%d. %s (�����: %s, ��������: %s, ���� �����: %s, �����: %d)\n",
                i + 1,
                db[i].nazvanie_raboti,
                db[i].avtor,
                db[i].opisanie,
                db[i].srok_sdachi,
                db[i].balli);
            found++;
        }
    }
    if (!found) {
        printf("������ � ����� '%s' �� �������.\n", tema);
    }
}

char* Trim_space(char* str) {
    setlocale(LC_ALL, "RUS");
    char* end;

    // �������� ��������� ��������
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  // ��� �������
        return str;

    // �������� �������� ��������
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // ����� ����� ������
    end[1] = '\0';

    return str;
}

void Pokazat_menu() {
    setlocale(LC_ALL, "RUS");
    printf("\n*** ���� ***\n");
    printf("1. ������� ��� ������\n");
    printf("2. �������� ����� ������\n");
    printf("3. �������� ������������ ������\n");
    printf("4. ��������� ������ � ����\n");
    printf("5. ����������� ������ �� ������\n");
    printf("6. ����� �� ����\n");
    printf("7. �����\n");
}
