#include <stdio.h>

#define RECORDS_PER_PAGE 10

#define TEXTIFY(A) #A

#define _REQUEST_RECORDS(OFFSET, LIMIT)                 \
    "SELECT Fields FROM Table WHERE Conditions"     \
" OFFSET %d * " TEXTIFY(OFFSET)                 \
" LIMIT " TEXTIFY(LIMIT) ";"

#define REQUEST_RECORDS _REQUEST_RECORDS(RECORDS_PER_PAGE, RECORDS_PER_PAGE)

int main() {
    printf("%s\n", REQUEST_RECORDS);
    return 0;
}
