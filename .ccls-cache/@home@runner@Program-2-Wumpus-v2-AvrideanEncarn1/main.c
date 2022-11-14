#include <stdio.h>
#include <stdlib.h>		// for srand
#include <ctype.h> // for toupper()


//--------------------------------------------------------------------------------
void displayCave()
{
    printf( "\n"
			"       ______18______             \n"
    		"      /      |       \\           \n"
    		"     /      _9__      \\          \n"
    		"    /      /    \\      \\        \n"
    		"   /      /      \\      \\       \n"
    		"  17     8        10     19       \n"
    		"  | \\   / \\      /  \\   / |    \n"
    		"  |  \\ /   \\    /    \\ /  |    \n"
    		"  |   7     1---2     11  |       \n"
    		"  |   |    /     \\    |   |      \n"
    		"  |   6----5     3---12   |       \n"
    		"  |   |     \\   /     |   |      \n"
    		"  |   \\       4      /    |      \n"
    		"  |    \\      |     /     |      \n"
    		"  \\     15---14---13     /       \n"
    		"   \\   /            \\   /       \n"
    		"    \\ /              \\ /        \n"
    		"    16---------------20           \n"
    		"\n");
}


//--------------------------------------------------------------------------------
void displayInstructions()
{
    printf( "Hunt the Wumpus:                                             \n"
    		"The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
    		"room has 3 tunnels leading to other rooms.                   \n"
    		"                                                             \n"
    		"Hazards:                                                     \n"
        	"1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
        	"2. Two other rooms have super-bats.  If you go there, the bats grab you and     \n"
        	"   fly you to some random room, which could be troublesome.  Then those bats go \n"
        	"   to a new room different from where they came from and from the other bats.   \n"
    		"3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and    \n"
        	"   is too heavy for bats to lift.  Usually he is asleep.  Two things wake       \n"
        	"    him up: Anytime you shoot an arrow, or you entering his room.  The Wumpus   \n"
        	"    will move into the lowest-numbered adjacent room anytime you shoot an arrow.\n"
        	"    When you move into the Wumpus' room, then he wakes and moves if he is in an \n"
        	"    odd-numbered room, but stays still otherwise.  After that, if he is in your \n"
        	"    room, he snaps your neck and you die!                                       \n"
        	"                                                                                \n"
        	"Moves:                                                                          \n"
        	"On each move you can do the following, where input can be upper or lower-case:  \n"
        	"1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
        	"   then a room number.                                                          \n"
        	"2. Shoot your guided arrow through a list of up to three adjacent rooms, which  \n"
        	"   you specify.  Your arrow ends up in the final room.                          \n"
        	"   To shoot enter 'S' followed by the number of rooms (1..3), and then the      \n"
        	"   list of the desired number (up to 3) of adjacent room numbers, separated     \n"
        	"   by spaces. If an arrow can't go a direction because there is no connecting   \n"
        	"   tunnel, it ricochets and moves to the lowest-numbered adjacent room and      \n"
        	"   continues doing this until it has traveled the designated number of rooms.   \n"
        	"   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You  \n"
        	"   automatically pick up the arrow if you go through a room with the arrow in   \n"
        	"   it.                                                                          \n"
        	"3. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
        	"4. Enter 'C' to cheat and display current board positions.                      \n"
        	"5. Enter 'D' to display this set of instructions.                               \n"
        	"6. Enter 'P' to print the maze room layout.                                     \n"
        	"7. Enter 'X' to exit the game.                                                  \n"
        	"                                                                                \n"
        	"Good luck!                                                                      \n"
        	" \n\n");
}//end displayInstructions()

