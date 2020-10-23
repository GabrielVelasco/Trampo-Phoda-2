typedef struct node* Queue;
typedef struct node_doadores* Qu_don;
typedef unsigned int ui;
typedef long long ll;

void _alloc_check(const void*, const void*);
Queue _create_list();
Qu_don _create_list_d();
int _is_empty(const void*);
int _is_available(Queue*, char*);
int _push_patient(Queue*, char*, char*, int, int);
int _push_back(Queue*, char*);
int _pop_name(Queue*, char*);
int _pop_front(Queue*, char*);
int _push_back_donator(Qu_don*, char*, char[][300], int j);
int _print_donator(Qu_don*);
int _print_patient(Queue*);
int _print_disp(Queue*);
int _clear_queue_patient(Queue*);
int _clean_don_queue(Qu_don*);
void _print_node(char*, char*, int, int, int);
void _print_don_node(char*, char[][300]);
void _print_node_disp(char*, int);