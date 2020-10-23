typedef struct node* Queue;
typedef unsigned int ui;
typedef long long ll;

void _alloc_check(const void*, const void*);
Queue _create_list();
int _is_empty(const void*);
int _is_available(Queue*, char*);
int _push_patient(Queue*, char*, char*, int, int);
int _push_back(Queue*, char*);
int _pop_name(Queue*, char*);
int _pop_front(Queue*, char*);
int _print_patient(Queue*);
int _print_disp(Queue*);
int _clear_queue_patient(Queue*);
void _print_node(char*, char*, int, int, int);
void _print_node_disp(char*, int);