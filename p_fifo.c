#include <stdlib.h>
#include <stdbool.h>

/**
 * Simple FIFO
 * @author Piotr Klasa
*/

typedef int p_fifo_type;

typedef struct {
    unsigned int head;
    unsigned int tail;
    unsigned int cnt;
    unsigned int size;
    p_fifo_type* tab;
} p_fifo;

p_fifo* p_fifo_init(unsigned int size) {
    p_fifo* f = calloc(1, sizeof(p_fifo));
    f->size = size;
    f->tab = malloc(size * sizeof(p_fifo_type));
    return f;
}

bool p_fifo_put(p_fifo* f, p_fifo_type val) {
    if (f->cnt >= f->size)
        return false;
    f->tab[f->head] = val;
    f->head = (f->head + 1) % (f->size);
    f->cnt++;
    return true;
}

bool p_fifo_get(p_fifo* f, p_fifo_type *val) {
    if (f->cnt <= 0)
        return false;
    *val = f->tab[f->tail];
    return true;
}

bool p_fifo_rm(p_fifo* f, p_fifo_type *val) {
    if (!p_fifo_get(f, val))
        return false;
    f->tail = (f->tail + 1) % (f->size);
    f->cnt--;
    return true;
}

/* interface */

#define P_FIFO_INIT(f, size) p_fifo * f = p_fifo_init(size)
bool p_fifo_put(p_fifo* f, p_fifo_type val);
bool p_fifo_get(p_fifo* f, p_fifo_type *val);
bool p_fifo_rm(p_fifo* f, p_fifo_type *val);

/* example usage */

int main(void) {
    P_FIFO_INIT(f, 10);

    p_fifo_put(f, 10);

    int tmp;
    if(p_fifo_get(f, &tmp)) {
        printf("%d", tmp);
    }
    return 0;
}