//Initialize rooms
void initializeRooms(int **rooms) {
  rooms[0][0] = 0; rooms[0][1] = 0; rooms[0][2] = 0;
  rooms[1][0] = 2; rooms[1][1] = 5; rooms[1][2] = 8;
  rooms[2][0] = 1; rooms[2][1] = 10; rooms[2][2] = 3;
  rooms[3][0] = 2; rooms[3][1] = 12; rooms[3][2] = 4;
  rooms[4][0] = 3; rooms[4][1] = 14; rooms[4][2] = 5;
  rooms[5][0] = 4; rooms[5][1] = 6; rooms[5][2] = 1;
  rooms[6][0] = 5; rooms[6][1] = 15; rooms[6][2] = 7;
  rooms[7][0] = 6; rooms[7][1] = 17; rooms[7][2] = 8;
  rooms[8][0] = 7; rooms[8][1] = 9; rooms[8][2] = 1;
  rooms[9][0] = 8; rooms[9][1] = 18; rooms[9][2] = 10;
  rooms[10][0] = 9; rooms[10][1] = 11; rooms[10][2] = 2;
  rooms[11][0] = 10; rooms[11][1] = 19; rooms[11][2] = 12;
  rooms[12][0] = 11; rooms[12][1] = 13; rooms[12][2] = 3;
  rooms[13][0] = 12; rooms[13][1] = 20; rooms[13][2] = 14;
  rooms[14][0] = 13; rooms[14][1] = 15; rooms[14][2] = 4;
  rooms[15][0] = 14; rooms[15][1] = 16; rooms[15][2] = 6;
  rooms[16][0] = 15; rooms[16][1] = 20; rooms[16][2] = 7;
  rooms[17][0] = 16; rooms[17][1] = 18; rooms[17][2] = 7;
  rooms[18][0] = 17; rooms[18][1] = 19; rooms[18][2] = 9;
  rooms[19][0] = 18; rooms[19][1] = 20; rooms[19][2] = 11;
  rooms[20][0] = 19; rooms[20][1] = 16; rooms[20][2] = 13;
}

//Function for assigning a random room to an entity
void assignRand(int *entityRoom) {
  *entityRoom = rand() % 20 + 1; //Assigns a random number 1..20
}

//Function for game set up
void setUpGame(int *user, int *wumpus, int *pit1, int *pit2, int *bat1, int *bat2, int *arrow) {
  
  assignRand(user); //Assign random room to user

  //Make sure components aren't assigned to same rooms
  while (*wumpus == 0) { //Set up wumpus
    assignRand(wumpus);
    if (*wumpus == *user) {
      *wumpus = 0;
    }
  }
  while (*pit1 == 0) { //Set up pit1
    assignRand(pit1);
    if ((*pit1 == *user) || (*pit1 == *wumpus)) {
      *pit1 = 0;
    }
  }
  while (*pit2 == 0) { //Set up pit2
    assignRand(pit2);
    if ((*pit2 == *user) || (*pit2 == *wumpus) || (*pit2 == *pit1)) {
      *pit2 = 0;
    }
  }
  while (*bat1 == 0) { //Set up bat1
    assignRand(bat1);
    if ((*bat1 == *user) || (*bat1 == *wumpus) || (*bat1 == *pit1) || (*bat1 == *pit2)) {
      *bat1 = 0;
    }
  }
  while (*bat2 == 0) { //Set up bat2
    assignRand(bat2);
    if ((*bat2 == *user) || (*bat2 == *wumpus) ||(*bat2 == *pit1) || (*bat2 == *pit2) || (*bat2 == *bat1)) {
      *bat2 = 0;
    }
  }
  while (*arrow == 0) { //Set up arrow
    assignRand(arrow);
    if ((*arrow == *user) || (*arrow == *wumpus) ||(*arrow == *pit1) || (*arrow == *pit2) || (*arrow == *bat1) || (*arrow == *bat2)) {
      *arrow = 0;
    }
  }
}

//Function for checking if room 2 is adjacent to room 1
int adjacent(int **rooms, int room1, int room2) {
  if ((rooms[room1][0] == room2) || (rooms[room1][1] == room2) || (rooms[room1][2] == room2)) {
    return 1;
  }
  else {
    return 0;
  }
}

//Function for moving the wumpus into the lowest adjoining room
void wumpusMove(int **rooms,int *wumpus) {
  int adjoin1 = rooms[*wumpus][0];
  int adjoin2 = rooms[*wumpus][1];
  int adjoin3 = rooms[*wumpus][2];

  //Find lowest adjoining room and send arrow to it
  if ((adjoin1 < adjoin2) && (adjoin1 < adjoin3)) {
    *wumpus = adjoin1;
  }
  else if (adjoin2 < adjoin3) {
    *wumpus = adjoin2;
  }
  else {
    *wumpus = adjoin3;
  }
}

//Check for the wumpus, returns 1 if user dies
int checkWumpus(int **rooms, int user, int *wumpus) {
  if (user == *wumpus) {
    if (user % 2 == 1) { //Check if the room number is odd
      return 2;
    }
    else { //If room is even user dies
      return 1;
    }
  }
  return 0;
}

//Check for a pit, returns 1 if user dies
int checkPit(int user, int pit1, int pit2) {
  if ((user == pit1) || (user == pit2)) {
    return 1;
  }
  return 0;
}

//Check for bats, returns 1 if user is moved
int checkBat(int user, int bat1, int bat2) {
  if (user == bat1) { //If the user is with bat1
    return 1;
  }
  else if (user == bat2) { //Same thing for bat2
    return 2;
  }
  //Return 0 if user isn't in a room with any bat
  return 0;
    
}

