#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "snakes_and_ladders.h"

void play()
{
	uint16_t i;
	printf("Welcome to snakes and ladders!\n");
	printf("Do you want to start the game? (y/n): ");

	struct GameStateVariables* state = malloc(sizeof(struct GameStateVariables));
	scanf("%c", &(state->start_game_q));

	if (state->start_game_q == 'n' || state->start_game_q == 'N')
	{
		printf("Exited game.\n");
		free(state);
		return;
	}
		
	printf("Number of players: ");
	scanf("%hu", &state->n_players);

	struct Player* p = malloc(sizeof(struct Player) * state->n_players);
	struct Board* b = malloc(sizeof(struct Board));
	struct Entity* e = generate_entities();

	init_board(b);
	init_player(state, b, p);

	printf("Setup complete.");
	printf("Starting game...\n\n");

	while (!game_ended_q(state, b, p))
	{
		printf("* -- Round %u -- *\n", (state->round + 1));
		for (i = 0; i < state->n_players; i++)
		{
			printf("Do you want to roll the dice, player %u? (y/n): ", (i + 1));
			scanf(" %c", &(state->roll_dice_q));

			if (state->roll_dice_q == 'n' || state->roll_dice_q == 'N')
			{
				printf("Game ended.");
				clear_game(state, p, b, e);
				return;
			}

			printf("Rolling dice...\n");
			uint16_t die_number = roll_dice();
			printf("Player %d rolled: %hu\n", (i + 1), die_number);
			move(die_number, (p + i), e);
			printf("Player %d Moved to %u.\n\n", (i + 1), (p + i)->position);
		}
		printf("---------------------------------------------");
		printf("\n\n");
		state->round++;
	}

	clear_game(state, p, b, e);
	return;
}

uint8_t game_ended_q(struct GameStateVariables* state, struct Board* b, struct Player* p)
{
	uint16_t i;
	for (i = 0; i < state->n_players; i++)
	{
		if ((p + i)->position >= b->board[BOARD_SIZE - 1])
		{
			printf("Player %u won!\n", (i + 1));
			return 1;
		}
	}
	return 0;
}

uint16_t roll_dice()
{
	return rand() % 6 + 1;
}

void move(uint16_t rolled, struct Player* p, struct Entity* e)
{
	p->position += rolled;

	// Check if new position coincides with entity position.
	uint16_t i;
	for (i = 0; i < N_ENTITIES; i++)
	{
		// Snake.
		if (i % 2 == 0)
		{
			if (p->position == (e + i)->top)
			{
				printf("Encountered snake at position %d.\n", p->position);
				p->position = (e + i)->bottom;
			}
		}
		// Ladder.
		else
		{
			if (p->position == (e + i)->bottom)
			{
				printf("Encountered ladder at position %d.\n", p->position);
				p->position = (e + i)->top;
			}
		}
	}
}

void init_board(struct Board* b)
{
	uint16_t i;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		b->board[i] = i + 1;
	}
}

void init_player(struct GameStateVariables* state, struct Board* b, struct Player* p)
{
	uint16_t i;
	for (i = 0; i < state->n_players; i++)
	{
		(p + i)->position = b->board[0];
	}
}

struct Entity* generate_entities()
{
	uint16_t i;
	struct Entity* entities = malloc(sizeof(struct Entity) * (N_ENTITIES));
	for (i = 0; i < N_ENTITIES; i++)
	{
		// Snakes
		if (i % 2 == 0)
		{
			uint32_t bottom = rand() % (BOARD_SIZE / 2);
			uint32_t top = rand() % (BOARD_SIZE / 2) + (BOARD_SIZE / 2); 
			(entities + i)->bottom = bottom;
			(entities + i)->top = top;
		}
		// Ladders
		else
		{
			uint32_t bottom = rand() % (BOARD_SIZE / 2);
			uint32_t top = rand() % (BOARD_SIZE / 2) + (BOARD_SIZE / 2); 
			(entities + i)->bottom = bottom;
			(entities + i)->top = top;
		}
	}

	return entities;
}

uint8_t exists_val_q(const int val, int* arr, const size_t size)
{
    int i;
    for (i = 0; i < size; i++) 
	{
        if (*(arr + i) == val)
		{
			return 1;
		}    
    }
    return 0;
}

void clear_game(struct GameStateVariables* state, struct Player* p, struct Board* b, struct Entity* e)
{
	free(state);
	free(p);
	free(b);
	free(e);
	return;
}



