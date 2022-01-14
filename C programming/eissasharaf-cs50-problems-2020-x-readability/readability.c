#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letter(string text);
int count_words(string text);
int count_sentences(string text);
int count_grade(int letters, int words, int sentences);

int main(void)
{
    int letters, words, sentences, grade, n = 0;
    string text = get_string("Text:");
    
    letters = count_letter(text);
    words = count_words(text);
    sentences =  count_sentences(text);
    grade =  count_grade(letters, words, sentences);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n"); 
    }    
    else    
    {
        printf("Grade %d\n", grade);
    }
}

int count_letter(string text)
{
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            letters++;
        }    
    }
    return letters;
}

int count_words(string text)
{
    int words = 0;
    
    for (int i = 0; i < strlen(text); i++)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            
            if (text[i - 1] == ' ' || text[i - 1] == '.' || text[i - 1] == ',' || text[i - 1] == '"' || i == 0)
            {
                words++;
            }    
        }
    }
    return words;
}

int count_sentences(string text)
{
    int sentences = 0;
    
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            if (isupper(text[i - 1]) || islower(text[i - 1]))
            {
                sentences++;
            }    
        }
    }
    return sentences;
}

int count_grade(int letters, int words, int sentences)
{
    float L, S, index;
    L = ((float)letters / (float)words) * 100;
    S = ((float)sentences / (float)words) * 100;
    index = 0.0588 * L - 0.296 * S - 15.8;
    return roundf(index);
    
}