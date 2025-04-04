#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>
#include <string.h>

void enqueue(struct queue *q, struct game_state state) {

    uint64_t sernum = serialize(state);
    insert_at_tail(&q->data,sernum);
    

}

struct game_state dequeue(struct queue *q) {
    
    struct linked_list del;
    del.head = q->data.head;
    uint64_t ser = remove_from_head(&q->data);

    q->data.head = del.head->next;
    
    
return deserialize(ser); 
}
int checkfun(uint64_t expected, struct game_state current){
    if(serialize(current) == expected) {
        return 1;
    }
    return 0;
}

int beenherebefore(struct linked_list donehad,struct queue at){
    struct list_node *curcheck;
    curcheck = donehad.head;

    struct list_node *traverse = at.data.head;
  
    while(at.data.head != NULL){
      traverse = traverse->next;
    }

    size_t curval = traverse->value;

    while(curcheck != NULL){
        if(curval == curcheck->value){
            return 0;
        }
        curcheck = curcheck->next;
    } 
    return 1;
}

int number_of_moves(struct game_state start) {
    struct queue q;
    q.data.head = NULL;
    struct linked_list check;
    struct game_state current;
    struct game_state correct; 
    struct game_state prevstate;
    int moves = 0;
    uint8_t cortiles[4][4] = {{1,2,3,4},
                               {5,6,7,8},
                               {9,10,11,12},
                               {13,14,15,0}};
    memcpy(correct.tiles, cortiles, sizeof(correct.tiles));
    uint64_t corser = serialize(correct);
    enqueue(&q, start);
    while (q.data.head != NULL) {
        current = dequeue(&q);
        insert_at_head(&check,serialize(current));
        while(checkfun(corser, current)){
            if(checkfun(corser, current)){return moves;}

            prevstate = current;

            if(serialize(prevstate) != serialize(current) && beenherebefore(check, q)){moves++;}

            prevstate = current;
            move_up(&current);

            if(checkfun(corser, current)){return moves;}

            if(serialize(prevstate) != serialize(current) && beenherebefore(check, q)){insert_at_head(&check, serialize(current)); moves++;}

            prevstate = current;
            move_down(&current);


            if(checkfun(corser, current)){return moves;}

            if(serialize(prevstate) != serialize(current) && beenherebefore(check, q)){insert_at_head(&check, serialize(current)); moves++;}

            prevstate = current;
            move_left(&current);

            if(checkfun(corser, current)){return moves;}

            if(serialize(prevstate) != serialize(current) && beenherebefore(check, q)){insert_at_head(&check, serialize(current)); moves++;}

            prevstate = current;
            move_right(&current);

            if(checkfun(corser, current)){insert_at_head(&check, serialize(current)); moves++;}
            moves++;
        }
        enqueue(&q, current);
    }
    return -1;
}
