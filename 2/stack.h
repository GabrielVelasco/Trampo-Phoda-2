typedef struct node* Stack;

void _alloc_check(const void*, char*);
Stack _create_stack();
int _empty_stack(Stack);
int _full_stack(Stack);
int _push(Stack*, char);
int _pop(Stack*, char*);
int _get_top(Stack*, char*);
int _is_valid(Stack*, char*);
int _preced_par(char);
void _print(Stack);
void _clean(Stack*);