#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <quadmath.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "fileman.h"
#include "nnlib.h"

char *model_name;
network *nn;

int128_t nnl[130];

int main(int argc, char **argv) {
  printf("Generating NN layer map... ");
  nnl[0] = 16658;
  for (uint16_t i = 1; i < 129; i++) {
    nnl[i] = 32768;
  }
  nnl[129] = 1105;
  printf("Done!\n");
  printf("Generating NN... ");
  nn = makenetwork(nnl, 3);
  printf("Done!\n");
  printf("Randomizing weights & biases... ");
  randomizenn(nn);
  printf("Done!\n");
  if (argc > 1) {
    if (strcmp(argv[1], "test") == 0) {
      if (argc == 3) {
        model_name = malloc(strlen(argv[2]));
        strcpy(model_name, argv[2]);
      } else if (argc == 2) {
        model_name = malloc(6);
        strcpy(model_name, "april");
      } else {
        printf("E002. Too many args parsed!\n");
        printf("Syntax: ./be_ai test/train/help [model]\n");
        return 2;
      }
      printf("Loading model '%s' from file '%s.mdl'...\n", model_name, model_name);
    } else if (strcmp(argv[1], "train") == 0) {
      if (argc == 3) {
        model_name = malloc(strlen(argv[2]));
        strcpy(model_name, argv[2]);
      } else if (argc == 2) {
        model_name = malloc(6);
        strcpy(model_name, "april");
      } else {
        printf("E003. Too many args parsed!\n");
        printf("Syntax: ./be_ai test/train/help [model]\n");
        return 3;
      }
      printf("Loading model '%s' from file '%s.mdl'...\n", model_name, model_name);
    }
  } else {
    printf("E001. No args parsed!\n");
    printf("Syntax: ./be_ai test/train/help [model]\n");
    return 1;
  }
  return 0;
}