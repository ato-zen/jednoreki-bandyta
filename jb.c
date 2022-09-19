#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define DLUGOSC_NAZWY_PLIKU 222
#define GIER "-gier"
#define KREDYT "-kredyt"
#define PLIK "-plik"

char plik[DLUGOSC_NAZWY_PLIKU];
bool plik_b = false;

int kredyt = 500000, gier = 100000, stawka = 100, znak[8] = {0,1,2,3,4,5,6,7};

// 5 bębnów po 40 pozycji każdy
int beben[5][40] = {
  {1,0,0,1,0,0,6,1,0,2,0,0,2,0,3,0,3,0,0,7,0,2,0,4,0,3,0,3,0,1,0,0,1,3,4,0,5,0,0,0},
  {0,2,0,0,1,0,0,1,0,3,0,7,0,0,1,0,5,0,0,4,1,0,0,5,0,0,3,6,0,2,0,4,2,0,7,0,6,2,0,0},
  {3,0,5,0,6,5,0,3,0,1,0,4,1,0,2,6,0,1,0,5,2,4,0,4,0,0,3,1,5,0,2,0,7,6,0,1,0,2,0,0},
  {6,2,1,5,7,6,1,0,0,5,1,1,0,0,0,2,0,4,0,3,7,2,6,4,2,2,4,1,5,0,3,3,7,5,3,0,4,0,1,6},
  {2,4,2,2,1,2,0,5,3,4,2,0,5,4,1,5,0,6,1,3,0,3,2,0,4,7,5,6,7,1,5,4,6,6,2,3,1,6,3,1}
};

// tabela wypłat dla każdego znaku począwszy od 0 za dwa trafienia
int stawki[8][5] = {
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
int wygrane[8][5], wiersz[5], wygrywa, trafien, razem, wygranych, rtp, hf;

void graj(){
  FILE *fp;

  srand(time(NULL));

  if(plik_b){
    fp = fopen (plik, "w");
    if (fp == NULL) {
      printf("Nie mozna utworzyć pliku\n");
      return;
    }
  }

  printf("Gier: %d, Stawka: %d, Kredyt: %d\n", gier, stawka, kredyt);

  for (int i = 0; i < gier; i++) {
    razem = razem + stawka;
    kredyt = kredyt - stawka;

    // wylosowanie linii/wiersza wygrywającego na 5-ciu bębnach
    for (int j = 0; j < 5; j++) wiersz[j] = znak[beben[j][rand()%40]];

    // wygrywa zawsze pierwszy
    wygrywa = wiersz[0];
    trafien=0;

    // zliczenie ile razy ten pierwszy się powtórzy
    for (int j=1; j < 5; j++) {
      if(wiersz[j]==wygrywa) trafien++;
      else break;
    }

    // jeżeli 0 wystąpi choć dwa razy to już jest "wygrana"
    // pozostałe znaki muszą wystąpić co najmniej 3 razy
    if((wygrywa==0 && trafien==1) || trafien>1) {
      wygranych = wygranych + stawki[wygrywa][trafien];
      kredyt = kredyt +stawki[wygrywa][trafien];
      wygrane[wygrywa][trafien] = wygrane[wygrywa][trafien] + 1;
      hf++;
    }

    if(plik_b){
      fprintf(fp, "%d, %d, %d, %d, %d, %d, %d\n", i, wiersz[0],wiersz[1],wiersz[2],
      wiersz[3],wiersz[4], kredyt);
    }
  }

  printf("Postawione: %d, Wygrane: %d, Bilans: %d\n", razem, wygranych, kredyt);
  printf("Ilość wygranych:\n\t[x1]\t[x2]\t[x3]\t[x4]\t[x5]\n");
  for (int i=0; i < 8; i++) printf("%d:\t%d,\t%d,\t%d,\t%d,\t%d\n", i,
    wygrane[i][0], wygrane[i][1], wygrane[i][2], wygrane[i][3], wygrane[i][4]);
  printf("RTP: %.2f\n", (100.0*wygranych/razem));
  printf("HF: %.2f\n", (100.0*hf/gier));

  if(plik_b) fclose(fp);
}

int main(int argc , char **argv){
  if((argc % 2)==1)
  for (int i = 1; i < argc; i=i+2) {
      if(strcmp(GIER, argv[i])==0){
        gier = atoi(argv[i+1]);
      } else if(strcmp(KREDYT, argv[i])==0){
        kredyt = atoi(argv[i+1]);
      } else if(strcmp(PLIK, argv[i])==0){
        if((strlen(argv[i+1]))<DLUGOSC_NAZWY_PLIKU){
          strcpy(plik, argv[i+1]);
          plik_b = true;
        } else {
          printf("Maksymalna długość nazwy pliku to %d znaków\n", DLUGOSC_NAZWY_PLIKU);
        }
      } else {
        printf("Nieznany argument: %s\n", argv[i] );
        printf("Przykład uruchomienia:\n%s %s 100000 %s 500000 %s plik.txt\n",
          argv[0], GIER, KREDYT, PLIK);
        return 1;
      }
  } else {
    printf("Podaj poprawną ilość argumentów\n" );
    printf("Przykład uruchomienia:\n%s %s 100000 %s 500000 %s plik.txt\n",
      argv[0], GIER, KREDYT, PLIK);
    return 1;
  }

  graj();
  return 0;
}
