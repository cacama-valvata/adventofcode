#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <adt/dynarray.h>


array* read_elves (FILE* in)
{
    array* elves = da_create (100);

    char* linebuf = calloc (256, sizeof (char));
    int current_elf_total = 0;

    while (fgets (linebuf, 256, in) != NULL)
    {
        // end of that elf's rations
        if ( !strcmp (linebuf, "\n") )
        {
            da_insert (elves, elves->size, current_elf_total);
            if (errno != 0)
                printf ("treacherous: %s\n", strerror (errno));
            current_elf_total = 0;
        }
        // more to count
        else 
        {
            linebuf[ strcspn (linebuf, "\n") ] = '\0';
            current_elf_total += atoi (linebuf);
        }
    }

    free (linebuf);
    fclose (in);

    return elves;
}

array* shit_sort (array* elves)
{
    array* top_elves = da_create (elves->size);

    for (int i = 0; i < elves->size; i++)
    {
        int c = 0;
        for (int j = 0; j < top_elves->size; j++)
        {
            if (elves->arr[i] > top_elves->arr[j])
            {
                da_insert (top_elves, j, elves->arr[i]);
                c = 1;
                break;
            }
        }
        // either:
        //    smallest element, or
        //    no elements yet
        if (! c)
            da_insert (top_elves, top_elves->size, elves->arr[i]);
    }

    da_destroy (&elves);

    return top_elves;
}

int sum_first_n (array* elves, int n)
{
    int result = 0;

    if (n > elves->size)
        n = elves->size;

    for (int i = 0; i < n; i++)
    {
        result += elves->arr[i];
    }

    return result;
}


int main (int argc, char* argv[])
{
    char* infile = "day1.in";

    FILE* in = fopen (infile, "r");
    if (!in)
    {
        printf ("Error opening file %s\n", infile);
        return 1;
    }

    array* elves = read_elves (in);
    elves = shit_sort (elves);

    printf ("PART A: %d calories\n", sum_first_n (elves, 1) );
    printf ("PART B: %d calories\n", sum_first_n (elves, 3) );

    da_destroy (&elves);
}