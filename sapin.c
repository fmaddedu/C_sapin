#include <stdio.h>
#include <stdlib.h>
#include "sapin.h"

#define USAGE "./sapin size"
#define INTEGER "Size must be greater than 0 !!!"

int usage() {
  printf("%s\n", USAGE);
  return 1;
}

int positive_integer() {
  printf("%s\n", INTEGER);
  return 1;
}

int my_putchar(int c) {
  write(1, &c, 1);
}

int my_putstr(char *str) {
  int i = 0;

  while (str[i] != '\0') {
    my_putchar(str[i]);
    i++;
  }
}

int my_getnbr(char *str) {
  int i = 0;
  int n = 0;

  if (str[0] == '-' && str[1] != '\0')
    i++;
  while (str[i] != '\0') {
    if ((str[i] < '0' || str[i] > '9')){
      my_putstr("There must be only numbers in the string.\n");
      return;
    }
    n = n + str[i] - 48;
    n *= 10;
    i++;
  } 
  n /= 10;
  if ((str[0] != '-' && n > 2147483647) || (str[0] == '-' && n > 2147483648)) 
    return;
  if (str[0] == '-')
    return (-1 * n);
  else
    return n;
}

int sapin_center(int size) {
  int nstars = 7;
  int i = 1;
  
  while (i < size) {
    if (i % 2 == 0)
      nstars += (6 + i);
    else
      nstars += (6 + i -1);
    i++;
    }
  return (nstars / 2);
}

void  sapin_rame(int size) {
  int i; // sapin size counter
  int l; // lines counter 
  int k; // spaces/stars counter
  int m; // sapin center
  int offset = 0; // finds start of new rame
  int t = 1; // technical counter one in two
  int nstars = 7; // stars in the longest line
  int nlin = 4; // lines in the biggest floor
  
  m = sapin_center(size); 
  i = 0;
  while (i < size) { 
    l = 0;
    if (i > 0) {
      if (i % 2 == 0) {
        offset += (2 + i - t);
        t++;
      }
      else
        offset += (2 + i - t);
    }
    while (l < nlin) { // lines
      k = 0;
      while (k < (m - l - offset)) { // spaces
        write(1, " ", 1);
        k++;
      }
      k = 0;
      while (k < (1 + 2 * (l + offset))) { // stars
        write(1, "*", 1);
        k++;
      }
      write(1, "\n", 1);
      l++;
    }
    nlin++;
    i++;
  }
}

int trunk_npipes(int size) {
  int i = 1;
  int npipes = 1;
  while (i <= size) {
    if (i % 2 == 0)
      npipes += 2;
    i++;
  }
  return npipes;
}

int trunk_offset(int size) {
  int m = sapin_center(size); 
  int npipes = trunk_npipes(size);
  return m - npipes / 2;
}

void  sapin_trunk(int size) {
  int l; // lines counter
  int k; // spaces/pipes counter
  int offset; // finds start of pipes
  int npipes; // pipes per line

  offset = trunk_offset(size);
  npipes = trunk_npipes(size);
  l = 0;
  while (l < size) {
    k = 0;
    while (k < offset) { // spaces
      write(1, " ", 1);
      k++;
    }
    k = 0;
    while (k < npipes) { // pipes
      write(1, "|", 1);
      k++;
    }
    write(1, "\n", 1);
    l++;
  }
}

int main(int argc, char **argv)
{
  int size;

  if (argc <= 1)
    return (usage());
  size  = my_getnbr(argv[1]); // = atoi(argv[1]);  
  if (size <= 0)
    return (positive_integer());
  else {
    sapin_rame(size);
    sapin_trunk(size);
  }
}
