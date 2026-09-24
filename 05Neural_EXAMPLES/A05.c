#include <stdio.h>

int main(void) {
    float w1 = 0.5;
    float w2 = 0.5;
    float bias = 0.5;
    float learning_rate = 0.01;
    printf("First w1: %.2f\n", w1);
    printf("First w2: %.2f\n", w2);
    printf("First bias: %.2f\n\n", bias);

    float x1[4] = {0.1, 0.1, 0.9, 0.9};  // pot
    float x2[4] = {0.4, 0.9, 0.4, 0.9};  // ses sensörü veya koyarsam başka bir pot
    float target[4] = {0.0, 1.0, 1.0, 1.0};
    float prediction;
    printf("\n\nTRAINING STARTS\n\n");
    int total_epcohs = 1000;
    for (int epoch = 1; epoch <= total_epcohs; epoch++) {
        for (int i = 0; i < 4; i++) {
            prediction = w1 * x1[i] + w2 * x2[i] + bias;
            float error = target[i] - prediction;
            w1 = w1 + (error * learning_rate * x1[i]);
            w2 = w2 + (error * learning_rate * x2[i]);
            bias = bias + (error *learning_rate);
            if (epoch == 1 || epoch % 50 == 0) {
                printf("x1[%d]: %.1f | x2[%d]: %.1f |Current Prediction: %.4f\n", i, x1[i], i, x2[i], prediction);
                printf("w1: %.4f, w2: %.4f\n\n", w1, w2);
            }

            if (epoch == 1 || epoch % 50 == 0) {
                if (prediction > 0.5)
                printf("x1[%d]: %.1f | x2[%d]: %.1f | Result: 1\n", i, x1[i], i, x2[i]);
                else
                printf("x1[%d]: %.1f | x2[%d]: %.1f | Result: 0\n", i, x1[i], i, x2[i]);
            }
        }
    }

    printf("\n\nTRAINING ENDED\n\n");
    printf("FINAL w1: %f\n", w1);
    printf("FINAL w2: %f\n", w2);
    printf("FINAL bias: %f\n\n", bias);

    printf("Please enter the values: ");
    float target_x1, target_x2;
    scanf("%f %f", &target_x1, &target_x2);
    prediction = w1 * target_x1 + w2 * target_x2 + bias;
    if (prediction > 0.5)
        printf("LED ON!\n\n");
    else
        printf("LED OFF\n\n");
    
    return 0;
}