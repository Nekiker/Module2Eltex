#ifndef TASK4_1_LIST_H
#define TASK4_1_LIST_H

#include "Task4_1.h"

struct Item 
{
    struct Person person;
    struct Item* next;
    struct Item* prev;
};

struct Item* InsertPerson(struct Person person, struct Item* head);
struct Item* DeletePerson(struct Person person, struct Item* head);
void PrintPersons(struct Item* head);
struct Person* SearchPersonInListByName(const char* firstname, const char* lastname, const char* middlename, struct Item* head);

#endif