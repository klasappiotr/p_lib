#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define V(a) (*p_vector_ptr(v, a))

typedef int p_vector_val_type;

typedef struct {
	p_vector_val_type *tab; 
	int size;
	int unit_size;
	int cnt;
} p_vector;

p_vector * p_vector_init(int size) {
	p_vector * v = calloc(1, sizeof(p_vector));
	v->size = size;
	v->unit_size = size;
	v->cnt = 0;
	v->tab = calloc(v->size, sizeof(p_vector_val_type));
	return v;
}

p_vector_val_type * p_vector_ptr(p_vector * v, int idx) {
	if(idx >= v->cnt) {
		v->cnt = idx+1;
		
		if(v->cnt > v->size) {
			int old_size = v->size;
			v->size = ((v->cnt / v->unit_size) + 1 ) * v->unit_size;
			v->tab = realloc(v->tab, v->size * sizeof(int));
			memset(v->tab + old_size, 0, (v->size - old_size) * sizeof(int));
		}
	}
	return &v->tab[idx];
}

p_vector_val_type p_vector_get(p_vector * v, int idx) {
	return *(p_vector_ptr(v, idx));
}

void p_vector_put(p_vector * v, int idx, p_vector_val_type val) {
	*(p_vector_ptr(v, idx)) = val;
}

void p_vector_pushBack(p_vector * v, p_vector_val_type val) {
	p_vector_put(v, v->cnt, val);
}

p_vector_val_type p_vector_popBack(p_vector * v) {
    if(v->cnt == 0)
        return 0;
    p_vector_val_type tmp = *(p_vector_ptr(v, v->cnt-1));
    v->cnt--;
	return tmp;
}

int p_vector_print(p_vector * v) {
	for(int i=0; i<v->cnt; i++)
		printf("%d ", v->tab[i]);
	printf("\ncnt:%d\n", v->cnt);
}

int main() {
    // Write C code here
    
    p_vector * v = p_vector_init(10);
    p_vector_pushBack(v, 1);
    p_vector_pushBack(v, 2);
    p_vector_pushBack(v, 3);
    p_vector_pushBack(v, 4);
    
    p_vector_print(v);
    
    printf("p_vector_get %d\n", p_vector_popBack(v));
    printf("p_vector_get %d\n", p_vector_popBack(v));
    printf("p_vector_get %d\n", p_vector_popBack(v));
    printf("p_vector_get %d\n", p_vector_popBack(v));
    printf("p_vector_get %d\n", p_vector_popBack(v));
    printf("p_vector_get %d\n", p_vector_popBack(v));
    p_vector_pushBack(v, 4);
    p_vector_pushBack(v, 5);
    p_vector_print(v);
    printf("p_vector_get %d\n", p_vector_popBack(v));
    printf("p_vector_get %d\n", p_vector_popBack(v));
    v->cnt = 10;
    p_vector_print(v);
    return 0;
}