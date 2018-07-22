#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// only use ASCII chars that are tested for in testme, since all others will be ignored
#define ASCII_CHAR_INPUTS "[({ axrest})]"

// the only explicit length requirement is for a null terminaled, 5 char string, for
// the last test, so only produce strings with 5 chars
#define STRING_LENGTH 5

char inputChar()
{
    // random int from range of test chars
    int randCharIndex = (rand() % (strlen(ASCII_CHAR_INPUTS)));

    // return char from possible ASCI inputs
    return ASCII_CHAR_INPUTS[randCharIndex];
}

char *inputString()
{
    // used fixed length string that has enough characters to produce error
    // use static, so variable is only initialed once
    static char randString[STRING_LENGTH + 1];

    // generate a random char for each element of string
    int i;
    for(i = 0;i < STRING_LENGTH;i++) {
      randString[i] = inputChar();
    }

    // return random string, with chars from ASCII range
    return randString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
