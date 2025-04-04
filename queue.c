#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>
#include <string.h>

void enqueue(struct queue *q, struct game_state state) {

    uint64_t sernum = serialize(state);
    insert_at_tail(&q->data,sernum);
    

}
struct game_state dequeue(struct queue *q) {
    
    uint64_t ser = remove_from_head(&q->data);
    
    
return deserialize(ser); 
}

int beenherebefore(struct linked_list *donehad, struct game_state at) {
    uint64_t serq = serialize(at);
    struct list_node *curcheck = donehad->head;

    while (curcheck != NULL) {
        if (curcheck->value == serq) {
            return 0;
        }
        curcheck = curcheck->next;
    }
    return 1;
}

int checkfun(uint64_t expected, struct game_state current){
    if(serialize(current) == expected) {
        return 1;
    }
    return 0;
}

int number_of_moves(struct game_state start) {
    struct queue q;
    q.data.head = NULL;
    
    struct linked_list check;
    check.head = NULL;
    
    enqueue(&q, start);
    insert_at_tail(&check, serialize(start));
    struct game_state correct; 
    uint8_t cortiles[4][4] = {{1,2,3,4},
                               {5,6,7,8},
                               {9,10,11,12},
                               {13,14,15,0}};
    memcpy(correct.tiles, cortiles, sizeof(correct.tiles));
    uint64_t corser = serialize(correct);
    struct game_state u;
    struct game_state d;
    struct game_state l;
    struct game_state r; 
    struct game_state cur;
    
    while (q.data.head != NULL) {
      
        cur = dequeue(&q);
        if (checkfun(corser ,cur)) {
            free_list(q.data);
            free_list(check);
            return cur.num_steps;
        }
        
        u = cur;
        move_up(&u);
        if (beenherebefore(&check, u)) {
            u.num_steps = cur.num_steps + 1;
            enqueue(&q, u);
            insert_at_tail(&check, serialize(u));
        }
        
        d = cur;
        move_down(&d);
        if (beenherebefore(&check, d)) {
            d.num_steps = cur.num_steps + 1;
            enqueue(&q, d);
            insert_at_tail(&check, serialize(d));
        }
        
        l = cur;
        move_left(&l);
        if (beenherebefore(&check, l)) {
            l.num_steps = cur.num_steps + 1;
            enqueue(&q, l);
            insert_at_tail(&check, serialize(l));
        }
        
        r = cur;
        move_right(&r);
        if (beenherebefore(&check, r)) {
            r.num_steps = cur.num_steps + 1;
            enqueue(&q, r);
            insert_at_tail(&check, serialize(r));
        }
    }
    return -1;
}
