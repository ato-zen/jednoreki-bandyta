#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define FILE_NAME_LENGTH 222
#define GAMES "-games"
#define CREDIT "-credit"
#define FILE_ARG "-file"

char file[FILE_NAME_LENGTH];
bool file_b = false;

int credit = 500000, games = 100000, bet = 100, symbol[8] = {0,1,2,3,4,5,6,7};

// 5 reels with 40 positions each
int reel[5][40] = {
  {1,0,0,1,0,0,6,1,0,2,0,0,2,0,3,0,3,0,0,7,0,2,0,4,0,3,0,3,0,1,0,0,1,3,4,0,5,0,0,0},
  {0,2,0,0,1,0,0,1,0,3,0,7,0,0,1,0,5,0,0,4,1,0,0,5,0,0,3,6,0,2,0,4,2,0,7,0,6,2,0,0},
  {3,0,5,0,6,5,0,3,0,1,0,4,1,0,2,6,0,1,0,5,2,4,0,4,0,0,3,1,5,0,2,0,7,6,0,1,0,2,0,0},
  {6,2,1,5,7,6,1,0,0,5,1,1,0,0,0,2,0,4,0,3,7,2,6,4,2,2,4,1,5,0,3,3,7,5,3,0,4,0,1,6},
  {2,4,2,2,1,2,0,5,3,4,2,0,5,4,1,5,0,6,1,3,0,3,2,0,4,7,5,6,7,1,5,4,6,6,2,3,1,6,3,1}
};

// payout table for each symbol starting from 0 for two hits
int payouts[8][5] = {
//    x2   x3   x4    x5
  {0, 50, 500, 1000, 2000}, //0
  {0,  0, 500, 1000, 2000}, //1
  {0,  0, 500, 1000, 2000}, //2
  {0,  0, 500, 1000, 2000}, //3
  {0,  0, 500, 2000, 4000}, //4
  {0,  0, 500, 2000, 4000}, //5
  {0,  0, 600, 3000, 6000}, //6
  {0,  0, 800, 5000, 8000}  //7
};
int wins[8][5], row[5], win_symbol, hits, total_bet, total_wins, rtp, hf;

void play(){
  FILE *fp;

  srand(time(NULL));

  if(file_b){
    fp = fopen (file, "w");
    if (fp == NULL) {
      printf("Cannot create file\n");
      return;
    }
  }

  printf("Games: %d, Bet: %d, Credit: %d\n", games, bet, credit);

  for (int i = 0; i < games; i++) {
    total_bet = total_bet + bet;
    credit = credit - bet;

    // draw a winning line/row on 5 reels
    for (int j = 0; j < 5; j++) row[j] = symbol[reel[j][rand()%40]];

    // always the first one wins
    win_symbol = row[0];
    hits = 0;

    // count how many times the first one repeats
    for (int j = 1; j < 5; j++) {
      if(row[j] == win_symbol) hits++;
      else break;
    }

    // if 0 occurs at least twice it is already a "win"
    // other symbols must occur at least 3 times
    if((win_symbol == 0 && hits == 1) || hits > 1) {
      total_wins = total_wins + payouts[win_symbol][hits];
      credit = credit + payouts[win_symbol][hits];
      wins[win_symbol][hits] = wins[win_symbol][hits] + 1;
      hf++;
    }

    if(file_b){
      fprintf(fp, "%d, %d, %d, %d, %d, %d, %d\n", i, row[0], row[1], row[2], row[3], row[4], credit);
    }
  }

  printf("Total Bet: %d, Total Wins: %d, Balance: %d\n", total_bet, total_wins, credit);
  printf("Number of Wins:\n\t[x1]\t[x2]\t[x3]\t[x4]\t[x5]\n");
  for (int i = 0; i < 8; i++) printf("%d:\t%d,\t%d,\t%d,\t%d,\t%d\n", i,
    wins[i][0], wins[i][1], wins[i][2], wins[i][3], wins[i][4]);
  printf("RTP: %.2f\n", (100.0 * total_wins / total_bet));
  printf("HF: %.2f\n", (100.0 * hf / games));

  if(file_b) fclose(fp);
}

int main(int argc, char **argv){
  if((argc % 2) == 1)
  for (int i = 1; i < argc; i = i + 2) {
      if(strcmp(GAMES, argv[i]) == 0){
        games = atoi(argv[i + 1]);
      } else if(strcmp(CREDIT, argv[i]) == 0){
        credit = atoi(argv[i + 1]);
      } else if(strcmp(FILE_ARG, argv[i]) == 0){
        if((strlen(argv[i + 1])) < FILE_NAME_LENGTH){
          strcpy(file, argv[i + 1]);
          file_b = true;
        } else {
          printf("Maximum file name length is %d characters\n", FILE_NAME_LENGTH);
        }
      } else {
        printf("Unknown argument: %s\n", argv[i] );
        printf("Example usage:\n%s %s 100000 %s 500000 %s file.txt\n",
          argv[0], GAMES, CREDIT, FILE_ARG);
        return 1;
      }
  } else {
    printf("Provide a correct number of arguments\n" );
    printf("Example usage:\n%s %s 100000 %s 500000 %s file.txt\n",
      argv[0], GAMES, CREDIT, FILE_ARG);
    return 1;
  }

  play();
  return 0;
}
