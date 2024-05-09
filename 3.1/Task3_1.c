#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <stdint.h> 
#define LEN_OF_PERMISSIONS 15
#define LEN_OF_FILENAME 128
#define LEN_OF_SYMBOLIC_REPRESENTATION 4

/*// Проверка ввода прав.
int rights_validation(const char* rights)
{
    int is_not_validate = 0;

    if (rights[0] == 'u' ||
        rights[0] == 'g' ||
        rights[0] == 'o' ||
        rights[0] == 'a') 
    {
        if (rights[1] == '-' ||
            rights[1] == '+' ||
            rights[1] == '=')
        {
            if (rights[2] == 'r' ||
                rights[2] == 'w' ||
                rights[2] == 'x')
                return is_not_validate;
            else 
                return is_not_validate = 1;
        }
        else
            return is_not_validate = 1;
    }
    else if (rights[0] == '0' ||
             rights[0] == '4' ||
             rights[0] == '5' ||
             rights[0] == '6' ||
             rights[0] == '7')
    {
        if (rights[1] == '0' ||
            rights[1] == '4' ||
            rights[1] == '5' ||
            rights[1] == '6' ||
            rights[1] == '7')
        {
            if (rights[2] == '0' ||
                rights[2] == '4' ||
                rights[2] == '5' ||
                rights[2] == '6' ||
                rights[2] == '7')
                return is_not_validate;
            else 
                return is_not_validate = 1;
        }
        else
            return is_not_validate = 1;       
    }
    else 
        return is_not_validate = 1;
}*/

// Перевод в двоичное представление.
void print_binary(char *str) 
{
    for (int i = 0; i < strlen(str); i++) 
    {
        for (int j = 7; j >= 0; j--) 
            printf("%d", (str[i] >> j) & 1);
        printf(" ");
    }
    printf("\n");
}

void remove_enter_symbol(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\n' || str[i] == '\r')
            {
            str[i] = '\0';
            break;
            }
        i++;
    }
}

void symbolic_representation(struct stat sb)
{
    printf((sb.st_mode & S_IRUSR) ? "r" : "-");
    printf((sb.st_mode & S_IWUSR) ? "w" : "-");
    printf((sb.st_mode & S_IXUSR) ? "x" : "-");
    printf((sb.st_mode & S_IRGRP) ? "r" : "-");
    printf((sb.st_mode & S_IWGRP) ? "w" : "-");
    printf((sb.st_mode & S_IXGRP) ? "x" : "-");
    printf((sb.st_mode & S_IROTH) ? "r" : "-");
    printf((sb.st_mode & S_IWOTH) ? "w" : "-");
    printf((sb.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

int main()
{
    setlocale(LC_ALL, "ru");

    // Ввод прав доступа.
    char permissions[LEN_OF_PERMISSIONS];
    do 
    {
        printf("Введите права доступа: ");
        fgets(permissions, LEN_OF_PERMISSIONS, stdin);
        remove_enter_symbol(permissions);
    } while (strlen(permissions) < 3);

    print_binary(permissions);

    // Ввод имени файла.
    char filename[LEN_OF_FILENAME];
    do 
    {
        printf("Введите название файла: ");
        fgets(filename, LEN_OF_FILENAME, stdin);
        int i = 0;
        remove_enter_symbol(filename);
    } while (strlen(filename) < 1);
    
    struct stat sb;

    if (lstat(filename, &sb) == -1) {
               perror("lstat");
               exit(EXIT_FAILURE);
           }

    int numeric_representation = (uintmax_t) sb.st_mode & 0777;
    //char symbolic_representation[LEN_OF_SYMBOLIC_REPRESENTATION];

    printf("Права доступа: %o\n", numeric_representation);
    symbolic_representation(sb);
}