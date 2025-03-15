#include "Header.h"


/*
NAME: Austin Tzib
DATE: 1/29/25
CLASS: cpts 122
OBJECTIVE:make a DIGITIAL MUSIC PLAYER where the user can sort and load a variety of different songs
and it will be able to organize it to their liking.
*/


void load(Node** pList)
{
	FILE* infile = fopen("musicPlayList.csv", "r");
	Record pCur;
	char buffer[100];
	int count = 0;
	Node *pHead = *pList;

	while (fgets(buffer, 100, infile) != NULL)
	{

		//// this is to get the first line out of the way 
		//strcpy(pCur.artist, buffer);
		// this is to get the artist 
		// if statement is looking for if the artist has a comma in between their name
		if (buffer[0] == '\"')
		{
			char* artist_token = strtok(buffer, "\"");// this checks for for ""
			/*strcpy(name, artist_token);
			strcat(name, " ");
			artist_token = strtok(NULL, ",");
			strcat(name, artist_token);*/
			strcpy(pCur.artist, artist_token);

		}
		else
		{
			char* artist_token = strtok(buffer, ","); // if no "" then get no ""
			strcpy(pCur.artist, artist_token);
		}
		// this is to get the album 
		char* album_token = strtok(NULL, ",");
		strcpy(pCur.album, album_token);

		// this is to get the title 
		char* title_token = strtok(NULL, ",");
		strcpy(pCur.title, title_token);

		// this is to get the genre 
		char* genre_token = strtok(NULL, ",");
		strcpy(pCur.genre, genre_token);

		// this is to get the length 
		char* length_token = strtok(NULL, ":");
		pCur.length.minutes = atoi(length_token);// gets the mintues 
		length_token = strtok(NULL, ",");
		pCur.length.seconds = atoi(length_token); //  gets the seconds 

		// this is to get the times played 
		char* times_played_token = strtok(NULL, ",");
		pCur.times_played = atoi(times_played_token);
		// this is to get the rating 
		char* rating_token = strtok(NULL, ",");
		pCur.rating = atoi(rating_token);

		Node* pMem = (Node*)malloc(sizeof(Node));// error finally went away with taking off pointer 

		
		
		// this is to create node of the song 
		if (pMem != NULL)
		{
			memcpy(&(pMem->record), &pCur, sizeof(Record)); // copies the record node of my pcur and puts it into 
			// the pMem which points to the record struct 

			if (*pList == NULL)
			{
				*pList = pMem;
				pMem->pNext = NULL;
				pMem->pPrev = NULL;
			}
			else
			{
				pMem->pNext = *pList;
				pMem->pPrev = NULL;
				(*pList)->pPrev = pMem;
				*pList = pMem;

			}

		}
		count++;
	}
	fclose(infile);
}

Node* createSong(Record newsong)
{
	Node* pMem = (Node*)malloc(sizeof(Node)); //took out the pointer 
	if (pMem != NULL)
	{
		pMem->record = newsong; 
		pMem->pNext = NULL;
		pMem->pPrev = NULL;
	}
	return pMem;
}



int storeSong(Node** pList)
{
	FILE* infile = fopen("musicPlayList.csv", "w");
	Node* pCur = *pList;

	if (pCur != NULL)
	{
		while (pCur != NULL)
		{
			// this stores the song into the file
			fprintf(infile, "%s,", pCur->record.artist);
			fprintf(infile, "%s,", pCur->record.album);
			fprintf(infile, "%s,", pCur->record.title);
			fprintf(infile, "%s,", pCur->record.genre);
			fprintf(infile, "%d:%d,", pCur->record.length.minutes, pCur->record.length.seconds);
			fprintf(infile, "%d,", pCur->record.times_played);
			fprintf(infile, "%d\n", pCur->record.rating);

			pCur = pCur->pNext;
		}
	}
	fclose(infile);
	return 0;
}

