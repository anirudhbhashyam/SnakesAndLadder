#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

#include "snakes_and_ladders.h"

void play()
{
	printf("Welcome to snakes and ladders!\n");
	char start_game_q;
	printf("Do you want to start the game? (y/n): ");
	scanf("%c", &start_game_q);

	if (start_game_q == 'n')
	{
		printf("Exited game.\n");
		return;
	}

	struct Player* p = malloc(sizeof(struct Player));
	struct Board* b = malloc(sizeof(struct Board));
	struct Entity* e = generate_entities();

	init_board(b);
	init_player(b, p);

	printf("Setup complete.\n\n");
	printf("Starting game...\n");

	while (!game_ended_q(b, p))
	{
		char roll_dice_q;
		printf("Do you want to roll the dice? (y/n): ");
		scanf("%c\n", &roll_dice_q);

		if (roll_dice_q == 'n')
		{
			printf("Game ended.");
			break;
		}

		printf("Rolling dice...\n");
		uint16_t die_number = roll_dice();
		printf("Rolled: %d\n", die_number);
		move(die_number, p, e);
		printf("Moved to %d.\n\n", p->position);
	}

	free(p);
	free(b);
	free(e);


	return;
}

u_int8_t game_ended_q(struct Board* b, struct Player* p)
{
	if (p->position == b->board[BOARD_SIZE - 1])
	{
		printf("Won!\n");
		return 1;
	}
	return 0;
}

u_int16_t roll_dice()
{
	return rand() % 6 + 1;
}

void move(uint16_t rolled, struct Player* p, struct Entity* e)
{
	p->position += rolled;

	// Check if new position coincides with entity position.
	u_int16_t i;
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
	u_int16_t i;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		b->board[i] = i + 1;
	}
}

void init_player(struct Board* b, struct Player* p)
{
	p->position = b->board[0];
}

struct Entity* generate_entities()
{
	u_int16_t i;
	struct Entity* entities = malloc(sizeof(struct Entity) * (N_ENTITIES));
	for (i = 0; i < N_ENTITIES; i++)
	{
		// Snakes
		if (i % 2 == 0)
		{
			u_int32_t bottom = rand() % (BOARD_SIZE / 2);
			u_int32_t top = rand() % (BOARD_SIZE / 2) + (BOARD_SIZE / 2); 
			(entities + i)->bottom = bottom;
			(entities + i)->top = top;
		}
		// Ladders
		else
		{
			u_int32_t bottom = rand() % (BOARD_SIZE / 2);
			u_int32_t top = rand() % (BOARD_SIZE / 2) + (BOARD_SIZE / 2); 
			(entities + i)->bottom = bottom;
			(entities + i)->top = top;
		}
	}

	return entities;
}

u_int8_t exists_val_q(const int val, int* arr, const size_t size)
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



