//DX版本使用了三目运算符

#include <stdio.h>

int isReapYear(int yearinput)
{
    if (((yearinput) % 4 == 0 && (yearinput) % 100 != 0) ||
        ((yearinput) % 400 == 0))
    {
        printf("%d is a leap year!\n", yearinput);
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    for (int i = 1900; i <= 2000; i++)
    {
        isReapYear(i);
    }
    return 0;
}
