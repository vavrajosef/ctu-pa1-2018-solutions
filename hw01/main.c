#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

double getEdge(double, double, double, double);
void getEdges(double *, double, double, double, double, double, double);
double getCircumference(double*);
int checkTriangle(double*);
int checkEquality(double*, double*);
int parseTriangle(int, double *, double *, double *, double *, double *, double *);
int checkTriangle(double, double, double, double, double, double);
int parseInput(const char *, double *, double *);

int main () {
  double ax1, ay1, bx1, by1, cx1, cy1;
  double ax2, ay2, bx2, by2, cx2, cy2;
  if(parseTriangle(1, &ax1, &ay1, &bx1, &by1, &cx1, &cy1)) {
    return 1;
  }
  double edges1[3];
  getEdges(edges1, ax1, ay1, bx1, by1, cx1, cy1);
  double c1 = getCircumference(edges1);
  if(checkTriangle(edges1) || c1 == 0) {
    printf("Body netvori trojuhelnik.\n");
    return 1;
  }

  if(parseTriangle(2, &ax2, &ay2, &bx2, &by2, &cx2, &cy2)) {
    return 1;
  }
  double edges2[3];
  getEdges(edges2, ax2, ay2, bx2, by2, cx2, cy2);
  double c2 = getCircumference(edges2);
  if(checkTriangle(edges2) || c2 == 0) {
    printf("Body netvori trojuhelnik.\n");
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

int parseInput(char const * lineToPrint, double * x, double * y) {
  printf("%s\n", lineToPrint);
  int parseResult;
  parseResult = scanf("%lf %lf", x, y);
  if(parseResult != 2) {
    printf("%s\n", "Nespravny vstup.");
    return 1;
  }
  return 0;
}

int parseTriangle(int triangleNumber, double * ax, double * ay,
  double * bx, double * by,
  double * cx, double * cy) {
  printf("%s%d:\n", "Trojuhelnik #", triangleNumber);
  char const *printStringA = "Bod A:";
  if (parseInput(printStringA, ax, ay)) {
    return 1;
  }
  char const *printStringB = "Bod B:";
  if (parseInput(printStringB, bx, by)) {
    return 1;
  }
  char const *printStringC = "Bod C:";
  if (parseInput(printStringC, cx, cy)) {
    return 1;
  }

  return 0;
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

int checkTriangle(double ax, double ay, double bx, double by, double cx, double cy) {
  double res = ax * (by - cy) + bx * (cy - ay) + cx * (ay - by);
  if(res > (DBL_EPSILON * res) && res < -(DBL_EPSILON * res)) {
    return 1;
  }
  return 0;
}

int checkTriangle(double * edges) {
  if ((fabs(edges[0] + edges[1] - edges[2]) < (DBL_EPSILON * fabs(edges[0] + edges[1] + edges[2])))
    || (fabs(edges[1] + edges[2] - edges[0]) < (DBL_EPSILON * fabs(edges[1] + edges[2] + edges[0])))
    || (fabs(edges[0] + edges[2] - edges[1]) < (DBL_EPSILON * fabs(edges[0] + edges[2] + edges[1])))) {
      return 1;
  }
  return 0;
}
