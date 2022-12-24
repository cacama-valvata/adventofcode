#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <adt/dynarray.h>


char find_common (char* p, char* q, int len)
{
    for (int i = 0; i < len; i++)
    {

        for (int j = 0; j < len; j++)
        {
            if (p[i] == q[j])
                return p[i];
        }
    }
}

char find_common_trio (char* p, int p_len, char* q, int q_len, char* w, int w_len)
{
    for (int i = 0; i < p_len; i++)
    {
        for (int j = 0; j < q_len; j++)
        {
            for (int k = 0; k < w_len; k++)
            if (p[i] == q[j] && q[j] == w[k])
                return p[i];
        }
    }
}

int decode_priority (char c)
{
    if (c >= 97 && c <= 122)
        return c - 96;
    else if (c >= 65 && c <= 90)
        return c - 38;
    else
        return 0;
}

array* read_knapsacks (FILE* in)
{
    array* knapsacks = da_create (100);

    char* linebuf = calloc (256, sizeof (char));

    while (fgets (linebuf, 256, in) != NULL)
    {
        int e = strcspn (linebuf, "\n");
        linebuf[ strcspn (linebuf, "\n") ] = '\0';

        char* p = linebuf;
        char* q = &(linebuf [e/2]);

        char common = find_common (p, q, e/2);

        int priority = decode_priority (common);

        da_insert (knapsacks, knapsacks->size, priority);
    }

    free (linebuf);
    fclose (in);

    return knapsacks;
}

array* read_knapsacks_trio (FILE* in)
{
    array* knapsacks = da_create (100);

    char* linebuf1 = calloc (256, sizeof (char));
    char* linebuf2 = calloc (256, sizeof (char));
    char* linebuf3 = calloc (256, sizeof (char));

    while (fgets (linebuf1, 256, in) != NULL)
    {
        fgets (linebuf2, 256, in);
        fgets (linebuf3, 256, in);

        int e1 = strcspn (linebuf1, "\n");
        int e2 = strcspn (linebuf2, "\n");
        int e3 = strcspn (linebuf3, "\n");

        char common = find_common_trio (linebuf1, e1, linebuf2, e2, linebuf3, e3);

        int priority = decode_priority (common);

        da_insert (knapsacks, knapsacks->size, priority);
    }

    free (linebuf1);
    free (linebuf2);
    free (linebuf3);
    fclose (in);

    return knapsacks;
}

int sum_first_n (array* priorities, int n)
{
    int result = 0;

    if (n > priorities->size)
        n = priorities->size;

    for (int i = 0; i < n; i++)
    {
        result += priorities->arr[i];
    }

    return result;
}

int main () 
{
    char* infile = "day3.in";

    FILE* in = fopen (infile, "r");
    if (!in)
    {
        printf ("Error opening file %s\n", infile);
        return 1;
    }

    array* priorities = read_knapsacks (in);

    printf("PART A: %d points\n", sum_first_n (priorities, priorities->size));

    da_destroy (&priorities);

    in = fopen (infile, "r");
    if (!in)
    {
        printf ("Error opening file %s\n", infile);
        return 1;
    }

    priorities = read_knapsacks_trio (in);

    printf("PART B: %d points\n", sum_first_n (priorities, priorities->size));

    da_destroy (&priorities);
}