#ifndef QUEUE_H_
#define QUEUE_H_

#include "linked_list.h"
#include "tile_game.h"

struct queue {
  struct linked_list data;
};

void enqueue(struct queue *q, struct game_state state);
struct game_state dequeue(struct queue *q);

bool states_equal(struct game_state s1, struct game_state s2);
bool been_visited(struct game_state * visited, int visited_count, struct game_state state);

int number_of_moves(struct game_state start);

#endif