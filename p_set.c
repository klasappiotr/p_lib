// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>

struct p_node {
	int val;
	struct p_node * left;
	struct p_node * right;
};

struct p_set {
	struct p_node * root;
	int cnt;
};

static inline int MAX(int a, int b) {
	return (((a) > (b)) ? (a) : (b));
}

static inline int MIN(int a, int b) {
	return (((a) > (b)) ? (a) : (b));
}

struct p_node * p_node_create(int val) {
	struct p_node * node = calloc(1, sizeof(struct p_node));
	node->val = val;
	return node;
}

struct p_node * p_node_add_(struct p_node * node, int val) {
	
	if(!node)
		return p_node_create(val);
	
	if(val < node->val)
		node->left = p_node_add_(node->left, val);
	else
		node->right = p_node_add_(node->right, val);
	
	return node;
}

struct p_node * p_node_rm(struct p_node * node, int val, int* success) {
    if(!node)
        return NULL;
    
    if(val < node->val) {
        node->left = p_node_rm(node->left, val, success);
        return node;   
    }
        
    if(val > node->val) {
        node->right = p_node_rm(node->right, val, success);
        return node;
    }
    
    if(!node->left) {
        struct p_node * tmp = node->right;
		*success = 1;
        free(node);
        return tmp;
    }
   
   if(!node->right) {
       struct p_node * tmp = node->left;
	   *success = 1;
       free(node);
       return tmp;
   }
   
    // find next node
    struct p_node *prev = node;
    struct p_node * next = node->right;
    while(next->left) {
        prev = next;
        next = next->left;
    }
    
   // swap_values
    node->val = next->val;
    next->val = val;
    
    //remove nextNode;
    if(prev == node)
        prev->right = p_node_rm(next, val, success);
    else
        prev->left = p_node_rm(next, val, success);
    
    return node;
}

/*******/

struct p_set * p_set_init(void) {
	return calloc(1, sizeof(struct p_set));
}

void p_set_add(struct p_set * set, int val) {
	set->root = p_node_add_(set->root, val);
	set->cnt++;
}
    
void p_set_rm(struct p_set * set, int val) {
	int success = 0;
    set->root = p_node_rm(set->root, val, &success);
	
	if(success)
		set->cnt--;
}

int p_set_min(struct p_set * set) {
    struct p_node * node = set->root;
    if(!node)
        return 0;
    while(node->left) {
        node = node->left;
    }
    return node->val;
}

int p_set_max(struct p_set * set) {
    struct p_node * node = set->root;
    if(!node)
        return 0;
    while(node->right) {
        node = node->right;
    }
    return node->val;
}


/*-------------------------   extra -----------------------------*/

int p_tree_depth(struct p_node * node) {
	if(!node)
		return 0;
	
	return MAX(p_tree_depth(node->left), p_tree_depth(node->right)) + 1;
}

void p_set_print_(int width, int depth, int tab[depth][width], int x, int y, struct p_node * node) {
	
	if(!node)
		return;
	
	tab[y][x] = node->val;
	
	p_set_print_(width, depth, tab, x*2, y+1, node->left);
	p_set_print_(width, depth, tab, x*2+1, y+1, node->right);	
}

void p_set_print(struct p_set * set) {
	int depth = p_tree_depth(set->root);
	int width = 1;
	for(int i=1; i<depth; i++) {
		width *= 2;
	}
	
	int tab[depth][width];
	
	for(int y=0; y<depth; y++) {
	    for(int x = 0; x<width; x++) 
	        tab[y][x] = 0;
	}
	
	p_set_print_(width, depth, tab, 0, 0, set->root);
	
	int actual_width = 1;
	width*=2;
	
	for(int y=0; y<depth; y++) {
	    for(int x=0; x<actual_width; x++) {
	        for(int i=0; i<width-2; i++) {
	            if(i>(width-1)/2 && tab[y][x])
	                printf("_");	
	            else
	                printf(" ");	
	        }
	        
	        if(tab[y][x] == 0)
	            printf("    ", tab[y][x]);    
	        else 
	            printf("(%.2d)", tab[y][x]);
	            
	        for(int i=0; i<width-2; i++) {
	            if(i<(width-3)/2 && tab[y][x])
	                printf("_");	
	            else
	                printf(" ");	
	        }
	    }
	    width/=2;
	    actual_width*=2;
	    printf("\n");
	}
}


int main() {
    // Write C code here
    printf("Try n");

    struct p_set * set = p_set_init();
    p_set_add(set, 5);
    p_set_add(set, 1);
    p_set_add(set, 3);
    p_set_add(set, 9);
    p_set_add(set, 8);
    p_set_add(set, 11);
    p_set_add(set, 10);
    p_set_add(set, 13);
    p_set_print(set);
    printf("min %d max %d\n", p_set_min(set), p_set_max(set));
    printf("-----\n");

    p_set_rm(set, 11);
    p_set_print(set);
    printf("min %d max %d\n", p_set_min(set), p_set_max(set));
    printf("-----\n");


    return 0;
}