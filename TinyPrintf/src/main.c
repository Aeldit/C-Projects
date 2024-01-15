#include <stdio.h>

#include "tinyprintf.h"

int main(void)
{
    tinyprintf("Testing with positives and negatives %d %d\n", 789, -541);
    tinyprintf("Testing with unsigned %u %u\n", 789, 45684965);
    tinyprintf("Testing with %%\n");
    tinyprintf("Testing with %c\n", 't');
    tinyprintf("Testing with %s\n", "strings");
    tinyprintf("Testing with %d %s\n", 8, NULL);
    tinyprintf("My name is %s and I am %d years old\n", "Raphael", 18);
    tinyprintf("Wrong directive %t %r\n", "Raphael", 18);

    printf("\n=== School's tests :\n");
    tinyprintf("%s [%d] %s\n", "Hello", 42, "world!");
    tinyprintf("%s [%o] %s\n", "Hello", 42, "world!"); // 52
    tinyprintf("%s [%x] %s\n", "Hello", 42, "world!"); // 2a
    tinyprintf("%s [%x] %s\n", "Hello", 242, "world!"); // 2a
    tinyprintf("%%s\n", "in your head");
    tinyprintf("Good morning ACU! %t Tinyprintf is cool\n", 12);
    tinyprintf("%c%c is %s... %d too.\n", '4', '2', "the answer", '*');

    tinyprintf("\n=== Dementor errors\n");
    // tinyprintf("Big positive %d and the biggest positive %d\n", 1054843172,
    // 2147483647);
    tinyprintf("I wish a had %d%% to my traces\n", 100);
    tinyprintf("Testing %s with other %s\n", NULL, "str");
    //   SEGV because of no arguments
    // int res = tinyprintf("Testing %s with other %s\n", NULL, NULL);
    tinyprintf("When you get tired, drink a %x%x%x%x\n", 12, 10, 15, 14);
    // int res = tinyprintf("Big %x and the biggest %x\n", 1054843172,
    // 2147483647);
    tinyprintf("%x %x %x\n", 16, 255, 12192683);
    tinyprintf("J'aime les ACU 7e7\n", 2023);
    //  int res = tinyprintf("%d%%", 100);
    int res = tinyprintf("%x%x%x%x%d%d%s%c%%%u%o%s%u\n", 10, 11, 12, 13, 50, -5,
                         "string", 'r', 70, 42, "", 50451201);
    int res2 = tinyprintf("%%%x%s%s\n", 15, NULL, NULL);
    printf("\n%d", res);
    printf("\n%d\n", res2);
    tinyprintf("No %x allowed\n", 3735929054);
    tinyprintf("{%%d}\n", 5);
    tinyprintf("A little combo: %4242*\n%-4242*\n%4242*\n%-4242*\n%4242*\n");
    tinyprintf(
        "Here all options of my_tiny_printf:\n%%c\n%%s\n%%d\n%%u\n%%o\n%%x\n");
    return 0;
}
