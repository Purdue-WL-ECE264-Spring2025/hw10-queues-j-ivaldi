#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
    uint64_t serial = serialize(state);
    insert_at_tail(&q->data, serial);
}

struct game_state dequeue(struct queue *q) {
    uint64_t serial = remove_from_head(&q->data);
    return deserialize(serial);
}

int visited(struct linked_list *visit, struct game_state *state) {
    uint64_t serial = serialize(*state);
    struct list_node *cur = visit->head;
    while (cur != NULL) {
        if (cur->value == serial) {
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

int solved(struct game_state *state) {
    uint8_t solve[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}
    };
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (state->tiles[i][j] != solve[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int number_of_moves(struct game_state start) {
    struct queue q;
    q.data.head = NULL; // Initialize queue
    
    struct linked_list visit;
    visit.head = NULL; // Initialize visited linked list
    
    enqueue(&q, start); // Initial state
    insert_at_tail(&visit, serialize(start)); // Starting state is visited
    
    while (q.data.head != NULL) {
        struct game_state cur = dequeue(&q);
        if (solved(&cur)) {
            free_list(q.data);
            free_list(visit);
            return cur.num_steps;
        }
        
        struct game_state up = cur;
        move_up(&up);
        if (visited(&visit, &up) == 0) {
            up.num_steps = cur.num_steps + 1;
            enqueue(&q, up);
            insert_at_tail(&visit, serialize(up));
        }
        
        struct game_state down = cur;
        move_down(&down);
        if (visited(&visit, &down) == 0) {
            down.num_steps = cur.num_steps + 1;
            enqueue(&q, down);
            insert_at_tail(&visit, serialize(down));
        }
        
        struct game_state left = cur;
        move_left(&left);
        if (visited(&visit, &left) == 0) {
            left.num_steps = cur.num_steps + 1;
            enqueue(&q, left);
            insert_at_tail(&visit, serialize(left));
        }
        
        struct game_state right = cur;
        move_right(&right);
        if (visited(&visit, &right) == 0) {
            right.num_steps = cur.num_steps + 1;
            enqueue(&q, right);
            insert_at_tail(&visit, serialize(right));
        }
    }
    return -1;
}
