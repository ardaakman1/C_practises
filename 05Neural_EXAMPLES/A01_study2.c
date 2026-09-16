#include <stdio.h>
// bu program nöronun ne kadar hatalı sonuçlar ürettiğini görmek için
int main(void) {
    // 1. GERÇEK DÜNYA VERİSİ (Dataset)
    float sensor_value = 3.0;
    float target = 6.0;  // beklediğimiz sonuç

    // 2. NÖRONUN BAŞLANGIÇ CEHALETİ
    // Nöron kuralı (x2 yapmayı) bilmiyor. Ağırlığa tamamen rastgele bir sayı sallıyoruz.
    float w = 0.5;

    // 3. İLERİ BESLEME (Tahmin Yapma - Forward Pass)
    float neural_regression = sensor_value * w;

    // YENİ: ÖĞRENME HIZI (Fren Mekanizması)
    float learning_rate = 0.01;

    // 4. HATA HESAPLAMA (Loss / Error)
    // Ne kadar yanıldık? (Hedef ile Tahmin arasındaki fark)
    float error = target - neural_regression;
    // SONUÇLARI GÖRELİM
    printf("\n\n---RESULTS BEFORE THE TRAINING---\n");
    printf("Target: %.2f\n", target);
    printf("Neural regression (estimate): %.2f\n", neural_regression);
    printf("Error (difference): %.2f\n", error);

    /* ==========================================================
       YENİ EKLENEN KISIM: EĞİTİM (TRAINING / WEIGHT UPDATE)
       Nöron hatasına ve girdisine bakarak ağırlığını güncelliyor.
       ========================================================== */
       
    // Gradyan İnişi Formülü (w = w + (Hata * Girdi * Öğrenme Hızı))
    w = w + (error * sensor_value * learning_rate);
    
    printf("\n--- LEARNING PROCESS ---\n");
    printf("Neuron has updated its weight!\n");
    printf("New Weight (w): %f\n", w);

    /* ==========================================================
       TEST: NÖRON BİR ŞEY ÖĞRENMİŞ Mİ?
       Aynı veriyi yeni ağırlıkla tekrar deniyoruz.
       ========================================================== */
       
    float neural_regression_2 = sensor_value * w;
    float error_2 = target - neural_regression_2;

    printf("\n--- RESULTS AFTER 1 STEP OF TRAINING ---\n");
    printf("Estimate 2: %.2f\n", neural_regression_2);
    printf("Error 2: %.2f\n", error_2);
    return 0;
}