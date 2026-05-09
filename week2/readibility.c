#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    char text[1000]; 

    
    printf("Text: ");
    fgets(text, sizeof(text), stdin);

    int letters = 0;
    int words = 1;
    int sentences = 0;

    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
       
        if (isalpha(text[i]))
        {
            letters++;
        }
       
        else if (isspace(text[i]) && i > 0 && !isspace(text[i-1]))
        {
            words++;
        }
       
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    
    float L = (float)letters / words * 100;
    float S = (float)sentences / words * 100;

    
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

    
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }

    return 0;
}