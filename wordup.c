//Name: Antonio Escobar
//Project 10
//Date: 4/22/25

#include <stdio.h>


#define WORD_LENGTH 10
#define INPUTFILE "mystery.txt"
#define ATTEMPTS 7
#define LENGTHREQ 5

void getword(FILE* word, char answer[]);
void guessword(int* num_guesses,char word[]);
void displayguesses(char guessed[], char answer[],int col ,char words[][col], int* r, int* d, int* win);
int lengthcheck(char guess[], int guesslen);
void show_win(int num_guesses, char guessed[]);
void show_lose();


int main(){
	char word[WORD_LENGTH], guessedword[WORD_LENGTH], displaywords [10][WORD_LENGTH];
	int guesses = 1, guesslength = 0, length, row = guesses - 1, displays = guesses, wingame = 0;
	
	FILE* fp;
	fp = fopen(INPUTFILE, "r");
	
	getword(fp, word);
	
	do{
	guessword(&guesses, guessedword);
	displayguesses(guessedword, word, WORD_LENGTH, displaywords, &row, &displays, &wingame);
	
	}while(guesses < ATTEMPTS && wingame != 1);
	
	if(guesses >= ATTEMPTS){
		show_lose();
	}
	
	else if(wingame == 1){
		show_win(guesses, guessedword);
	
	}
	
	return 0;
}

void getword(FILE* word, char answer[]){
	if(word == NULL){
		printf("Can't open file.");
		return;
	}
	fscanf(word, "%s", answer);
	answer[5] = '\0';
	fclose(word);

}

void guessword(int* num_guesses,char word[]){
	int length = 0;
	if(*num_guesses == ATTEMPTS - 1){
		printf("FINAL GUESS: ");
		scanf (" %s", word);
		length = lengthcheck(word, length);
	}
	else{
	printf("GUESS %d! Enter your guess: ", *num_guesses);
	scanf (" %s", word);
	length = lengthcheck(word, length);
	}
	
	while(length != LENGTHREQ){
	printf("Your guess must be 5 letters long.\nPlease try again: ");
	scanf (" %s", word);
	length = lengthcheck(word, length);
	}
	
	*num_guesses += 1;
}

void displayguesses(char guessed[], char answer[],int col ,char words[][col], int* r, int* d, int* win){


	int found = 0;
	int matches = 0;
	for(int i = 0; answer[i] != '\0'; i++){
		for(int j = 0; guessed[j] != '\0'; j++){
			if(guessed[j] == answer[j]){
				words[*r][j] = guessed[j] - 32;
				words[*r + 1][j] = ' ';
				matches += 1;
			
			}
			else if(guessed[j] == answer[i]){
				words[*r][j] = guessed[j];
				words[*r + 1][j] = '^';
				found = 1;
			}
			
			else if (found == 0){
				words[*r][j] = guessed[j];
				words[*r + 1][j] = ' ';
			}
			
			
		}
	
	}
	
	if(matches == 25){
		*win = 1;
		return;
	
	}
	
	printf("================================\n");
	for(int k = 0; k < *d + 1; k++){
		for(int c = 0; words[k][c] != '\0'; c++){
			printf("%c", words[k][c]);
		}
		printf("\n");
	}
	*r += 2;
	*d += 2;

}



void show_lose(){
	printf("\n");
	printf("You lost, better luck next time!\n");

}

void show_win(int num_guesses, char guessed[]){
	
	for(int i = 0; guessed[i] != '\0'; i++){
		guessed[i] -= 32;
	
	}
	
	num_guesses -= 1;
	printf("================================\n");
	printf("		%s\n", guessed);
	printf("	You won in %d guess!\n", num_guesses);



	switch(num_guesses){
		case 1: printf("		GOATED!\n");
			break;
		case 2:
		case 3: printf("		Amazing!\n");
			break;
		case 4:
		case 5: printf("		Nice!\n");
			break;
		case 6:
			break;
	
	
	
	}
}

int lengthcheck(char guess[], int guesslen){
	guesslen = 0;
	 for(int i = 0; guess[i] != '\0'; i++){
	 	if(guess[i] >= 'a' && guess[i] <= 'z'){
	 		guesslen++;
	 	}
	 }
	
	return guesslen;
}
