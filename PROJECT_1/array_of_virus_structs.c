#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <array_of_virus_structs.h>

virus create_virus(char* name,int bloomsize)
{
    virus vir;
    char* na =(char*)malloc(strlen(name)+1);
    strcpy(na,name);
    vir.name = na;
    vir.bloom_filter =calloc(bloomsize,sizeof(int));
    for(int i =0;i<bloomsize;i++)
        vir.bloom_filter[i]=0;

    return vir;
}

int elexos_for_new_virus(record* tmp, virus *array_of_virus_structs,int count)
{
	int e =-1;
	for (int j =0; j<count; j++)
    {
        if(strcmp(tmp->virusName,array_of_virus_structs[j].name) == 0)
            return j;
    }
    return e;
}

int* gemisma_tou_bloom_filter(record* tmp,int bloomsize,int* blfil)
{
    unsigned long* pinakas_thesewn;
    pinakas_thesewn = NULL;
    unsigned char* citid = tmp->citizenID;
    pinakas_thesewn = pinakas_me_k_hash(citid, bloomsize);
    for(int i =0; i<16; i++)
    {
        unsigned long byteposition = pinakas_thesewn[i]/8;
        unsigned int bitposition = pinakas_thesewn[i]%8;
        unsigned int flag = 1;
        flag = flag << bitposition;
        blfil[byteposition] = blfil[byteposition] | flag;
    }
    return blfil;
}

re create_array_of_virus_structs(record** array_for_structs,int bloomsize)
{
	virus *array_of_virus_structs;
    array_of_virus_structs = NULL;
	int count = 0;
    re r;

    for(int i =0; array_for_structs[i] != NULL; i++)
    {
        record* tmp=array_for_structs[i];
        while(tmp!= NULL)
        {	
            if(strcmp(tmp->YN,"YES") == 0)
            {
            	int e = -1;
            	e = elexos_for_new_virus(tmp,array_of_virus_structs,count);
            	if(e >=0)
            	{
                    int* blfil = array_of_virus_structs[e].bloom_filter;
                    array_of_virus_structs[e].bloom_filter = gemisma_tou_bloom_filter(tmp,bloomsize,blfil);
            		tmp=tmp->next;
            		continue;
            	}
            	else if (e == -1)
            	{
            		array_of_virus_structs = (virus*)realloc(array_of_virus_structs,(count+1)*sizeof(virus));
                    virus v = create_virus(tmp->virusName,bloomsize);
                    v.bloom_filter = gemisma_tou_bloom_filter(tmp,bloomsize,v.bloom_filter);
            		array_of_virus_structs[count] = v;
            		count++;
            	}
            }
            tmp=tmp->next;
        }
    }
    r.elements = count;
    r.array_of_virus_structs = array_of_virus_structs;
    return r;
}

void print_array_of_virus_structs(virus *array_of_virus_structs,int elements,int bloomsize)
{
    for(int i =0; i<= elements; i++)
    {
        printf("%s ",array_of_virus_structs[i].name);
        for(int j =0; j<bloomsize; j++)
            printf("%d ",array_of_virus_structs[i].bloom_filter[j]);
        printf("\n\n");
    }
}
