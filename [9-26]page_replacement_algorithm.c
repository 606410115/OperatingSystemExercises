#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define RANDOM_REF_STR_LEN 20
#define TYPE_INT = 0

typedef enum LIST_TYPE {
    QUEUE = 0,
    STACK = 1
} LIST_TYPE;

struct Node {
    int val;
    struct Node* next;
};

typedef struct Node Node;

struct Queue {
    Node* head, *tail;
    int length;
};

struct Stack {
    Node* top;
    int length;
};

typedef struct Queue Queue;
typedef struct Stack Stack;

void print_int_list(void*, LIST_TYPE);
Node* new_node(int);
int queue_get_by_index(Queue*, int);
void queue_remove(Queue*, int);
void queue_push(Queue*, int);
void queue_pop(Queue*);
int in_queue(Queue*, int);
int stack_get_by_index(Stack*, int);
void stack_push(Stack*, int);
void stack_remove_bottom(Stack*);
void stack_remove_and_push(Stack*, int);
int in_stack(Stack*, int);
  
void fifo(int[], int);
void lru(int[], int);
void opt(int[], int);

int main() {
    srand(time(NULL));
    int i;
    int rand_ref_str[] = {7, 2, 3, 1, 2, 5, 3, 4, 6, 7, 7, 1, 0, 5, 4, 6, 2, 3, 0, 1};
//     int rand_ref_str[RANDOM_REF_STR_LEN], i;
//     for(i=0; i<RANDOM_REF_STR_LEN; i++) rand_ref_str[i] = rand() % 10;
    int frame_number = 3;//rand() % 8 + 1;
    fifo(rand_ref_str, frame_number);
    lru(rand_ref_str, frame_number);
    opt(rand_ref_str, frame_number);
    return 0;
}

void print_int_list(void* list, LIST_TYPE l_t) {
    Queue *q;
    Stack *s;
    Node* cur;
    int i, length;
    switch(l_t) {
        case QUEUE:
            q = (Queue*)list;
            cur = q->head;
            length = q->length;
            break;
        case STACK:
            s = (Stack*)list;
            cur = s->top;
            length = s->length;
            break;
    }
    for(i=0; i<length; i++) {
        printf("%d ", cur->val);
        cur = cur->next;
    }
    puts("");
}

Node* new_node(int v) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = v;
    node->next = NULL;
    return node;
}

int queue_get_by_index(Queue* q, int index) {
    int i;
    if(index > q->length-1) return -1;
    Node* cur = q->head;
    for(i=0; i<index; i++) cur = cur->next;
    return cur->val;
}

void queue_remove(Queue* q, int v) {
    int i;
    Node* pre = new_node(-1);
    Node* cur = q->head;
    pre->next = cur;
    for(i=0; i<q->length; i++) {
        if(cur->val == v) {
            if(cur == q->head) q->head = q->head->next;
            else if(cur == q->tail) q->tail = pre;
            else pre->next->next = cur->next;
            free(cur);
            --q->length;
            return;
        }
        pre->next = cur;
        cur = cur->next;
    }
}

void queue_push(Queue* q, int v) {
    if(q->length == 0) {
        q->head = q->tail = new_node(v);
        q->length = 1;
    } else {
        q->tail->next = new_node(v);
        q->tail = q->tail->next;
        ++q->length;
    }
}

void queue_pop(Queue* q) {
    if(q->length == 0) return;
    if(q->length == 1) {
        free(q->head);
        q->length = 0;
    } else {
        Node* temp = q->head;
        q->head = q->head->next;
        free(temp);
        --q->length;
    }
}

int in_queue(Queue* q, int v) {
    int i;
    Node* cur = q->head;
    for(i=0; i<q->length; i++) {
        if(cur->val == v) return 1;
        cur = cur->next;
    }
    return 0;
}

int stack_get_by_index(Stack* s, int index) {
    int i;
    if(index > s->length-1) return -1;
    Node* cur = s->top;
    for(i=0; i<index; i++) cur = cur->next;
    return cur->val;
}

