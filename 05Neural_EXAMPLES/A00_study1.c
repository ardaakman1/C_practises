#include <stdio.h>

/* =====================================================================
   BÖLÜM 1: YAPAY ZEKA MODELİNİN "ÖĞRENMİŞ" OLDUĞU BİLGİLER (SİHİRLİ SAYILAR)
   Normalde bu sayıları Python'da saatlerce süren "Eğitim (Training)" 
   sonucunda buluruz. TinyML'de bu sayıları bulduktan sonra C koduna 
   sabit (const) olarak gömeriz.
====================================================================== */

// 3 sensörümüz (Örn: X, Y, Z eksenleri) olduğu için 3 adet Ağırlık (Weight) var.
const float w1 = 0.85;   // X ekseni verisi kararımızda %85 etkili
const float w2 = -0.40;  // Y ekseni ters orantılı bir etkiye sahip
const float w3 =  1.10;  // Z ekseni kararımızı en çok tetikleyen veri

// Nöronumuzun doğuştan gelen eşik değeri (Bias)
const float bias = -0.50;

/* =====================================================================
   BÖLÜM 2: AKTİVASYON FONKSİYONU (DİYOT)
   Gelen verideki "negatif/yararsız" kısımları bloke eder.
====================================================================== */

float relu_activation(float z) {  // ReLU rectified linear unit
    if (z < 0.0)
    return 0.0; // Negatifse sinyal geçemez (Ateşleme yok)
    else
    return z;  // Pozitifse sinyal aynen geçer
}

/* =====================================================================
   BÖLÜM 3: NÖRONUN KENDİSİ (İLERİ BESLEME / FORWARD PASS)
   Sensör verilerini alır, matematiği uygular ve kararı verir.
====================================================================== */

float single_neuron_compute(float x1, float x2, float x3) {
    // Adım A: Toplam formülü: z = (x1*w1) + (x2*w2) + (x3*w3) + b
    float z = (x1 * w1) + (x2 * w2) + (x3 * w3) + bias;

    // Adım B: Çıkan sonucu Aktivasyon Fonksiyonundan (ReLU) geçir
    float output = relu_activation(z);
    return output; // nöronun nihai kararı
}

/* =====================================================================
   BÖLÜM 4: ANA PROGRAM (TEST AŞAMASI)
====================================================================== */

int main(void) {
    // Diyelim ki UART'tan veya ADC'den anlık olarak şu 3 sensör verisi geldi:
    float sensor_x = 2.0;
    float sensor_y = 1.5;
    float sensor_z = 0.5;

    // Sensör verilerini YZ Nöronumuza gönderiyoruz
    float regression_result = single_neuron_compute(sensor_x, sensor_y, sensor_z);
    // Sonucu ekrana yazdırıyoruz
    printf("---AI INFERENCE---\n");  // çıkarımı
    printf("Sensor Data: X=%.1f, Y=%.1f, Z=%.1f\n", sensor_x, sensor_y, sensor_z);
    printf("Neuron's result: %f\n", regression_result);

    if (regression_result > 0.0)
    printf("Decision: run the engine (impuls has created)\n");
    else
    printf("Wait: neuron did not create impuls\n");

    return 0;
}