//Function to move user and bats when they interact
void batPickup(int *user, int *movingBat, int *otherBat) {
  int currRoom = *user; //Keep track of current room so entities don't move back into this room

  while(*user == currRoom) { //Assign a random room to the user that isn't the current room
    assignRand(user);
  }

  while(*movingBat == currRoom || *movingBat == *otherBat) { //And assign a random room to the bat that isn't the current room or the same room as the other bat
    assignRand(movingBat);
  }
}

//Function to check all hazards present in the same room as the user
int checkHazards(int **rooms, int *user, int *wumpus, int pit1, int pit2, int *bat1, int *bat2) {
  
  if(checkWumpus(rooms, *user, wumpus) == 1) { //First check for wumpus
    printf(	"You briefly feel a slimy tentacled arm as your neck is snapped. \n"
			"It is over.\n");
    return 1;
  }
  else if(checkWumpus(rooms, *user, wumpus) == 2) {
    wumpusMove(rooms, wumpus); //Wumpus will move if checkWumpus is odd
    printf( "You hear a slithering sound, as the Wumpus slips away. \n"
			"Whew, that was close! \n");
  }

  if(checkPit(*user, pit1, pit2) == 1) { //Second check for pits
    printf("Aaaaaaaaahhhhhh....   \n");
	  printf("    You fall into a pit and die. \n");
    return 1;
  }

  //While a user is found in the same room as a bat since a bat chain is possible
  while (checkBat(*user, *bat1, *bat2) != 0) {
    if(checkBat(*user, *bat1, *bat2) == 1) { //If user is with bat1
      batPickup(user, bat1, bat2);
      
      printf("Woah... you're flying! \n");
      printf("You've just been transported by bats to room %d.\n", *user);
    }

    if(checkBat(*user, *bat1, *bat2) == 2) { //If user is with bat2
      batPickup(user, bat2, bat1);
      
      printf("Woah... you're flying! \n");
      printf("You've just been transported by bats to room %d.\n", *user);
    }
  }

  return 0;
}

//Function to check adjacent rooms for hazards and display their respective messages
void checkAdjHazards(int **rooms, int user, int wumpus, int pit1, int pit2, int bat1, int bat2) {

  //Check for adjacent wumpus
  if (adjacent(rooms, user, wumpus) == 1) {
    printf("You smell a stench. ");
  }

  //Check for adjacent pits
  if ((adjacent(rooms, user, pit1) == 1) || (adjacent(rooms, user, pit2) == 1)) {
    printf("You feel a draft. ");
  }

  //Check for adjacent bats
  if ((adjacent(rooms, user, bat1) == 1) || (adjacent(rooms, user, bat2) == 1)) {
    printf("You hear rustling of bat wings. ");
  }
  printf("\n\n");
}

//Function to ricochet arrow
void ricochet(int **rooms, int room, int *arrow) {
  int adjoin1 = rooms[room][0];
  int adjoin2 = rooms[room][1];
  int adjoin3 = rooms[room][2];

  //Find lowest adjoining room and send arrow to it
  if ((adjoin1 < adjoin2) && (adjoin1 < adjoin3)) {
    *arrow = adjoin1;
  }
  else if (adjoin2 < adjoin3) {
    *arrow = adjoin2;
  }
  else {
    *arrow = adjoin3;
  }
}

//Function for shooting the arrow
int shootArrow(int **rooms, int user, int *wumpus, int *arrow, int *arrowMoves) {
  int currRoom = user;

  printf("Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: "); // Prompt user to enter amount of rooms for arrow to shoot through
  scanf("%d", arrowMoves);

  if (*arrowMoves > 3) {
    printf("Sorry, the max number of rooms is 3.  Setting that value to 3."); // User enters more than 3 rooms to shoot arrow through
    *arrowMoves = 3;
  }

  int valid = 1;

  for (int i = 0; i < *arrowMoves; i++) {
    if (valid != 0) { //Will stop scanning if arrow starts to ricochet
      scanf(" %d", arrow); //Read in next room from input buffer

      valid = adjacent(rooms, currRoom, *arrow);
    }
    
    if (valid == 1) { //Check if arrow move is valid
      currRoom = *arrow; //Update current room arrow is at

      if (*arrow == *wumpus) { //Check if arrow pierces wumpus
	      printf( "Wumpus has just been pierced by your deadly arrow! \n"
            "Congratulations on your victory, you awesome hunter you.\n"); // Arrow killed Wumpus
        return 1;
      }
      if (*arrow == user) { //or user
	      printf( "You just shot yourself.  \n"
            "Maybe Darwin was right.  You're dead.\n"); // Arrow killed player
        return 1;
      }
    }
    else { //Ricochet if not valid
	    printf("Room %d is not adjacent.  Arrow ricochets...\n", *arrow); // Attempt to shoot arrow through room that is not adjacent
      
      valid = 0; //Start the ricochet by making valid = 0
      
      ricochet(rooms, currRoom, arrow);
      
      currRoom = *arrow; //Update current room arrow is at

      if (*arrow == *wumpus) { //Check if ricochet arrow pierces wumpus
	      printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n"
            "Accidental victory, but still you win!\n"); // Arrow ricochets, and kills Wumpus
        return 1;
      }
      if (*arrow == user) { //or user
	      printf( "You just shot yourself, and are dying.\n"
            "It didn't take long, you're dead.\n"); // Arrow ricochets, and kills person
        return 1;
      }
    }
  }
  wumpusMove(rooms, wumpus); //Wumpus moves when user shoots an arrow and is still alive

  return 0;
}

