#include "beggar.h"

int main() 
{
	
	int deck[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	shuffle(deck, 52, 0);
	beggar(4, deck, 1);
	return 0;
}

/*
 *
 * Returns the player ID of the player who has won; 0 if no player has won.
 *
 * Arguments:
 * 	players: array of pointers to structs for each player
 * 	Nplayers: number of players in game
 *
 * Returns:
 * 	id of winning player (or 0 if no player has won yet)
 *
 */
int finished(PLAYER **players, int Nplayers)
{
	int winner = 0;
	int i;
	for (i = 0; i < Nplayers; i++)
	{
		if (get_length(players[i] -> hand) == 52)
		{
			winner = i;
		}
	}
	return winner;
}


/*
 *
 * Finds previous player by ID.
 *
 * Arguments:
 * 	id: ID of next player from target
 * 	Nplayers: Number of players in game
 *
 * Returns:
 * 	The ID of the player previous to the player specified by 'id'
 *
 */
int previous(int id, int Nplayers)
{
	int prev;
	if (id == 0)
	{
		return Nplayers;
	}
	else
	{
		return id -1 ;
	}

}


/*
 * 
 * Plays a single round of beggar-your-neighbour.
 *
 * This function is extremely incomplete, and will run for some time before terminating due to a 
 * 	segmentation fault when dealing with rewards.
 *
 *
 * Arguments:
 * 	Nplayers: The number of players in the game
 * 	deck: A (preshuffled) deck of ints, representing denominations (suits are not represented)
 * 	talkative (redundant): An verbose mode for describing operations (indicated to be 'on' by 1)
 *
 * Returns:
 * 	The number of turns taken to finish the game (not working) 
 *
 */
int beggar(int Nplayers, int *deck, int talkative)
{
	int turns;
	int i;
	PLAYER *players[Nplayers];
	int cardCount = 52;
	printf("Card count: %d\n", cardCount);	
	for (i = 0; i < Nplayers; i++)
	{
		PLAYER *player = (PLAYER *) safe_malloc(sizeof(PLAYER));
		player -> hand = new_queue();
		player -> playing = 1;

		players[i] = player;
	}
	
	for (i = 1; i < Nplayers - 2; i++)
	{
		players[i] -> next = players[i + 1];
		players[i] -> prev = players[i - 1];
	}
	players[0] -> prev = players[Nplayers - 1];
	players[Nplayers - 1] -> next = players[0];

	int j;
	for (i = 0; i < cardCount; i++) 
	{
		enqueue(players[i%Nplayers] -> hand, deck[i]);
	}

	for (i = 0; i < Nplayers; i++)
	{
		printf("Player %d hand: ", i);
		print_queue(players[i] -> hand -> head);
	}
	int turn = 0;
	int topCard = 0;
	int winner = 0;
	int drawnCard = 0;
	int chances = 0;
	int success = 0;
	QUEUE *pile = new_queue();
	while (winner == 0)
	{
		for (i = 0; i < Nplayers; i++)
		{
			printf("\n");
			turn++;
			printf("Current turn: %d\n", turn);
			printf("Player in play: player %d\n", i);
			printf("Current pile: ");
			print_queue(pile -> head);
			
			if ((players[i] -> playing) == 0)
			{
				printf("Player %d has dropped out!\n", i);
				continue;
			}

			printf("Player %d hand is: ", i);
			print_queue(players[i] -> hand -> head);
			
			if (topCard > 10)
			{
				printf("Player %d has to pay a penalty.\n", i);
				success = 0;
				for (chances = 0; chances < (topCard - 10); chances++)
				{
					if (is_empty(players[i] -> hand))
					{
						printf("Player %d has dropped out!\n", i);
						players[i] -> playing = 0;
						players[i] -> prev -> next = players[i] -> next;
						players[i] -> next -> prev = players[i] -> prev;
						break;
					}
					drawnCard = dequeue(players[i] -> hand);
					enqueue(pile, drawnCard);
					printf("Player %d plays: %d\n", i, drawnCard);
					if (drawnCard > 10)
					{
						success = 1;
						break;
					}
				}

				if (success == 0)
				{
					printf("%p\n", players[i] -> prev);
					printf("Player %d failed to pay penalty. Player %d picks up the pile.\n", i, previous(i, Nplayers));
					merge_queue(players[i] -> prev -> hand, pile);
					empty_queue(pile);
					topCard = 0;
					i = previous(previous(i, Nplayers), Nplayers);
					printf("Current pile: ");
					print_queue(pile -> head);
					if (is_empty(players[i] -> hand))
					{
						printf("Player %d has dropped out!\n", i);
						players[i] -> playing = 0;
						players[i] -> prev -> next = players[i] -> next;
						players[i] -> next -> prev = players[i] -> prev;
					}
					continue;
				}
				else
				{
					printf("Player %d paid the penalty. Game on.\n", i);
					topCard = drawnCard;
					printf("Current pile: ");
					success = 0;
					print_queue(pile -> head);
					if (is_empty(players[i] -> hand))
					{
						printf("Player %d has dropped out!\n", i);
						players[i] -> playing = 0;
						players[i] -> prev -> next = players[i] -> next;
						players[i] -> next -> prev = players[i] -> prev;
					}
					continue;
				}
			}
			topCard = dequeue(players[i] -> hand);
			enqueue(pile, topCard);
			printf("Player %d: Playing %d!\n", i, topCard);
			printf("Current pile: ");
			print_queue(pile -> head);
			winner = finished(players, Nplayers);
		}
	}
	return 0;
}
