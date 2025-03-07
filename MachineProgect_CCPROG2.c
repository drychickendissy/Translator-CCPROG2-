/*********************************************************************************************************
This is to certify that this project is our own work, based on our personal efforts in studying and applying the concepts
learned. We have constructed the functions and their respective algorithms and corresponding code by ourselves. The
program was run, tested, and debugged by our own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
Edmund Kendrick D. Bilanes, DLSU ID# 12414980
Spencer Caleb S. Lim Un, DLSU ID# 12414778
*********************************************************************************************************/

#include <stdio.h>
#include <string.h>
//----------------------------------------------------------------------------------------------------------
// Place definitions here: 

#define MAX_ENTRIES 150
#define MAX_LETTERS 20

//----------------------------------------------------------------------------------------------------------
// Structs

//  Struct TranslationPair stores a word and its language
typedef struct 
{
    char language[20];    // Language name
    char translation[20]; // Translated word
} TranslationPair;

// Struct Entry stores up to 10 translations per word
typedef struct 
{
    TranslationPair pairs[10]; // Pairs
    int pairCount;             // Pair Count
} Entry;

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
void tokenizeInput(char *sentence, char words[][MAX_LETTERS]);
void translateTextInput();  
void translateTextFile();  
void removeSymbols(char *input, char *cleaned);
int findExistingEntry(Entry entry, int entryCount, char *lang, char *trans);

// Menu functions
int manageDataMenu(int *validMenuInput);  
void translateMenu(); 
int menu();

//----------------------------------------------------------------------------------------------------------
// Global Variables: 

Entry entries[MAX_ENTRIES];
int entryCount = 0;

//----------------------------------------------------------------------------------------------------------
// Functions:

// Functions for translation actual
/* 
This function puts the individual words in char *sentence and places them into char words[] array
NOTE: It does not take into account spaces or symbols. Use removeSymbols before using this function.
*/ 
void tokenizeInput(char *sentence, char words[][MAX_LETTERS])
{
	int i, j;
	int wordCount = 0;
	int letterCount = 0;
	
	for (j=0; j < MAX_ENTRIES; j++)
	{
		words[j][0] = '\0';
	}
	
	i=0;
	
	while (sentence[i] != '\0')
	{
		while (sentence[i] == ' ')
		{
			i++;
		}
		
		letterCount = 0;
		
		while (sentence[i] != ' ')
		{
			if (letterCount < MAX_LETTERS-1)
			{
				words[wordCount][letterCount] = sentence[i];
				letterCount++;
			}
			i++;
		}
		words[wordCount][letterCount] = '\0'; // Null-termination
		wordCount++;
	}
}

// This function removes symbols in char *input (non-numbers and non-letters)
void removeSymbols(char *input, char *cleaned)
{
    int i, j;
    
    i = 0;
    j = 0;

    while (input[i] != '\0')
    {
        if (
		(input[i] >= 'A' && input[i] <= 'Z') || 
		(input[i] >= 'a' && input[i] <= 'z') ||
		(input[i] >= '0' && input[i] <= '9') ||
		input[i] == ' ') // I included numbers and spaces
        {
            cleaned[j] = input[i];
            j++;
        }
        i++;
    }

    cleaned[j] = '\0';
}

/*
This function finds if an entry, given its language and translation, already exists and returns the index.
If it doesn't, returns -1 
*/ 
int findExistingEntry(Entry entry, int entryCount, char *lang, char *trans) // I added entry and entryCount to the parameters and changed the prototype
{
    int i, j;

    for (i = 0; i < entryCount; i++) 
	{
        for (j = 0; j < entries[i].pairCount; j++) 
		{
            if (strcmp(entries[i].pairs[j].language, lang) == 0 && strcmp(entries[i].pairs[j].translation, trans) == 0) 
			{
                return i;
            }
        }
    }

    return -1;
}

// Menu functions
/*
This function displays the menu and asks for the user's input on what they would like to choose.
If the input is not 1, 2, or 3, keep repeating the menu. Otherwise, return the input.
*/ 
int menu(int *validMenuInput)
{
	int flagMenu = 0;
	
	printf("Translator of Kendrick and Spencer. Ver 1.0\n");
	
	while (flagMenu == 0)
	{
		printf("\nPlease select an option and insert a number for that option:\n");
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
	char tempWords[MAX_ENTRIES][MAX_LETTERS]; 	// Represents tokenized sentence
												// Uses MAX_ENTRIES to be safe on the amount of valid words possible,
												// Does not take into acount invalid words (should I change it so that it can?)
	
	menu(validMenuInput);
	
	return 0;
}
