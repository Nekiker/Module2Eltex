#include "Task4_1_list.h"

// Insert and sort by lastname.
struct Item* InsertPerson(struct Person person, struct Item* head)
{
    struct Item* newItem;
    struct Item* tmp = head;

    newItem = malloc(sizeof(struct Item));
    newItem->person = person;

    // Insert for the first time.
    if (head == NULL) 
    {
        newItem->prev = newItem;
        newItem->next = newItem;
        head = newItem;
        return head;
    }

    // Insert in the beginning or middle.
    do
    {
        int personsCompareResult = PersonsCompare(&(newItem->person), &(tmp->person));
        if (personsCompareResult == 2)
        {
            printf("This person is already in list!\n");
            return head;
        }

        if (personsCompareResult == 1)
        {
            newItem->next = tmp;
            newItem->prev = tmp->prev;
            tmp->prev->next = newItem;
            tmp->prev = newItem;
            if (tmp == head)
                head = newItem;
            return head;
        }
        tmp = tmp->next;
    } while (tmp != head);

    // Insert in the ending.
    newItem->next = tmp;
    newItem->prev = tmp->prev;
    tmp->prev->next = newItem;
    tmp->prev = newItem;
    return head;
}

struct Item* DeletePerson(struct Person person, struct Item* head)
{
    struct Item *tmp = head;
    
    if (head == NULL)
    {
        printf("List is empty!\n");
        return head;
    }

    // Searching and deleting.
    do 
    {
        int personsCompareResult = PersonsCompare(&person, &(tmp->person));
        if (personsCompareResult == 2)
        {
            if (tmp->next == tmp->prev)
            {
                free(tmp);
                return NULL;
            }

            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;

            if (tmp == head)
                head = head->next;
            
            free(tmp);
            return head;
        }
        tmp = tmp->next;
    } while (tmp != head);

    printf("List doesn't contain %s %s %s!\n", person.lastname, person.firstname, person.middlename);
    return head;
}

void PrintPersons(struct Item* head)
{
    struct Item* tmp = head;
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    int counter = 1;
    do
    {
        printf("%d.\n", counter);
        printPerson(&(tmp->person));
        counter++;
        tmp = tmp->next;
    } while (tmp != head);
    printf("\n");
}

struct Person* SearchPersonInListByName(const char* firstname, const char* lastname, const char* middlename, struct Item* head)
{
    struct Item* tmp = head;
    if (head == NULL)
    {
        printf("List is empty!\n");
        return NULL;
    }

    do 
    {
        if (NameAndPersonCompare(firstname, lastname, middlename, &tmp->person) == 2)
        {
            return &tmp->person;
        }
        tmp = tmp->next;
    } while (tmp != head);

    printf("List doesn't contain %s %s %s!\n", lastname, firstname, middlename);
    return NULL;
}