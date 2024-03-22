struct p_stack {
    int size;
    int cnt;
    int *tab;
};


struct p_stack * p_stack_init(int size) {
    struct p_stack *stack = calloc(1, sizeof(struct p_stack));
    stack->size = size;
    stack->tab = malloc((size +1 )* sizeof(int));
    return stack;
}

void p_stack_put(struct p_stack * stack, int val) {
    if(stack->cnt < stack->size) {
        stack->tab[stack->cnt++] = val;
    }
}

int p_stack_get(struct p_stack * stack) {
    if (stack->cnt > 0) {
        return stack->tab[--stack->cnt];
    }
    return -1;
}
