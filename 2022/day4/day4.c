#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <adt/dynarray.h>


int read_pairs (FILE* in)
{
    int pairs = 0;

    char* linebuf = calloc (256, sizeof (char));

    while (fgets (linebuf, 256, in) != NULL)
    {
        array* elf1 = da_create (0);
        array* elf2 = da_create (0);

        int range1 [2];
        int range2 [2];

        sscanf (linebuf, "%d-%d,%d-%d\n", &(range1[0]), &(range1[1]), &(range2[0]), &(range2[1]));

        for (int i = range1[0]; i <= range1[1]; i++)
        {
            da_insert (elf1, elf1->size, i);
        }

        for (int i = range2[0]; i <= range2[1]; i++)
        {
            da_insert (elf2, elf2->size, i);
        }

        array* result;
        array* subtractme;

        if (range1[0] < range2[0])
        {
            result = elf1;
            subtractme = elf2;
        }
        else
        {
            result = elf2;
            subtractme = elf1;
        }

        for (int i = 0; i < subtractme->size; i++)
        {
            int j = da_firstindexof (result, subtractme->arr[i]);
            if (j < 0)
                continue;
            da_remove (result, subtractme->arr[j]);
        }

        if (result->size == 0)
            pairs += 1;

        da_destroy (&elf1);
        da_destroy (&elf2);
    }

    free (linebuf);
    fclose (in);

    return pairs;
}

int main ()
{
    char* infile = "day4.in";

    FILE* in = fopen (infile, "r");
    if (!in)
    {
        printf ("Error opening file %s\n", infile);
        return 1;
    }


    printf("PART A: %d pairs\n", read_pairs (in));
}