int edit_song(Node* pList, Record newsong)
{
	FILE* infile = fopen("musicPlayList.csv", "r");
	Node* pCur = pList;
	Node* matches[100];
	char buffer[100];
	int counter = 0;
	int choice = 0;


	printf("ENTER ARTIST: ");
	scanf("%s", newsong.artist); // using scanf to get the artist from the user

	//strcpy(newsong.artist, buffer);	
	// dont know if this is right or needed tbh
	if (pCur == NULL)
	{
		printf("The list is empty.\n");
		return 0;
	}
	// find all songs that match the artists
	while (pCur != NULL)
	{
		// trying to finding all songs that match the same artist

		if (strcmp(pCur->record.artist, newsong.artist) == 0)
		{
			// once it finds the songs that match it displays them to the user 
			matches[counter] = pCur;
			counter++;
			printf("title: %s\n", pCur->record.title);
			printf("album: %s\n", pCur->record.album);
			printf("genre: %s\n", pCur->record.genre);
			printf("length: %d:%d\n", pCur->record.length.minutes, pCur->record.length.seconds);
			printf("times played: %d\n", pCur->record.times_played);
			printf("rating: %d\n", pCur->record.rating);

		}
		pCur = pCur->pNext;
	}
	//this prompts the user to edit the song they want 
	if (counter > 1)
	{
		printf("which song would you like to edit: ");
		scanf("%d", &choice);
		if (choice < 1 || choice > counter)
		{
			printf("invalid choice try again");
		}
	}
	if (counter == 1)
	{
		pCur = matches[0];

	}
	else {
		printf("no matches were found");
	}
	// saftey code 
	if (pCur == NULL)
	{
		printf("song not found\n");
		return 0;
	}

	// edit songs that were selected 
	printf("ENTER TITLE: ");
	scanf("%s", pCur->record.title);

	printf("ENTER ALBUM: ");
	scanf("%s", pCur->record.album);

	printf("ENTER GENRE: ");
	scanf("%s", pCur->record.genre);

	printf("ENTER length of song: ");
	scanf("%d %d", &pCur->record.length.minutes, &pCur->record.length.seconds);

	printf("Enter amount of times played: ");
	scanf("%d", &pCur->record.times_played);

	printf("Enter rating");
	scanf("%d", &pCur->record.rating);

	fclose(infile);
	return 0;
}

int pause()
{
	if (getchar() == '\n')
	{
		return 1;
	}
	return 0;
}

// delete new song and use plist instead for all other functions
// i took out record new song struct and replace missing field for pList should work but not sure
int Display(Node* pList)
{
	FILE* infile = fopen("musicPlayList.csv", "r");
	Node* pCur = pList;
	Node* matches[100];
	char buffer[100];
	int counter = 0;
	int choice = 0;
	int options = 0;

	if (pCur == NULL)
	{
		printf("The list is empty.\n");
		return 0;
	}

	// if the next box in the list is not empty keep going 
	if (pCur->pNext != NULL)
	{
		// gave them options to pick which one they want 
		printf("which one would you like to choose:\n"); 
		printf("1.print all records.\n"); 
		printf("2.print all records that match an artist\n\n");
		printf("ENTER: \n");

		scanf("%d", &options);

		do
		{
			switch (options)
			{
			case 1:
				// this is print all records that are found in the csv file 
				printf("print all records in file: ");
				if (pCur != NULL)
				{
					printf("printing all records\n");
					while (pCur != NULL)
					{
						printf("ARTIST: %s\n", pCur->record.artist);
						printf("ALBUM: %s\n", pCur->record.album);
						printf("TITLE: %s\n", pCur->record.title);
						printf("GENRE: %s\n", pCur->record.genre);
						printf("TIME: %d:%d\n", pCur->record.length.minutes, pCur->record.length.seconds);
						printf("TIMES PLAYED: %d\n", pCur->record.times_played);
						printf("Rating: %d\n", pCur->record.rating);
						pCur = pCur->pNext;
					}
				}

				break;

			case 2:

				// copying code form edit function
			   // giving the user the option to enter their artist and to find all 
			   // records that match the artist they entered
				printf("ENTER ARTIST: ");
				scanf("%s", pList->record.artist); // using scanf to get the artist from the user



				while (pCur != NULL)
				{
					// trying to finding all songs that match the same artist

					if (strcmp(pCur->record.artist, pList->record.artist) == 0)
					{

						// fix this shit bro 
						// 
						// once it finds the songs that match it displays them to the user 
						matches[counter] = pCur;
						counter++;
						printf("title: %s\n", pCur->record.title);
						printf("album: %s\n", pCur->record.album);
						printf("genre: %s\n", pCur->record.genre);
						printf("length: %d:%d\n", pCur->record.length.minutes, pCur->record.length.seconds);
						printf("times played: %d\n", pCur->record.times_played);
						printf("rating: %d\n", pCur->record.rating);

					}
					pCur = pCur->pNext;
				}
				break;

			case 3:
				printf("exit");
				break;
			}
		} while (options != 3);
	}
	fclose(infile);
	return 0;
}

