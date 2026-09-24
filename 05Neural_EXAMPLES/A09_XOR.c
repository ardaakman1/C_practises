#include <stdio.h>
#include <math.h>
#include <stdlib.h>  // rand vesrand için
#include <time.h>

// p ve q nun xor'u
// 1.nöron or kapısı
// 2.nöron nand kapısı
// 3. nöron and kapısı


float sigmoid(float z);

float random_float();

int main(void) {
    srand(time(NULL));
    float x1[4] = {0.0, 0.0, 1.0, 1.0};
    float x2[4] = {0.0, 1.0, 0.0, 1.0};
    float target[4] = {0.0, 1.0, 1.0, 0.0};

    // çok nöronlu yapılarda weight değerlerinin başlangıç değerleri aynı olamaz
    // aynı olursa eğitim boyunca hep aynı değerde kalıp yanlış değer üretirler
    float n1_w[2][2];
    float l1_b[2];
    float n2_w[2];
    float l2_b;
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            n1_w[i][j] = random_float();
        }
        l1_b[i] = random_float();
        n2_w[i] = random_float();
    }
    l2_b = random_float();


    float learning_rate = 0.1;
    float z[3];
    float prediction;
    float activasion[2];
    int total_epochs = 10000;
    for (int epoch = 1; epoch <= total_epochs; epoch++) {
        for (int i = 0; i < 4; i++) {
            z[0] = n1_w[0][0] * x1[i] + n1_w[0][1] * x2[i] + l1_b[0];
            activasion[0] = sigmoid(z[0]);
            z[1] = n1_w[1][0] * x1[i] + n1_w[1][1] * x2[i] + l1_b[1];
            activasion[1] = sigmoid(z[1]);
            z[2] = n2_w[0] * activasion[0] + n2_w[1] * activasion[1] + l2_b;
            prediction = sigmoid(z[2]);


            float error = target[i] - prediction;
            float output_delta = error * prediction * (1 - prediction);
            float hidden_delta1 = output_delta * n2_w[0] * activasion[0] * (1 - activasion[0]);
            float hidden_delta2 = output_delta * n2_w[1] * activasion[1] * (1 - activasion[1]);
            // burası eskiden hatalıydı çünkü deltaları n2 yi değiştirdikten sonra tanımlıyordum bu da hatay neden oluyordu

            n2_w[0] += output_delta * activasion[0] * learning_rate;
            n2_w[1] += output_delta * activasion[1] * learning_rate;
            l2_b += output_delta * learning_rate;
            
            n1_w[0][0] += hidden_delta1 * x1[i] * learning_rate;
            n1_w[0][1] += hidden_delta1 * x2[i] * learning_rate;
            n1_w[1][0] += hidden_delta2 * x1[i] * learning_rate;
            n1_w[1][1] += hidden_delta2 * x2[i] * learning_rate;
            l1_b[0] += hidden_delta1 * learning_rate;
            l1_b[1] += hidden_delta2 * learning_rate;

            if (epoch == 1 || epoch % 500 == 0) {
                printf("x1: %f, x2: %f\n", x1[i], x2[i]);
                printf("Prediction: %f, activasion[0]: %f, activasion[1]: %f\n", prediction, activasion[0], activasion[1]);
                if (prediction > 0.5) {
                    printf("Result: 1\n\n");
                }
                else {
                    printf("Result: 0\n\n");
                }
            }
        }
    }

    float test_x1, test_x2;
    printf("Please enter your values: ");
    scanf("%f %f", &test_x1, &test_x2);
    z[0] = n1_w[0][0] * test_x1 + n1_w[0][1] * test_x2 + l1_b[0];
    activasion[0] = sigmoid(z[0]);
    z[1] = n1_w[1][0] * test_x1 + n1_w[1][1] * test_x2 + l1_b[1];
    activasion[1] = sigmoid(z[1]);
    z[2] = n2_w[0] * activasion[0] + n2_w[1] * activasion[1] + l2_b;
    prediction = sigmoid(z[2]);
    if (prediction > 0.5) {
        printf("Result: 1\n\n");
    }
    else {
        printf("Result: 0\n\n");
    }
    return 0;
}

float sigmoid(float z) {
    return 1 / (1 + expf(-z));  // exp -> 64 bit, expf -> 32 bit
}

float random_float() {
    return ((float)rand() / RAND_MAX) * 2.0f - 1.0f;  // 0.2f 4 byte yer kaplaması için konuluyor
}