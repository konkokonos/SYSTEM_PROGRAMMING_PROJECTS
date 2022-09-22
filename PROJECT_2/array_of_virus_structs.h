#include <hash_i.h>
#include <array_for_structs.h>

typedef struct Virus
{
    char* name;
    int* bloom_filter;
}virus;

typedef struct RETURN
{
	int elements;
	virus *array_of_virus_structs;
}re;

re create_array_of_virus_structs(record**, int);
int elexos_for_new_virus(record*, virus* ,int );
void print_array_of_virus_structs(virus* ,int ,int );