int rate(Node* pList)
{
	// FILE* infile = fopen("musicPlayList.csv", "r");
	Node* pCur = pList;
	int answer = 0; // this is used to rate the song and to pick a song 
	int counter = 0;

	if (pCur == NULL)
	{
		printf("The list is empty.\n");
		return 0;
	}

	// all i is doing is being a place holder for songs 1-5
	// this displays all songs 
	for (int i = 1; pCur != NULL; i++)
	{
		printf("%d : %s\n", i, pCur->record.title);
		pCur = pCur->pNext;
		counter++; 
	}

	printf("what song you want to raet: ");
	scanf("%d", &answer);

	// making sure the user cant mess up. 
	if (answer < 1 || answer > counter)
	{
		printf("invalid choice try again");
	}

	 pCur = pList; // resets current to the head of the list

	// this itterates to what song they pick
	for (int i = 1; pCur != NULL; i++)
	{
		if (i == answer)
		{
			break;
		}
		pCur = pCur->pNext;
	}

	if (pCur == NULL)
	{
		printf("song not found\n");
		return 0;
	}

	printf(" what would you rate this song: (1-5)\n");
	scanf("%d", &answer);

	if (answer < 1 || answer > 5)
	{
		printf("invalid choice try again");
	}

	pCur->record.rating = answer;
	printf("your rating updated succefully"); 
	return answer;
}

int play(Node* pList)
{
	FILE* infile = fopen("musicPlayList.csv", "r");
	Node* pCur = pList;
	int answer = 0;

	if (pCur == NULL)
	{
		printf("The list is empty.\n");
		fclose(infile);
		return 0;
	}

	// this displays all songs 
	for (int i = 1; pCur != NULL; i++)
	{
		printf("%d : %s\n", i, pCur->record.title);
		pCur = pCur->pNext;
	}
	pCur = pList;
	printf("what song you want");
	scanf("%d", &answer);

	// this moves to what song they pick
	for (int i = 1; pCur != NULL; i++)
	{
		if (i == answer)
		{
			break;
		}
		pCur = pCur->pNext;
	}

	while (pCur != NULL)
	{
		printf("title: %s\n", pCur->record.title);
		printf("album: %s\n", pCur->record.album);
		printf("genre: %s\n", pCur->record.genre);
		printf("length: %d:%d\n", pCur->record.length.minutes, pCur->record.length.seconds);
		printf("times played: %d\n", pCur->record.times_played);
		printf("rating: %d\n", pCur->record.rating);
		Sleep(3000); // this is to pause the program for 3 seconds
		system("cls");

	}

	return answer;
}

// inset function itself 
int insert(Node** pList, Record newsong)
{
	// creates a Node with the Record struct 
	Node* pCur = createSong(newsong);

	// if the list is empty set the node to the front of the list
	if (*pList == NULL)
	{
		// if the beginning of the list is empty set pcur to the beginning of the list.
		*pList = pCur;
	}

	// if the list is not empty set the node to the front of the list
	if (pList != NULL)
	{
		pCur->pNext = *pList; // sets the next link to the pointer to the front of the list 
		(*pList)->pPrev = pCur; // sets the previous link to the front of the list
		*pList = pCur; // sets the front of the list to the node
	}
}

