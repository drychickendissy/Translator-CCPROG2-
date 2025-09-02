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
#define MAX_TRANSLATIONS 10
#define MAX_WORD 21
#define MAX_FILENAME 31
#define MAX_SENTENCE 151

//----------------------------------------------------------------------------------------------------------
// Structs

//  Struct TranslationPair stores a word and its language
typedef struct 
{
    char language[MAX_WORD];    // Language name
    char translation[MAX_WORD]; // Translated word
} TranslationPair;

// Struct Entry stores up to 10 translations per word
typedef struct 
{
    TranslationPair pairs[MAX_TRANSLATIONS]; // Pairs
    int pairCount;             // Pair Count
} Entry;

//----------------------------------------------------------------------------------------------------------
// Place function prototypes here:
// Add parameters in the future

// Data management functions:
void addEntry(Entry wordList[], int *entryCount);
void addTranslation(Entry wordList[], int entryCount);
void deleteEntry(Entry wordList[], int *entryCount);
void deleteTranslation(Entry wordList[], int *entryCount);
void displayAllEntries(Entry wordList[], int entryCount);
void searchWord(Entry wordList[], int entryCount);  
void searchTranslation(Entry wordList[], int entryCount);  
void exportToFile(Entry wordList[], int entryCount);  
void importFromFile(Entry wordList[], int *entryCount);

// Functions for translation actual
void tokenizeInput(char *sentence, char words[][MAX_WORD]);
void translateTextInput(Entry wordList[], int entryCount);  
void translateTextFile(Entry wordList[], int entryCount);  
void removeSymbols(char *input, char *cleaned);

// Menu functions
void manageDataMenu(Entry wordList[], int *entryCount);
void translateMenu(Entry wordList[], int *entryCount); 
int menu(int *validMenuInput);

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------
// Functions:

// Functions for data management functions=======================================================================

