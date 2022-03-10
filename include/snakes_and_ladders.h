#ifndef SNAKES_AND_LADDERS_H
#define SNAKES_AND_LADDERS_H

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

struct GameStateVariables
{
	uint32_t round;
	uint16_t n_players;
	uint8_t start_game_q;
	uint8_t roll_dice_q;
};

void play();
u_int8_t game_ended_q(struct GameStateVariables*, struct Board*, struct Player*);
uint16_t roll_dice();
void move(uint16_t rolled, struct Player*, struct Entity*);
void init_board(struct Board*);
void init_player(struct GameStateVariables*, struct Board*, struct Player*);
struct Entity* generate_entities();
void clear_game(struct GameStateVariables*, struct Player*, struct Board*, struct Entity*);

#endif /* SNAKES_AND_LADDERS_H */