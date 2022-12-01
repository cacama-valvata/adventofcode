#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int partA (FILE* in)
{
    int result = 0;

    char* linebuf = malloc (256 * sizeof (char));
    int cur = 0;
    while (fgets (linebuf, 256, in) != NULL)    // until EOF
    {
        // end of that elf's rations
        if (!strcmp (linebuf, "\n"))
        {
            if (cur > result)
                result = cur;

            cur = 0;
        }
        // more to count
        else
        {
            linebuf [ strcspn (linebuf, "\n") ] = '\0';
            cur += atoi (linebuf);
        }
    }

    free(linebuf);
    fclose (in);

    return result;
}

int partB (FILE* in)
{
    int result [] = {0, 0, 0};

    char* linebuf = malloc (256 * sizeof (char));
    int cur = 0;
    while (fgets (linebuf, 256, in) != NULL)    // until EOF
    {
        // end of that elf's rations
        if (!strcmp (linebuf, "\n"))
        {
            // find lowest and replace it
            int res = 0;
            int i;
            for (i = 1; i < 3; i++)
            {
                if (result [i] < result [res])
                    res = i;
            }
            if (cur > result [res])
                result [res] = cur;

            cur = 0;
        }
        // more to count
        else
        {
            linebuf [ strcspn (linebuf, "\n") ] = '\0';
            cur += atoi (linebuf);
        }
    }

    free(linebuf);
    fclose (in);

    int sum = 0;
    int i;
    for (i = 0; i < 3; i++)
    {
        sum += result [i];
    }

    return sum;
}


int main (int argc, char* argv[])
{
    if (argc < 2)
    {
        printf ("Specify input file.\n");
        return 1;
    }

    FILE* in = fopen (argv[1], "r");
    if (!in)
    {
        printf ("Error opening file %s\n", argv[1]);
        return 1;
    }

    printf ("PART A: %d calories\n", partA (in));

    in = fopen (argv[1], "r");
    if (!in)
    {
        printf ("Error opening file %s\n", argv[1]);
        return 1;
    }

    printf ("PART B: %d calories\n", partB (in));
}