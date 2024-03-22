#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

/**
 * Simple Unordered Map
 * @author Piotr Klasa
*/

typedef int p_umap_val_type;

typedef struct p_umap_elem_t{
    unsigned int key;
    p_umap_val_type val;
    struct p_umap_elem_t *next;
} p_umap_elem;

typedef struct {
    int cnt;
    int size;
    struct p_umap_elem ** tab;
} p_umap;

p_umap_elem * p_unmap_create_elem(unsigned int key, p_umap_val_type val) {
    p_umap_elem *e = calloc(1, sizeof(p_umap_elem));
    e->key = key;
    e->val = val;
    return e;
}

void p_unmap_rm_elem(p_umap_elem * e) {
    free(e);
}

p_umap * p_umap_init(int size) {
    p_umap * m = calloc(1, sizeof(p_umap));
    m->size = size;
	m->tab = calloc(size, sizeof(p_umap_elem*));
    return m;
}

bool p_umap_put(p_umap *m, unsigned int key, p_umap_val_type val) {
    p_umap_elem *e = m->tab[key % (m->size)];
    
    while (e && e->key != key)
        e = e->next;
    
    if (e) {
        e->val = val;
        return true;
    }    
    
    e = p_unmap_create_elem(key, val);
    e->next = m->tab[key % (m->size)];
    m->tab[key % (m->size)] = e;
    m->cnt++;
	return true;
}

bool p_umap_get(p_umap *m, unsigned int key, p_umap_val_type *val) {
    p_umap_elem *e = m->tab[key % (m->size)];
    
    while(e && e->key != key)
        e = e->next;
    
    if(!e)
        return false;
    
    *val = e->val;
    return true;
}

void p_umap_print(p_umap *m) {
    
    printf("size %d\n", m->size);
    printf("cnt  %d\n", m->cnt);
    
    for (int i=0; i<m->size; i++)
    {
         p_umap_elem *e = m->tab[i];
         printf("%2d : ", i);
         while (e) {
             printf("(%3d ->%4d) ", e->key, e->val);
             e = e->next;
         }
         printf("\n");
    }
}

bool p_umap_ext(p_umap *m, unsigned int* key, p_umap_val_type *val, bool is_min) {
    
    p_umap_val_type ext = (is_min) ? INT_MAX : INT_MIN;
    unsigned int ext_key = -1;
    
    if (m->cnt == 0)
        return false;
        
    for (int i=0; i<m->size; i++)
    {
         p_umap_elem *e = m->tab[i];
         while (e) {
             if ((e->val < ext && is_min) || (e->val > ext && !is_min)) {
                 ext = e->val;
                 ext_key = e->key;
             }
             e = e->next;
         }
    }
    *key = ext_key;
    *val = ext;
    return true;
}

bool p_umap_min(p_umap *m, unsigned int* key, p_umap_val_type *val) {
    return p_umap_ext(m, key, val, true);
}

bool p_umap_max(p_umap *m, unsigned int* key, p_umap_val_type *val) {
    return p_umap_ext(m, key, val, false);
}

bool p_umap_rm(p_umap *m, unsigned int key) {
    p_umap_elem *pre = p_unmap_create_elem(-1, -1);
    p_umap_elem *e = pre;
    pre->next = m->tab[key % (m->size)];
    bool result = false;
    
    while (e->next && e->next->key != key)
        e = e->next;
    
    if (e->next) {
        p_umap_elem *tmp = e->next;
        e->next = e->next->next;
        p_unmap_rm_elem(tmp);
        m->cnt--;
        m->tab[key % (m->size)] = pre->next;
        result = true;
    }

    p_unmap_rm_elem(pre);
    return result;
}

/* ----- Interface ----- */

p_umap * p_umap_init(int size);                                          // O(1)
bool p_umap_put(p_umap *m, unsigned int key, p_umap_val_type val);       // O(1)
bool p_umap_get(p_umap *m, unsigned int key, p_umap_val_type *val);      // O(1)
bool p_umap_rm(p_umap *m, unsigned int key);                             // O(1)
bool p_umap_min(p_umap *m, unsigned int* key, p_umap_val_type *val);     // O(n)
bool p_umap_max(p_umap *m, unsigned int* key, p_umap_val_type *val);     // O(n)
