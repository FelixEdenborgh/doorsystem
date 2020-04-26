#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

int GetInput(char *buff, int maxSize)
{
	fgets(buff, maxSize, stdin);
	int length = strlen(buff);
	int indexOfLastChar = length - 1;
	if (buff[indexOfLastChar] == '\n')
	{
		buff[indexOfLastChar] = 0;
		return 1;
	}
	int hasExtra = 0;
	char ch;
	while (((ch = getchar()) != '\n') && (ch != EOF))
		hasExtra = 1;
	if (hasExtra)
		return 0;
	return 1;
}

int GetIntInput(char *string) {

	int newnumber;
	while (1)
	{

		if (GetInput(string, 4) == 1) {
			if (AllAreNumbers(string)) {
				newnumber = atoi(string);
				return newnumber;
			}


			printf("Ange endast nummer\n");


		}
	}
}
AllAreNumbers(char *string) {
	for (int i = 0; i < strlen(string); i++)
		if (!isdigit(string[i]))  return 0;
	return 1;
}