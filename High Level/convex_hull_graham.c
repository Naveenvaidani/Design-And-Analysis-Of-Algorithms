#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Point {
    int x, y;
} Point;

Point p0;

long long dist_sq(const Point *a, const Point *b) {
    long long dx = (long long)a->x - b->x;
    long long dy = (long long)a->y - b->y;
    return dx*dx + dy*dy;
}

int compare(const void *vp1, const void *vp2) {
    const Point *p1 = (const Point *)vp1;
    const Point *p2 = (const Point *)vp2;
    long long o = (long long)(p1->y - p0.y) * (p2->x - p0.x) - (long long)(p2->y - p0.y) * (p1->x - p0.x);
    if (o == 0) {
        return (dist_sq(&p0, p1) <= dist_sq(&p0, p2)) ? -1 : 1;
    }
    return (o > 0) ? -1 : 1; // sort in descending order of angle
}

int orientation(const Point p, const Point q, const Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; // colinear
    return (val > 0) ? 1 : 2; // 1: clockwise, 2: counterclockwise
}

void swap(Point *a, Point *b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

void convexHull(Point points[], int n) {
    if (n < 3) {
        printf("Convex hull not defined for n < 3\n");
        return;
    }

    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        if ((points[i].y < ymin) || (points[i].y == ymin && points[i].x < points[min].x)) {
            ymin = points[i].y;
            min = i;
        }
    }
    swap(&points[0], &points[min]);
    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // Remove colinear points at the end that are closer to p0
    int m = 1; // size of modified array
    for (int i = 1; i < n; i++) {
        while (i < n-1 && orientation(p0, points[i], points[i+1]) == 0)
            i++;
        points[m++] = points[i];
    }

    if (m < 3) {
        printf("Convex hull not defined after removing colinear points.\n");
        return;
    }

    Point stack[m];
    int top = 0;
    stack[0] = points[0];
    stack[1] = points[1];
    stack[2] = points[2];
    top = 2;

    for (int i = 3; i < m; i++) {
        while (top > 0 && orientation(stack[top-1], stack[top], points[i]) != 2)
            top--;
        stack[++top] = points[i];
    }

    printf("\nPoints in Convex Hull:\n");
    for (int i = 0; i <= top; i++)
        printf("(%d, %d)\n", stack[i].x, stack[i].y);
}

int main() {
    int n;
    clock_t start, end;
    double total_time;

    printf("Enter number of points: ");
    if (scanf("%d", &n) != 1) return 1;
    if (n <= 0) {
        printf("Number of points must be positive.\n");
        return 1;
    }

    Point *points = malloc(sizeof(Point) * n);
    if (!points) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter coordinates (x y):\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%d %d", &points[i].x, &points[i].y) != 2) {
            free(points);
            return 1;
        }
    }

    start = clock();
    convexHull(points, n);
    end = clock();

    free(points);

    total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nExecution Time: %f seconds\n", total_time);

    return 0;
}
