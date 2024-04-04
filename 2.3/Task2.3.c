#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#define INCORRENT_INPUT "Неверный ввод!\n"
#define NUMBER_SIZE 40

float operationAddition(float a, float b)
{
	return a + b;
}

float operationSubstraction(float a, float b)
{
	return a - b;
}

float operationMultiplication(float a, float b)
{
	return a * b;
}

float operationDivision(float a, float b)
{
	return a / b;
}

float functionPow(float a, float b)
{
	return pow(a, b);
}

int isNumber(const char* str)
{
	int DecimalSeparatorCounter = 0;
	int counter = 0;
	while (*str)
	{

		if (*str == ',' || *str == '.')
		{
			DecimalSeparatorCounter++;
			*str++;
		}
		if (!isdigit(*str++))
			return 0;
		counter++;
	}
	if (DecimalSeparatorCounter > 1)
		return 0;
	if (counter == 0)
		return 0;
	return 1;
}

void inputNumber(float* num)
{
	do
	{
		char str[NUMBER_SIZE];
		char outStr[NUMBER_SIZE];
		if (fgets(str, NUMBER_SIZE, stdin))
		{
			for (int i = 0; i < strlen(str); i++)
				if (str[i] != '\n' && str[i] != '\r')
					outStr[i] = str[i];
				else outStr[i] = '\0';

			if (isNumber(outStr))
			{
				*num = atof(outStr);
				break;
			}
		}
		else printf(INCORRENT_INPUT);
	} while (1);
}

void input(float* num1, float* num2)
{
	printf("Введите первое значение: ");
	inputNumber(num1);
	printf("Введите второе значение: ");
	inputNumber(num2);
}

float (*select(char choice)) (float, float)
{
	switch (choice)
	{
	case 2: return operationSubstraction;
	case 3: return operationMultiplication;
	case 4: return operationDivision;
	case 5: return functionPow;
	default: return operationAddition;
	}
}

int main(void)
{
	setlocale(0, "ru");
	char selectField;
	do
	{
		printf("Выбор операции\n1. +\n2. -\n3. *\n4. /\n5. ^\n0. Выход\n");
		selectField = _getch();
		float num1;
		float num2;
		float (*operation)(float, float);
		if (selectField >= '1' && selectField <= '5')
		{
			input(&num1, &num2);
			if (selectField == '1')
				operation = select(1);
			else if (selectField == '2')
				operation = select(2);
			else if (selectField == '3')
				operation = select(3);
			else if (selectField == '4')
				operation = select(4);
			else if (selectField == '5')
				operation = select(5);
			printf("Результат: %g\n", operation(num1, num2));
		}
		else if (selectField == '0')
			break;
		else
			printf(INCORRENT_INPUT);
	} while (selectField != '0');
	return 0;
}