#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPS 1e-7


int is_valid(double k, int n, double t, int s[], int v[]) {
    double total_time = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] + k <= 0) return 0; 
        total_time += s[i] / (v[i] + k);
    }
    return total_time <= t;
}

double find_k(int n, double t, int s[], int v[]) {
    double left = -10000, right = 10000; 
    while (right - left > EPS) {
        double mid = (left + right) / 2;
        if (is_valid(mid, n, t, s, v))
            right = mid;
        else
            left = mid;
    }
    return (left + right) / 2;
}

int main() {
    int n;
    double t;
    int s[1000], v[1000];
    scanf("%d %lf", &n, &t);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &s[i], &v[i]);
    }
    
    printf("%.6f\n", find_k(n, t, s, v));
    return 0;
}
