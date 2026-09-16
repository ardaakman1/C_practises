#include <stdio.h>
// veya kapısı
int main(void) {

    float x1[4] = {0.0, 0.0, 1.0, 1.0};
    float x2[4] = {0.0, 1.0, 0.0, 1.0};
    float target[4] = {0.0, 1.0, 1.0, 1.0};

    //2. başlangıç durumu -> artık 2 girdi olduğu için iki ağırlık olucak
    float w1 = 0.50;
    float w2 = 0.50;
    float bias = 0.50;
    printf("\nFirst target: ");
    for (int i = 0; i < 4; i++) {
        printf("%.1f ", target[i]);
    }
    printf("First Weight1: %.2f\n", w1);
    printf("First Weight2: %.2f\n", w2);
    printf("First Bias: %.2f\n\n", bias);
    float learning_rate = 0.01;
    int total_ephocs = 1000;  // 4 veriyi işleyeceği için döngü arttı
    float neural_prediction;
    float error;

    printf("\n\nTRAINING STARTS\n\n");

    for (int epoch = 1; epoch <= total_ephocs; epoch++) {
        for (int i = 0; i < 4; i++) {
            neural_prediction = w1 * x1[i] + w2 * x2[i] + bias;
            error = target[i] - neural_prediction;
            w1 = w1 + (error * x1[i] * learning_rate);
            w2 = w2 + (error * x2[i] * learning_rate);
            bias = bias + (error * learning_rate);
        }
        if (epoch <= 10 || epoch % 50 == 0) {
            printf("Epoch %3d | Weight1: %.4f | Weight2: %.4f| Bias: %.4f| Estimate: %.4f | Error: %.4f\n"
                , epoch, w1, w2, bias, neural_prediction, error);
        }
    }

    printf("\n\nTRAINING ENDED\n\n");
    printf("w1: %.4f\n", w1);
    printf("w2: %.4f\n", w2);
    printf("bias: %.4f\n", bias);
    printf("Prediction: %.4f\n", neural_prediction);

    float test_x1;
    float test_x2;
    printf("Please enter the logic 1.0 or 0.0: ");
    scanf("%f %f", &test_x1, &test_x2);

    neural_prediction = w1 * test_x1 + w2 * test_x2 + bias;
    printf("Prediction Result: %.2f\n\n", neural_prediction);
    if (neural_prediction > 0.5)
    printf("Result: 1\n");
    else
    printf("Result: 0\n");
    return 0;
}