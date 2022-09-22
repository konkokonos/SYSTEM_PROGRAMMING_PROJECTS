#include <stdlib.h>
#include <stdio.h>

unsigned long djb2(unsigned char *str)
{
	int c;
	unsigned long hash = 5381;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; // hash * 33 + c

	return hash;
}

unsigned long sdbm(unsigned char *str) 
{
	int c;
	unsigned long hash = 0;

	while ((c = *str++))
		hash = c + (hash << 6) + (hash << 16) - hash;

	return hash;
}

unsigned long hash_i(unsigned char *str, unsigned int i)
{
	return djb2(str) + i * sdbm(str) + i * i;
}

// DIKIA MOY SYNARTHSH
unsigned long* pinakas_me_k_hash(unsigned char *str,int bloomsize)
{
	unsigned long* pinakas_me_k;
	pinakas_me_k = (unsigned long*)malloc(16 * sizeof(unsigned long));
	for(int i =0; i<16; i++)
	{
		unsigned long hi = hash_i(str,i)%bloomsize;
		pinakas_me_k[i] = hi;
	}
	return pinakas_me_k;
}