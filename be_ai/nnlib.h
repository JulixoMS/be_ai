#ifndef __NNLIB
#define __NNLIB
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <quadmath.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define NN_HIDDEN 0
#define NN_INPUT  1
#define NN_OUTPUT 2

typedef __int128 int128_t;
typedef __float128 float128_t;

typedef struct neuron {
  float128_t add;
  float128_t value;
  float128_t bias;
  float128_t *weights;
  int128_t index;
  uint8_t mode : 2;
} neuron;

typedef struct layer {
  neuron *neurons;
  int128_t index;
  int128_t size;
} layer;

typedef struct network {
  layer *layers;
  int128_t size;
} network;

neuron *makeneuron(uint8_t mode, int128_t index) {
  neuron *n = malloc(sizeof(neuron));
  n->add = 0;
  n->value = 0;
  n->bias = 0;
  n->mode = mode;
  n->weights = NULL;
  n->index = index;
  return n;
}

layer *makelayer(uint8_t mode, int128_t size, int128_t index) {
  layer *l = malloc(sizeof(layer));
  l->index = 0;
  l->neurons = malloc(sizeof(neuron)*size);
  l->size = size;
  for (int128_t i = 0; i < size; i++) {
    l->neurons[i] = *makeneuron(mode, i);
  }
  return l;
}

network *makenetwork(int128_t *layrl, int128_t layrc) {
  network *t = malloc(sizeof(network));
  t->size = layrc;
  t->layers = malloc(sizeof(layer)*layrc);
  for (int128_t i = 0; i < layrc; i++) {
    uint8_t mode = (i==0)?(NN_INPUT):((i==layrc-1)?(NN_OUTPUT):(NN_HIDDEN));
    t->layers[i] = *makelayer(mode, layrl[i], i);

    for (int128_t j = 0; j < t->layers[i].size-1; j++) {
      t->layers[i].neurons[j].weights = malloc(sizeof(float128_t)*t->layers[i+1].size);
      for (int128_t k = 0; k < t->layers[i+1].size; k++) {
        t->layers[i].neurons[j].weights[k] = 0;
      }
    }
  }
  return t;
}

void randomizenn(network *n) {
  
}
#endif