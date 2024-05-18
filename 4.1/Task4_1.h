#ifndef TASK4_1_H
#define TASK4_1_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define N 30
#define LONG_STRING 200
#define NOT_FILLED "НЕ ЗАПОЛНЕНО"
#define INCORRENT_INPUT "Неверный ввод!\n"
#define EDIT_TEXT "Введите, на что вы хотите изменить: "

struct Person
{
    char firstname[N];
    char lastname[N];
    char middlename[N];
    char workplace[LONG_STRING];
    char post[LONG_STRING];
    char numbers[LONG_STRING];
    char emails[LONG_STRING];
    char links[LONG_STRING];
};

struct Person createPerson();
void printPerson(const struct Person *person);
int NamesCompare(const char* firstnameLeft, const char* lastnameLeft, const char* middlenameLeft, const char* firstnameRight, const char* lastnameRight, const char* middlenameRight);
int PersonsCompare(const struct Person *personLeft, const struct Person *personRight);
int NameAndPersonCompare(const char* firstnameLeft, const char* lastnameLeft, const char* middlenameLeft, const struct Person *person);
void input(char* outStr, int size);
void editPerson(struct Person *person);

#endif