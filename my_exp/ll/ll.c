
struct _dbl_node {
    dbl_node *next;
    dbl_node *prev;
}dbl_node;

struct _dbl_head {
    dbl_node    *head;
    u_int32_t   count;
}dbl_head;

void
dbl_insert(dbl_head *head, dbl_node *node) {
    dbl_node *ptr;
    if (!head || !node) {
        return;
    }
    if (head->head) {
        ptr = head->head;
        while (ptr->next) {
            ptr = ptr->next;
        }
        ptr->next = node;
        node->prev = ptr;
    } else {
        head->head = node;
        node->prev = head->head;
    }
    head->count++;
    return;
}

void
dbl_delete(dbl_head *head, dbl_node *node) {
    if (!head || !node) {
        return;
    }
    if (head->head == node) {
        head->head = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    head->count--;
    return;
}

#define FOR_ALL_DBL(dbl_head *head, dbl_node *node) {\
    for(node = head->head; node!=NULL; node = node->next){

