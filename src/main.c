#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRSIZE 300
// a struct that contains question information
struct Infos {
  char level_no[ARRSIZE];
  char question[ARRSIZE];
  char choiceA[ARRSIZE];
  char choiceB[ARRSIZE];
  char choiceC[ARRSIZE];
  char choiceD[ARRSIZE];
  char correctChoice[ARRSIZE];
};
// a struct that contains player data
struct User {
  int money;

  int correct;
  int halvCheck;
  int dDipCheck;
};
// functions declared
struct Infos assignment(int);
struct User game(struct Infos, struct User);

int main() {
  // required variables and arrays are assigned
  struct Infos info;
  struct User user;
  user.halvCheck = 0;
  user.dDipCheck = 0;
  char name[ARRSIZE];
  char allVar1[500];
  char allVar2[500];
  char toStr[6];
  int k;
  // open the file to read the player’s name and the prize won
  FILE *fPtr2 = fopen("players.txt", "r+");
  if (fPtr2 == NULL) {
    printf("cannot open the file");
  }
  // read the file line by line until the end and print each line to the screen
  while (!feof(fPtr2)) {
    fgets(allVar2, sizeof(allVar2), fPtr2);
    printf(" %s\n", allVar2);
  }
  // close the file
  fclose(fPtr2);

  // greet the player, show the prizes, and explain the lifelines
  // get the player's name
  printf(
      "Welcome to Who wants to be a millionaire?\nPlease enter your name:\n");
  scanf(" %s", name);
  printf("\n1 question answered correctly: 2000 TL\n 2 questions answered "
         "correctly: 5000 TL\n 3 questions answered correctly: 7500 TL\n");
  printf("4 questions answered correctly: 10000 TL TL\n 5 questions answered "
         "correctly: 20000 TL \n 6 questions answered correctly: 30000 TL\n");
  printf("7 questions answered correctly: 50000 TL TL\n 8 questions answered "
         "correctly: 100000 TL \n 9 questions answered correctly: 200000 TL\n");
  printf(
      "10 questions answered correctly: 300000 TL\n 11 questions answered "
      "correctly: 500000 TL\n 12 questions answered correctly: 1000000 TL\n");
  printf("\nLifelines: '50/50' and 'Doubledip'\n");
  printf("If you want to leave and take your money enter 'leave'.\n");
  printf("If you want to use lifelines enter '50/50' or 'doubledip'.\n");
  // loop through the 12 questions in the game
  for (k = 1; k <= 12; k++) {
    // the assignment() function, which assigns the question data to the created
    // struct in an organized way, is called. In this way, the questions are
    // stored in the struct for later use
    info = assignment(k);
    // the previously defined info struct, which is filled by assignment(), is
    // passed to the game() function the struct returned by game() is assigned
    // to the created user struct. In this way, the player data is stored
    user = game(info, user);
    // if the correct value taken from the user struct is not equal to 1, the
    // game ends at that point
    if (user.correct != 1)
      break;
  }
  // the file is opened to write the player’s name and the prize won
  FILE *fPtr1 = fopen("players.txt", "r+");
  // it gets the current active file position in the stream
  fpos_t pos;
  if (fPtr1 == NULL) {
    printf("cannot open the file");
  }
  // the file is read line by line until the end and the content is stored in
  // the allVar1 array
  while (!feof(fPtr1)) {
    fgets(allVar1, sizeof(allVar1), fPtr2);
  }
  // the current position of the file in the stream is obtained and assigned to
  // pos
  fgetpos(fPtr1, &pos);
  // with fseek, writing starts from the last written position in the file
  // by writing this code block, the aim is to write the data to the file line
  // by line
  fseek(fPtr1, pos, SEEK_SET);

  fprintf(fPtr1, "\nplayer name: %s won prize: %d", name, user.money);

  // close the file
  fclose(fPtr1);

  return 0;
}
// a function that assigns the questions to the struct structure in an organized
// way.
struct Infos assignment(int key_lvlno) {
  // the necessary variables and arrays were defined
  struct Infos info;
  char foundStr[ARRSIZE];
  char realFoundStr[ARRSIZE];
  char toStr[6];

  char s[2] = ",";
  char *token, *temp;
  int compareNum;

  srand(time(NULL));

  // the question number of the selected question is obtained and compared with
  // the key_levelno entered in the function
  while (compareNum != key_lvlno) {
    // open the file to read data
    FILE *fPtr = fopen("question.csv", "r+");
    // generate a random number and convert it to a string to compare it with
    // levelno
    int rndm = rand() % 1923 + 343;
    sprintf(toStr, "%ld", rndm);

    while (fgets(realFoundStr, sizeof(realFoundStr), fPtr) !=
           NULL) { // read a line from the file
      if (strstr(realFoundStr, toStr) !=
          NULL) { // was the data you are looking for found in the line
        // printf("The searched data was found: %s\n", realFoundStr);
        break; // terminate the loop when the data is found
      }
    }
    // assign the found line to the real array
    strcpy(foundStr, realFoundStr);
    // split the string by commas, get the question number, and check whether it
    // satisfies the loop condition
    token = strtok(foundStr, s);
    token = strtok(NULL, s);
    sscanf(token, "%d", &compareNum);
    // printf("%d\n",compareNum);

    /*while (fgets(realFoundStr, sizeof(realFoundStr), fPtr) != NULL)
    { // read a line from the file
        if (strstr(realFoundStr, toStr) != NULL)
        { // was the data you are looking for found in the line?
            printf("The searched data was found: %s\n", realFoundStr);
            break; // terminate the loop when the data is found
        }
    }
*/
    // close the file
    fclose(fPtr);
  }
  // the real string is assigned to the struct by splitting it with commas
  temp = strtok(realFoundStr, s);
  strcpy(info.level_no, strtok(NULL, s));
  strcpy(info.question, strtok(NULL, s));
  strcpy(info.choiceA, strtok(NULL, s));
  strcpy(info.choiceB, strtok(NULL, s));
  strcpy(info.choiceC, strtok(NULL, s));
  strcpy(info.choiceD, strtok(NULL, s));
  strcpy(info.correctChoice, strtok(NULL, s));
  // return struct
  return info;
}
// function for collecting player data and running the main game
struct User game(struct Infos info, struct User user) {
  // required variables assigned
  char answer[ARRSIZE];
  // the array containing the prize amounts was defined
  int balArr[12] = {2000,  5000,   7500,   10000,  20000,  30000,
                    50000, 100000, 200000, 300000, 500000, 1000000};
  int balance = 0, i, j;

