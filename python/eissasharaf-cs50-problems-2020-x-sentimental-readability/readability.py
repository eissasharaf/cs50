from __future__ import division
from cs50 import get_string
from re import findall, split


def main():
    text = get_string("Text: ")
    letters = count_letters(text)
    words = count_words(text) 
    sentences = count_sentences(text)
    grade = count_grade(letters, words, sentences)
    print(sentences, words, letters)
    if grade > 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print('Grade', grade)


def count_letters(text):
    letter = 0
    for c in text:
        if not c.isalpha():
            letter += 1
    return len(text) - letter
    

def count_words(text):
    count = 1
    for c in text:
        if c == ' ':
            count += 1
    return count
    

def count_sentences(text):
    count = 0
    for c in text:
        if c == '?' or c == '!' or c == '.':
            count += 1
    if text[len(text) - 1].isalpha():
        count += 1
    return count
    

def count_grade(letters, words, sentences):
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    print(L, S)
    return round(index)
        
    
main()

