#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func(double x);
int writeOutput(double a, int N, double delta, char group_name[40], char student_name[40]);
void writeBinary(char group_name[40], char student_name[40]);

int main()
{

    double a, b, delta;
    int N;
    char group_name[40];
    char student_name[40];

    FILE *input = fopen("input.txt", "r");

    if (input == NULL)
    {
        printf("Error opening file");
        return 1;
    }
    else
    {
        fscanf(input, "%lf %lf %d %lf %s %s", &a, &b, &N, &delta, group_name, student_name);
    }

    writeOutput(a, N, delta, group_name, student_name);
    writeBinary(group_name, student_name);

    printf("\nProgram finished successfully!\n\n");

    return 0;
}

double func(double x)
{
    return 0.25 * pow(x - 25, 2) + (pow(x + 25, 3)) / 100 + 1;
}

int writeOutput(double a, int N, double delta, char group_name[40], char student_name[40])
{

    FILE *output = fopen("output.txt", "w");
    FILE *binary = fopen("binary.bin", "w+b");

    fwrite(&N, sizeof(int), 1, binary);
    fprintf(output, "N\tx\t\tf(x)\n\n");

    for (int i = 0; i < N; i++)
    {

        fprintf(output, "%d\t%.2f\t%.2f\n", i, a, func(a));

        fwrite(&a, sizeof(double), 1, binary);
        double c = func(a);
        fwrite(&c, sizeof(double), 1, binary);
        a += delta;
    }

    fprintf(output, "\n%s, %s", group_name, student_name);
    fclose(output);
    fclose(binary);

    return 1;
}

void writeBinary(char group_name[40], char student_name[40])
{

    int N = 0;
    double x = 0;
    double f = 0;
    FILE *binary = fopen("binary.bin", "r+b");

    if (binary == NULL)
    {
        printf("Error opening file");
        return 0;
    }

    printf("+-------+------------+------------+\n");
    printf("|   N   |     X      |      F     |\n");
    printf("+-------+------------+------------+\n");

    fread(&N, sizeof(int), 1, binary);

    for (int i = 0; i < N; i++)
    {
        
        fread(&x, sizeof(double), 1, binary);
        fread(&f, sizeof(double), 1, binary);

        printf("|%7d|%12.2f|%12.2f|\n", i, x, f);
        printf("+-------+------------+------------+\n");
    }

    printf("|       %s, %s       |", group_name, student_name);
    printf("\n+-------+------------+------------+\n");

    fclose(binary);
}