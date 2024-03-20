/******************************************
Name: Dolev shlomo    proj: Pancratius game
******************************************/
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAKE_SIGN_INT '0'
#define ONE 1
#define WIN_HITS 4
#define MAX_LEVEL 4
#define MIN_LEVEL 1
#define MIN_PASSWORD_NUMBER 1
#define MAX_PASSWORD_NUMBER 6
#define FALSE 0
#define TRUE !FALSE

//colors 
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_BACKGROUND_MAGENTA "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void printTheExit();
void printWlecome(void);
int inputLevel(void);
int getAndCheckLevel(int user_leve);
int inputPrint(void);
void missesOrHit(int sign, int sing_password);
void randmPassword(void);
int randomNumber(int max, int min);
int getMaxGusses(int level);
bool findDup(int sign1, int sign2, int sign3, int sign4);
void lose(void);
void winner(int gusses_user_have);
bool checkUserSign(int sign);
bool playAgin(void);
void setConsoleColor(int color);

//local varibals 
int sign1_password = 0;
int sign2_password = 0;
int sign3_password = 0;
int sign4_password = 0;
int max_guesses = 0;
int hits = 0;
int misses = 0;

enum maxGusses {MIN_CRAZY_LEVEL = 5, MAX_HARD_LEVEL = 10, MAX_MODERATE_LEVEL = 15, MAX_EASY_LEVEL = 20, MAX_CRAZY_LEVEL = 25};
enum difficultyLevel {Easy = 1, Moderate, Hard, Crazy};
enum userChoiceOption {One = 1, Two, Three, Four, Five, Six };


/*
this function is the mange
input: NONE
output: 0 is on sucsses 
*/
int main()
{
	int gusses_try = 0; 
	int user_leve_choice = 0;
	srand(time(NULL));
	
	do //main loop (stop only if the user push n)
	{
		system("cls");
		
		hits = 0; //rest hits
		
		randmPassword(); //creat a random password
		printWlecome();
		setConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);  // Reset to default color
		user_leve_choice = inputLevel(); //get the level
		max_guesses = getMaxGusses(user_leve_choice);  //find the guesses
		gusses_try = getAndCheckLevel(user_leve_choice);//save how much try the user did

		if (hits == WIN_HITS) //win check
		{
			winner(gusses_try);
		}
		else //lose
		{
			lose();
		}
	}
	while(!(playAgin())); //Check if the user want to play agin
	
	printTheExit();
	printf("Press any key to continue . . .");
	getch();
	printf("\n");
}

/*
this function print welcome and the game ruls
input: NONE
output: NONE
*/
void printWlecome(void)
{

	printf("               .__                                  __     \n");
	printf("__  _  __ ____ |  |   ____  ____   _____   ____   _/  |_  ____ \n");
	printf("\\ \\/ \\/ // __ \\|  | _/ ___\\/  _ \\ /     \\_/ __ \\  \\   __\\/  _ \\  \n");
	printf(" \\     /\\  ___/|  |_\\  \\__(  <_> )  Y Y  \\  ___/   |  | (  <_> ) \n");
	printf("  \\/\\_/  \\_____>____/\\_____>____/|__|_|__/\\_____>  |__|  \\____/  \n");
	
	printf("\t\t\t\t\t\"MAGSHIMIM CODE-BREAKER\"!!!\n\n");
 	setConsoleColor(FOREGROUND_RED);		
	printf("A secret password was chosen to protect the credit card of Pancratius,\n"
			"the descendant of Antiochus.\n"
			"Your mission is to stop Pancratius by revealing his secret password.\n\n");
	setConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);  // Reset to default color

	printf("The rules are as follows:\n");
	printf("1. In each round you try to guess the secret password (4 distinct digits)\n");
	printf("2. After every guess you'll receive two hints about the password\n");
	printf("HITS:   The number of digits in your guess which were exactly right.\n");
	printf("MISSES: The number of digits in your guess which belongs to\n");
	printf("the password but were miss-placed.\n");
	printf("Pancratius will buy all the gifts for Hanukkah!!!\n\n");
	printf("3. If you'll fail to guess the password after a certain number of rounds\n");
}

