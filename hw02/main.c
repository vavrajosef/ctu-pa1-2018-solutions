#include<stdio.h>

int getDigitCount(int number, int base);
int getZeroCount(int number, int base);
int getZeroSequence(int number, int base);
int loadData(int * first, int * last, int * base, char * requiredAction);

int main()
{
  int first, last, base, loadResult;
  long int digitCount, zeroCount, zeroSequence, currentZeroSequence;
  char requiredAction;
  printf("Zadejte intervaly:\n");
  while (true) {
    digitCount = 0;
    zeroCount = 0;
    zeroSequence = 0;
    loadResult = loadData(&first, &last, &base, &requiredAction);
    if(loadResult == 2) {
      break;
    }
    if(loadResult == 1) {
      printf("Nespravny vstup.\n");
      return 1;
    }
    if(first == 0) {
      digitCount ++;
      zeroCount ++;
      zeroSequence ++;
    }
    if(requiredAction == 'l') {
      for(int i = first; i <= last; i++) {
        digitCount += getDigitCount(i, base);
      }
      printf("%s %ld\n", "Cifer:", digitCount);
    } else if(requiredAction == 's') {
      for(int i = first; i <= last; i++) {
        currentZeroSequence = getZeroSequence(i, base);
        if(currentZeroSequence > zeroSequence) {
          zeroSequence = currentZeroSequence;
        }
      }
      printf("%s %ld\n", "Sekvence:", zeroSequence);
    }
    else {
      for(int i = first; i <= last; i++) {
        zeroCount += getZeroCount(i, base);
      }
      printf("%s %ld\n", "Nul:", zeroCount);
    }
  }
  return 0;
}


int getZeroSequence(int number, int base) {
  int zeroSequence = 0, maxZeroSequence = 0;
  while(number > 0) {
    if(number % base == 0){
      zeroSequence ++;
    } else {
      if(zeroSequence > maxZeroSequence) {
        maxZeroSequence = zeroSequence;
      }
      zeroSequence = 0;
    }
    number/=base;
  }
  return maxZeroSequence;
}

int getZeroCount(int number, int base) {
  int zeroCount = 0;
  while(number > 0) {
    if(number % base == 0) {
      zeroCount++;
    }
    number /= base;
  }
  return zeroCount;
}

int getDigitCount(int number, int base) {
  int digitCount = 0;
  while (number > 0) {
    digitCount++;
    number /= base;
  }
  return digitCount;
}

int loadData(int * first, int * last, int * base, char * requiredAction) {
  *base = 10;
  char loadedChar;
  if(scanf("%c", &loadedChar) == EOF) {
    return 2;
  }

  if(loadedChar == 'r') {
    if(scanf(" %d", base) != 1 || (*base < 2 || *base > 36)) {
      return 1;
    }
    if(scanf(" %c", &loadedChar) != 1 || loadedChar != ':') {
      return 1;
    }
    if(scanf(" %c", &loadedChar) != 1) {
      return 1;
    }
  }
  if(loadedChar != '<') {
    return 1;
  }
  if(scanf(" %d", first) != 1 || *first < 0) {
    return 1;
  }
  if(scanf(" %c", &loadedChar) != 1 || loadedChar != ';') {
    return 1;
  }
  if(scanf(" %d", last) != 1 || *first > *last) {
    return 1;
  }
  if(scanf(" %c", &loadedChar) != 1 || loadedChar != '>') {
    return 1;
  }
  if(scanf(" %c", requiredAction) != 1
  || (*requiredAction  != 'l' && *requiredAction != 's' && *requiredAction != 'z')) {
    return 1;
  }
  while(scanf("%c", &loadedChar) == 1 && loadedChar == ' ');
  if(loadedChar != '\n') {
    return 1;
  }

  return 0;
}
