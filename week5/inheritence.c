#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int indentation);
void free_family(person *p);
char random_allele();

int main(void)
{
    srand(time(0));

    person *p = create_family(GENERATIONS);

    print_family(p, 0);

    free_family(p);
}

person *create_family(int generations)
{
    person *new_person = malloc(sizeof(person));

    if (generations > 1)
    {
        new_person->parents[0] = create_family(generations - 1);
        new_person->parents[1] = create_family(generations - 1);

        new_person->alleles[0] = new_person->parents[0]->alleles[rand() % 2];
        new_person->alleles[1] = new_person->parents[1]->alleles[rand() % 2];
    }
    else
    {
        new_person->parents[0] = NULL;
        new_person->parents[1] = NULL;
        new_person->alleles[0] = random_allele();
        new_person->alleles[1] = random_allele();
    }

    return new_person;
}

void free_family(person *p)
{
    if (p == NULL)
    {
        return;
    }

    free_family(p->parents[0]);
    free_family(p->parents[1]);

    free(p);
}

char random_allele()
{
    int r = rand() % 3;
    if (r == 0) return 'A';
    else if (r == 1) return 'B';
    else return 'O';
}

void print_family(person *p, int indentation)
{
    if (p == NULL) return;

    for (int i = 0; i < indentation; i++) printf(" ");

    printf("Generation %d, blood type %c%c\n", indentation / INDENT_LENGTH, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], indentation + INDENT_LENGTH);
    print_family(p->parents[1], indentation + INDENT_LENGTH);
}