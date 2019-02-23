#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

int parseEdgesFromStdIn(double *);
int parsePoints(double*, double*);
double getEdge(double, double, double, double);
void getEdges(double *, double, double, double, double, double, double);
double getCircumference(double*);
int checkTriangle(double*);
int checkEquality(double*, double*);

int main () {

  double edges1[3];
  printf("%s\n", "Trojuhelnik #1:");
  if(parseEdgesFromStdIn(edges1)) {
    printf("Nespravny vstup.\n");
    return 1;
  }
  double c1 = getCircumference(edges1);
  if(checkTriangle(edges1) || c1 == 0) {
    printf("Neplatny trojuhelnik.\n");
    return 1;
  }

  double edges2[3];
  printf("%s\n", "Trojuhelnik #2:");
  if(parseEdgesFromStdIn(edges2)) {
    printf("Nespravny vstup.\n");
    return 1;
  }
  double c2 = getCircumference(edges2);
  if(checkTriangle(edges2) || c2 == 0) {
    printf("Neplatny trojuhelnik.\n");
    return 1;
  }

  if(fabs(c1 - c2) < (DBL_EPSILON * fabs(c1 + c2))) {
    if(checkEquality(edges1, edges2)) {
      printf("%s", "Trojuhelniky jsou shodne.");
    } else {
      printf("%s", "Trojuhelniky nejsou shodne, ale maji stejny obvod.");
    }
  } else if(c1 < c2) {
    printf("%s", "Trojuhelnik #2 ma vetsi obvod.");
  } else {
    printf("%s", "Trojuhelnik #1 ma vetsi obvod.");
  }
  printf("\n");
  return 0;
}

int parseEdgesFromStdIn(double * edges) {
  char beginingBracket, endingBracket, comma;
  if(scanf(" %c", &beginingBracket) != 1 || beginingBracket != '{') {
    return 1;
  }
  if(scanf(" %lf", &edges[0]) == 1) {
      if(scanf(" , %lf", &edges[1]) == 1) {
        if(scanf(" , %lf", &edges[2]) == 1) {
          if(scanf(" %c", &endingBracket) == 1
            && endingBracket == '}') {
            return 0;
          }
        }
      }
    return 1;
  } 
  double ax, ay, bx, by, cx, cy;
  if(parsePoints(&ax, &ay)
    && scanf(" %c", &comma) == 1
    && comma == ','
    && parsePoints(&bx, &by)
    && scanf(" %c", &comma) == 1
    && comma == ','
    && parsePoints(&cx, &cy)
    && scanf(" %c", &endingBracket) == 1
    && endingBracket == '}') {
    getEdges(edges, ax, ay, bx, by, cx, cy);
    return 0;
  }
  return 1;
}

int parsePoints(double * x, double * y) {
  char temporarySeparator;
  return scanf(" %c", &temporarySeparator) == 1
   && temporarySeparator == '['
   && scanf(" %lf ; %lf", x, y) == 2
   && scanf(" %c", &temporarySeparator) == 1
   && temporarySeparator == ']';
}

double getEdge(double x1, double y1, double x2, double y2) {
  double edge = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
  return edge;
}

double getCircumference(double * edges) {
  return fabs(edges[0]) + fabs(edges[1]) + fabs(edges[2]);
}

int checkEquality(double * edges1, double * edges2) {
  for(int i = 0; i < 3; i++) {
    int edgeEqual = 1;
    for (int k = 0; k < 3; k++) {
      if(fabs(edges1[i] - edges2[k]) < (DBL_EPSILON *(edges1[i] + edges2[k]))) {
        edgeEqual = 0;
        break;
      }
    }
    if(!edgeEqual) {
      return 1;
    }
  }

  for(int i = 0; i < 3; i++) {
    int edgeEqual = 1;
    for (int k = 0; k < 3; k++) {
      if(fabs(edges2[i] - edges1[k]) < (DBL_EPSILON * fabs(edges2[i] + edges1[k]))) {
        edgeEqual = 0;
      }
    }
    if(!edgeEqual) {
      return 1;
    }
  }
  return 0;
}

void getEdges(double* edges, double ax, double ay, double bx, double by, double cx, double cy) {
  *(edges) = getEdge(ax, ay, bx, by);
  *(edges + 1) = getEdge(ax, ay, cx, cy);
  *(edges + 2) = getEdge(bx, by, cx, cy);
}

int checkTriangle(double * edges) {
  if ((fabs(edges[0] + edges[1] - edges[2]) < (DBL_EPSILON * fabs(edges[0] + edges[1] + edges[2])))
    || (fabs(edges[1] + edges[2] - edges[0]) < (DBL_EPSILON * fabs(edges[1] + edges[2] + edges[0])))
    || (fabs(edges[0] + edges[2] - edges[1]) < (DBL_EPSILON * fabs(edges[0] + edges[2] + edges[1])))) {
      return 1;
  }
  if(edges[0] + edges[1] < edges[2]
    || edges[0] + edges[2] < edges[1]
    || edges[1] + edges[2] < edges[0]) {
      return 1;
  }
  return 0;
}
