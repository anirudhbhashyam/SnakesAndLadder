#ifndef SNAKES_AND_LADDER_H
#define SNAKES_AND_LADDER_H

#include <stdint.h>

#define BOARD_SIZE 100
#define N_SNAKES 5
#define N_LADDERS 5
#define N_ENTITIES (N_SNAKES + N_LADDERS)


struct Board
{
	uint32_t board[BOARD_SIZE];
	uint8_t snakes[BOARD_SIZE];
	uint8_t ladders[BOARD_SIZE];
};

struct Player
{
	uint32_t position;
};

struct Entity
{
	uint32_t bottom;
	uint32_t top;
};

void play();
u_int8_t game_ended_q(struct Board*, struct Player*);
uint16_t roll_dice();
void move(uint16_t rolled, struct Player*, struct Entity*);
void init_board(struct Board*);
void init_player(struct Board*, struct Player*);
struct Entity* generate_entities();

#endif /* SNAKES_AND_LADDER_H */