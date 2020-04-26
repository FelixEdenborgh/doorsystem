#define _CRT_SECURE_NO_WARNINGS 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "GetInput.h"
#include <time.h>
typedef struct
{

	int CardNumber;
	int state;
	time_t timeStamp;
}Card;

typedef struct
{
	Card *array;
	int antal;
}CARD_MEMORY_HOLDER;

Card *GetCard(int kortnummer, CARD_MEMORY_HOLDER *p)
{
	for (int i = 0; i < p->antal;i++)
	{
		Card *c = &p->array[i];
		if (c->CardNumber == kortnummer)
			return c;
	}
	return NULL;
}

void AddOneCardToArray(CARD_MEMORY_HOLDER *p)
{
	if (p->antal == 0)
		p->array = malloc(sizeof(Card));
	else
		p->array = realloc(p->array,
			sizeof(Card) *(p->antal + 1));

	p->antal++;
}
void PrintAll(CARD_MEMORY_HOLDER *holder)
{
	char hasAccess[20] = "has access";
	char hasNoAccess[20] = "has no access";
	printf("List of all cards\n");
	for (int i = 0; i < holder->antal; i++)
	{
		if (HasAccess(i, holder) == true)
			printf("Cardnumber: %d %s \n", holder->array[i].CardNumber, hasAccess);
		else
			printf("Cardnumber: %d %s \n", holder->array[i].CardNumber, hasNoAccess);

	}
}
void ListLoggedInCards(CARD_MEMORY_HOLDER *holder)
{
	time_t currentTime;
	currentTime = time(NULL);
	printf("List of logged in: \n");
	for (int i = 0; i < holder->antal; i++)
	{
		double seconds = difftime(currentTime, holder->array[i].timeStamp);
		if (seconds >= 3600)
			;
		else if (seconds == 0)
			printf("%d never logged in\n", holder->array[i].CardNumber);
		else
			printf("%d Logged in %.f seconds ago\n", holder->array[i].CardNumber, seconds);
	}
}
int CheckIfCardExists(int cardNumber, CARD_MEMORY_HOLDER *holder)
{
	for (int i = 0; i < holder->antal; i++)
	{
		if (holder->array[i].CardNumber == cardNumber)
		{
			return true;
		}
	}
	return false;

}
void SetAccess(CARD_MEMORY_HOLDER *holder)
{
	Card *pekareTillSenaste = &holder->array[holder->antal - 1];
	printf("Enter 1 for access, 2 for no access\n");

	scanf("%d", &pekareTillSenaste->state);
	printf("Card created\n");
}

int HasAccess(int index, CARD_MEMORY_HOLDER *holder)
{
	return holder->array[index].state == 1;
}

void CreateCard(int kontonummer, CARD_MEMORY_HOLDER *holder)
{
	Card *pekareTillSenaste = &holder->array[holder->antal - 1];

	pekareTillSenaste->CardNumber = kontonummer;

	SetAccess(holder);
}
void sleep(int milliSeconds)
{
	time_t t1, t2;
	t1 = time(NULL);
	t2 = time(NULL);
	while ((t2 - t1) * 1000 < milliSeconds)
		t2 = time(NULL);
}

Add_Remove(CARD_MEMORY_HOLDER *holder) {
	int kontonummer;
	int input;
	printf("Ange kontonummer: ");
	scanf("%d", &kontonummer);

	if (CheckIfCardExists(kontonummer, holder) == true)
	{
		Card *theCard = GetCard(kontonummer, holder);
		if (theCard->state == 1)
			printf("This card has access\n");
		else
			printf("This card has no access\n");

		printf("Enter 1 for access, 2 for no access");
		scanf("%d", &input);
		if (input == 1)
			theCard->state = input;
		else
			theCard->state = 2;
	}
	else
	{
		printf("This card does not exist\n");
		AddOneCardToArray(holder);
		CreateCard(kontonummer, holder);
	}
}

void AdminMenu(CARD_MEMORY_HOLDER *holder)
{


	int kontonummer;
	int option;
	while (true)
	{
		printf("Adminmenu - door is set to offline\n");
		printf("CURRENTLY LAMP IS: Yellow\n");
		printf("1. Remote open door\n2. List all logged in\n3. List all\n4. Add/remove access\n5. Back\n");

		scanf("%d", &option);
		switch (option)
		{
		case 1:
			printf("CURRENTLY LAMP IS: Green\n");
			sleep(3000);
			fflush(stdout);
			break;

		case 2:
			ListLoggedInCards(holder);
			break;
		case 3:
			PrintAll(holder);
			printf("\n");
			break;
		case 4:
		{
			Add_Remove(holder);
			break;
		}
		case 5:
			return;
		default:
			printf("Only enter a number between 1-5\n");
			break;
		}




	}
}

int main(void)
{
	CARD_MEMORY_HOLDER holder;
	holder.array = NULL;
	holder.antal = 0;
	char input[5];
	while (1)
	{
		printf("Please scan card to enter or A to enter Adminmode\nCURRENTLY LAMP IS: Off\n");
		GetInput(input, 5);

		if (strncmp(input, "A", 1) == false)
		{
			AdminMenu(&holder);

		}

		else
		{
			int cardNumber = atoi(input);
			Card *theCard = GetCard(cardNumber, &holder);
			if (CheckIfCardExists(cardNumber, &holder) == true)
			{
				if (theCard->state == 1)
				{
					theCard->timeStamp = time(NULL);
					//StoreLoggedIn(&theCard, &holder2);
					printf("CURRENTLY LAMP IS: Green\n");
					sleep(3000);
				}
				else
				{
					printf("CURRENTLY LAMP IS: Red\n");
					sleep(3000);
				}

			}
			else {
				printf("Card is not in the system\n");
				continue;
			}
		}
	}
	getchar();
}