#include <libkern/string.h>

static void
strrev(char *str)
{
	uint64_t i;
	uint64_t j;
	unsigned char a;
	unsigned len = strlen((const char *)str);
	for (i = 0, j = len - 1; i < j; i++, j--)
	{
		a = str[i];
		str[i] = str[j];
		str[j] = a;
	}
}
 
// Implementation of itoa()
char* itoa(uint64_t num, char *str, uint64_t base)
{
    uint64_t i = 0;
 
    /* Handle 0 explicitly, otherwise empty string is pruint64_ted for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    for (size_t i = 0; i < 12; i++) {
        str[i] = '\0';
    }
 
    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
 
    // Process individual digits
    while (num != 0)
    {
        uint64_t rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    
 
    // Reverse the string
    //reverse(str, i);

    strrev(str);

    str[i] = '\0'; // Append string terminator
 
    return str;
}
