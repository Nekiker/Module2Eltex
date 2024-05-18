#include "Task4_1.h"
#include "Task4_1_list.h"

int main(void)
{
    setlocale(0, "ru");
    struct Item* head = NULL;
    struct Person *person = NULL;
    struct Person p;
    char firstname[N];
    char lastname[N];
    char middlename[N];
    head = InsertPerson(createPerson(), head);
    head = InsertPerson(createPerson(), head);
    head = InsertPerson(createPerson(), head);
    PrintPersons(head);
    
    while (1)
    {
        printf("Выберите действие: \n1. Добавление контакта.\n2. Редактирование контакта.\n3. Удаление контакта.\n4. Вывод контактов.\n0. Выход.\n");
        char selectField[3];
        fgets(selectField, 3, stdin);
        switch ( selectField[0] )
        {
            case '1':
                printf("Вы выбрали добавление контакта.\n");
                head = InsertPerson(createPerson(), head);
                break;
            case '2':
                printf("Вы выбрали редактирование контакта.\n");

                do
                {
                    printf("Введите имя: ");
                    input(firstname, N);
                    if (strlen(firstname) > 1)
                    break;
                } while (1);

                do
                {
                    printf("Введите фамилию: ");
                    input(lastname, N);
                    if (strlen(lastname) > 1)
                        break;
                } while (1);

                printf("Введите отчество: ");
                input(middlename, N);
                if (middlename)
                    strcpy(middlename, NOT_FILLED);

                person = SearchPersonInListByName(firstname, lastname, middlename, head);
                if (person == NULL)
                    break;
                
                // Deep copying.
                strcpy(p.firstname, person->firstname);
                strcpy(p.lastname, person->lastname);
                strcpy(p.middlename, person->middlename);
                strcpy(p.emails, person->emails);
                strcpy(p.links, person->links);
                strcpy(p.numbers, person->numbers);
                strcpy(p.post, person->post);
                strcpy(p.workplace, person->workplace);

                head = DeletePerson(*person, head);
                editPerson(&p);
                head = InsertPerson(p, head);
                break;
            case '3':
                printf("Вы выбрали удаление контакта.\n");

                do
                {
                    printf("Введите имя: ");
                    input(firstname, N);
                    if (strlen(firstname) > 1)
                    break;
                } while (1);

                do
                {
                    printf("Введите фамилию: ");
                    input(lastname, N);
                    if (strlen(lastname) > 1)
                        break;
                } while (1);

                printf("Введите отчество: ");
                input(middlename, N);
                if (middlename)
                    strcpy(middlename, NOT_FILLED);
                
                person = SearchPersonInListByName(firstname, lastname, middlename, head);
                if (person == NULL)
                    break;
                head = DeletePerson(*person, head);
                break;
            case '4':
                printf("Вы выбрали вывод контактов.\n");
                PrintPersons(head);
                break;
            case '0':
                exit(0);
            default:
                printf(INCORRENT_INPUT);
                break;
        }
    }
}