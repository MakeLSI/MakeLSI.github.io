#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LAYER 14 // ML2
#define STEP 6 // 6um
//#define LAYER 7 // POL
//#define STEP 2 // 2um

int Judge(int value, int th1, int th2)
{
  if (th2 == 0){
    if (value == th1) return(1); else return(0);
  }
  else{
    if (value >= th1 && value <= th2) return(1); else return(0);
  }
}

#define BLACK 0

int main(int ac, char **av)
{
  unsigned char **p;
  int X, Y;
  int x, y;
  char buf[256];
  FILE *fp;
  int xs, ys, xe, ye;
  int th1, th2;

  if (ac == 1){ fprintf(stderr, "usage: %s *.pgm\n", av[0]); exit(1);}
  fp = fopen(av[1], "rb");
  if (ac == 2){ th1 = BLACK; th2 = 0;}
  else if (ac == 3){ th1 = atoi(av[2]); th2 = 0;}
  else {th1 = atoi(av[2]); th2 = atoi(av[3]);}

  fgets(buf, 255, fp);
  fgets(buf, 255, fp);
  while(buf[0] == '#')
    fgets(buf, 255, fp);
  X = atoi(strtok(buf, " \t\n"));
  Y = atoi(strtok(NULL, " \t\n"));
  fgets(buf, 255, fp);
  p = (unsigned char **)malloc(sizeof(unsigned char *) * X);
  for (x = 0; x < X; x++)
    p[x] = (unsigned char *)malloc(sizeof(unsigned char) * Y);

  for (y = 0; y < Y; y++)
    for (x = 0; x < X; x++)
      p[x][y] = (unsigned char)fgetc(fp);

  // fill orthological corner
  for (y = 0; y < Y - 1; y++){
    for (x = 0; x < X - 1; x++){
      int p00, p01, p10, p11;
      p00 = Judge(p[x][y], th1, th2);
      p10 = Judge(p[x+1][y], th1, th2);
      p01 = Judge(p[x][y+1], th1, th2);
      p11 = Judge(p[x+1][y+1], th1, th2);
      if (p00 == 0 && p10 == 1 && p01 == 1 && p11 == 0) p[x+1][y+1] = p[x][y+1];
      if (p00 == 1 && p10 == 0 && p01 == 0 && p11 == 1) p[x][y+1] = p[x+1][y+1];
    }
  }

  printf("l %d\n", LAYER);
  for (y = 0; y < Y; y++){
    xs = -1;
    for (x = 0; x < X; x++){
      if (Judge(p[x][y], th1, th2) == 1 && xs == -1)	xs = x;
      if ((Judge(p[x][y], th1, th2) != 1 || x == X-1) && xs != -1){
	xe = x;
	printf("B %d %d %d %d\n", xs*STEP, -y*STEP, xe*STEP, -(y+1)*STEP);
	xs = -1;
      }
    }
  }
  fclose(fp);
  return(0);
}