// come back to this and make sure i put time in correctly
void insertsong(Node** pList)
{
	Record newsong; // using the record struct to hold new data 

	// all these just prompt the user to input information they want 
	// fgets retrieves the lines until new lines 
	printf("Enter artist name: \n");
	fgets(newsong.artist, 100, stdin);
	newsong.artist[strcspn(newsong.artist, "\n")] = '\0'; // this removes the new line \n from the  the begining of the line

	printf("enter album: \n");
	fgets(newsong.album, 100, stdin);
	newsong.album[strcspn(newsong.album, "\n")] = '\0';

	printf("Enter song title: \n");
	fgets(newsong.title, 100, stdin);
	newsong.title[strcspn(newsong.title, "\n")] = '\0';

	printf("Enter genre: ");
	fgets(newsong.genre, 100, stdin);
	newsong.genre[strcspn(newsong.genre, "\n")] = '\0';

	// doing the same thing but scanf lets the user put in times, ratings and times played
	// for the integers 
	printf("Enter song length (minutes seconds): ");
	scanf("%d %d", &newsong.length.minutes, &newsong.length.seconds);

	printf("Enter number of times played: ");
	scanf("%d", &newsong.times_played);


	printf("Enter rating (1-5): ");
	scanf("%d", &newsong.rating);

	// creat a new node to sotre information
	Node* pMem = (Node*)malloc(sizeof(Node));
	if (pMem != NULL)
	{
		pMem->record = newsong;
		pMem->pNext = *pList;
		pMem->pPrev = NULL;
	}

	// this sets the node to the front of the list
	if (*pList != NULL)
	{
		(*pList)->pPrev = pMem;
	}
	*pList = pMem;
}



// get help on this function
// delete function iterates through the songs that user has inputted to delete
void deleteSong(Node** pList)
{
	Node* pCur = *pList;
	char newsong[100]; // this is the song that the user wants to delete
	
	// safety code 
	if (pCur == NULL)
	{
		printf("The list is empty.\n");
		return;
	}

	// asks and receives input from the user 
	printf("Enter the title of the song to delete: ");
	fgets(newsong, 100, stdin);
	newsong[strcspn(newsong, "\n")] = '\0'; // this removes the new line \n 

	// this traverses through the list until it finds a song that matches
	while (pCur != NULL && strcmp(pCur->record.title, newsong) != 0)
	{
		pCur = pCur->pNext;
	}

	// if a node is found delete it
	if (pCur != NULL)
	{
		if (pCur->pPrev != NULL)
		{
			pCur->pPrev->pNext = pCur->pNext;
		}
		else
		{
			*pList = pCur->pNext;
		}
		if (pCur->pNext != NULL) // unlinks the node from the list 
		{
			pCur->pNext->pPrev = pCur->pPrev;
		}
		free(pCur);
		printf("Deleted song: %s\n", newsong);
	}
	else
	{
		printf("Song not found: %s\n", newsong);
	}
}

// get help with this 
int sort(Node* pList)
{
	Node* pCur = pList;
	int options = 0;
	int swapped;
	int sort;

	if (pCur == NULL)
	{
		printf("The list is empty.\n");
		return 0;
	}

	printf("what kind of sorting would you like to choose\n"); 
	// this is just for the user asking them if they want to sort the songs.

	printf("1. sort by artist\n");
	printf("2. sort by album\n");
	printf("3. sort by rating\n");
	printf("4. sort by times played\n");
	printf("5. exit sorting\n"); 
	printf("Enter choice: []"); 
	scanf("%d", &options);

	do
	{
		swapped = 0;
		while (pCur->pNext != NULL)
		{

			switch (options)
			{
			case 1:
				// this is sort int just holds the sorting results 
				printf("sorting by artist\n");
				sort = (strcmp(pCur->record.artist, pCur->pNext->record.artist));
				break;
			case 2:
				printf("sorting by album\n");
				sort = (strcmp(pCur->record.album, pCur->pNext->record.album));
				break; 
			case 3:
				printf("sorting by rating\n");
				// sorting by rating from greatest to least rated 
				sort = (pCur->record.rating - pCur->pNext->record.rating);// gets next node and the rating of it
				break;
			case 4:
				printf("sorting by times played\n");
				// sorting by greatest to least times played 
				sort = (pCur->record.times_played - pCur->pNext->record.times_played); // gets mext node and the times played of it 
				break;
			case 5:
				printf("exiting sorting\n"); 
				break;
			}

			if (sort > 0)
			{
				Record pMem = pCur->record;
				pCur->record = pCur->pNext->record;
				pCur->pNext->record = pMem;
				swapped = 1;
				// swapped equaling 1 means a swap occurred 
			}
			pCur = pCur->pNext;
		}
		pCur = pList;
	} while (swapped);
	return 0;
}

