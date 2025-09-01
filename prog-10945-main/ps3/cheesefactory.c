#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793

int main() {
    int M, S;
    scanf("%d %d", &M, &S);

    double total_volume = 1000000.0; 

    double total_hole_volume = 0.0;
    for (int i = 0; i < M; i++) {
        double R, X, Y, Z;
        scanf("%lf %lf %lf %lf", &R, &X, &Y, &Z);

        double hole_volume = (4.0 / 3.0) * PI * pow(R, 3);
        total_hole_volume += hole_volume;
    }

    double cheese_volume = total_volume - total_hole_volume;

    double slice_thickness = 100.0 / S;

    double target_volume_per_slice = cheese_volume / S;

    double accumulated_volume = 0.0;
    for (int i = 0; i < S; i++) {
        accumulated_volume += target_volume_per_slice;
        printf("%.7f\n", slice_thickness);
    }

    return 0;
}
