#include <stdio.h>
#include <math.h>
#include <stdlib.h>

unsigned long long int hyperloop                           ( unsigned long long int length,
                                                             unsigned int        s1,
                                                             unsigned int        s2,
                                                             unsigned int        s3,
                                                             unsigned int        bulkhead,
                                                             unsigned int      * c1,
                                                             unsigned int      * c2,
                                                             unsigned int      * c3 )
{
  unsigned long long int solutioncount = 0;
  if(length == 0 || bulkhead > length || (s1 == 0 && s2 == 0 && s3 == 0 && bulkhead != length))
  {
    return 0;
  }
  if(bulkhead == length)
  {
    *c3 = *c2 = *c1 = 0;
    return 1;
  }
  length-=bulkhead;
  unsigned int s1wbulk = s1 + bulkhead;
  unsigned int s2wbulk = s2 + bulkhead;
  unsigned int s3wbulk = s3 + bulkhead;
  if(s1wbulk > length && s2wbulk > length && s3wbulk > length)
  {
    return 0;
  }
  unsigned int largestVal;
  unsigned int mediumVal;
  unsigned int smallestVal;
  if(s1wbulk == s2wbulk && s2wbulk == s3wbulk)
  {
    if(length % s1wbulk == 0)
    {
      *c1 = length / s1wbulk;
      *c2 = *c3 = 0;
      return 1;
    }
    return 0;
  } else if (s1wbulk == 0)
  {
    largestVal = s2wbulk > s3wbulk ? s2wbulk : s3wbulk;
    smallestVal = s2wbulk < s3wbulk ? s2wvulk : s3wbulk;
    if(smallestVal == 0)
    {
      if(length % largestVal == 0)
      {
        return 1;
      }
      return 0;
    }
    unsigned long long int maxReach = length / largestVal;
    for(int i = 0; i <=maxReach; i++)
    {
      unsigned long long int rest = length - (largestVal * i);
      if(rest % smallestVal == 0)
      {
        solutioncount ++;
      }
    }
  } else if(s2wbulk == 0)
  {

  } else if(s3wbulk == 0)
  {

  }
  else if(s1wbulk == s2wbulk || s2wbulk == s3wbulk || s1wbulk == s3wbulk)
  {
    largestVal = s1wbulk > s2wbulk ? s1wbulk : s2wbulk;
    largestVal = largestVal > s3wbulk ? largestVal : s3wbulk;
    smallestVal = s1wbulk < s2wbulk ? s1wbulk : s2wbulk;
    smallestVal = smallestVal < s3wbulk ? smallestVal : s3wbulk;
    unsigned long long int maxReach = length / largestVal;
    for(int i = 0; i <=maxReach; i++)
    {
      unsigned long long int rest = length - (largestVal * i);
      if(rest % smallestVal == 0)
      {
        solutioncount ++;
      }
    }
  }
  else
  {
    largestVal = s1wbulk > s2wbulk ? s1wbulk : s2wbulk;
    largestVal = largestVal > s3wbulk ? largestVal : s3wbulk;
    smallestVal = s1wbulk < s2wbulk ? s1wbulk : s2wbulk;
    smallestVal = smallestVal < s3wbulk ? smallestVal : s3wbulk;
    mediumVal = s1wbulk == largestVal
    ? (s2wbulk == smallestVal
      ? s3wbulk : s2wbulk) : (s1wbulk == smallestVal
        ? (s2wbulk == largestVal
          ? s3wbulk : s2wbulk) : s1wbulk);

    unsigned long long int maxReach = length / largestVal;
    unsigned long long int medReach = length / mediumVal;
    for(int i = 0; i <= maxReach; i++)
    {
      for (int k = 0; k <= medReach; k ++)
      {
        unsigned long long int minus = (i* largestVal + k * mediumVal);
        if(minus > length) {
          break;
        }
        unsigned long long int currentresult = length - minus;
        if(currentresult % smallestVal == 0) {
          solutioncount++;
        }
      }
    }
  }
  return solutioncount;
}
