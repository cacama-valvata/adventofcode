#include <stdlib.h>
#include <stdio.h>

#define ROCK 1
#define PAPER 2
#define SCISSORS 3

#define LOSE 0
#define TIE 3
#define WIN 6

#define LOSE_OFF 2
#define TIE_OFF 0
#define WIN_OFF -2

int play (int self, int opp)
{
    if (self == opp)
        return self + TIE;
    else if (self == ROCK && opp == SCISSORS)
        return self + WIN;
    else if (self == PAPER && opp == ROCK)
        return self + WIN;
    else if (self == SCISSORS && opp == PAPER)
        return self + WIN;
    else
        return self + LOSE;
}

int decode_move (char self, int opp)
{
    switch (self)
    {
        case ('A'):
        case ('X'):
            return ROCK;
        case ('B'):
        case ('Y'):
            return PAPER;
        case ('C'):
        case ('Z'):
            return SCISSORS;
        default:
            return 0;
    }
}

int decode_conditional (char self, int opp)
{
    int outcome = 0;

    switch (self)
    {
        case ('X'):
            return ((opp - 1) + LOSE_OFF + 3) % 3 + 1;
        case ('Y'):
            return ((opp - 1) + TIE_OFF + 3) % 3 + 1;
        case ('Z'):
            return ((opp - 1) + WIN_OFF + 3) % 3 + 1;
        default:
            return 0;
    }
}

int read_strategy (FILE* in, int decoder (char, int))
{
    int result = 0;
    char* linebuf = calloc (256, sizeof (char));

    while (fgets (linebuf, 256, in) != NULL)
    {
        int opp = decode_move (linebuf[0], 0);
        int self = decoder (linebuf[2], opp);

        result += play (self, opp);
    }

    free (linebuf);
    fclose (in);

    return result;
}

int main ()
{
    char* infile = "day2.in";

    FILE* in = fopen (infile, "r");
    if (!in)
    {
        printf ("Error opening file %s\n", infile);
        return 1;
    }

    printf("PART A: %d points\n", read_strategy(in, decode_move));

    in = fopen (infile, "r");
    if (!in)
    {
        printf ("Error opening file %s\n", infile);
        return 1;
    }

    printf("PART B: %d points\n", read_strategy(in, decode_conditional));
}