//--------------------------------------------------------------------------------
int main(void) {

	// Seed the random number generator.  Change seed to time(0) to change output each time.
    // srand(time(0));
    srand(1);

  //Dynamically allocate space for first dimension of array
  int **adjRooms = (int **)malloc(21 * sizeof(int *));
  for (int i = 0; i < 21; i++) {
    adjRooms[i] = (int *)malloc(3 * sizeof(int));
  }

  initializeRooms(adjRooms); //Fill rooms with their values

  int end = 0;

  //Declare entities and hazards
  int user = 0;
  int wumpus = 0;
  int pit1 = 0, pit2 = 0;
  int bat1 = 0, bat2 = 0;
  int arrow = 0;

  int moveNum = 1;

  setUpGame(&user, &wumpus, &pit1, &pit2, &bat1, &bat2, &arrow); //Game set up

  //Create variables for user inputs
  char userInput = ' ';
  int userMove = -1;
  int arrowMoves = 0,arrowMove1 = -1, arrowMove2 = -1, arrowMove3 = -1;

  while (end == 0) {

    //Check for immediate hazards within the room
    if (checkHazards(adjRooms, &user, &wumpus, pit1, pit2, &bat1, &bat2) == 1) {
      break;
    }

    if (user == arrow) {
      printf("Congratulations, you found the arrow and can once again shoot.\n"); // Player picks up arrow
      arrow = -1;
    }

    printf("You are in room %d. ", user); //Display room of user

    checkAdjHazards(adjRooms, user, wumpus, pit1, pit2, bat1, bat2); //Check and display for hazards in adjacent rooms

    printf("%d. Enter your move (or 'D' for directions): ", moveNum); //Move number and prompt
    
    scanf(" %c", &userInput); //User input

    userInput = toupper(userInput);
    
    //Check if input is X
    if (userInput == 'X') {
      break;
    }
    
    switch(userInput) {
      case 'D' :
        displayCave();
        displayInstructions();
        break;
      case 'M' :
        scanf(" %d", &userMove);
        if (adjacent(adjRooms, user, userMove) == 1) {
          user = userMove;
          moveNum++;
        }
        else {
          printf("Invalid move.  Please retry. \n"); // Message for invalid move
        }
        break;
      case 'R' : // Prompt for user when they choose to reset
  	    printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, bats2, and arrow: \n");
        scanf("%d %d %d %d %d %d %d", &user, &wumpus, &pit1, &pit2, &bat1, &bat2, &arrow);
        break;
      case 'C' : // Message for menu option C (cheating). Note that the printf() statement below always prints
        printf( "Cheating! Game elements are in the following rooms: \n"
    		  "Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n"
    		  "%4d %5d %6d %5d %5d %5d %5d \n\n", 
  			  user, wumpus, pit1, pit2, bat1, bat2, arrow);
        break;
      case 'P' :
        displayCave();
        break;
      case 'S' :
        if(arrow != -1) { // Attempt to shoot arrow you don't have
          printf("Sorry, you can't shoot an arrow you don't have.  Go find it.\n");
        }
        else {
          end = shootArrow(adjRooms, user, &wumpus, &arrow, &arrowMoves);
        }
        moveNum++;
        break;
    }
  }

	printf("\nExiting Program ...\n"); // Message that prints at the end of the program

  // Free array memory
  for (int i = 0; i < 21; i++) {
    free(adjRooms[i]);
  }
  free(adjRooms);
	
	return 0;
}