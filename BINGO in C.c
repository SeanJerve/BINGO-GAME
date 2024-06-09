#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define ROWS 5
#define COLS 5
#define ARRAY 10

void bcard(int card[ROWS][COLS][ARRAY]);
void displaybcard(int card[ROWS][COLS][ARRAY], int marked[ROWS][COLS][ARRAY]);
void numletcombi(char *letter, int *number, int unique_num[75]);
int wcheckPATTERN(int marked[ROWS][COLS][ARRAY], int *arr, int *pattern);
void wcheckCUSTOMPATTERN(int marked[ROWS][COLS][ARRAY], int pickercard[ROWS][COLS], int picked[ROWS][COLS]) ;


// BINGO CARD BACKEND
void bcard(int card[ROWS][COLS][ARRAY]) {
	
    // Clear the card // making a 2D 5 x 5 array
    for (int z = 0; z < ARRAY; z++) {
	    for (int i = 0; i < ROWS; i++) {
    		for (int j = 0; j < COLS; j++) {
        		card[i][j][z] = 0;
		}
    }

    // Seed for random number generation
    srand(time(NULL));

    // Generate unique random numbers for each column
    for (int z = 0; z < ARRAY; z++) {
    	for (int j = 0; j < COLS; ++j) {
        	int min = j * 15 + 1;
    	    int max = (j + 1) * 15;
			int usednum[15] = {0}; // Keep track of used numbers in each column so that there are no duplicates

        for (int i = 0; i < ROWS; ++i) {
            int num;
            do {
                num = rand() % (max - min + 1) + min;
            } while (usednum[num - min] != 0);

            card[i][j][z] = num;
            usednum[num - min] = 1;
        	}
    	}
    // Mark the center as free
    card[2][2][z] = 0;
		}
	}
}

//BINGO CARD FRONTEND - DISPLAY
void displaybcard(int card[ROWS][COLS][ARRAY], int marked[ROWS][COLS][ARRAY]) {
	
	FILE *cardstorage;
	
	cardstorage = fopen("Bingo_Card.txt", "w");
	
	for (int z = 0; z < ARRAY; z++) {
		fprintf(cardstorage, "\nBingo Card: %i\n", z + 1);
    	fprintf(cardstorage, "  B  |   I  |   N  |   G  |  O\n");
    	for (int i = 0; i < ROWS; i++) {
        	for (int j = 0; j < COLS; j++) {
            	if (j > 0) {
                	fprintf(cardstorage, " | ");
            	}
            	if (marked[i][j][z] && card[i][j][z] == 0) {
                	fprintf(cardstorage, " F  "); // Free space in the middle
            	} else {
                    fprintf(cardstorage, "%3d ", card[i][j][z]);
                	}
        		}
        	fprintf(cardstorage, "\n");
    	}
	}
	fclose(cardstorage);
}

//BINGO CARD FRONTEND - LETTER AND NUMBER COMBINATION
void numletcombi(char *letter, int *number, int unique_num[75]) {
		
	FILE *numberstorage;
	
	numberstorage = fopen("Number_Storage.txt", "a");
	char letters[] = "BINGO";
    int eachlet = rand() % 5;
    *letter = letters[eachlet];
	bool unique;
	
    // Generate unique numbers for each letter
    switch (eachlet) {
    case 0: // B
    		
		do {
    		*number = rand() % 15 + 1;	
    		unique = true;
    			
    		for (int j = 0; j < 75; j++) {
    			if (*number == unique_num[j]) {
    				unique = false;
    				break;
				}
			}

		} while(!unique);
	
		if (unique) {
			fprintf(numberstorage,"%c, %i\n", *letter, *number);	
			fclose(numberstorage);
		}
		break;
		
    case 1: // I
        		
		do {
    		*number = rand() % 15 + 16;	
    		unique = true;
    			
    		for (int j = 0; j < 75; j++) {
    			if (*number == unique_num[j]) {
    				unique = false;
    				break;
				}
			}
			
		} while(!unique);
		
		if (unique) {
			fprintf(numberstorage,"%c, %i\n", *letter, *number);	
			fclose(numberstorage);
		}
		break;
		
    case 2: // N
        
        do {
    		*number = rand() % 15 + 31;	
    		unique = true;
    			
    		for (int j = 0; j < 75; j++) {
    			if (*number == unique_num[j]) {
    				unique = false;
    				break;
				}
			}
			
		} while(!unique);

		if(unique) {
			fprintf(numberstorage,"%c, %i\n", *letter, *number);	
			fclose(numberstorage);
		}
		break;
		
    case 3: // G

        do {
    		*number = rand() % 15 + 46;	
    		unique = true;
    			
    		for (int j = 0; j < 75; j++) {
    			if (*number == unique_num[j]) {
    				unique = false;
    				break;
				}
			}
			
		} while(!unique);

		if (unique) {
			fprintf(numberstorage,"%c, %i\n", *letter, *number);	
			fclose(numberstorage);
		}
		
		break;
		
    case 4: // O
        
        do {
    		*number = rand() % 15 + 61;	
    		unique = true;
    			
    		for (int j = 0; unique == false; j++) {
    			if (*number == unique_num[j]) {
    				unique = false;
    				break;
				}
			}
			
		} while(!unique);

		fprintf(numberstorage,"%c, %i\n", *letter, *number);
		fclose(numberstorage);	
		break;
	}
}

