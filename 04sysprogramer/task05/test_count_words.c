#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

bool is_word_char(char c);

int count_words(const char* str);

int main()
{
    assert(count_words("") == 0);
	assert(count_words(" ") == 0);
	assert(count_words("it") == 1);
	assert(count_words("it ") == 1);
	assert(count_words("it is") == 2);
	assert(count_words("it is used to count words.") == 6);
	assert(count_words("it is used to count words. is it easy?") == 9);

    puts("=== all over ===");
    return 0;
}

bool is_word_char(char c)
{
    return isalpha(c) || isdigit(c);
}

int count_words(const char* str)
{
    typedef enum _State
    {
        INIT,
        IN,
        OUT
    } State;

    State st = OUT;
    const char* ptr = str;
    int count = 0;

    while (*ptr != '\0')
    {
        switch (st)
        {
            case INIT:
            {
                if (is_word_char(*ptr))
                {
                    st = IN;
                }
                else
                {
                    st = OUT;
                }
                ++ptr;
            }
            break;
            case IN:
            {
                if (!is_word_char(*ptr))
                {
                    st = OUT;
                    ++count;
                }
                ++ptr;
            }
            break;
            case OUT:
            {
                if (is_word_char(*ptr))
                {
                    st = IN;
                }
                ++ptr;
            }
            break;
            default:
            break;
        }
    }
    
    if (st == IN)
    {
        ++count;
    }

    return count;
}