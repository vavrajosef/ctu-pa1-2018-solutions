#include<stdio.h>
#include<stdlib.h>

const int MAX_SIZE = 100000;
const int LOAD_ERROR = -1;
const int VALUE_ERROR = -2;
const int LOAD_OK = 1;

int loadChar(char*);
int loadNumber(int*);
int loadNumberWithValueCheck(int*);
int compare (const void*, const void*);
int isPossibleToPlace(int, int[], int, int);
int largestMinDist(int[], int, int);
int loadLocationsGetSize(int[], int*);
int loadAndCalculateDistances(int[], int);

int main()
{
  int locations[MAX_SIZE], locationsSize = 0;
  printf("Mozna umisteni:\n");
  int loadResult = loadLocationsGetSize(locations, &locationsSize);
  if(loadResult == LOAD_ERROR)
  {
    return 1;
  }
  printf("Pocet billboardu:\n");
  loadResult = loadAndCalculateDistances(locations, locationsSize);
  if(loadResult == LOAD_ERROR)
  {
    return 1;
  }
  return 0;
}

/*
 * Attempts to load array of locations in { number, number, number } pattern.
 * When error occurs or *MAX_SIZE* is reached, function will return LOAD_ERROR
 *
 */
int loadLocationsGetSize(int locations[], int *locationsSize)
{
  *locationsSize = 0;
  int tempNumber;
  char tempChar;
  if(!loadChar(&tempChar) || tempChar != '{')
  {
    return LOAD_ERROR;
  }
  while(1)
  {
    if(loadNumber(&tempNumber) != LOAD_OK || loadChar(&tempChar) != LOAD_OK || tempChar == '{')
    {
      return LOAD_ERROR;
    }
    locations[*locationsSize] = tempNumber;
    *(locationsSize)+= 1;
    if(MAX_SIZE == *locationsSize)
    {
      printf("Nespravny vstup.\n");
      return LOAD_ERROR;
    }
    if(tempChar == '}')
    {
      break;
    }
  }
  return LOAD_OK;
}

/*
 * Loads locations requests and calculates best distances.
 * Locations array is lazily sorted.
 * LOAD_ERROR is returned in case of error in loading.
 * When there is no other location request, LOAD_OK is returned.
 */
int loadAndCalculateDistances(int locations[], int locationsSize)
{
  int tempNumber, locationsLoadResult, bestDistance, sorted = 0;
  char tempChar;
  while(1)
  {
    locationsLoadResult = loadNumberWithValueCheck(&tempNumber);
    if(locationsLoadResult == VALUE_ERROR)
    {
      return LOAD_ERROR;
    }
    if(locationsLoadResult == LOAD_ERROR)
    {
      break;
    }
    if(tempNumber < 2)
    {
      printf("Vzdalenost: inf\n");
      continue;
    }

    if(tempNumber > locationsSize)
    {
      printf("N/A\n");
      continue;
    }
    if(!sorted)
    {
      qsort(locations, locationsSize, sizeof(int), compare);
      sorted = 1;
    }
    if(tempNumber == 2)
    {
      bestDistance = locations[locationsSize -1 ] - locations[0];
    } else
    {
      bestDistance = largestMinDist(locations, locationsSize, tempNumber);
    }
    printf("Vzdalenost: %d\n", bestDistance);
  }
  if(scanf(" %c", &tempChar) != EOF)
  {
    printf("Nespravny vstup.\n");
    return LOAD_ERROR;
  }
  return LOAD_OK;
}

/*
 * loads number and returns LOAD_ERROR when loading fails.
 * VALUE_ERROR error is returned when loaded number is negative otherwise LOAD_OK
 */
int loadNumberWithValueCheck(int * var)
{
  if(scanf(" %d", var) != 1)
  {
    return LOAD_ERROR;
  }
  if(*var < 0)
  {
    printf("Nespravny vstup.\n");
    return VALUE_ERROR;
  }
  return LOAD_OK;
}

/*
 * wrapping method for loadNumberWithValueCheck
 * Checks result and prints error line
 */
int loadNumber(int * var)
{
  int result = loadNumberWithValueCheck(var);
  if(result == LOAD_ERROR)
  {
    printf("Nespravny vstup.\n");
  }
  return result;
}

/*
 * Tries to load one of approved characters. When fails it will print error line.
 * Otherwise LOAD_OK is returned.
 */
int loadChar(char * var)
{
  if(scanf(" %c", var) == 1 && (*var == ',' || *var == '}' || *var == '{'))
  {
    return LOAD_OK;
  }
  printf("Nespravny vstup.\n");
  return LOAD_ERROR;
}

/*
 * Comparing method for quick sort
 */
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

/*
 * Tries to place *numberToReach* points into array with minimum distance of *smallestDifference*
 * returns 1 if this combination is possible otherwise 0
 */
int isPossibleToPlace(int smallestDifference, int array[], int arraySize, int numberToReach)
{
  int pos = array[0];
  int positionsPlaced = 1;
  for (int i = 0 ; i < arraySize; i++)
  {
    if (smallestDifference <= (array[i] - pos))
    {
      positionsPlaced++;
      if (positionsPlaced == numberToReach)
      {
        return 1;
      }
      pos = array[i];
    }
  }
  return 0;
}

/*
 * This function calculates largest minimum distance in sorted array using simplified binary search.
 */
int largestMinDist(int array[], int arraySize, int elementsToPlace)
{
  int result = 0, left = 0, right = array[arraySize - 1] - array[0];
  while (left < right)
  {
    int middle = (right + left) / 2;
    if (isPossibleToPlace(middle, array, arraySize, elementsToPlace))
    {
      result = result > middle ? result : middle;
      left = middle + 1;
    }
    else
    {
      right = middle;
    }
  }
  return result;
}
