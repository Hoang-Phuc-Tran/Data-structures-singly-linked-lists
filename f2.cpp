/*
 * Project:	    Focused 2
 * Author:	    Hoang Phuc Tran
 * Student ID:  8789102
 * Date:		May 23, 2022
 * Description: a program that takes in information about flights and stores the destination and
				date in a linked list to be displayed. Dynamic memory allocation is used to store
				the strings in the linked list data structure FlightNode.
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#pragma warning(disable: 4996)
#pragma warning(disable: 6001)


#define STRING_LENGTH 30


// Prototype
int fillFlightInfo(struct FlightNode** newHead, char destinationInfo[], char dateInfo[]);
void printFlightInfo(struct FlightNode* head);	
void deleteAllInfo(struct FlightNode** head);


 // Define a struct called FlightNode
struct FlightNode {
	char* destination;
	char* date;
	struct FlightNode* next;
};




int main()
{
	FlightNode* head = NULL;

	int checkCompare = 1;
	int checkReturnValue = 0;

	while(checkCompare)
	{
		char strDestination[STRING_LENGTH] = { 0 };
		char strDate[STRING_LENGTH] = { 0 };

		// Get a flight destination from the user
		printf("Enter a flight destination: ");
		fgets(strDestination, sizeof(strDestination), stdin);

		// Get rid of newline character
		strDestination[strcspn(strDestination, "\n")] = '\0';

		checkCompare = strcmp(strDestination, ".");
		// Check if user's input contains '.' character
		if (checkCompare == 0)
		{
			break;
		}
		// Get a flight date from the user
		printf("Enter a flight date: ");
		fgets(strDate, sizeof(strDate), stdin);

		// Get rid of newline character
		strDate[strcspn(strDate, "\n")] = '\0';

		checkCompare = strcmp(strDate, ".");
		// Check if user's input contains '.' character
		if (checkCompare == 0)
		{
			break;
		}

		checkReturnValue = fillFlightInfo(&head, strDestination, strDate);

		if (checkReturnValue == -1)
		{
			printf("Run out of memory");

			return -1;
		}

	}

	// Print all information in the linked list
	printFlightInfo(head);

	// Delete all information in the linked list
	deleteAllInfo(&head);

	return 0;
}



/*
* Function: fillFlightInfo()
* Description: This function will allocate a new entry in the linked list and allocate the two
				blocks of memory to contain the destination string and date string.
* Parameters: 3 parameters (phoneInfo** head(a double pointer): start of the linked list - a string containing the
			  destination information - a string containing the date information).
* Returns: int: -1 if the allocation is out of memory, 0 otherwise
*/
int fillFlightInfo(struct FlightNode** newHead, char destinationInfo[], char dateInfo[])
{
	FlightNode* temp = NULL;
	FlightNode* ptr = NULL;
	
	size_t maxLengthOfDestination = 0;
	size_t maxLengthOfDate = 0;

	// maxLengthOfDestination adds one for the null-termination
	maxLengthOfDestination = strlen(destinationInfo) + 1;

	// maxLengthOfDate adds one for the null-termination
	maxLengthOfDate = strlen(dateInfo) + 1;

	// allocate a block of memory for new block
	temp = (FlightNode*)malloc(sizeof(FlightNode));

	if (temp == NULL)
	{
		
		return -1;
	}

	// Allocate a block of memory to cantain the destination string
	temp->destination = (char*)malloc(maxLengthOfDestination * sizeof(char));

	// Check if the allocation fails
	if (temp->destination == NULL)
	{
		return -1;
	}

	// Copy the destination to new block
	strcpy(temp->destination, destinationInfo);

	// Allocate a block of memory to cantain the date string
	temp->date = (char*)malloc(maxLengthOfDate * sizeof(char));

	// Check if the allocation fails
	if (temp->date == NULL)
	{
		return -1;
	}

	// copy the date to new block
	strcpy(temp->date, dateInfo);

	temp->next = NULL;

	// check if the list is empty
	if (*newHead == NULL)
	{
		*newHead = temp;
	}
	else
	{
		ptr = *newHead;
		
		// Find the end of list
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		// Append the new block to the list
		ptr->next = temp;
	}

	return 0;
}


/*
* Function: printFlightInfo()
* Description : This function will prints all of the information contained within the list
* Parameters : 1 parameter(FlightNode *head: start of the linked list).
* Returns : void
* 
*/
void printFlightInfo(struct FlightNode *head)
{
	FlightNode* ptr = head;

	printf("\n");

	while(ptr != NULL)
	{
		// Displayed destination and date information in the next 35 characters of the line (left-justified)
		printf("%-35s", ptr->destination);
		printf("%-35s\n", ptr->date);
		ptr = ptr->next;
	}

}


/*
 * Function: deleteAllInfo(phoneInfo *head)
 *
 * Description: This function will free all allocated memory in the linked list.
 *
 * Parameter: FlightNode **head(a double pointer): start of the linked list
 * Returns: void
 */
void deleteAllInfo(struct FlightNode** head)
{
	FlightNode* curr = NULL;
	FlightNode* ptr = *head;

	// follow the chain until the pointer is null

	while (ptr != NULL)
	{
		// first, save ptr to next, then delete current
		curr = ptr;
		ptr = ptr->next;

		free(curr->destination);
		free(curr->date);
		free(curr);
	}	/* end while */

	*head = NULL;

}