/*
This function adds a new word with a translation/set of translations to wordList.
@param wordList[] - List of entries containing the translation pairs
@param *entryCount - Number of entries wordList already has
*/ 
void 
addEntry(Entry wordList[], int *entryCount)
{
    char language[MAX_WORD], translation[MAX_WORD];
    int foundEntry[MAX_ENTRIES], foundCount = 0, i, j;
    char confirm, more;
    int doneFlag = 0;

    // Step 1: Ask for a language-translation pair (ensure input is not empty)
    do
    {
        printf("Enter language: ");
        scanf(" %20s", language);

        printf("Enter translation: ");
        scanf(" %20s", translation);
    } 
    while (strlen(language) < 1 || strlen(translation) < 1);

    // Step 2: Check if this language-translation pair already exists
    for (i = 0; i < *entryCount; i++)
    {
        for (j = 0; j < wordList[i].pairCount; j++)
        {
            if (strcmp(wordList[i].pairs[j].language, language) == 0 &&
                strcmp(wordList[i].pairs[j].translation, translation) == 0)
            {
                foundEntry[foundCount] = i;
                foundCount++;
            }
        }
    }

    // Step 3: If matching entries exist, display them
    if (foundCount > 0)
    {
        printf("\nExisting entries with \"%s - %s\":\n", language, translation);
        for (i = 0; i < foundCount; i++)
        {
            int index = foundEntry[i];
            printf("  Entry %d:\n", index + 1);
            for (j = 0; j < wordList[index].pairCount; j++)
            {
                printf("   %s: %s\n", wordList[index].pairs[j].language, wordList[index].pairs[j].translation);
            }
            printf("\n");
        }

        // Step 4: Ask if this is a new entry
        do
        {
            printf("Is this a new entry? (y/n): ");
            scanf(" %c", &confirm);
        } 
        while (confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N');

        if (confirm == 'n' || confirm == 'N')
        {
            printf("Returning to Manage Data menu...\n");
            doneFlag = 1;
        }
    }

    // Step 5: Create a new entry (only if the user confirmed)
    if (doneFlag == 0)
    {
        if (*entryCount < MAX_ENTRIES)
        {
            Entry *newEntry = &wordList[*entryCount];
            newEntry->pairCount = 0;

            // Store the first language-translation pair
            strcpy(newEntry->pairs[newEntry->pairCount].language, language);
            strcpy(newEntry->pairs[newEntry->pairCount].translation, translation);
            newEntry->pairCount++;

            // Step 6: Allow user to input additional language-translation pairs
            printf("\nAdding a new entry. Enter language-translation pairs (type \"done\" to stop):\n");

            while (doneFlag == 0)
            {
                if (newEntry->pairCount >= MAX_TRANSLATIONS)
                {
                    printf("Reached maximum translations for this entry (%d).\n", MAX_TRANSLATIONS);
                    doneFlag = 1;
                }
                else
                {
                    printf("Enter language (or \"done\" to finish): ");
                    scanf(" %20s", language);

                    if (strcmp(language, "done") == 0)
                    {
                        doneFlag = 1;  // Use flag instead of break
                    }
                    else
                    {
                        printf("Enter translation: ");
                        scanf(" %20s", translation);

                        if (strlen(language) >= 1 && strlen(translation) >= 1)
                        {
                            strcpy(newEntry->pairs[newEntry->pairCount].language, language);
                            strcpy(newEntry->pairs[newEntry->pairCount].translation, translation);
                            newEntry->pairCount++;

                            // Step 7: Ask if the user wants to add another
                            do
                            {
                                printf("Add another pair? (y/n): ");
                                scanf(" %c", &more);
                            } 
                            while (more != 'y' && more != 'Y' && more != 'n' && more != 'N');

                            if (more == 'n' || more == 'N')
                            {
                                doneFlag = 1;  // Use flag instead of break
                            }
                        }
                    }
                }
            }

            (*entryCount)++;
            printf("? New entry added successfully!\n");
        }
        else
        {
            printf("Translator is full. Cannot add more entries.\n");
        }
    }
}

/*
This function is supposed to add translations to an existing entry, asks the user to input for language and translation.
@param wordList[] - List of entries containing the translation pairs
@param *entryCount - Number of entries wordList already has
*/
void 
addTranslation(Entry wordList[], int entryCount)
{													  
    char language[MAX_WORD];     
    char translation[MAX_WORD];  
    char newLanguage[MAX_WORD];   
    char newTranslation[MAX_WORD]; 
    int i, j, index, choice, selected;
    int foundCount = 0;            
    int foundEntry[MAX_ENTRIES];   

    // Get the language and translation to search for
    printf("Enter language: ");
    scanf(" %20[^\n]", language);
        
    printf("Enter translation: ");
    scanf(" %20[^\n]", translation);

    // Search for existing entry in the word list
    for (i = 0; i < entryCount; i++)
    {
        for (j=0; j < wordList[i].pairCount; j++)
        {
        	if (strcmp(wordList[i].pairs[j].language, language) == 0 && 
            strcmp(wordList[i].pairs[j].translation, translation) == 0) 
	        {
	            // Store the index of the found entry
	            foundEntry[foundCount] = i;
	            foundCount++;
	        }
		}
    }

    // If no matching entry is found, prompt the user to add a new entry
    if (foundCount == 0)
    {
        printf("\nNo existing entry found. Please use Add Entry option.\n");
    }
    else 
    {
        // Display all found entries
        printf("\nExisting entry/entries:\n");
        for (i = 0; i < foundCount; i++)
        {
            index = foundEntry[i];
            for (j = 0; j<wordList[index].pairCount; j++)
            {
            	printf("  %s: %s\n", wordList[index].pairs[j].language, wordList[index].pairs[j].translation);
			}
        }

        // If only one entry is found, auto-select it
        if (foundCount == 1)
        {
            selected = foundEntry[0];
        }
        else
        {
            // If multiple entries are found, let the user select one
            printf("Choose entry number to add translation: ");
            scanf("%d", &choice);
            choice--; // Convert to array index
            selected = foundEntry[choice];
        }

        // Check if the entry has space for more translations
        if (wordList[selected].pairCount >= 10)
        {
            printf("Entry already has 10 translations. Cannot add more.\n");
        }
        else
        {
            // Get the new language and translation from the user
            printf("Enter new language: ");
            scanf(" %20[^\n]", newLanguage);
            
            printf("Enter new translation: ");
            scanf(" %20[^\n]", newTranslation);

            // Add the new translation to the selected entry
            strcpy(wordList[selected].pairs[wordList[selected].pairCount].language, newLanguage);
            strcpy(wordList[selected].pairs[wordList[selected].pairCount].translation, newTranslation);
            wordList[selected].pairCount++;

            printf("Translation added successfully.\n");
        }
    }
}


/*This function deletes an entry specified by the user
@param wordList[] - List of entries containing the translation pairs
@param *entryCount - Number of entries wordList already has
*/
void 
deleteEntry(Entry wordList[], int *entryCount) 
{
    int index, i;

    // Check if there are no entries to delete
    if (*entryCount == 0) 
    {
        printf("\nNo entries available to delete.\n");
    }
    else 
    {
        // Display all entries before deletion
        displayAllEntries(wordList, *entryCount);

        // Ask the user which entry to delete
        printf("Enter the entry number to delete (1 to %d): ", *entryCount);
        scanf("%d", &index);

        // Validate user input
        if (index < 1 || index > *entryCount) 
        {
            printf("Invalid entry number. Returning to Manage Data menu.\n");
        }
        else 
        {
            index--; // Convert to zero-based index

            // Shift remaining entries to fill the gap
            for (i = index; i < *entryCount - 1; i++) 
            {
                wordList[i] = wordList[i + 1];
            }

            // Reduce the total entry count
            (*entryCount)--;

            printf("Entry deleted successfully.\n");
        }
    }
}

/*This function deletes a translation under an entry
@param wordList[] - List of entries containing the translation pairs
@param *entryCount - Number of entries wordList already has
*/
void 
deleteTranslation(Entry wordList[], int *entryCount) 
{
    int entryIndex, pairIndex, i;
    char choice;
    int continueDeleting = 1;

    // Check if there are no entries available
    if (*entryCount == 0) 
    {
        printf("\nNo entries available to delete.\n");
    } 
    else 
    {
        // Display all entries before deletion
        displayAllEntries(wordList, *entryCount);

        // Ask the user which entry to delete a translation from
        printf("Enter entry number to delete a translation pair from (1 to %d): ", *entryCount);
        scanf("%d", &entryIndex);
        entryIndex--; // Convert to zero-based index

        // Validate entry index
        if (entryIndex < 0 || entryIndex >= *entryCount) 
        {
            printf("Invalid entry number.\n");
        } 
        else 
        {
            // Check if the entry has translation pairs
            if (wordList[entryIndex].pairCount == 0) 
            {
                printf("This entry has no translation pairs to delete.\n");
            } 
            else 
            {
                // Continue deleting while the user wants to and there are pairs left
                while (continueDeleting && wordList[entryIndex].pairCount > 0) 
                {
                    printf("Translation pairs for entry %d:\n", entryIndex + 1);
                    
                    // Display translation pairs for the selected entry
                    for (i = 0; i < wordList[entryIndex].pairCount; i++) 
                    {
                        printf("%d. %s - %s\n", i + 1, wordList[entryIndex].pairs[i].language, wordList[entryIndex].pairs[i].translation);
                    }

                    // Ask the user which translation pair to delete
                    printf("Enter the number of the translation pair to delete (1 to %d): ", wordList[entryIndex].pairCount);
                    scanf("%d", &pairIndex);
                    pairIndex--; // Convert to zero-based index

                    // Validate translation pair index
                    if (pairIndex < 0 || pairIndex >= wordList[entryIndex].pairCount) 
                    {
                        printf("Invalid translation pair number.\n");
                        printf("Do you want to try again? (y/n): ");
                        scanf(" %c", &choice);

                        if (choice == 'n' || choice == 'N') 
                        {
                            continueDeleting = 0;
                        }
                    } 
                    else 
                    {
                        // Shift translation pairs to fill the gap
                        for (i = pairIndex; i < wordList[entryIndex].pairCount - 1; i++) 
                        {
                            wordList[entryIndex].pairs[i] = wordList[entryIndex].pairs[i + 1];
                        }

                        // Reduce the translation pair count
                        wordList[entryIndex].pairCount--;

                        // If no translation pairs remain, delete the entry
                        if (wordList[entryIndex].pairCount == 0) 
                        {
                            printf("All translation pairs deleted. The entry will also be removed.\n");

                            // Shift entries to fill the gap
                            for (i = entryIndex; i < *entryCount - 1; i++) 
                            {
                                wordList[i] = wordList[i + 1];
                            }

                            (*entryCount)--;
                            continueDeleting = 0;
                        } 
                        else 
                        {
                            // Ask if the user wants to delete another translation from the same entry
                            printf("Translation pair deleted. Do you want to delete another pair from this entry? (y/n): ");
                            scanf(" %c", &choice);

                            if (choice != 'y' && choice != 'Y') 
                            {
                                continueDeleting = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}

/*
This function displays all the entries in the wordList.
@param wordList[] - List of entries containing the translation pairs
@param *entryCount - Number of entries wordList already has
*/
void 
displayAllEntries(Entry wordList[], int entryCount) 
{
    char choice = ' ';
    int i, j, k, index = 0, hasEnglishI, hasEnglishJ;
    Entry temp;
    TranslationPair tempPair;
    char wordI[MAX_WORD], wordJ[MAX_WORD];

    // Check if there are no entries available
    if (entryCount == 0) 
    {
        printf("\nNo entries available.\n");
    }
    else 
    {
        // Inter-entry sorting (Sort entries based on the English word if available)
        for (i = 0; i < entryCount - 1; i++) 
        {
            for (j = i + 1; j < entryCount; j++) 
            {
                hasEnglishI = 0;
                hasEnglishJ = 0;
                wordI[0] = '\0';
                wordJ[0] = '\0';

                // Find the English translation in entry i
                for (k = 0; k < wordList[i].pairCount; k++) 
                {
                    if (strcmp(wordList[i].pairs[k].language, "English") == 0) 
                    {
                        strcpy(wordI, wordList[i].pairs[k].translation);
                        hasEnglishI = 1;
                    }
                }

                // Find the English translation in entry j
                for (k = 0; k < wordList[j].pairCount; k++) 
                {
                    if (strcmp(wordList[j].pairs[k].language, "English") == 0) 
                    {
                        strcpy(wordJ, wordList[j].pairs[k].translation);
                        hasEnglishJ = 1;
                    }
                }

                // Sorting logic: Entries with English words are sorted alphabetically
                if (hasEnglishI && hasEnglishJ) 
                {
                    if (strcmp(wordI, wordJ) > 0) 
                    {
                        temp = wordList[i];
                        wordList[i] = wordList[j];
                        wordList[j] = temp;
                    }
                }
                // If entry j has English but entry i does not, swap them
                else if (!hasEnglishI && hasEnglishJ) 
                {
                    temp = wordList[i];
                    wordList[i] = wordList[j];
                    wordList[j] = temp;
                }
            }
        }

        // Loop to navigate and display entries
        while (choice != 'X' && choice != 'x') 
        {
            // Intra-entry sorting (Sort translations alphabetically by language)
            for (i = 0; i < wordList[index].pairCount - 1; i++) 
            {
                for (j = i + 1; j < wordList[index].pairCount; j++) 
                {
                    if (strcmp(wordList[index].pairs[i].language, wordList[index].pairs[j].language) > 0) 
                    {
                        tempPair = wordList[index].pairs[i];
                        wordList[index].pairs[i] = wordList[index].pairs[j];
                        wordList[index].pairs[j] = tempPair;
                    }
                }
            }

            // Display the current entry
            printf("\n== Translator Entries ==\n");
            printf("Entry %d/%d (Total Pairs: %d):\n", index + 1, entryCount, wordList[index].pairCount);

            for (i = 0; i < wordList[index].pairCount; i++) 
            {
                printf("  %s: %s\n", wordList[index].pairs[i].language, wordList[index].pairs[i].translation);
            }

            // Navigation options
            printf("\n[N] Next | [P] Previous | [X] Exit\n");
            printf("Enter choice: ");
            scanf(" %c", &choice);

            // Move to the next entry
            if ((choice == 'N' || choice == 'n') && index < entryCount - 1) 
            {
                index++;
            }
            // Move to the previous entry
            else if ((choice == 'P' || choice == 'p') && index > 0) 
            {
                index--;
            }
        }
    }
}



/*
This function is supposed to search if the word exists in the language-translation array.
@param wordList[] - List of entries containing the translation pairs
@param *entryCount - Number of entries wordList already has
*/
void 
searchWord(Entry wordList[], int entryCount) 
{
    char word[MAX_WORD];  
    char choice;  
    int foundEntry[MAX_ENTRIES];  
    int foundCount;  
    int i, j, index, entry, loop;

    foundCount = 0;
    index = 0;
    loop = 1;

    // Step 1: Ask the user for a word to search
    printf("Enter word to search: ");
    scanf(" %20s", word);  

	printf("\nSearching for \"%s\"...\n", word);
	
    // Step 2: Search through all entries
    for (i = 0; i < entryCount; i++)  
    {
        for (j = 0; j < wordList[i].pairCount; j++)  
        {
            // Step 3: If translation matches, store the entry index
            if (strcmp(wordList[i].pairs[j].translation, word) == 0)  
            {
                foundEntry[foundCount] = i;  
                foundCount++;  
            }
        }  
    }

    // Step 4: If no matches, notify the user and exit
    if (foundCount == 0)  
    {
        printf("No entries found for the word '%s'.\n", word);  
    }
    else  
    {
        // Step 5: Start displaying matching entries
        while (loop)  
        {
            // Step 6: Get the index of the current entry to display
            entry = foundEntry[index];  

            // Step 7: Display the current entry number
            printf("\nEntry %d:\n", index + 1);

            // Step 8: Display all translations for this entry
            for (j = 0; j < wordList[entry].pairCount; j++)  
            {
                printf("  %s: %s\n", wordList[entry].pairs[j].language, wordList[entry].pairs[j].translation);
            }

            // Step 9: Provide navigation options
            printf("\n[N] Next | [P] Previous | [X] Exit\n");
            printf("Enter choice: ");
            scanf(" %c", &choice);

            // Step 10: Navigate to the next entry if possible
            if ((choice == 'N' || choice == 'n') && index < foundCount - 1)  
            {
                index++;
            }

            // Step 11: Navigate to the previous entry if possible
            if ((choice == 'P' || choice == 'p') && index > 0)  
            {
                index--;
            }

            // Step 12: Exit if the user chooses to
            if (choice == 'X' || choice == 'x')  
            {
                loop = 0;
            }
        }
    }
}


/*
This function searches whether a specific translation is present or not. Prints the index where it's found and prints "no matching translation found" if there is none.
@param wordList[] - List of entries containing the translation pairs
@param *entryCount - Number of entries wordList already has
*/
void 
searchTranslation(Entry wordList[], int entryCount) 
{
    char lang[MAX_WORD], word[MAX_WORD], choice;
    int foundEntry[MAX_ENTRIES];  
    int foundCount, i, j, k, index, entry, loop, entryFound;

    foundCount = 0;
    index = 0;
    loop = 1;

    // Step 1: Get user input for language and word
    printf("Enter language: ");
    scanf(" %20s", lang);
    printf("Enter translation: ");
    scanf(" %20s", word);

    printf("\nSearching for \"%s\" in %s...\n", word, lang);

    // Step 2: Search for all matching entries
    for (i = 0; i < entryCount; i++) 
    {
        entryFound = 0;  // Reset flag for each entry

        for (j = 0; j < wordList[i].pairCount; j++) 
        {
            if (strcmp(wordList[i].pairs[j].language, lang) == 0 &&
                strcmp(wordList[i].pairs[j].translation, word) == 0) 
            {
                entryFound = 1;
            }
        }

        // Step 3: If match found, store entry index
        if (entryFound) 
        {
            foundEntry[foundCount] = i;
            foundCount++;
        }
    }

    // Step 4: If no matching translations, display message and return to menu
    if (foundCount == 0)  
    {
        printf("No entries found for '%s' in language '%s'.\n", word, lang);
    }
    else  
    {
        // Step 5: Start displaying matching entries with navigation
        while (loop)  
        {
            entry = foundEntry[index];  // Get the index of the current entry

            // Step 6: Display the current entry number
            printf("\nEntry %d:\n", index + 1);

            // Step 7: Display all translations for this entry
            for (k = 0; k < wordList[entry].pairCount; k++)  
            {
                printf("  %s: %s\n", wordList[entry].pairs[k].language, wordList[entry].pairs[k].translation);
            }

            // Step 8: Provide navigation options
            printf("\n[N] Next | [P] Previous | [X] Exit\n");
            printf("Enter choice: ");
            scanf(" %c", &choice);

            // Step 9: Navigate to the next entry if possible
            if ((choice == 'N' || choice == 'n') && index < foundCount - 1)  
            {
                index++;
            }

            // Step 10: Navigate to the previous entry if possible
            if ((choice == 'P' || choice == 'p') && index > 0)  
            {
                index--;
            }

            // Step 11: Exit if the user chooses to
            if (choice == 'X' || choice == 'x')  
            {
                loop = 0;
            }
        }
    }
}

/*
This function exports the given info of the translator into a file provided by the user. If the file doesn't exist, make a new one.
@param wordList[] - List of entries containing the translation pairs
@param *entryCount - Number of entries wordList already has
*/
void 
exportToFile(Entry wordList[], int entryCount)
{
    FILE *fp;
    char filename[MAX_FILENAME];
    int i, j;

    // Step 1: Prompt the user for a filename and ensure a valid file is opened
    do 
    {
        printf("Enter filename (max 30 characters including extension): ");
        scanf(" %30s", filename);

        fp = fopen(filename, "w");

        // Step 2: Check if the file was successfully opened
        if (fp == NULL)  
        {
            printf("Error opening file! Please try again.\n");
        }

    } 
    while (fp == NULL);

    // Step 3: Loop through each entry in wordList
    for (i = 0; i < entryCount; i++) 
    {
        // Step 4: Loop through all language-translation pairs in the current entry
        for (j = 0; j < wordList[i].pairCount; j++)  
        {
            fprintf(fp, "%s: %s\n", wordList[i].pairs[j].language, wordList[i].pairs[j].translation);
        }

        // Step 5: Add a newline after each entry to separate them
        fprintf(fp, "\n");
    }

    // Step 6: Close the file
    fclose(fp);

    // Step 7: Confirm successful file export to the user
    printf("Data saved successfully to %s.\n", filename);
}

/*
This function imports language translations from a file chosen by the user
@param wordList[] - List of entries containing the translation pairs
@param *entryCount - Number of entries wordList already has
*/
void 
importFromFile(Entry wordList[], int *entryCount)
{
    FILE *fp;
    char filename[MAX_FILENAME];
    char line[MAX_WORD * 2];
    char choice;
    int i;

    TranslationPair tempPairs[MAX_TRANSLATIONS]; 
    int tempPairCount = 0; 

    // Step 1: Get filename from user and open file
    printf("Enter filename to import: ");
    scanf(" %30s", filename);
    fp = fopen(filename, "r");

    if (fp == NULL)  
    {
        printf("Error opening file. Returning to menu.\n");
    }
    else
    {
        // Step 2: Read file line by line
        while (fgets(line, sizeof(line), fp) != NULL)
        {
            line[strcspn(line, "\n")] = '\0'; // Remove newline

            // Step 3: Empty line signals a new entry
			if (strlen(line) == 0) 
            {
                if (tempPairCount > 0) 
                {
                    // Step 4: Display and confirm entry addition
                    printf("\nEntry Preview:\n");
                    for (i = 0; i < tempPairCount; i++)
                    {
                        printf("  %s: %s\n", tempPairs[i].language, tempPairs[i].translation);
                    }
                    printf("\nAdd this entry? [Y/N]: ");
                    scanf(" %c", &choice);

                    if ((choice == 'Y' || choice == 'y')&& *entryCount < MAX_ENTRIES)  
                    {
                        wordList[*entryCount].pairCount = tempPairCount;
                        for (i = 0; i < tempPairCount; i++)
                        {
                            wordList[*entryCount].pairs[i] = tempPairs[i];
                        }
                        (*entryCount)++;
                    }
					// Step 5: Reset for next entry
                    tempPairCount = 0; 
                }
            }
            // Step 6: Process language-translation pair
			else 
            {
                if (tempPairCount < MAX_TRANSLATIONS) 
                {
                    char *langPart = strtok(line, ":");
                    char *wordPart = strtok(NULL, "");

                    if (langPart != NULL && wordPart != NULL) 
                    {
                        strncpy(tempPairs[tempPairCount].language, langPart, MAX_WORD - 1);
                        strncpy(tempPairs[tempPairCount].translation, wordPart + 1, MAX_WORD - 1);
                        tempPairs[tempPairCount].language[MAX_WORD - 1] = '\0';
                        tempPairs[tempPairCount].translation[MAX_WORD - 1] = '\0';
                        tempPairCount++;
                    }
                }
            }
        }

        // Step 7: Handle last entry if no final empty line
        if (tempPairCount > 0)
        {
            printf("\nEntry Preview:\n");
            for (i = 0; i < tempPairCount; i++)
            {
                printf("  %s: %s\n", tempPairs[i].language, tempPairs[i].translation);
            }
            printf("\nAdd this entry? [Y/N]: ");
            scanf(" %c", &choice);

            if ((choice == 'Y' || choice == 'y') && *entryCount < MAX_ENTRIES)  
            {
                wordList[*entryCount].pairCount = tempPairCount;
                for (i = 0; i < tempPairCount; i++)
                {
                    wordList[*entryCount].pairs[i] = tempPairs[i];
                }
                (*entryCount)++;
            }
        }
		// Step 8: Close file
        fclose(fp); 
        printf("Import process completed.\n");
    }
}

// Functions for translation actual ================================================================================

/* 
This function puts the individual words in char *sentence and places them into char words[] array
NOTE: It does not take into account spaces or symbols. Use removeSymbols before using this function.

@param *sentence - Sentence to be tokenized
@param words[][MAX_WORDS] - words array where the tokenized sentence will be placed in
*/ 
void 
tokenizeInput(char *sentence, char words[][MAX_WORD])
{
    int i = 0;
	int j;
	int wordCount = 0;
	int letterCount = 0;

    // Initialize words array
    for (j = 0; j < MAX_ENTRIES; j++)
    {
        words[j][0] = '\0';
    }

    while (sentence[i] != '\0')
    {
        // Skip leading spaces
        while (sentence[i] == ' ')
        {
            i++;
        }

        letterCount = 0;

        // Extract word until a space or end of string
        while (sentence[i] != ' ' && sentence[i] != '\0')
        {
            if (letterCount < MAX_WORD - 1)
            {
                words[wordCount][letterCount] = sentence[i];
                letterCount++;
            }
            i++;
        }

        // Null-terminate the word
        if (letterCount > 0)
        {
            words[wordCount][letterCount] = '\0';
            wordCount++;
        }
    }
}


/*
This function removes symbols in char *input (non-numbers and non-letters)
@param *input - input of user to be cleaned
@param *cleaned - sentence where the cleaned version of input will be placed in
*/ 

void 
removeSymbols(char *input, char *cleaned)
{
    int i, j;
    
    i = 0;
    j = 0;

    while (input[i] != '\0' && j < MAX_SENTENCE - 1)
    {
        if (
		(input[i] >= 'A' && input[i] <= 'Z') || 
		(input[i] >= 'a' && input[i] <= 'z') ||
		(input[i] >= '0' && input[i] <= '9') ||
		input[i] == ' ') // included numbers and spaces
        {
            cleaned[j] = input[i];
            j++;
        }
        i++;
    }

    cleaned[j] = '\0';
}


/*
This function translates the input given by the user based on the target language (accepts sentences and words, not accurate to grammar)
@param wordList[] - List of entries containing the translation pairs
@param *entryCount - Number of entries wordList already has
*/
void 
translateTextInput(Entry wordList[], int entryCount) 
{
    char origLang[MAX_WORD], targetLang[MAX_WORD], sentence[MAX_SENTENCE];
    char cleanedSentence[MAX_SENTENCE], words[MAX_ENTRIES][MAX_WORD];
    char translatedSentence[MAX_SENTENCE];
    char choice;
    int i, j, k, m, found, validInput;

    do 
    {
        // Step 1: Get source and target languages
        printf("Enter source language: ");
        scanf(" %20s", origLang);
        printf("Enter target language: ");
        scanf(" %20s", targetLang);

        // Step 2: Get text to translate
        printf("Enter text to translate (max 150 characters, no punctuation): ");
        scanf(" %150[^\n]", sentence);

        // Convert sentence to lowercase
        for (i = 0; sentence[i] != '\0'; i++) 
        {
            if (sentence[i] >= 'A' && sentence[i] <= 'Z') 
            {
                sentence[i] += 'a' - 'A'; // Convert to lowercase
            }
        }

        // Step 3: Clean input (remove punctuation)
        removeSymbols(sentence, cleanedSentence);

        // Step 4: Tokenize input
        tokenizeInput(cleanedSentence, words);

        // Step 5: Initialize translated sentence
        translatedSentence[0] = '\0';

        // Step 6: Translate each word
        for (i = 0; words[i][0] != '\0'; i++) 
        {
            found = 0;

            for (j = 0; j < entryCount && found == 0; j++) 
            {
                for (k = 0; k < wordList[j].pairCount; k++) 
                {
                    if (strcmp(wordList[j].pairs[k].language, origLang) == 0 && 
                        strcmp(wordList[j].pairs[k].translation, words[i]) == 0) 
                    {
                        // Step 7: Find corresponding translation in target language
                        for (m = 0; m < wordList[j].pairCount; m++) 
                        {
                            if (strcmp(wordList[j].pairs[m].language, targetLang) == 0) 
                            {
                                strcat(translatedSentence, wordList[j].pairs[m].translation);
                                found = 1;
                            }
                        }
                    }
                }
            }

            // Step 8: Use original word if no translation is found
            if (found == 0) 
            {
                strcat(translatedSentence, words[i]);
            }

            // Step 9: Add space between words
            strcat(translatedSentence, " ");
        }

        // Step 10: Display result
        printf("Translated text: %s\n", translatedSentence);

        // Step 11: Ask if the user wants to translate again (validate input)
        validInput = 0;
        while (!validInput)
        {
            printf("Translate another text? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N') 
            {
                validInput = 1;
            }
            else 
            {
                printf("Invalid input. Please enter 'y' or 'n'.\n");
            }
        }

    } 
    while (choice == 'y' || choice == 'Y');  // Step 12: Repeat if user says "yes"
}

/*
This function processes a text file by translating its content sentence by sentence based on the target language
@param wordList[] - List of entries containing the translation pairs
@param *entryCount - Number of entries wordList already has
*/
void 
translateTextFile(Entry wordList[], int entryCount)
{
    char sourceLang[MAX_WORD], targetLang[MAX_WORD], inputFilename[MAX_FILENAME], outputFilename[MAX_FILENAME];
    FILE *inputFile, *outputFile;
    char word[MAX_SENTENCE], ch;
    int wordIndex = 0, i, j, k, found;

    // Get user input for languages and file names
    printf("Enter source language: ");
    scanf("%20s", sourceLang);
    printf("Enter target language: ");
    scanf("%20s", targetLang);
    printf("Enter input filename: ");
    scanf("%30s", inputFilename);
    printf("Enter output filename: ");
    scanf("%30s", outputFilename);

    // Open input file for reading
    inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL)
    {
        printf("Error: Unable to open input file.\n");
    }
    else
    {
        // Open output file for writing
        outputFile = fopen(outputFilename, "w");
        if (outputFile == NULL)
        {
            printf("Error: Unable to open output file.\n");
            fclose(inputFile);
        }
        else
        {
            // Read file character by character
            while ((ch = fgetc(inputFile)) != EOF)
            {
                // Check if character is a sentence delimiter or whitespace
                if (ch == '.' || ch == '?' || ch == '!' || ch == ' ' || ch == '\n')
                {
                    // Process the collected word if it's not empty
                    if (wordIndex > 0)
                    {
                        word[wordIndex] = '\0'; // Null-terminate the word

                        // Convert word to lowercase manually
                        for (i = 0; word[i] != '\0'; i++)
                        {
                            if (word[i] >= 'A' && word[i] <= 'Z')
                            {
                                word[i] += 32;
                            }
                        }

                        // Search for translation in wordList
                        found = 0;
                        for (i = 0; i < entryCount; i++)
                        {
                            for (j = 0; j < wordList[i].pairCount; j++)
                            {
                                if (strcmp(wordList[i].pairs[j].language, sourceLang) == 0 &&
                                    strcmp(wordList[i].pairs[j].translation, word) == 0)
                                {
                                    for (k = 0; k < wordList[i].pairCount; k++)
                                    {
                                        if (strcmp(wordList[i].pairs[k].language, targetLang) == 0)
                                        {
                                            fprintf(outputFile, "%s ", wordList[i].pairs[k].translation);
                                            printf("%s ", wordList[i].pairs[k].translation);
                                            found = 1;
                                        }
                                    }
                                }
                            }
                        }

                        // If no translation is found, keep the original word
                        if (!found)
                        {
                            fprintf(outputFile, "%s ", word);
                            printf("%s ", word);
                        }
                        wordIndex = 0; // Reset word index for next word
                    }

                    // If character is a sentence delimiter, add a newline
                    if (ch == '.' || ch == '?' || ch == '!')
                    {
                        fprintf(outputFile, "\n");
                        printf("\n");
                    }
                }
                else
                {
                    // Store character in the word buffer if within limits
                    if (wordIndex < 150)
                    {
                        word[wordIndex++] = ch;
                    }
                }
            }

            // Close files after processing
            fclose(outputFile);
            printf("Translation completed. Saved to %s.\n", outputFilename);
        }
        fclose(inputFile);
    }
}


// Menu functions ==================================================================================

/*
This function displays the menu and asks for the user's input on what they would like to choose.
If the input is not 1, 2, or 3, keep repeating the menu. Otherwise, return the input.
@param *validMenuInput - Integer value that returns the choice of the user. Also dictates whether or not input is valid
*/ 
int 
menu(int *validMenuInput)
{
    int flagMenu = 0;
    int inputStatus;

    printf("Translator of Kendrick and Spencer. Ver 3.5\n");

    while (flagMenu == 0)
    {
        printf("\nPlease select an option and insert a number for that option:\n");
        printf("1. Manage Data\n2. Translate\n3. Exit Program\n");
        printf("Enter your choice: ");

        inputStatus = scanf("%d", validMenuInput);

        if (inputStatus != 1)
        {
            printf("\nInvalid choice! Please enter a number between 1-3.\n");

            // Clear input buffer
            while (getchar() != '\n');
        }
        else if (*validMenuInput >= 1 && *validMenuInput <= 3)
        {
            flagMenu = 1;
        }
        else
        {
            printf("\nInvalid choice! Please enter a number between 1-3.\n");
        }
    }
    return *validMenuInput;
}

/*
This function displays the menu for data manipulation and asks for the user's input.
If the input is not between 1-10, keep repeating the menu.
@param wordList[] - List of entries containing the translation pairs
@param *entryCount - Number of entries wordList already has
*/ 
void 
manageDataMenu(Entry wordList[], int *entryCount)
{
    int choice = 0;
    int exported = 0; // Track if data was exported
    int inputStatus;
	
    while (choice != 10)
    {
        printf("\n==Manage Data Menu==\n");
        printf("1. Add Entry\n");
        printf("2. Add Translation\n");
        printf("3. Delete Entry\n");
        printf("4. Delete Translation\n");
        printf("5. Display All Entries\n");
        printf("6. Search Word\n");
        printf("7. Search Translation\n");
        printf("8. Export\n");
        printf("9. Import\n");
        printf("10. Return to Main Menu\n");
        printf("Enter your choice: ");
		
		inputStatus = scanf("%d", &choice);
		
		if (inputStatus != 1)
        {
            printf("\nInvalid choice! Please enter a number between 1-10.\n");

            // Clear input buffer
            while (getchar() != '\n');
    	}
    	else if (choice > 0 && choice < 11)
    	{
	        switch (choice)
	        {
	            case 1:
	                addEntry(wordList, entryCount);
	                break;
	            case 2:
	                addTranslation(wordList, *entryCount);
	                break;
	            case 3:
	                deleteEntry(wordList, entryCount);
	                break;
	            case 4:
	                deleteTranslation(wordList, entryCount);
	                break;
	            case 5:
	                displayAllEntries(wordList, *entryCount);
	                break;
	            case 6:
	                searchWord(wordList, *entryCount);
	                break;
	            case 7:
	                searchTranslation(wordList, *entryCount);
	                break;
	            case 8:
	                exportToFile(wordList, *entryCount);
	                exported = 1; // Mark data as exported
	                break;
	            case 9:
	                importFromFile(wordList, entryCount);
	                break;
	            case 10:
	                printf("\nReturning to main menu...\n\n");
	                
	                if (!exported) // Clear data only if exported
	                {
	                    *entryCount = 0;
	                }
	                break;
	        }
        }
        else
        {
        	printf("\nInvalid choice! Please enter a number between 1-10.\n");
		}
    }
}


/*
This function displays the menu for translation and asks for the user's input.
If the input is not between 1-3, keep repeating the menu.
@param wordList[] - List of entries containing the translation pairs
@param *entryCount - Number of entries wordList already has
*/ 
void 
translateMenu(Entry wordList[], int *entryCount)
{
	int choice = 0;
	int inputStatus;
	
	while (choice !=3)
	{
		printf("\n==Translate Menu==\n");
        printf("1. Translate Text Input\n");
        printf("2. Translate Text File\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        
        inputStatus = scanf("%d", &choice);
		
		if (inputStatus != 1)
        {
            printf("\nInvalid choice! Please enter a number between 1-3.\n");

            // Clear input buffer
            while (getchar() != '\n');
    	}
    	else if (choice > 0 && choice < 4)
    	{
	        switch (choice)
	        {
	        	case 1:
	        		translateTextInput(wordList, *entryCount);
	        		break;
	        	case 2:
	        		translateTextFile(wordList, *entryCount);
	        		break;
	        	case 3:
	        		printf("\nReturning to main menu...\n\n");
	        		*entryCount = 0;
	        		break;
			}
		}
		else
		{
			printf("\nInvalid choice! Please enter a number between 1-3\n");
		}
	}
}

//---------------------------------------------------------------------------------------------------------

int 
main()
{
    // Declare all variables needed beforehand
    int validMenuInput = 0;
    int entryCount = 0;
    Entry wordList[MAX_ENTRIES];

    while (validMenuInput != 3)
    {
        switch (menu(&validMenuInput))  // Pass address
        {
            case 1: // Manage Data
                manageDataMenu(wordList, &entryCount);
                break;
            case 2: // Translate
                translateMenu(wordList,&entryCount);
				break;
            case 3: // Exit
                printf("\nExiting program...");
                break;
            default:
                printf("\n\nInvalid choice! Please enter a number between 1-3");
                break;
        }
    }

    return 0;
}