int shuffle(Node** pList) // changed it to a doubly node 
{
	Node* pCur = *pList;
	int counter = 0;

	if (pCur == NULL)
	{
		printf("The list is empty.\n");
		return 0;
	}

	// this counts the number of songs in the list 
	while (pCur != NULL)
	{
		counter++;
		pCur = pCur->pNext;
	}

	// creates nodes of pointer arrays for the songs to be tracked. 
	Node** pointArray = (Node**)malloc(counter * sizeof(Node*));

	pCur = *pList; // Reset current to the head of the list

	for (int i = 0; i < counter; i++)
	{
		pointArray[i] = pCur; //this stores each node to the current node
		pCur = pCur->pNext; // Move to the next node and repeats
	}

	// shuffles the playlist based on time 
	srand(time(NULL));

	// traversing through the songs 
	for (int i = counter - 1; i > 0; i--)
	{
		int time = rand() % (i + 1); // make a time int where it iterates 
		// through each song and it continues plus 1
		Node* temp = pointArray[i];
		pointArray[i] = pointArray[time]; // made a temp variable to hold each iteration. 
		pointArray[time] = temp;
	}

	// after is has been shuffled it iterates in the new order
	for (int i = 0; i < counter - 1; i++) // potential fix by  removing - 1
	{
		pointArray[i]->pNext = pointArray[i + 1];  
		pointArray[i + 1]->pPrev = pointArray[i]; 
	}
	pointArray[counter - 1]->pNext = NULL;
	pointArray[0]->pPrev = NULL;

	// Update the head 
	*pList = pointArray[0];

	// printing out the shuffled songs
	printf("shuffled playlist new order: \n");
	pCur = *pList;
	while (pCur != NULL) // this is just to print out the songs in the new order
	{
		printf("title: %s\n", pCur->record.title);
		pCur = pCur->pNext;
	}

	// Free the allocated memory for the array
	free(pointArray);
	return 0;
}


void main_menu(Node** pList)
{

	int option = 0;
	Record songs; 
	do
	{
		printf("_________!!WELCOME TO THE MAIN MENU!!\n_________");
		printf("1:load\n");
		printf("2:store\n");
		printf("3:display\n");
		printf("4:insert\n");
		printf("5:delete\n");
		printf("6:edit\n");
		printf("7:sort\n");
		printf("8:rate\n");
		printf("9:play\n"); 
		printf("10:shuffle\n");
		printf("11:exit\n\n");
		printf("ENTER:   \n");
		scanf("%d", &option);
		system("cls");

		switch (option)
		{
		case 1:
			load(pList);
			break;

		case 2:
			storeSong(pList);
			break;

		case 3:
			Display(*pList);
			break;

		case 4:
			insertsong(pList); // look more into this 
			break;

		case 5:

			deleteSong(pList); 
			break;

		case 6:
			edit_song(*pList, songs);
			break;

		case 7:
			sort(*pList);
			break;
		case 8:

			rate(*pList);
			break;

		case 9:
			play(*pList);
			break;

		case 10:
			shuffle(pList);
			break;

		case 11:
			printf("exit");
			break;

		default:
			printf("invalid option\n");
			break; 
		}
	} while (option != 11);
}
