#include <stdio.h>
#include <stdlib.h>

#include "ICal.h"
#include "CalAdd.h"
#include "CalSub.h"

int main()
{
    int a = 5;
    int b = 3;

    ICal* pCal = ICal_add_create();
    ICal_input(pCal, a, b);
    printf("%d + %d = %d\n", a, b, ICal_get_result(pCal));
    ICal_destroy(pCal);

    pCal = ICal_sub_create();
    ICal_input(pCal, a, b);
    printf("%d - %d = %d\n", a, b, ICal_get_result(pCal));
    ICal_destroy(pCal);

    return 0;
}