  // flags to track which options are visible (1=visible, 0=hidden by lifeline)
  int showA = 1, showB = 1, showC = 1, showD = 1;
  // flag to track if doubledip is active for this question (gives 2 chances)
  int dDipActive = 0;
  // tracks how many wrong attempts have been made with doubledip
  int dDipAttempts = 0;

  // loop to allow using multiple lifelines on the same question
  while (1) {
    // print the question with currently visible options
    printf("%s. question\n %s\n", info.level_no, info.question);
    if (showA)
      printf(" A-%s\n", info.choiceA);
    if (showB)
      printf(" B-%s\n", info.choiceB);
    if (showC)
      printf(" C-%s\n", info.choiceC);
    if (showD)
      printf(" D-%s\n", info.choiceD);

    // collect the player's answer
    scanf(" %s", answer);

    // if the player types "leave", they exit the game
    if (strcmp(answer, "leave") == 0) {
      // the amount of money the player has won is determined and assigned to
      // the struct
      sscanf(info.level_no, "%d", &i);
      balance = balArr[i - 2];
      user.money = balance;
      printf("your money: %d\n", balance);
      // the game ended status is assigned to the struct
      user.correct = 0;
      return user;
    }
    // if the player types "50/50", the lifeline is activated
    else if (strcmp(answer, "50/50") == 0) {
      // determine whether the player has used the lifeline
      if (user.halvCheck != 1) {
        // eliminate two wrong options based on the correct answer, keeping the
        // correct one and one other
        if (strcmp(info.correctChoice, "A") == 0) {
          showB = 0;
          showD = 0;
        } else if (strcmp(info.correctChoice, "B") == 0) {
          showC = 0;
          showD = 0;
        } else if (strcmp(info.correctChoice, "C") == 0) {
          showB = 0;
          showD = 0;
        } else if (strcmp(info.correctChoice, "D") == 0) {
          showA = 0;
          showC = 0;
        }
        // indicate that the lifeline has been used
        user.halvCheck = 1;
        // continue the loop to re-display the question with reduced options
        continue;
      } else {
        // if the lifeline has already been used, inform the player and let them
        // try again
        printf("used lifeline.\n");
        continue;
      }
    }
    // if the player types doubledip, the lifeline is activated
    else if (strcmp(answer, "doubledip") == 0) {
      // determine whether the player has used the lifeline
      if (user.dDipCheck != 1) {
        // activate doubledip for this question and mark it as used
        dDipActive = 1;
        user.dDipCheck = 1;
        // continue the loop to re-display the question and let the player
        // answer
        continue;
      } else {
        // if the lifeline has already been used, inform the player and let them
        // try again
        printf("used lifeline.\n");
        continue;
      }
    }
    // if no lifeline or "leave" was entered, treat the input as a direct answer
    // (A/B/C/D)
    else {
      // compare the player's answer with the correct answer of the question
      if (strcmp(info.correctChoice, answer) == 0) {
        printf("Correct answer.\n");
        sscanf(info.level_no, "%d", &i);
        balance = balArr[i - 1];
        user.money = balance;
        printf("your money: %d\n", balance);
        // the game continuing status is assigned to the struct
        user.correct = 1;
        return user;
      } else {
        // wrong answer given
        // if doubledip is active and this is the first wrong attempt, remove
        // the wrong option and give another chance
        if (dDipActive && dDipAttempts == 0) {
          printf("Wrong answer.\n");
          dDipAttempts = 1;
          // hide the wrong option that the player chose
          if (strcmp(answer, "A") == 0)
            showA = 0;
          else if (strcmp(answer, "B") == 0)
            showB = 0;
          else if (strcmp(answer, "C") == 0)
            showC = 0;
          else if (strcmp(answer, "D") == 0)
            showD = 0;
          // continue the loop to re-display the question without the wrong
          // option
          continue;
        } else {
          // final wrong answer - game ends
          printf("Wrong answer.\n");
          sscanf(info.level_no, "%d", &j);
          // the amount of money the player has won is determined based on their
          // current position and assigned to the struct
          if (j > 2 && j <= 7) {
            balance = 5000;
            user.money = balance;
            printf("your money: %d\n", balance);
            user.correct = 0;
          } else if (j >= 8 && j < 12) {
            balance = 50000;
            user.money = balance;
            printf("your money: %d\n", balance);
            user.correct = 0;
          } else {
            balance = 0;
            user.money = balance;
            printf("your money: %d\n", balance);
            user.correct = 0;
          }
          // return the player information
          return user;
        }
      }
    }
  }
}
