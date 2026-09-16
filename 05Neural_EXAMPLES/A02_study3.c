#include <stdio.h>

int main(void) {
    // 1.DATASET
    float sensor_value = 3.0;
    float target = 6.0;

    // 2. INITIAL IGNORANCE (Rastgele sallanmış başlangıç ağırlığı)
    float w = 0.5;

    // LEARNING RATE (Öğrenme Hızı - Hızlı ama kontrollü adımlar atması için)
    float learning_rate = 0.01;

    printf("--- STARTING NEURAL NETWORK TRAINING ---\n");
    printf("Target Output: %.2f\n\n", target);

    /* ==========================================================
       TRAINING LOOP (EĞİTİM DÖNGÜSÜ)
       İşte TensorFlow ve Keras'ın arka planda saatlerce yaptığı şey!
       Nörona "Bu işlemi 100 kere tekrar et (100 Epoch)" diyoruz.
       ========================================================== */

    int total_epochs = 150;
    for (int epoch = 1; epoch <= total_epochs; epoch++) {

        // Adım 1: Forward Pass (Mevcut ağırlıkla tahmin yap)
        float neural_regression = sensor_value * w;

        // Adım 2: Calculate Loss/Error (Hatayı bul)
        float error = target - neural_regression;

        // Adım 3: Gradient Descent / Weight Update (Hatadan ders çıkarıp ağırlığı güncelle)
        w = w + (error * sensor_value * learning_rate);

        // Her 10 Epoch'ta bir (ve ilk Epoch'ta) ekrana durumu yazdır ki gelişimi görelim
        if (epoch == 1 || epoch % 10 == 0) {
            printf("Epoch %3d | Weight: %.4f | Estimate: %.4f | Error: %.4f\n", 
                epoch, w, neural_regression, error);
        }
    }
    /* ==========================================================
       TRAINING COMPLETE (EĞİTİM BİTTİ)
       Artık nöron ideal kuralı (w = 2.0) kendi kendine bulmuş olmalı!
       ========================================================== */
    printf("\n--- TRAINING COMPLETE ---\n");
    printf("Final Learned Weight (w): %.4f\n", w);
    printf("Final Estimate for input %.1f: %.4f\n", sensor_value, (sensor_value * w));
    printf("Target: %.2f", target);

    return 0;
} 

// burada tek bilinmeyen olduğu için 6.00 değerine ulaşabildi