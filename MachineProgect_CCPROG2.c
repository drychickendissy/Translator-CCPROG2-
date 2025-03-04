/*********************************************************************************************************
This is to certify that this project is our own work, based on our personal efforts in studying and applying the concepts
learned. We have constructed the functions and their respective algorithms and corresponding code by ourselves. The
program was run, tested, and debugged by our own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
Edmund Kendrick D. Bilanes, DLSU ID# 12414980
<your full name>, DLSU ID# <number>
*********************************************************************************************************/

#include <stdio.h>
#include <string.h>

//----------------------------------------------------------------------------------------------------------
// Place function prototypes here:
// Add parameters in the future

// Data management functions:
void addEntry();
void addTranslation();
void deleteEntry();
void displayAllEntries();
void searchWord();  
void searchTranslation();  
void exportToFile();  
void importFromFile();

// Functions for translation actual
void tokenizeInput(char *sentence, char words[20]);
void translateTextInput();  
void translateTextFile();  
void removeSymbols(char *input, char *cleaned);

// Menu functions
int manageDataMenu(int *validMenuInput);  
void translateMenu(); 
void menu();
//----------------------------------------------------------------------------------------------------------
//Structs

typedef struct 
{
    char language[20];    // Language name
    char translation[20]; // Translated word
} Translation;

//----------------------------------------------------------------------------------------------------------
// Functions:

// Functions for translation actual
void tokenizeInput(char *sentence, char words[20])
{
	int i, j;
	
	words[0] = '\0';
	
	i=0;
	j=0;
	
	while (sentence[i] != '\0')
	{
		while (sentence[i] == ' ' && !(sentence[i] > 'A' && sentence[i] < 'Z') || !(sentence[i] > 'a' && sentence[i] < 'z'))
		{
			i++;
		}
		//CONTINUE HERE	
	}
}

// Menu functions
int menu(int *validMenuInput)
{
	int flagMenu = 0;
	
	printf("Translator of Kendrick and Spencer. Ver 1.0\n\n");
	
	while (flagMenu = 0)
	{
		printf("Please select an option and insert a number for that option:\n");
		printf("1. Manage Data\n2. Translate\n3. Exit Program\n");
		
		scanf("%d", validMenuInput);
		
		if (*validMenuInput == 1 || *validMenuInput == 2 || *validMenuInput == 3)
		{
			flagMenu = 1;
		}
	}
	
	return *validMenuInput;
}


//----------------------------------------------------------------------------------------------------------


int
main()
{
	//Declare all variables needed beforehand
	int flagMenu = 0;
	int *validMenuInput = 0;
	
	menu(validMenuInput);
	
	return 0;
}