//BINGO CARD BACKEND - PATTERN CHECKER
int wcheckPATTERN(int marked[ROWS][COLS][ARRAY], int *arr, int *pattern) {
	
	if (*pattern == 1) { //BLACK OUT GAME
		
		for (int z = 0; z < ARRAY; z++) {
		int blacked = 1; 
    	for (int i = 0; i < ROWS; i++) {
        	for (int j = 0; j < COLS; j++) {
            	if (!marked[i][j][z]) {
                	blacked = 0; 
                	break;
            		}
				}
        	if (!blacked) {
            	break;
        	}
        }
        if (blacked) {
        	*arr = z;
        	return 1; 
        	break;
    				}
    }
    	
    	return 0; // No win yet
    	
	} else if (*pattern == 2) { //ROW GAME
		
		for (int z = 0; z < ARRAY; z++) {
    	for (int i = 0; i < ROWS; i++) {
        	int wrow = 1; 
        	for (int j = 0; j < COLS; j++) {
            	if (!marked[i][j][z]) {
                	wrow = 0; // Not a win in this row
                	break;
            	}
        	}
        	if (wrow) {
        		*arr = z;
            	return 1;
        	}
    	}
	}
		
	} else if (*pattern == 3) { //COLUMNS GAME
		
		for (int z = 0; z < ARRAY; z++) {
		for (int j = 0; j < COLS; j++) {
        	int wcol = 1; 
        	for (int i = 0; i < ROWS; i++) {
            	if (!marked[i][j][z]) {
                	wcol = 0; 
                	break;
            	}
        	}
        	if (wcol) {
            	*arr = z;
				return 1; 
        	}
    	}
	}
		
	} else if (*pattern == 4) { //DIAGONALS GAME
		
		for (int z = 0; z < ARRAY; z++) {
		int wdiag = 1; 
    		for (int i = 0; i < ROWS; i++) {
        			if (!marked[i][i][z]) {
        				wdiag = 0;
        			}
					if (!wdiag) {
        				if (!marked[i][COLS - 1 - i][z]) {
        					wdiag = 0;
        					break;
						}
					}
			} if (wdiag) {
        		*arr = z;
				return 1; 
			}
    	}
		
	} else if (*pattern == 5) { // X CROSS GAME
		
		for (int z = 0; z < ARRAY; z++) {
		int wcross = 1; 
    		for (int i = 0; i < ROWS; i++) {
        			if (!marked[i][i][z] || !marked[i][COLS - 1 - i][z]) {
            			wcross = 0; 
            			break;
        			}
        	} if (wcross) {
        		*arr = z;
				return 1;
			}		
    	}
		
	} else if (*pattern == 6) { // T CROSS GAME
		
		for (int z = 0; z < ARRAY; z++) {
		int wcrossv2 = 1;
			for (int i = 0; i < ROWS; i++) {
				if (!marked[i][2][z]) {
					wcrossv2 = 0;
					break;
				}
			} for (int j = 0; j < COLS; j++) {
				if (!marked[2][j][z]) {
					wcrossv2 = 0;
					break;
				}
			}
			if (wcrossv2) {
				*arr = z;
				return 1;
			}
	}
		
	} 
}

//BINGO CARD BACKEND - CUSTOM PATTERN CHECKER

void wcheckCUSTOMPATTERN(int marked[ROWS][COLS][ARRAY], int pickercard[ROWS][COLS], int picked[ROWS][COLS]) {
    int square;
    printf("Enter the squares you want to mark for your pattern (enter 0 to finish):\n");
    while (1) {
        scanf("%d", &square);
        if (square == 0) break;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (square == pickercard[i][j]) {
                    picked[i][j] = 1;
                }
            }
        }
    }

    // Mark the squares in the 'marked' array
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (picked[i][j] == 1) {
                marked[i][j][0] = 1;
            }
        }
    }
}

void displayCard(int pickercard[ROWS][COLS], int picked[ROWS][COLS]) {
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (j > 0) {
                printf(" | ");
            }
            if (picked[i][j] == 1) {
                printf(" X ");
            } else {
                printf("%2d ", pickercard[i][j]);
            }
        }
        printf("\n");
    }
}

void displayPattern(int pickercard[ROWS][COLS], int picked[ROWS][COLS]) {
    printf("\nCustom Pattern:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (j > 0) {
                printf(" | ");
            }
            if (picked[i][j] == 1) {
                printf("()");
            } else {
                printf("   ");
            }
        }
        printf("\n");
    }
}



// BINGO GAME

