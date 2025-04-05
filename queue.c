#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
    //insert at head

    uint64_t serialized = serialize(state);
    insert_at_head(&(q->data), serialized);
}

struct game_state dequeue(struct queue *q) {
    //remove from tail

    uint64_t serialized = remove_from_tail(&(q->data));
    struct game_state new_state = deserialize(serialized);
    
    return new_state;
}

bool states_equal(struct game_state s1, struct game_state s2) {
    // iterate through tiles to check if states are equivalent

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (s1.tiles[i][j] != s2.tiles[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

bool been_visited(struct game_state * visited, int visited_count, struct game_state state) {
    // iterate through queue to check if state has already been visited

    for (int i = 0; i < visited_count; i++) {
        if (states_equal(visited[i], state)) {
            return true;
        }
    }

    return false;
}

int number_of_moves(struct game_state start) {
    // use move_up, move_down, move_left, move_right to adjust tiles
    // initialize queue
    // initialize target state
    // check if already solved
    // enqueue given start case
    // while queue is not empty
        // set current state to first up in queue by dequeueing
        // if correct
            // return state's number of moves
        // if not correct
            // calculate all variations
                // check if variation is actually different from current
                // check if variation hasn't been visited yet
            // added all valid variations to queue
    // return -1 if not solvable

    struct queue q;
    q.data.head = NULL;

    struct game_state target = {.tiles = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}}, 
                                .empty_row = 3,
                                .empty_col = 3,
                                .num_steps = 0 // Arbitrary
                                };
    
    if (states_equal(start, target)) {
        return 0;
    }

    enqueue(&q, start);

    struct game_state visited[100000];
    int visited_count = 0;

    while(q.data.head) {
        struct game_state current = dequeue(&q);
        visited[visited_count++] = current;

        if (states_equal(current, target)) {
            free_list(q.data);
            return current.num_steps;
        }

        struct game_state up = current;
        struct game_state down = current;
        struct game_state left = current;
        struct game_state right = current;

        move_up(&up);
        move_down(&down);
        move_left(&left);
        move_right(&right);

        if (!states_equal(up, current) && !been_visited(visited, visited_count, up)) {
            enqueue(&q, up);
        }
        if (!states_equal(down, current) && !been_visited(visited, visited_count, down)) {
            enqueue(&q, down);
        }
        if (!states_equal(left, current) && !been_visited(visited, visited_count, left)) {
            enqueue(&q, left);
        }
        if (!states_equal(right, current) && !been_visited(visited, visited_count, right)) {
            enqueue(&q, right);
        }
    }

    free_list(q.data);
    return -1;
}