/*
this function input the user choices, check his hits and misses and return how much gusses the user did 
input: user level 
output: how much gusses the user did 
*/
int getAndCheckLevel(int user_leve_choice)
{
	int guesses_user_have = 0;
	char user_sign1 = 0;
	char user_sign2 = 0;
	char user_sign3 = 0;
	char user_sign4 = 0;
	bool user_check_answer = 0;

	system("cls");
	printf(ANSI_COLOR_RED "I use getch and becuse that ctrl + c not work\nfor stop the program write 0000\n\n\n" ANSI_COLOR_RESET);

	for(guesses_user_have = max_guesses;((guesses_user_have) && (hits != WIN_HITS));guesses_user_have--) //user win or lose loop
	{
		do
		{
			printf("Write your guess (only 1-6, no ENTER is needed)\n");
			if(user_leve_choice != Crazy) //if its not crazy level 
			{
				printf("%d guesses left\n", guesses_user_have);
			}
			else //if its crazy level 
			{
				printf("CRAZY MODE!!!\n");
			}
			
			user_sign1 = inputPrint();   //input and print char 1
			user_sign2 = inputPrint();  //input and print char 2
			user_sign3 = inputPrint(); //input and print char 3
			user_sign4 = inputPrint();//input and print char 4
			
			if(user_sign1 == 0 && user_sign2 == 0 && user_sign3 == 0 && user_sign4 == 0)
			{
				printTheExit();
				exit(1);
			}
			findDup(user_sign1, user_sign2, user_sign3, user_sign4);
			printf("\n");
			
			hits = 0;   //rest to hits 
			misses = 0;//rest to misses
			
			//check user sign + the bouns
			user_check_answer = (((checkUserSign(user_sign1)) || (checkUserSign(user_sign2)) || (checkUserSign(user_sign3)) || (checkUserSign(user_sign4))));
			user_check_answer = (user_check_answer  || (!findDup(user_sign1, user_sign2, user_sign3, user_sign4)));
			
			if(user_check_answer == TRUE) //check if need to print error message 
			{
				printf("""\x1b[31m""\nOnly 1-6 are allowed, try again!\n\n""\x1b[0m");
			}
			
			missesOrHit(user_sign1, sign1_password) ;  //find misses and hit 1
			missesOrHit(user_sign2, sign2_password);  //find misses and hit 2
			missesOrHit(user_sign3, sign3_password); //find misses and hit 3
			missesOrHit(user_sign4, sign4_password);//find misses and hit 4
		}
		while(user_check_answer); //get guesses and check loop
		
		if(hits != WIN_HITS)    //if the user didn't win
		{
			printf("You got    %s%d HITS%s    %s%d MISSES%s.\n\n\n",
            ANSI_COLOR_GREEN, hits, ANSI_COLOR_RESET,
            ANSI_COLOR_YELLOW, misses, ANSI_COLOR_RESET);
		}
	}
	return guesses_user_have;//return the gusses user do.
}


void printTheExit()
{
	system("cls");
	printf(ANSI_COLOR_GREEN "\n\nIt is your choice to stop the show and I respect that but it is not respected\n\n" ANSI_COLOR_RESET);
    printf("\x1b[32m");  // ANSI escape code for green color
    printf("                         __    _                                   \n"
           "                    _wr\"\"        \"-q__                            \n"
           "                 _dP                 9m_                          \n"
           "               _#P                     9#_                        \n"
           "              d#@                       9#m                       \n"
           "             d##        Lildolev         ###                      \n"
           "            J###                         ###L                     \n"
           "            {###K                       J###K                     \n"
           "            ]####K      ___aaa___      J####F                     \n"
           "        __gmM######_  w#P\"\"   \"\"9#m  _d#####Mmw__                 \n"
           "     _g##############mZ_         __g##############m_              \n"
           "   _d####M@PPPP@@M#######Mmp gm#########@@PPP9@M####m_            \n"
           "  a###\"          ,Z\"#####@\" '######\"\\g          \"\"M##m           \n"
           " J#\"             0L  \"*##     ##@\"  J#              *#K          \n"
           " #\"               `#    \"_gmwgm_~    dF               `#_         \n"
           "7F        will     \"#_   ]#####F   _dK      revenge    JE         \n"
           "]                    *m__ ##### __g@\"                   F         \n"
           "                       \"PJ#####LP\"                                \n"
           "`                       0######_                      '          \n"
           "                       _0########_                                   \n"
           "     .               _d#####^#####m__              ,              \n"
           "      \"*w_________am#####P\"   ~9#####mw_________w*\"                  \n"
           "          \"\"9@#####@M\"\"           \"\"P@#####@M\"\"                      \n");
    printf("\x1b[0m");  // Reset ANSI escape code to default color

}

/*
	This function will change the color of the cmd
	input: the type of color 
	output: none
*/
void setConsoleColor(int color) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/*
this function print the option of game levels and return the user choice
input: NONE 
output: user level choice 
*/
int inputLevel(void)
{
	enum difficultyLevel user_choice = 0;

    printf("Please choose the game level:\n");
    printf(ANSI_COLOR_GREEN "1 - Easy (20 rounds)\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "2 - Moderate (15 rounds)\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_RED "3 - Hard (10 rounds)\n" ANSI_COLOR_RESET);
    printf(ANSI_BACKGROUND_MAGENTA "4 - Crazy (random number of rounds 5-25)\n\n" ANSI_COLOR_RESET);

	do
	{
		printf("Make a choice:");
		scanf("%d", &user_choice); //input the user lrvrl choice 
		while(getchar()!= '\n'); //cleaning the buffer 
	}
	while((user_choice > MAX_LEVEL) || (user_choice < MIN_LEVEL)); //check user choice 
	return user_choice;
}

/*
this function get the level the user want and change the guesses to user choice
input: level the user choice 
output: how much guesses the user have  
*/
int getMaxGusses(int level)
{
	int gusses = 0;
	switch(level)
	{
		//easy level(20)
		case Easy:
			gusses = MAX_EASY_LEVEL;
			break;
			
		//moderate level(15)
		case Moderate:
			gusses = MAX_MODERATE_LEVEL;
			break;
			
		//hard level(10)
		case Hard:
			gusses = MAX_HARD_LEVEL;
			break;
			
		//crazy level(5-25)
		case Crazy:
			gusses = randomNumber(MAX_CRAZY_LEVEL, MIN_CRAZY_LEVEL); // a random guesses between 5-25
			break;
 	}
	return gusses;
}

/*
this function input char from the user, make him to int and check if the number is fine 
input: NONE
output: the int value of char
*/
int inputPrint(void)
{
	char sign = 0;
	
	sign = getch();
	putch(sign);
	
	return (sign - MAKE_SIGN_INT); //make char to int and return 
}

/*
this function is get signs and the sing password
input: sign of the user and sing of password 
output: NONE
*/
void missesOrHit(int sign, int sign_password)
{
	if(((sign == sign1_password) || (sign == sign2_password) || (sign == sign3_password) || (sign == sign4_password))) //sign1 misses checking
	{
		if(sign == sign_password) //if it hit
		{
			hits++;
		}
		else //if its not hit its misses
		{
			misses++;
		}
	}
}

/*
this function creat the random number password
input: NONE
output: NONE 
*/
void randmPassword(void)
{
	do
	{
	sign1_password = randomNumber(MAX_PASSWORD_NUMBER, MIN_PASSWORD_NUMBER);   //random sign password 1
	sign2_password = randomNumber(MAX_PASSWORD_NUMBER, MIN_PASSWORD_NUMBER);  //random sign password 2
	sign3_password = randomNumber(MAX_PASSWORD_NUMBER, MIN_PASSWORD_NUMBER); //random sign password 3
	sign4_password = randomNumber(MAX_PASSWORD_NUMBER, MIN_PASSWORD_NUMBER);//random sign password 4
	}
	while(!findDup(sign1_password, sign2_password, sign3_password, sign4_password)); //check if we have dup numbers
}

/*
this function get a maximom number and minimom number and do random number between min to the max
input: max and min numbers for random
output: the random number 
*/
int randomNumber(int max, int min)
{
	int random_answer = 0;
	random_answer = (rand() % (max - min + ONE)+ min); //random number between max - min
	return random_answer;
}

/*
this function check if we have duplicate number in the code 
input: 4 sign
output: if we have a duplicate (True/False)
*/
bool findDup(int sign1, int sign2, int sign3, int sign4)
{
	bool check = TRUE;
	
	if((sign1 == sign2)||(sign1 == sign3)||(sign1 == sign4)||(sign2 == sign3)||(sign2 == sign4)||(sign3 == sign4)) //duplicate check
	{
		check = FALSE;
	}
	return check;
}

/*
this function check if the user choice is between 1-6
input: the sign we want to check
output: if the sign is correct (true / false)
*/
bool checkUserSign(int sign)
{
	bool dont_pass_test = 0;
	
	if((sign > MAX_PASSWORD_NUMBER)||(sign < MIN_PASSWORD_NUMBER)) //check if the number is 0<number<7
	{
		dont_pass_test = TRUE;  
	}
	return dont_pass_test;
}

/*
this function print the win message 
input: the gusses_user_have 
output: NONE
*/
void winner(int gusses_user_have)
{
	system("cls");
	
	printf("\x1b[32m");

    // Print the rest of the text in blue
    printf("\n\n                                              ._.\n");
    printf(" ___.__. ____  __ __   __  _  ______   ____   | |\n");
    printf("<   |  |/  _ \\|  |  \\  \\ \\/ \\/ /  _ \\ /    \\  | |\n");
    printf(" \\___  (  <_> )  |  /   \\     (  <_> )   |  \\  \\|\n");
    printf(" / ____|\\____/|____/     \\/\\_/ \\____/|___|  /  __\n");
    printf(" \\/                                       \\/   \\/\n\n");
	printf("\x1b[0m");
	
	printf("""\x1b[38;2;128;128;128m""a,  8a\n");
    printf("""\x1b[38;2;128;128;128m"" `8, `8)""\x1b[0m""                            ""\x1b[38;2;150;75;0m"",adPPRg,""\x1b[0m""\n");
    printf("""\x1b[38;2;128;128;128m""  8)  ]8""\x1b[0m""                        ""\x1b[38;2;150;75;0m"",ad888888888b\n""\x1b[0m""");
    printf("""\x1b[38;2;128;128;128m"" ,8' ,8'""\x1b[0m""                   ,gPP""\x1b[38;2;150;75;0m""R888888888888\n""\x1b[0m""");
    printf("""\x1b[38;2;128;128;128m"",8' ,8'""\x1b[0m""                 ,ad8\"\"   ""\x1b[38;2;150;75;0m""`Y888888888P\n""\x1b[0m""");
    printf("""\x1b[38;2;128;128;128m""8)  8)""\x1b[0m""              ,ad8\"\"        ""\x1b[38;2;150;75;0m""(8888888\"\"\n""\x1b[0m""");
    printf("""\x1b[38;2;128;128;128m""8,  8,""\x1b[0m""          ,ad8\"\"            d8""\x1b[38;2;150;75;0m""88\"\"\n""\x1b[0m""");
    printf("""\x1b[38;2;128;128;128m""`8, `8,""\x1b[0m""     ,ad8\"\"            ,ad8\"\"\n");
    printf("""\x1b[38;2;128;128;128m"" `8, `\"""\x1b[0m"" ,ad8\"\"            ,ad8\"\"\n");
    printf("""\x1b[38;2;50;50;50m""    ,gPPR8b""\x1b[0m""           ,ad8\"\"\n");
    printf("""\x1b[38;2;50;50;50m""   dP:::::Yb""\x1b[0m""      ,ad8\"\"\n");
    printf("""\x1b[38;2;50;50;50m""   8):::::(8""\x1b[0m""  ,ad8\"\"\n");
    printf("""\x1b[38;2;50;50;50m""   Yb:;;;:d88""\x1b[0m""8\"\"\n");
    printf("""\x1b[38;2;50;50;50m""    \"8ggg8P\"""\x1b[0m""      \x1b[0m ""\x1b[38;2;255;215;0m""\"Lildolev Game\" \n");
	
	printf("\nIt took you only %d guesses, but it is not impressed me!\n\n""\x1b[0m""", (max_guesses - gusses_user_have));
}

/*
this function print the lose message
input: NONE
output: NONE
*/
void lose(void)
{
printf("\n \x1b[31m/**                         \n");
printf("/**  \x1b[31m******   ******  ***** \n");
printf("/** \x1b[31m**////** **////  **///**\n");
printf("/**\x1b[31m/**   /**//***** /*******\n");
printf("/**\x1b[31m/**   /** /////**/**//// \n");
printf("***\x1b[31m//******  ****** //******\n");
printf("///\x1b[31m //////  //////   ////// \n\n\x1b[0m");
    printf("OOOOHHHH!!! Pancratius won and bought all of Hanukkah's gifts.\n");
    printf("Nothing left for you...\n");
    printf("The secret password was %d%d%d%d\n\n", sign1_password, sign2_password, sign3_password, sign4_password);
    printf("\n\nNow I invite u to take one pice\n");
    printf("                               _.._      _\n");
    printf("                              (\\   `-.  /' `\\\n");
    printf("                     _..--..__|_)      )   )`-.\n");
    printf("                    (_       |  |     /   |    `-..,,\n");
    printf("                    | )      |  |    (   ,'         )\n");
    printf("                    |,'     (  (    '  (          ,'\n");
    printf("               __..-'   \\     )  )      |         ,\\.__\n");
    printf("              `\\         \\    `. `.     )        ,'    ``--,  \n");
    printf("                `\\        \\    )  )    (        ,'        /\n");
    printf("                  `\\_      |   (  (    |       (        ,'" "Y8a,_\n");
    printf("              __,,ad8b,    (   `. `.   |      ,'     _,d88b          `\"Y8a,_\n");
    printf("      __,,aad8P\"'' _,8b    )   )  )   |     ,'   _,d88b     `\"\"\"Y8a,\n");
    printf("_,aad8P\"''       ,d8888b   )   (  (   (    (  ,d8888P\"'     __,,aadd8PP8\n");
    printf("8\"Y8b,_           `Y888888a,(,,,,),,),aabaaadgd8PP\"'__,,aadd8PP\"''    8\n");
    printf("8   \"\"Y8a,_          ``\"YYYYY88888PPPP\"''__,,aadd8PP\"''            8\n");
    printf("8       \"\"Y8a,_                     __,,aadd8PP\"''           Normand  8\n");
    printf("8           \"\"Y8a,_         __,,aadd8PP\"''                   Veilleux 8\n");
    printf("8               \"\"Y8a,,,aadd8PP\"''                                    8\n");
    printf("8                   \"8P\"''                                           _8\n");
    printf("8                    8                                         _,,aadd88\n");
    printf("8b,_                 8                                  _,,aadd88888888P\n");
    printf("8888ba,              8                           _,,aadd88888888PP\"''\n");
    printf("\"`Y8888b,_          8                    _,,aadd88888888PP\"''\n");
    printf("    \"`Y8888ba,       8             _,,aadd88888888PP\"''\n");
    printf("       \"`Y88888b,_   8      _,,aadd88888888PP\"''\n");
    printf("           \"\"88888ba,8,,aadd88888888PP\"''\n");
    printf("              \"`Y888888888888PP\"''\n");
    printf("                 \"`Y88PP\"''\n");
    printf("                     \"\n");
}



/*
this function ask the user if he want to play agin after he finished a game and return his choice 
input: NONE
output: the choice if keep playing or not (True/False)
*/
bool playAgin(void)
{
	bool answer = 0;
	char user_play_choice = 0;
	
	do
	{
		printf("Would you like to play again? (y/n): ");
		user_play_choice = getch(); //input if the user want to play agin or not 
		printf("%c\n", user_play_choice);
		
		if((user_play_choice == 'y')||(user_play_choice == 'Y'))//yes, play agin 
		{
			answer = FALSE;
		}
		else if((user_play_choice == 'n')||(user_play_choice != 'N'))//no, please stop
		{
			answer = TRUE;
		}
	}
	while(((user_play_choice != 'n') && (user_play_choice != 'y')&&((user_play_choice != 'N'))&&((user_play_choice != 'Y')))); //if its not a correct answer
		
	return answer; //return True or False 
}