#include <colle_c.h>
#include "test.h"

UNIT(sum) {
    assert(sum(2, 3) == 5);
}

UNIT(sumsum) {
    assert(sum(4, sum(2, 3)) == 9);
}