void stack_push(Stack* s, int v) {
    if(s->length == 0) {
        s->top = new_node(v);
        s->length = 1;
    } else {
        Node* _new_node = new_node(v);
        _new_node->next = s->top;
        s->top = _new_node;
        ++s->length;
    }
}

void stack_remove_bottom(Stack* s) {
    if(s->length == 0) return;
    if(s->length == 1) {
        free(s->top);
        s->length = 0;
    } else {
        Node* node_to_delete = s->top;
        int i;
        for(i=0; i<s->length-2; i++) node_to_delete = node_to_delete->next;
        free(node_to_delete->next);
        node_to_delete->next = NULL;
        --s->length;
    }
}

void stack_remove_and_push(Stack* s, int v) {
    Node *pre = new_node(-1); // an empty node used to follow cur pointer
    Node *cur = s->top;
    pre->next = cur;
    int i;
    for(i=0; i<s->length; i++) {
        if(cur->val == v) {
            if(s->length == 1 || cur == s->top) return; // the first node
            else if(i == s->length-1) { // the last node
                pre->next->next = NULL;
            } else {
                pre->next->next = cur->next;
            }
            cur->next = s->top;
            s->top = cur;
            return;
        }
        pre->next = cur;
        cur = cur->next;
    }
}

int in_stack(Stack* s, int v) {
    int i;
    Node* cur = s->top;
    for(i=0; i<s->length; i++) {
        if(cur->val == v) return 1;
        cur = cur->next;
    }
    return 0;
}

void fifo(int rand_ref_str[], int frame_number) {
    int page_fault_time = 0, i;
    Queue frames;
    frames.length = 0;
    for(i=0; i<RANDOM_REF_STR_LEN; i++) {
        if(in_queue(&frames, rand_ref_str[i]) == 0) {
            ++page_fault_time;
            queue_push(&frames, rand_ref_str[i]);
            if(frames.length > frame_number) queue_pop(&frames);
            print_int_list(&frames, QUEUE);
        }
    }
    printf("FIFO page fault time: %d\n", page_fault_time);
}

void lru(int rand_ref_str[], int frame_number) {
    int page_fault_time = 0, i;
    Stack frames;
    frames.length = 0;
    for(i=0; i<RANDOM_REF_STR_LEN; i++) {
        if(in_stack(&frames, rand_ref_str[i]) == 0) {
            ++page_fault_time;
            stack_push(&frames, rand_ref_str[i]);
            if(frames.length > frame_number) stack_remove_bottom(&frames);
            print_int_list(&frames, STACK);
        } else stack_remove_and_push(&frames, rand_ref_str[i]);
    }
    printf("LRU page fault time: %d\n", page_fault_time);
}

void opt(int rand_ref_str[], int frame_number) {
    int page_fault_time = 0, i;
    Queue frames;
    frames.length = 0;
    for(i=0; i<RANDOM_REF_STR_LEN; i++) {
        if(!in_queue(&frames, rand_ref_str[i])) {
            ++page_fault_time;
            if(frames.length == frame_number) {
                Stack s;
                s.length = 0;
                int j;
                for(j=i+1; j<RANDOM_REF_STR_LEN; j++) {
                    if(in_queue(&frames, rand_ref_str[j]) && !in_stack(&s, rand_ref_str[j]))
                        stack_push(&s, rand_ref_str[j]);    
                }
                int replace_val = -1;
                if(s.length > 0) replace_val = s.top->val;
                for(j=0; j<frames.length; j++) {
                    int frame = queue_get_by_index(&frames, j);
                    if(!in_stack(&s, frame)) {
                        replace_val = frame;
                        break;
                    }
                }
                queue_remove(&frames, replace_val);
            }
            queue_push(&frames, rand_ref_str[i]);
            print_int_list(&frames, QUEUE);
        }
    }
    printf("OPT page fault time: %d\n", page_fault_time);
}