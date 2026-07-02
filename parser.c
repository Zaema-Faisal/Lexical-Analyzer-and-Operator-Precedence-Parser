/*
 * COMP 451 - Compiler Construction - Project Task 2
 * Operator Precedence Parser
 *
 * DESIGN:
 *   The display stack mirrors exactly what the spec shows:
 *     $ a + b * c $  (tokens, with $ at bottom)
 *   We track a parallel VALUE stack for evaluation.
 *
 *   The precedence table determines SHIFT or REDUCE at each step.
 *   SHIFT: push current input token, advance input pointer.
 *   REDUCE (POP in spec terminology):
 *     - If top is an id: pop it (its value goes to val-stack).
 *     - If top is an operator: pop op, compute result from top two
 *       values on val-stack, push result back.
 *
 *   We follow EXACTLY the sample output format from the spec.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ---- Precedence table ---- */
/* Indices: 0=id, 1=+, 2=-, 3=*, 4=/, 5=$ */
#define NR 6
static const int T[NR][NR] = {
    /*      id  +   -   *   /   $  */
    /* id */ {0, 2, 2, 2, 2, 2},
    /* +  */ {1, 2, 2, 1, 1, 2},
    /* -  */ {1, 2, 2, 1, 1, 2},
    /* *  */ {1, 2, 2, 2, 2, 2},
    /* /  */ {1, 2, 2, 2, 2, 2},
    /* $  */ {1, 1, 1, 1, 1, 0},
    /* 1=SHIFT(<)  2=REDUCE(>)  0=error/accept */
};

static int tidx(char c)
{
    if (islower(c))
        return 0;
    if (c == '+')
        return 1;
    if (c == '-')
        return 2;
    if (c == '*')
        return 3;
    if (c == '/')
        return 4;
    if (c == '$')
        return 5;
    return -1;
}

/* ---- Display stack (chars) ---- */
static char ds[256];
static int dt = -1;
static void dpush(char c) { ds[++dt] = c; }
static char dpeek(void) { return dt >= 0 ? ds[dt] : 0; }
static void dpop(void)
{
    if (dt >= 0)
        dt--;
}

/* Return precedence-table index of top terminal in display stack */
static int topterm(void)
{
    for (int i = dt; i >= 0; i--)
    {
        int x = tidx(ds[i]);
        if (x >= 0)
            return x;
    }
    return 5; /* $ */
}

/* ---- Value stack ---- */
static double vs[256];
static int vt = -1;
static void vpush(double x) { vs[++vt] = x; }
static double vpeek(void) { return vs[vt]; }
static double vpop_(void) { return vs[vt--]; }

/* ---- Print display stack, padded ---- */
static void pds(int w)
{
    int n = 0;
    for (int i = 0; i <= dt; i++)
    {
        printf("%c", ds[i]);
        n++;
    }
    for (; n < w; n++)
        printf(" ");
}

static double idv[26];

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s expr$\n", argv[0]);
        return 1;
    }
    char *inp = argv[1];
    int len = (int)strlen(inp);
    if (!len || inp[len - 1] != '$')
    {
        fprintf(stderr, "Error: must end with $\n");
        return 1;
    }

    /* Validate */
    for (int i = 0; i < len - 1; i++)
    {
        char c = inp[i];
        if (!islower(c) && c != '+' && c != '-' && c != '*' && c != '/')
        {
            fprintf(stderr, "Syntax Error: invalid token '%c'\n", c);
            return 1;
        }
    }

    /* Collect unique ids */
    int seen[26] = {0};
    char ids[26];
    int nc = 0;
    for (int i = 0; i < len - 1; i++)
        if (islower(inp[i]) && !seen[inp[i] - 'a'])
        {
            seen[inp[i] - 'a'] = 1;
            ids[nc++] = inp[i];
        }

    printf("Enter integer values of the following identifiers:\n");
    for (int i = 0; i < nc; i++)
    {
        printf("Value of %c: ", ids[i]);
        fflush(stdout);
        scanf("%lf", &idv[ids[i] - 'a']);
    }

    printf("\nThe stack implementation table for operator precedence parser");
    printf(" for the given expression is as follows:\n\n");

    int SW = 28, IW = 22;
    printf("%-*s %-*s %s\n", SW, "Stack", IW, "Input", "Action");

    /* Init: push $ on display stack */
    dpush('$');
    int pos = 0;

    /* Initial row (no action) */
    pds(SW);
    printf(" %-*s\n", IW, inp);

    for (;;)
    {
        char cur = inp[pos];
        int ti = topterm();
        int ci = tidx(cur);

        /* Accept */
        if (ti == 5 && ci == 5)
        {
            pds(SW);
            printf(" %-*s %s\n", IW, "$", "Accepted");
            break;
        }

        if (ci < 0)
        {
            printf("Syntax Error: bad token '%c'\n", cur);
            return 1;
        }

        int rel = T[ti][ci];

        if (rel == 1)
        {
            /* SHIFT */
            double v = islower(cur) ? idv[cur - 'a'] : 0;
            dpush(cur);
            if (islower(cur))
                vpush(v); /* ids contribute to value stack */
            pos++;
            pds(SW);
            printf(" %-*s Push\n", IW, inp + pos);
        }
        else if (rel == 2)
        {
            /* REDUCE = POP */
            char top = dpeek();

            if (islower(top))
            {
                /* Pop the id from display stack */
                /* Its value is already on the value stack from when it was pushed */
                dpop();
                pds(SW);
                printf(" %-*s Pop\n", IW, inp + pos);
            }
            else if (top == '+' || top == '-' || top == '*' || top == '/')
            {
                /* Pop operator, evaluate */
                char op = top;
                dpop();
                double r = vpop_();
                double l = vpop_();
                double res = 0;
                switch (op)
                {
                case '+':
                    res = l + r;
                    break;
                case '-':
                    res = l - r;
                    break;
                case '*':
                    res = l * r;
                    break;
                case '/':
                    if (r == 0)
                    {
                        printf("Error: division by zero\n");
                        return 1;
                    }
                    res = l / r;
                    break;
                }
                vpush(res);
                pds(SW);
                printf(" %-*s Pop\n", IW, inp + pos);
            }
            else if (top == '$')
            {
                /* Shouldn't reduce $, but handle gracefully */
                printf("Syntax Error: unexpected state\n");
                return 1;
            }
            else
            {
                dpop();
                pds(SW);
                printf(" %-*s Pop\n", IW, inp + pos);
            }
        }
        else
        {
            /* rel==0 and not accept => error */
            printf("Syntax Error: no relation between '%c' and '%c'\n", dpeek(), cur);
            return 1;
        }
    }

    double ans = vpeek();
    if (ans == (long long)ans)
        printf("\nThe output of the given expression is: %lld\n", (long long)ans);
    else
        printf("\nThe output of the given expression is: %.6g\n", ans);
    return 0;
}
