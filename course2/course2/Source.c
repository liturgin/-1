#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_WORKS 1000  // Максимальное количество работ
#define BUFFER_SIZE 256 // Размер буфера для ввода

// Определение структуры для курсовых работ
struct kursovie_raboti {
    char nazvanie_raboti[50];  // Название работы
    char avtor[50];            // Автор
    char opisanie[200];        // Описание
    char srok_sdachi[20];      // Срок сдачи
    int balli;                 // Баллы
};

typedef struct kursovie_raboti kursovaya_rabota_t;

// Прототипы функций
void Vvod_file(kursovaya_rabota_t* db, int* size, const char* filename);
void Vivod(kursovaya_rabota_t* db, int size);
void Sortirovka_balli(kursovaya_rabota_t* db, int size);
void Vivod_file(kursovaya_rabota_t* db, int size, const char* filename);
void Dobavit_zapis(kursovaya_rabota_t* db, int* size);
void Izmenit_zapis(kursovaya_rabota_t* db, int size);
void Poisk_po_teme(kursovaya_rabota_t* db, int size, const char* tema);
char* Trim_space(char* str);
void Pokazat_menu();

// Главная функция
int main() {
    setlocale(LC_ALL, "RUS");
    kursovaya_rabota_t db[MAX_WORKS];
    int size = 0;
    char filename[] = "data.txt";  // Имя файла для загрузки и сохранения данных
    char choice;
    char tema[BUFFER_SIZE];

    Vvod_file(db, &size, filename);  // Загрузка данных из файла

    while (1) {
        Pokazat_menu();  // Показать меню пользователя
        printf("Выберите опцию: ");
        scanf(" %c", &choice);  // Получить выбор пользователя

        switch (choice) {
        case '1':  // Вывести все записи
            Vivod(db, size);
            break;
        case '2':  // Добавить новую запись
            Dobavit_zapis(db, &size);
            break;
        case '3':  // Изменить существующую запись
            Izmenit_zapis(db, size);
            break;
        case '4':  // Сохранить данные в файл
            Vivod_file(db, size, filename);
            break;
        case '5':  // Сортировать по баллам
            Sortirovka_balli(db, size);
            break;
        case '6':  // Поиск по теме
            printf("Введите тему для поиска: ");
            scanf("%255s", tema);
            Poisk_po_teme(db, size, tema);
            break;
        case '7':  // Выход
            printf("Выход из программы.\n");
            return 0;
        default:
            printf("Неверный ввод. Пожалуйста, выберите действительный вариант.\n");
        }
    }

    return 0;
}

// Определения функций

void Vvod_file(kursovaya_rabota_t* db, int* size, const char* filename) {
    setlocale(LC_ALL, "RUS");
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка при открытии файла '%s'.\n", filename);
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
    printf("Данные загружены из файла '%s'.\n", filename);
}

void Vivod(kursovaya_rabota_t* db, int size) {
    setlocale(LC_ALL, "RUS");
    printf("\nСписок курсовых работ:\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s (Автор: %s, Описание: %s, Срок сдачи: %s, Баллы: %d)\n",
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
    printf("Данные отсортированы по убыванию баллов.\n");
}

void Vivod_file(kursovaya_rabota_t* db, int size, const char* filename) {
    setlocale(LC_ALL, "RUS");
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка при открытии файла '%s' для записи.\n", filename);
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
    printf("Данные сохранены в файл '%s'.\n", filename);
}

void Dobavit_zapis(kursovaya_rabota_t* db, int* size) {
    setlocale(LC_ALL, "RUS");
    if (*size >= MAX_WORKS) {
        printf("База данных полна. Невозможно добавить новую запись.\n");
        return;
    }

    printf("Введите название работы: ");
    scanf("%49s", db[*size].nazvanie_raboti);
    printf("Введите автора работы: ");
    scanf("%49s", db[*size].avtor);
    printf("Введите описание работы: ");
    scanf("%199s", db[*size].opisanie);
    printf("Введите срок сдачи работы: ");
    scanf("%19s", db[*size].srok_sdachi);
    printf("Введите баллы за работу: ");
    scanf("%d", &db[*size].balli);

    (*size)++;
    printf("Новая запись добавлена.\n");
}

void Izmenit_zapis(kursovaya_rabota_t* db, int size) {
    setlocale(LC_ALL, "RUS");
    int index;
    printf("Введите номер записи для изменения (1-%d): ", size);
    scanf("%d", &index);
    index--;  // Переводим в индекс массива

    if (index < 0 || index >= size) {
        printf("Неверный номер записи.\n");
        return;
    }

    printf("Изменение записи номер %d.\n", index + 1);
    printf("Текущее название работы: %s\n", db[index].nazvanie_raboti);
    printf("Новое название работы (оставьте пустым, чтобы не менять): ");
    scanf("%49s", db[index].nazvanie_raboti);
    printf("Новый автор (оставьте пустым, чтобы не менять): ");
    scanf("%49s", db[index].avtor);
    printf("Новое описание (оставьте пустым, чтобы не менять): ");
    scanf("%199s", db[index].opisanie);
    printf("Новый срок сдачи (оставьте пустым, чтобы не менять): ");
    scanf("%19s", db[index].srok_sdachi);
    printf("Новые баллы (введите -1, чтобы не менять): ");
    scanf("%d", &db[index].balli);

    printf("Запись номер %d обновлена.\n", index + 1);
}

void Poisk_po_teme(kursovaya_rabota_t* db, int size, const char* tema) {
    setlocale(LC_ALL, "RUS");
    int found = 0;
    printf("Результаты поиска по теме '%s':\n", tema);
    for (int i = 0; i < size; i++) {
        if (strstr(db[i].nazvanie_raboti, tema)) {
            printf("%d. %s (Автор: %s, Описание: %s, Срок сдачи: %s, Баллы: %d)\n",
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
        printf("Записи с темой '%s' не найдены.\n", tema);
    }
}

char* Trim_space(char* str) {
    setlocale(LC_ALL, "RUS");
    char* end;

    // Удаление начальных пробелов
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  // Все пробелы
        return str;

    // Удаление конечных пробелов
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Новый конец строки
    end[1] = '\0';

    return str;
}

void Pokazat_menu() {
    setlocale(LC_ALL, "RUS");
    printf("\n*** Меню ***\n");
    printf("1. Вывести все записи\n");
    printf("2. Добавить новую запись\n");
    printf("3. Изменить существующую запись\n");
    printf("4. Сохранить данные в файл\n");
    printf("5. Сортировать записи по баллам\n");
    printf("6. Поиск по теме\n");
    printf("7. Выход\n");
}
