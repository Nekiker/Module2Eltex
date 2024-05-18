#include "Task4_1.h"

struct Person createPerson()
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

void printPerson(const struct Person *person)
{
    printf("\t1. Имя: %s\n\t2. Фамилия: %s\n\t3. Отчество: %s\n\t4. Место работы: %s\n\t5. Должность: %s\n\t6. Номер телефона: %s\n\t7. Электронная почта: %s\n\t8. Ссылки на соцсети или профили в мессенджерах: %s\n", person->firstname, person->lastname, person->middlename, person->workplace, person->post, person->numbers, person->emails, person->links);
}

/* Compares by lastname, firstname and middlename  
   Returns 0 - if personLeft is bigger than personRight, 1 - if less, 2 - equal. */
int NamesCompare(const char* firstnameLeft, const char* lastnameLeft, const char* middlenameLeft, const char* firstnameRight, const char* lastnameRight, const char* middlenameRight)
{
    if (strcmp(lastnameLeft, lastnameRight) < 0)
        return 1;
    else if (strcmp(lastnameLeft, lastnameRight) > 0)
        return 0;
    else if (strcmp(firstnameLeft, firstnameRight) < 0)
        return 1;
    else if (strcmp(firstnameLeft, firstnameRight) > 0)
        return 0;
    else if (strcmp(middlenameLeft, middlenameRight) < 0)
        return 1;
    else if (strcmp(middlenameLeft, middlenameRight) > 0)
        return 0;
    else return 2;
}

int PersonsCompare(const struct Person *personLeft, const struct Person *personRight)
{
    return NamesCompare(personLeft->firstname, personLeft->lastname, personLeft->middlename, personRight->firstname, personRight->lastname, personRight->middlename);
}

int NameAndPersonCompare(const char* firstnameLeft, const char* lastnameLeft, const char* middlenameLeft, const struct Person *person)
{
    return NamesCompare(firstnameLeft, lastnameLeft, middlenameLeft, person->firstname, person->lastname, person->middlename);
}

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

void editPerson(struct Person *person)
{
    printf("Какое поле вы хотите изменить?\n");
    printPerson(person);
    char selectField[3];
    fgets(selectField, 3, stdin);
    char replaceText[LONG_STRING];
    switch ( selectField[0] )
    {
        case '1':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(person->firstname, replaceText);
            break;
        case '2':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(person->lastname, replaceText);
            break;
        case '3':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(person->middlename, replaceText);
            break;
        case '4':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(person->workplace, replaceText);
            break;
        case '5':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(person->post, replaceText);
            break;
        case '6':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(person->numbers, replaceText);
            break;
        case '7':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(person->emails, replaceText);
            break;
        case '8':
            printf(EDIT_TEXT);
            input(replaceText, sizeof(replaceText));
            strcpy(person->links, replaceText);
            break;
        default:
            printf(INCORRENT_INPUT);
            break;
    }
}