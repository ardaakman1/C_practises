#include <stdio.h>

int main(void) {
    float sensor_value = 3.0;
    float target = 6.0;

    float w = 0.50;  // başlangıç weight i
    float b = 0.50;  // başlangıç bias i
    float learning_rate = 0.01;
    printf("---START---\n");
    printf("Target: %.2f\n", target);
    printf("First Weight: %.2f\n", w);
    printf("First Bias: %.2f\n\n", b);

    int total_epochs = 100;
    for (int epoch = 1; epoch <= total_epochs; epoch++) {
        float neural_prediction = sensor_value * w + b;  // regression olayın adı preditcion adı daha doğru
        float error = target - neural_prediction;
        w = w + (error * sensor_value * learning_rate);
        b = b + (error * learning_rate);

        printf("Epoch %3d | Weight: %.4f | Bias: %.4f| Estimate: %.4f | Error: %.4f\n", 
            epoch, w, b, neural_prediction, error);
    }
    printf("\n--- TRAINING COMPLETE ---\n");
    printf("Final Learned Weight (w): %.4f\n", w);
    printf("Final Learned Bias (w): %.4f\n", b);
    printf("Final Estimate for input %.1f: %.4f\n", sensor_value, (sensor_value * w + b));
    printf("Target: %.2f\n", target);

    return 0;
}

// burda asla tam olması gereken değer ulaşamıyor çünkü iki bilinmeyen ve tek denklem var