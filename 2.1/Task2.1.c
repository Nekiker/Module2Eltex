#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define N 30
#define LONG_STRING 200
#define NOT_FILLED "НЕ ЗАПОЛНЕНО"
#define INCORRENT_INPUT "Неверный ввод!\n"
#define EDIT_TEXT "Введите, на что вы хотите изменить: "

typedef struct Person
{
    char firstname[N];
    char lastname[N];
    char middlename[N];
    char workplace[LONG_STRING];
    char post[LONG_STRING];
    char numbers[LONG_STRING];
    char emails[LONG_STRING];
    char links[LONG_STRING];
} Person;

void input(char* outStr, int size)
{
    char str[size];
    do
    {
        if (fgets(str, size, stdin))
            break;
        else printf(INCORRENT_INPUT);
    } while (1);

    for (int i = 0; i < strlen(str); i++)
        if (str[i] != '\n' && str[i] != '\r')
            outStr[i] = str[i];
        else outStr[i] = '\0';
}

Person createPerson()
{
    struct Person person;

    do
    {
        printf("Введите имя: ");
        input(person.firstname, N);
        if (strlen(person.firstname) > 1)
            break;
    } while (1);
    
    do
    {
        printf("Введите фамилию: ");
        input(person.lastname, N);
        if (strlen(person.lastname) > 1)
            break;
    } while (1);

    printf("Введите отчество: ");
    input(person.middlename, N);
    if (person.middlename)
        strcpy(person.middlename, NOT_FILLED);

    printf("Введите место работы: ");
    input(person.workplace, N);
    if (strlen(person.workplace) <= 1 )
        strcpy(person.workplace, NOT_FILLED);

    printf("Введите должность: ");
    input(person.post, N);
    if (strlen(person.post) <= 1 )
        strcpy(person.post, NOT_FILLED);

    printf("Введите номер телефона (можно несколько): ");
    input(person.numbers, LONG_STRING);
    if (strlen(person.numbers) <= 1 )
        strcpy(person.numbers, NOT_FILLED);

    printf("Введите электронную почту (можно несколько): ");
    input(person.emails, LONG_STRING);
    if (strlen(person.emails) <= 1 )
        strcpy(person.emails, NOT_FILLED);

    printf("Введите ссылки на страницы в соцсетях или профили в мессенджере: ");
    input(person.links, LONG_STRING);
    if (strlen(person.links) <= 1 )
        strcpy(person.links, NOT_FILLED);

    return person;
}

void printPerson(Person *person)
{
    printf("\t1. Имя: %s\n\t2. Фамилия: %s\n\t3. Отчество: %s\n\t4. Место работы: %s\n\t5. Должность: %s\n\t6. Номер телефона: %s\n\t7. Электронная почта: %s\n\t8. Ссылки на соцсети или профили в мессенджерах: %s\n", person->firstname, person->lastname, person->middlename, person->workplace, person->post, person->numbers, person->emails, person->links);
}

void printContacts(Person* contacts, int *personsCounter)
{
    if (*personsCounter == 0)
    {
        printf("Список контактов пуст!\n");
        return;
    }
    for (int i = 1; i < (*personsCounter + 1); i++)
    {
        printf("%d.\n", i);
        printPerson(&contacts[i - 1]);
    }
}

void addPerson(Person *contacts, Person person, int *personsCounter)
{
    if (*personsCounter >= N)
        {
            printf("В списке контактов нет места!");
            return;
        }

    contacts[*personsCounter] = person;
    *personsCounter = *personsCounter + 1;
}

int getPersonIndex(Person *contacts, int *personsCounter)
{
    printf("Выберите нужный контакт: \n");
    printContacts(contacts, personsCounter);
    if (*personsCounter == 0)
        return -1;
    char selectPerson[3];
    int personIndex;
    do 
    {
        input(selectPerson, sizeof(selectPerson));
        if (selectPerson)
            {
                personIndex = atoi(selectPerson);
                if (personIndex > 0 && personIndex <= *personsCounter)
                    break;
            }
        else printf(INCORRENT_INPUT);
    } while (1);

    return personIndex - 1;
}

void editPerson(Person* contacts, int personIndex)
{
    if (personIndex == -1)
    return;
    printf("Какое поле вы хотите изменить?\n");
    printPerson(&contacts[personIndex]);
    char selectField[3];
    fgets(selectField, 3, stdin);
    char replaceText[LONG_STRING];
    switch ( selectField[0] )
    {
        case '1':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(contacts[personIndex].firstname, replaceText);
            break;
        case '2':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(contacts[personIndex].lastname, replaceText);
            break;
        case '3':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(contacts[personIndex].middlename, replaceText);
            break;
        case '4':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(contacts[personIndex].workplace, replaceText);
            break;
        case '5':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(contacts[personIndex].post, replaceText);
            break;
        case '6':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(contacts[personIndex].numbers, replaceText);
            break;
        case '7':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(contacts[personIndex].emails, replaceText);
            break;
        case '8':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(contacts[personIndex].links, replaceText);
            break;
        default:
            printf(INCORRENT_INPUT);
            break;
    }
}

void deletePerson(Person* contacts, int *personsCounter, int personIndex)
{
    for (int i = personIndex; i < *personsCounter - 1; i++)
        contacts[i] = contacts[i + 1];
    *personsCounter = *personsCounter - 1;
}

int main(void)
{
    setlocale(0, "ru");
    struct Person contacts[N];
    int personsCounter = 0;

    while (1)
    {
        printf("Выберите действие: \n1. Добавление контакта.\n2. Редактирование контакта.\n3. Удаление контакта.\n4. Вывод контактов.\n0. Выход.\n");
        char selectField[3];
        fgets(selectField, 3, stdin);

        switch ( selectField[0] )
        {
            case '1':
                printf("Вы выбрали добавление контакта.\n");
                addPerson(contacts, createPerson(), &personsCounter);
                break;
            case '2':
                printf("Вы выбрали редактирование контакта.\n");
                editPerson(contacts, getPersonIndex(contacts, &personsCounter));
                break;
            case '3':
                printf("Вы выбрали удаление контакта.\n");
                deletePerson(contacts, &personsCounter, getPersonIndex(contacts, &personsCounter));
                break;
            case '4':
                printf("Вы выбрали вывод контактов.\n");
                printContacts(contacts, &personsCounter);
                break;
            case '0':
                exit(0);
            default:
                printf(INCORRENT_INPUT);
                break;
        }
    }
}