int main() {

    int options; //pattern choice - ui
    char let; //letter pointer - picker
    int num; //number pointer - picker
    int arr; //array pointer - display card
	int numcheck;
	int chs; //pattern choice ui
	bool unique;
	int selection;
	int pick1, pick2;
	int replay = 1;
	int pick = 1;
	
	while (pick) {
	printf("\n\033[1;33m||===========================||\033[0m\n");
	printf("\033[1;33m||\033[0m\033[1;43m WELCOME TO THE BINGO GAME \033[0m\033[1;33m||\033[0m");
	printf("\n\033[1;33m||===========================||\033[0m");
	printf("\n\033[1;33m||\033[0m\033[1;32m\t 1 \033[1;33m-\033[0m \033[1;32mPLAY\033[0m\t   \033[1;33m  ||\033[0m\n");
	printf("\033[1;33m||\033[0m\033[1;34m\t 2 \033[1;33m-\033[0m \033[1;34mHOW TO PLAY\033[0m\033[1;33m     ||\033[0m\n");
	printf("\033[1;33m||\033[0m\033[1;31m\t 3 \033[1;33m-\033[0m \033[1;31mEXIT\033[0m\t   \033[1;33m  ||\033[0m\n");
	printf("\033[1;33m||===========================||\033[0m\n\n");
	printf("\033[1;33m     Enter your choice: \033[0m");
	scanf("%i", &selection);
	
	
	if (selection == 1) {
	
	while (replay == 1) {
	FILE *numberstorage;
	
	numberstorage = fopen("Number_Storage.txt", "w");
	fclose(numberstorage);
	
	int bingocard[ROWS][COLS][ARRAY];
    int marked[ROWS][COLS][ARRAY] = {0}; // 0 indicates unmarked, 1 indicates marked
	int picked[ROWS][COLS] = {0}; // for custom pattern
	int unique_num[75] = {0};
    // Initialize the bingo card with unique numbers
    bcard(bingocard);


	printf("\033[2J");//clear terminal
    printf("\033[H");// Move cursor to the top left corner

	printf("\n\033[1;33m||=========================||\033[0m\n");
	printf("\033[1;33m||\033[0m\033[1;32mWELCOME TO THE BINGO GAME\033[0m\033[1;33m||\033[0m");
	printf("\n\033[1;33m||=========================||\033[0m");
	printf("\n\033[1;105m      PATTERNS AVAILABLE     \033[0m\n");
	printf("\n");
	printf("\033[1;34m1 - Black Out\t2 - ROWS\033[0m\n");
	printf("\033[1;36m3 - COLUMNS\t4 - DIAGONALS\033[0m\n");
	printf("\033[1;34m5 - CROSS\t6 - HORIZONTAL CROSS\033[0m\n");
	printf("\033[1;36m      7 - CUSTOM PATTERN\033[0m\n");
	printf("\n\033[1;104mWhat pattern do you want to play?\033[0m ");
	printf("\n\033[1;34mEnter number of choice: \033[0m");
	scanf("%d", &options);


	displaybcard(bingocard, marked);
	
	int *pattern = &options;
	int x = 0;
	char choice[5];


	if (options == 1) {

	if (*pattern == 1) { // BLACK OUT 

    printf("PATTERN:\n");
    printf("() () () () ()\n");
    printf("() () () () ()\n");
    printf("() () () () ()\n");
    printf("() () () () ()\n");
    printf("() () () () ()\n");
    printf("Is this the pattern you want to play? (yes/no):\n");
    scanf("%5s", choice);

	if (strcmp(choice, "yes") == 0) {
        printf("You chose to play the BLACK OUT PATTERN.\n");
		for (int z = 0; z < ARRAY; z++) {
			marked[2][2][z] = 1;
		}
		do {
        
		numletcombi(&let, &num, unique_num);
        
        int *number = &num;
        
        for (int z = 0; z < ARRAY; z++) {
        	for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    if (bingocard[i][j][z] == num) {
                        marked[i][j][z] = 1; // Mark the number on the card
                        break;
                    } 
                }
            }
		}
    } while (!wcheckPATTERN(marked, &arr, &options));

    if (wcheckPATTERN(marked, &arr, &options)) {
    	
		printf("\n\033[1;41mBingo Card: %i\033[0m\n", arr + 1);
    	printf("\033[1;33m  B    |   I    |   N    |   G    |   O \033[0m\n");
    	for (int i = 0; i < ROWS; i++) {
        	for (int j = 0; j < COLS; j++) {
            	if (j > 0) {
                	printf("\033[1;33m | \033[0m");
            	}
            	if (marked[i][j][arr] && bingocard[i][j][arr] == 0) {
                	printf("\033[1;31m  F   \033[0m"); // Free space in the middle
            	} else if (marked[i][j][arr] && bingocard[i][j][arr] != 0) {
                    	printf("\033[1;96m (%2d) \033[0m", bingocard[i][j][arr]); 
                	} else {
                    	printf("%5d ", bingocard[i][j][arr]);
                	}
        		}
        	printf("\n");
    	} 
    		if (arr < ARRAY - 1) {
    			for (int z = arr + 1; z < ARRAY; z++) {
    				int blacked = 1;
    				for (int i = 0; i < ROWS; i++) {
    					for (int j = 0; j < COLS; j++) {
    						if (!marked[i][j][z]) {
    							blacked = 0;
    							break;
							}
						}
					if (!blacked) {
						break;
					}
					}
					if (blacked) {
						printf("\n\033[1;41mBingo Card: %i\033[0m\n", z + 1);
    				printf("\033[1;33m  B    |   I    |   N    |   G    |   O \033[0m\n");
    						for (int i = 0; i < ROWS; i++) {
        						for (int j = 0; j < COLS; j++) {
            						if (j > 0) {
                						printf("\033[1;33m | \033[0m");
            							}
            						if (marked[i][j][z] && bingocard[i][j][z] == 0) {
                						printf("\033[1;31m  F   \033[0m");// Free space in the middle
            						} else if (marked[i][j][z] && bingocard[i][j][z] != 0) {
                    					printf("\033[1;96m (%2d) \033[0m", bingocard[i][j][z]); 
                					} else {
                    					printf("%5d ", bingocard[i][j][z]);
                					}
        						}
        					printf("\n");
    					} 
					}
				}
			}
    	printf("\n    \033[1;42mCongratulations You hit a Bingo!!!\033[0m\n");
    } 

    } else if (strcmp(choice, "no") == 0) {
        printf("\nYou chose not to play the BLACK OUT PATTERN.\n");
    } else {
        printf("Invalid choice. Please enter 'yes' or 'no'.\n");
    }
}	

	} else if (options == 2) { //ROWS GAME

    printf("PATTERN:\n");
    printf("() () () () ()\n");
    printf("Is this the pattern you want to play? (yes/no):\n");
    scanf("%5s", choice);

	if (strcmp(choice, "yes") == 0) { 
        printf("You chose to play the ROWS PATTERN.\n");
		
		for (int z = 0; z < ARRAY; z++) {
			marked[2][2][z] = 1;
		}
		do { 
        numletcombi(&let, &num, unique_num);
        
        int *number = &num;
        
        for (int z = 0; z < ARRAY; z++) {
        	for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    if (bingocard[i][j][z] == num) {
                        marked[i][j][z] = 1; // Mark the number on the card
                        break;
                    } 
                }
            }
		}
    } while (!wcheckPATTERN(marked, &arr, &options));

    if (wcheckPATTERN(marked, &arr, &options)) {
    	
		printf("\n\033[1;41mBingo Card: %i\033[0m\n", arr + 1);
    	printf("\033[1;33m  B    |   I    |   N    |   G    |   O \033[0m\n");
    	for (int i = 0; i < ROWS; i++) {
        	for (int j = 0; j < COLS; j++) {
            	if (j > 0) {
                	printf("\033[1;33m | \033[0m");
            	}
            	if (marked[i][j][arr] && bingocard[i][j][arr] == 0) {
                	printf("\033[1;31m  F   \033[0m"); // Free space in the middle
            	} else if (marked[i][j][arr] && bingocard[i][j][arr] != 0) {
                    	printf("\033[1;96m (%2d) \033[0m", bingocard[i][j][arr]); 
                	} else {
                    	printf("%5d ", bingocard[i][j][arr]);
                	}
        		}
        	printf("\n");
    	}
    		if (arr < ARRAY - 1) {
    			for (int z = arr + 1; z < ARRAY; z++) {
    				for (int i = 0; i < ROWS; i++) {
        				int wrow = 1; 
        				for (int j = 0; j < COLS; j++) {
            				if (!marked[i][j][z]) {
                				wrow = 0; // Not a win in this row
                				break;
            					}
        					}
        				if (wrow) {
        					printf("\n\033[1;41mBingo Card: %i\033[0m\n", z + 1);
    						printf("\033[1;33m  B    |   I    |   N    |   G    |   O \033[0m\n");
    						for (int i = 0; i < ROWS; i++) {
        						for (int j = 0; j < COLS; j++) {
            						if (j > 0) {
                						printf("\033[1;33m | \033[0m");
            							}
            						if (marked[i][j][z] && bingocard[i][j][z] == 0) {
                						printf("\033[1;31m  F   \033[0m"); // Free space in the middle
            						} else if (marked[i][j][z] && bingocard[i][j][z] != 0) {
                    					printf("\033[1;96m (%2d) \033[0m", bingocard[i][j][z]); 
                					} else {
                    					printf("%5d ", bingocard[i][j][z]);
                					}
        						}
        					printf("\n");
    						} 
        				}
    				}
				}
    		}
    		printf("\n    \033[1;43mCongratulations You hit a Bingo!!!\033[0m\n");
    } 
	
	} else if (strcmp(choice, "no") == 0) {
        printf("\nYou chose not to play the ROWS PATTERN.\n");
    } else {
        printf("Invalid choice. Please enter 'yes' or 'no'.\n");
    }

	} else if (options == 3) {  //COLUMNS 
		printf("PATTERN:\n");
    printf("()\n");
	printf("()\n");
	printf("()\n");
	printf("()\n");
	printf("()\n");
    printf("Is this the pattern you want to play? (yes/no):\n");
    scanf("%5s", choice);

	if (strcmp(choice, "yes") == 0) {
        printf("You chose to play the COLUMNS PATTERN.\n");
		
		for (int z = 0; z < ARRAY; z++) {
			marked[2][2][z] = 1;
		}
		do {
        numletcombi(&let, &num, unique_num);
        
        int *number = &num;
        
        for (int z = 0; z < ARRAY; z++) {
        	for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < COLS; j++) {
                    if (bingocard[i][j][z] == num) {
                        marked[i][j][z] = 1; // Mark the number on the card
                        break;
                    } 
                }
            }
		}
    } while (!wcheckPATTERN(marked, &arr, &options));

    if (wcheckPATTERN(marked, &arr, &options)) {
    	
		printf("\n\033[1;41mBingo Card: %i\033[0m\n", arr + 1);
    	printf("\033[1;33m  B    |   I    |   N    |   G    |   O \033[0m\n");
    	for (int i = 0; i < ROWS; i++) {
        	for (int j = 0; j < COLS; j++) {
            	if (j > 0) {
                	printf("\033[1;33m | \033[0m");
            	}
            	if (marked[i][j][arr] && bingocard[i][j][arr] == 0) {
                	printf("\033[1;31m  F   \033[0m"); // Free space in the middle
            	} else if (marked[i][j][arr] && bingocard[i][j][arr] != 0) {
                    	printf("\033[1;96m (%2d) \033[0m", bingocard[i][j][arr]); 
                	} else {
                    	printf("%5d ", bingocard[i][j][arr]);
                	}
        		}
        	printf("\n");
    	}
    		if (arr < ARRAY - 1) {
    			for (int z = arr + 1; z < ARRAY; z++) {
					for (int j = 0; j < COLS; j++) {
        				int wcol = 1; 
        					for (int i = 0; i < ROWS; i++) {
            					if (!marked[i][j][z]) {
                				wcol = 0; 
                				break;
            				}
        				}
        			if (wcol) {
            			printf("\n033[1;41mBingo Card: %i\033[0m\n", z + 1);
    						printf("\033[1;33m  B    |   I    |   N    |   G    |   O \033[0m\n");
    						for (int i = 0; i < ROWS; i++) {
        						for (int j = 0; j < COLS; j++) {
            						if (j > 0) {
                						printf("\033[1;33m | \033[0m");
            							}
            						if (marked[i][j][z] && bingocard[i][j][z] == 0) {
                						printf("\033[1;31m  F   \033[0m"); // Free space in the middle
            						} else if (marked[i][j][z] && bingocard[i][j][z] != 0) {
                    					printf("\033[1;96m (%2d) \033[0m", bingocard[i][j][z]); 
                					} else {
                    					printf("%5d ", bingocard[i][j][z]);
                					}
        						}
        					printf("\n");
    					}  
        			}
    			}
			}
		}
   		 printf("\n    \033[1;43mCongratulations You hit a Bingo!!!\033[0m\n");
    } 

	} else if (strcmp(choice, "no") == 0) {
        printf("\nYou chose not to play the COLUMNS PATTERN.\n");
    } else {
        printf("Invalid choice. Please enter 'yes' or 'no'.\n");
    } 
	
    
    } else if (options == 4) { //DIAGONAL
	printf("PATTERN:\n");
    printf("()\n");
	printf("  ()\n");
	printf("    ()\n");
	printf("      ()\n");
	printf("        ()\n");
    printf("Is this the pattern you want to play? (yes/no):\n");
    scanf("%5s", choice);

	if (strcmp(choice, "yes") == 0) {
        printf("You chose to play the DIAGONAL PATTERN.\n");
    	
		for (int z = 0; z < ARRAY; z++) {
			marked[2][2][z] = 1;
		}
		do { 
        numletcombi(&let, &num, unique_num);
        
        int *number = &num;
		
		for (int z = 0; z < ARRAY; z++) {
    	    for (int i = 0; i < ROWS; ++i) {
    	    	if (num == bingocard[i][i][z]) {
            			marked[i][i][z] = 1;
            		} else if (num == bingocard[i][COLS - 1 - i][z]) {
        				marked[i][COLS - 1 - i][z] = 1;
					} 
				}
			}
    	} while (!wcheckPATTERN(marked, &arr, &options));
    
    if (wcheckPATTERN(marked, &arr, &options)) {
    	
		printf("\n\033[1;41mBingo Card: %i\033[0m\n", arr + 1);
    	printf("\033[1;33m  B    |   I    |   N    |   G    |   O \033[0m\n");
    	for (int i = 0; i < ROWS; i++) {
        	for (int j = 0; j < COLS; j++) {
            	if (j > 0) {
                	printf("\033[1;33m | \033[0m");
            	}
            	if (marked[i][j][arr] && bingocard[i][j][arr] == 0) {
                	printf("\033[1;31m  F   \033[0m"); // Free space in the middle
            	} else if (marked[i][j][arr] && bingocard[i][j][arr] != 0) {
                    	printf("\033[1;96m (%2d) \033[0m", bingocard[i][j][arr]); 
                } else {
                    printf("%5d ", bingocard[i][j][arr]);
                }
        	}
        	printf("\n");
    	}
    	if (arr < ARRAY) {
    		for (int z = arr + 1; z < ARRAY; z++) {
				int wdiag = 1; 
    				for (int i = 0; i < ROWS; i++) {
        			if (!marked[i][i][z]) {
        				wdiag = 0;
        				}
						if (!wdiag) {
        				if (!marked[i][COLS - 1 - i][z]) {
        					wdiag = 0;
        					break;
						}
					}
				} if (wdiag) {
        		
					printf("\n\033[1;41mBingo Card: %i\033[0m\n", z + 1);
    					printf("\033[1;33m  B    |   I    |   N    |   G    |   O \033[0m\n");
    					for (int i = 0; i < ROWS; i++) {
        					for (int j = 0; j < COLS; j++) {
            					if (j > 0) {
                					printf("\033[1;33m | \033[0m");
            						}
            					if (marked[i][j][z] && bingocard[i][j][z] == 0) {
                					printf("\033[1;31m  F   \033[0m"); // Free space in the middle
            					} else if (marked[i][j][z] && bingocard[i][j][z] != 0) {
                    				printf("\033[1;96m (%2d) \033[0m", bingocard[i][j][z]); 
                				} else {
                    				printf("%5d ", bingocard[i][j][z]);
                				}
        					}
        				printf("\n");
    				}  
				}
    		}
		}
    	printf("\n    \033[1;43mCongratulations You hit a Bingo!!!\033[0m\n");
    } 

	} else if (strcmp(choice, "no") == 0) {
        printf("\nYou chose not to play the DIAGONAL PATTERN.\n");
    } else {
        printf("Invalid choice. Please enter 'yes' or 'no'.\n");
    } 
	
	} else if (options == 5) { //CROSS "X" GAME
	printf("PATTERN:\n");
    printf("()      ()\n");
	printf("  ()  ()\n");
	printf("    ()\n");
	printf("  ()  ()\n");
	printf("()      ()\n");
    printf("Is this the pattern you want to play? (yes/no):\n");
    scanf("%5s", choice);

	if (strcmp(choice, "yes") == 0) {
        printf("You chose to play the X CROSS PATTERN.\n");
		
		for (int z = 0; z < ARRAY; z++) {
			marked[2][2][z] = 1;
		}
		do { 
        numletcombi(&let, &num, unique_num);
        
        int *number = &num;
		
		for (int z = 0; z < ARRAY; z++) {
    	    for (int i = 0; i < ROWS; ++i) {
    	    	if (num == bingocard[i][i][z] ) {
            			marked[i][i][z] = 1;
        			} else if (num == bingocard[i][COLS - 1 - i][z]) {
        				marked[i][COLS - 1 - i][z] = 1;
					} 
				}
			}
    	} while (!wcheckPATTERN(marked, &arr, &options));
    
    if (wcheckPATTERN(marked, &arr, &options)) {
    	
		printf("\n\033[1;41mBingo Card: %i\033[0m\n", arr + 1);
   		printf("\033[1;33m  B    |   I    |   N    |   G    |   O \033[0m\n");
    	for (int i = 0; i < ROWS; i++) {
        	for (int j = 0; j < COLS; j++) {
            	if (j > 0) {
                	printf("\033[1;33m | \033[0m");
            	}
            	if (marked[i][j][arr] && bingocard[i][j][arr] == 0) {
                	printf("\033[1;31m  F   \033[0m"); // Free space in the middle
            	} else if (marked[i][j][arr] && bingocard[i][j][arr] != 0) {
                    	printf("\033[1;96m (%2d) \033[0m", bingocard[i][j][arr]); 
                	} else {
                    	printf("%5d ", bingocard[i][j][arr]);
                	}
        		}
        	printf("\n");
    	}
    	if (arr < ARRAY) {
    		for (int z = arr + 1; z < ARRAY; z++) {
				int wcross = 1; 
    				for (int i = 0; i < ROWS; i++) {
        			if (!marked[i][i][z] || !marked[i][COLS - 1 - i][z]) {
            			wcross = 0; 
            			break;
        			}
        		} if (wcross) {
        		
					printf("\n\033[1;41mBingo Card: %i\033[0m\n", z + 1);
    					printf("\033[1;33m  B    |   I    |   N    |   G    |   O \033[0m\n");
    					for (int i = 0; i < ROWS; i++) {
        					for (int j = 0; j < COLS; j++) {
            					if (j > 0) {
               						printf("\033[1;33m | \033[0m");
            						}
            					if (marked[i][j][z] && bingocard[i][j][z] == 0) {
                					printf("\033[1;31m  F   \033[0m"); // Free space in the middle
            					} else if (marked[i][j][z] && bingocard[i][j][z] != 0) {
                   				printf("\033[1;96m (%2d) \033[0m", bingocard[i][j][z]); 
                				} else {
                   					printf("%5d ", bingocard[i][j][z]);
                			}
        						}
        				printf("\n");
    				}  
				}		
    		}
		}
    	printf("\n    \033[1;43mCongratulations You hit a Bingo!!!\033[0m\n");
    } 

    } else if (strcmp(choice, "no") == 0) {
        printf("\nYou chose not to play the X CROSS PATTERN.\n");
    } else {
        printf("Invalid choice. Please enter 'yes' or 'no'.\n");
    } 

    } else if (options == 6) { //CROSS "t" GAME
	printf("PATTERN:\n");
    printf("      ()      \n");
	printf("      ()      \n");
	printf("() () () () ()\n");
	printf("      ()      \n");
	printf("      ()      \n");
    printf("Is this the pattern you want to play? (yes/no):\n");
    scanf("%5s", choice);

	if (strcmp(choice, "yes") == 0) {
        printf("You chose to play the T CROSS PATTERN.\n");
    	
		for (int z = 0; z < ARRAY; z++) {
			marked[2][2][z] = 1;
		}
		do { 
        numletcombi(&let, &num, unique_num);
        
        int *number = &num;
        
        for (int z = 0; z < ARRAY; z++) {
        	for (int i = 0; i < ROWS; ++i) {
        		if (num == bingocard[i][2][z]) {
        			marked[i][2][z] = 1;
				} for (int j = 0; j < COLS; ++j) {
                    if (bingocard[2][j][z] == num) {
                    	marked[2][j][z] = 1;
                    } 
                }
            }
		}
    } while (!wcheckPATTERN(marked, &arr, &options));

    if (wcheckPATTERN(marked, &arr, &options)) {
    	
		printf("\n\033[1;41mBingo Card: %i\033[0m\n", arr + 1);
    	printf("\033[1;33m  B    |   I    |   N    |   G    |   O \033[0m\n");
    	for (int i = 0; i < ROWS; i++) {
        	for (int j = 0; j < COLS; j++) {
            	if (j > 0) {
            		printf("\033[1;33m | \033[0m");
            	}
            	if (marked[i][j][arr] && bingocard[i][j][arr] == 0) {
                	printf("\033[1;31m  F   \033[0m"); // Free space in the middle
            	} else if (marked[i][j][arr] && bingocard[i][j][arr] != 0) {
                    	printf("\033[1;96m (%2d) \033[0m", bingocard[i][j][arr]); 
                	} else {
                    	printf("%5d ", bingocard[i][j][arr]);
                	}
        		}
        	printf("\n");
    	}
    	if (arr < ARRAY) {
    		for (int z = arr + 1; z < ARRAY; z++) {
				int wcrossv2 = 1;
				for (int i = 0; i < ROWS; i++) {
				if (!marked[i][2][z]) {
					wcrossv2 = 0;
					break;
				}
			} for (int j = 0; j < COLS; j++) {
				if (!marked[2][j][z]) {
					wcrossv2 = 0;
					break;
					}
				}
				if (wcrossv2) {
					
					printf("\n\033[1;41mBingo Card: %i\033[0m\n", z + 1);
    					printf("\033[1;33m  B    |   I    |   N    |   G    |   O \033[0m\n");
    						for (int i = 0; i < ROWS; i++) {
        						for (int j = 0; j < COLS; j++) {
            						if (j > 0) {
                						printf("\033[1;33m | \033[0m");
            							}
            						if (marked[i][j][z] && bingocard[i][j][z] == 0) {
                						printf("\033[1;31m  F   \033[0m");// Free space in the middle
            						} else if (marked[i][j][z] && bingocard[i][j][z] != 0) {
                    					printf("\033[1;96m (%2d) \033[0m", bingocard[i][j][z]); 
                					} else {
                    					printf("%5d ", bingocard[i][j][z]);
                					}
        						}
        					printf("\n");
    					}  
				}
			}
		}
    	printf("\n    \033[1;43mCongratulations You hit a Bingo!!!\033[0m\n");
    }

	} else if (strcmp(choice, "no") == 0) {
        printf("\nYou chose not to play the T CROSS PATTERN.\n");
    } else {
        printf("Invalid choice. Please enter 'yes' or 'no'.\n");
    } 

	} else if (options == 7) {  //CUSTOM PATTERN

    int replay = 1;
    char choice[6];

    while (replay == 1) {
        int custom = 1;
        int customchoice;
        int pickercard[ROWS][COLS] = {
            {1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10},
            {11, 12, 13, 14, 15},
            {16, 17, 18, 19, 20},
            {21, 22, 23, 24, 25}
        };
        int picked[ROWS][COLS] = {0}; 
        int marked[ROWS][COLS][ARRAY] = {{{0}}};

        while (custom == 1) {
            displayCard(pickercard, picked);

            wcheckCUSTOMPATTERN(marked, pickercard, picked);

            displayCard(pickercard, picked);

            printf("\nThis is your pattern. Are you going to play with this or would you like to pick another pattern?\n");
            printf("1 - Pick/Delete a pattern \n2 - Confirm Pattern\n");
            scanf("%d", &customchoice);

            if (customchoice == 1) {
                printf("Do you want to pick a new pattern or delete the current pattern?\n");
                printf("1 - Pick a new pattern\n2 - Delete the current pattern\n");
                int pickDeleteChoice;
                scanf("%d", &pickDeleteChoice);
                if (pickDeleteChoice == 1) {
                    // Pick a new pattern
                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLS; j++) {
                            picked[i][j] = 0;
                        }
                    }
                    wcheckCUSTOMPATTERN(marked, pickercard, picked);
                } else if (pickDeleteChoice == 2) {
                    // Delete the current pattern
                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLS; j++) {
                            picked[i][j] = 0;
                            marked[i][j][0] = 0;
                        }
                    }
                    printf("Pattern deleted. Please pick a new pattern.\n");
                    wcheckCUSTOMPATTERN(marked, pickercard, picked);
                }

            } else if (customchoice == 2) {
                printf("You chose to play this pattern.\n\n");
                displayPattern(pickercard, picked);

                int arr = 0; 
                int customPatternComplete = 0;

                do {
                    int num = 1; 

                    for (int z = 0; z < ARRAY; z++) {
                        for (int i = 0; i < ROWS; ++i) {
                            if (num == pickercard[i][2]) {
                                marked[i][2][z] = 1;
                            }
                        }
                        for (int j = 0; j < COLS; ++j) {
                            if (pickercard[2][j] == num) {
                                marked[2][j][z] = 1;
                            }
                        }
                    }

                    customPatternComplete = 1;
                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLS; j++) {
                            if (picked[i][j] == 1 && marked[i][j][arr] == 0) {
                                customPatternComplete = 0;
                            }
                        }
                    }
                } while (!customPatternComplete);

                if (customPatternComplete) {
                    printf("\n\033[1;41mBingo Card: %i\033[0m\n", arr + 1);
                    printf("\033[1;33m B    |   I    |   N    |   G    |   O \033[0m\n");
                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLS; j++) {
                            if (j > 0) {
                                printf("\033[1;33m  | \033[0m");
                            }
                            if (marked[i][j][arr] && pickercard[i][j] == 0) {
                                printf("\033[1;31m F \033[0m"); // Free space in the middle
                            } else if (marked[i][j][arr] && pickercard[i][j] != 0) {
                                printf("\033[1;96m (%2d) \033[0m", pickercard[i][j]); 
                            } else if (pickercard[i][j] == 0) {
                                printf("  F ");
                            } else {
                                printf("%5d ", pickercard[i][j]);
                            }
                        }
                        printf("\n");
                    }
                    if (arr < ARRAY) {
                        for (int z = arr + 1; z < ARRAY; z++) {
                            int wL = 1;
                            for (int i = 0; i < ROWS; i++) {
                                if (!marked[i][0][z]) {
                                    wL = 0;
                                    break;
                                }
                            }
                            for (int j = 0; j < COLS; j++) {
                                if (!marked[4][j][z]) {
                                    wL = 0;
                                    break;
                                }
                            }
                            if (wL) {
                                printf("\n\033[1;41mBingo Card: %i\033[0m\n", z + 1);
                                printf("\033[1;33m B    |   I    |   N    |   G    |   O \033[0m\n");
                                for (int i = 0; i < ROWS; i++) {
                                    for (int j = 0; j < COLS; j++) {
                                        if (j > 0) {
                                            printf("\033[1;33m | \033[0m");
                                        }
                                        if (marked[i][j][arr] && pickercard[i][j] == 0) {
                                            printf("\033[1;31m F \033[0m"); // Free space in the middle
                                        } else if (marked[i][j][arr] && pickercard[i][j] != 0) {
                                            printf("\033[1;96m (%2d) \033[0m", pickercard[i][j]); 
                                        } else {
                                            printf("%5d ", pickercard[i][j] == 0 ? 'F' : pickercard[i][j]);
                                        }

                                    }
                                    printf("\n");
                                }
                                printf("\n    \033[1;43mCongratulations You hit a Bingo!!!\033[0m\n");
                            }
                        }
                    }
                }

                // Ask if the user wants to play again
                printf("\nPlay Again?\n");
                printf("YES / NO\n");
                scanf("%5s", choice);
                if (strcmp(choice, "yes") == 0 || strcmp(choice, "YES") == 0) {
                    replay = 1;
                    custom = 1;
                    // Reset picked and marked arrays
                    for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLS; j++) {
                            picked[i][j] = 0;
                            marked[i][j][0] = 0;
                        }
                    }
                } else {
                    printf("\nTHANK YOU FOR PLAYING!\n");
                    replay = 0;
                }
            }
        }
    }}
    return 0;
        }
    
	} else if (selection == 2) {
			printf("\033[2J");//clear terminal
			printf("\033[H");// Move cursor to the top left corner
			printf("\n\033[1;33m||===================================||\033[0m\n");
			printf("\033[1;33m||\033[0m\033[1;96mRULES ON HOW TO PLAY THE BINGO GAME\033[0m\033[1;33m||\033[0m");
			printf("\n\033[1;33m||===================================||\033[0m\n");
			printf("\n\033[1;32m1\033[0m - You will be given cards, with each card having\n");
			printf("    different combinations of numbers within them.\n");
			printf("    In each column below each letter has a corresponding\n");
			printf("    range of numbers (B = 1 - 15, I = 16 - 30, N = 31 - 45,\n");
			printf("    G = 46 - 60, 0 = 61 - 75)\n");
			printf("\033[1;32m2\033[0m - You will then select the pattern you want to play\n");
			printf("    with the given patterns in the menu.\n");
			printf("\033[1;32m3\033[0m - After having cards and selecting a pattern, A random\n");
			printf("    number will be called each time. If the number called\n");
			printf("    matches the number in your card and the number in your\n");
			printf("    card is part of the pattern, that number will be marked\n");
			printf("\033[1;32m4\033[0m - After calling different numbers (1 - 75), The first person\n");
			printf("    to complete a pattern with the marked numbers in their card\n");
			printf("    will be declared as the winner\n");
			printf("\n\033[1;32m1 - Back\033[0m\n\033[1;31m2 - Exit\033[0m\n");
			printf("\033[1;33mEnter choice here: \033[0m");
			scanf("%i", &pick1);
			if (pick1 == 1) {
				continue; // Go back to the main menu
			} else if (pick1 == 2) {
				printf("\033[2J");//clear terminal
				printf("\033[H");// Move cursor to the top left corner
				printf("\033[1;31m\t  GOOD BYE...\033[0m\033");
				pick = 0; // Exit the program
			}
		} else if (selection == 3) {
			printf("\033[2J");//clear terminal
			printf("\033[H");// Move cursor to the top left corner
			printf("\033[1;31m\t  GOOD BYE...\033[0m\033");
			pick = 0; // Exit the program
		}
	}
	return 0;
}