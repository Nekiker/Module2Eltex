#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <limits.h>

#define IP_LENGTH 16

int ip_str_to_ip_int(const char* str)
{
    char ip_str[IP_LENGTH];
    strcpy(ip_str, str);
    int ip_int = 0;

    char separator[2] = ".";
    char *istr;
    int octets[4];
    int octet_counter = 0;
    istr = strtok(ip_str, separator);
    while (istr != NULL)
    {
        octets[octet_counter] = strtol(istr, NULL, 10);
        octet_counter++;
        istr = strtok(NULL, separator);
    }

    ip_int = (octets[0] << 24) + (octets[1] << 16) + (octets[2] << 8) + octets[3];

    /*for (int i = 0; i < IP_LENGTH; i++)
    {
        if (ip_str[i] == '.')
        {
            for (int j = i; j < IP_LENGTH - 1; j++)
                ip_str[j] = ip_str[j + 1];
        }
    }
    ip_int = strtol(str, NULL, 10);*/
    return ip_int;
}

int ip_validation(const char* str)
{
    int is_valid = 0;
    char ipstr[IP_LENGTH];
    for (int i = 0; i < IP_LENGTH - 1; i++)
        ipstr[i] = str[i];
    ipstr[IP_LENGTH] = '\0';

    char separator[2] = ".";
    char *istr;
    istr = strtok(ipstr, separator);
    while (istr != NULL)
    {
        int octet = strtol(istr, NULL, 10);
        if (octet >= 0 && octet < 256)
            istr = strtok(NULL, separator);
        else
            return is_valid = 0;
    }
    return is_valid = 1;
}

int main(int argc, char* argv[])
{
    // Validations.
    if (argc < 4)
    {
        printf("Not enough arguments!\n");
        exit(EXIT_FAILURE);
    }

    char ip_source_str[IP_LENGTH];
    strcpy(ip_source_str, argv[1]);
    if (ip_validation(ip_source_str) == 0)
    {
        printf("Invalid IP!\n");
        exit(EXIT_FAILURE);
    }
    int ip_source_int = ip_str_to_ip_int(ip_source_str);

    char mask_str[IP_LENGTH];
    strcpy(mask_str, argv[2]);
    if (ip_validation(mask_str) == 0)
    {
        printf("Invalid Mask!\n");
        exit(EXIT_FAILURE);
    }
    int mask_int = ip_str_to_ip_int(mask_str);

    int number_of_packages = strtol(argv[3], NULL, 10);
    if (number_of_packages < 1)
    {
        printf("Invalid number of packages!\n");
        exit(EXIT_FAILURE);
    }

    // Generation of IPs.
    srand(time(NULL));
    long ip_destinations[number_of_packages]; // long - guarantee 4 bytes.
    for (int i = 0; i < number_of_packages; i++)
    {
        int sign = rand() % 2 ? 1 : -1;
        ip_destinations[i] = rand() * sign;
    }

    // Check belonging IP addresses to subnetwork.
    int number_of_packages_is_in_subnet = 0;
    int number_of_packages_is_not_in_subnet = 0;
    for (int i = 0; i < number_of_packages; i++)
    {
        int network_source = ip_source_int & mask_int;
        int network_destination = ip_destinations[i] & mask_int;
        int result = network_source ^ network_destination;
        if (result == 0)
            number_of_packages_is_in_subnet++;
        else
            number_of_packages_is_not_in_subnet++;
    }
    if (number_of_packages_is_in_subnet == 0)
        printf("Number of packages for this subnet: 0 (0 %%)\n");
    else 
    {
        float percent_of_packages_is_in_subnet = (number_of_packages_is_in_subnet * 1.0  / number_of_packages) * 100;
        printf("Number of packages for this subnet: %d (%g %%)\n", number_of_packages_is_in_subnet, percent_of_packages_is_in_subnet);
    }

    if (number_of_packages_is_not_in_subnet == 0)
        printf("Number of packages not for this subnet: 0 (0 %%)\n");
    else
    {
        float percent_of_packages_is_not_in_subnet = (number_of_packages_is_not_in_subnet * 1.0 /  number_of_packages) * 100;
        printf("Number of packages not for this subnet: %d (%g %%)\n", number_of_packages_is_not_in_subnet, percent_of_packages_is_not_in_subnet);
    }
}