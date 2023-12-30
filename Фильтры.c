#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define SIGNAL_LENGTH 100 // Длина сигнала
#define FILTER_WINDOW_4 4  // Размер окна для скользящего среднего фильтра 1
#define FILTER_WINDOW_5 5  // Размер окна для скользящего среднего фильтра 2
#define MEDIAN_WINDOW_3 3  // Размер окна для медианного фильтра 1
#define MEDIAN_WINDOW_8 8  // Размер окна для медианного фильтра 2

double moving_average(double signal[], int window_size, int index)
{
    double sum = 0;
    int i;
    for (i = index; i < index + window_size; i++) {
        sum += signal[i];
    }
    return sum / window_size;
}

double median_filter(double signal[], int window_size, int index) {
    double window[window_size];
    int i;
    for (i = 0; i < window_size; i++) {
        window[i] = signal[index + i];
    }
    // Сортировка окна
    for (i = 0; i < window_size - 1; i++) {
        for (int j = 0; j < window_size - i - 1; j++) {
            if (window[j] > window[j + 1]) {
                double temp = window[j];
                window[j] = window[j + 1];
                window[j + 1] = temp;
            }
        }
    }
    // Возвращаем средний элемент (медиану)
    return window[window_size / 2];
}

// Генерируем случайный шум
double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

int main()
{
    double signal[SIGNAL_LENGTH];
    double signal_noise[SIGNAL_LENGTH];
    double signal_noise_after_moving_average_filter_4[SIGNAL_LENGTH];
    double signal_noise_after_moving_average_filter_5[SIGNAL_LENGTH];
    double signal_noise_after_median_filter_3[SIGNAL_LENGTH];
    double signal_noise_after_median_filter_8[SIGNAL_LENGTH];
    int i;
    
    // Генерируем исходный сигнал синуса 
    for (i = 0; i < SIGNAL_LENGTH; i++) {
        signal[i] = sin(2 * M_PI * i / SIGNAL_LENGTH);
    }
    
    // Генерируем сигнал с шумом
    for (i = 0; i < SIGNAL_LENGTH; i++) {
        signal_noise[i] = signal[i] + randfrom(-0.3, 0.3);
    }
    
    // Сигнал после скользящего среднего фильтра с окном 4
    for (i = 0; i < SIGNAL_LENGTH - FILTER_WINDOW_4 + 1; i++) {
        signal_noise_after_moving_average_filter_4[i] = moving_average(signal_noise, FILTER_WINDOW_4, i);
    }
    
    // Сигнал после скользящего среднего фильтра с окном 5
    for (i = 0; i < SIGNAL_LENGTH - FILTER_WINDOW_5 + 1; i++) {
        signal_noise_after_moving_average_filter_5[i] = moving_average(signal_noise, FILTER_WINDOW_5, i);
    }

    // Сигнал после скользящего медианного фильтра с окном 3
    for (i = 0; i < SIGNAL_LENGTH - MEDIAN_WINDOW_3 + 1; i++) {
        signal_noise_after_median_filter_3[i] = median_filter(signal_noise, MEDIAN_WINDOW_3, i);
    }
 
    // Сигнал после скользящего медианного фильтра с окном 8
    for (i = 0; i < SIGNAL_LENGTH - MEDIAN_WINDOW_8 + 1; i++) {
        signal_noise_after_median_filter_8[i] = median_filter(signal_noise, MEDIAN_WINDOW_8, i);
    } 
    
    // Скачивание файлов
    FILE *fp = fopen("Сигналы.txt", "w");
    char t[SIGNAL_LENGTH];
    for (i = 0; i < SIGNAL_LENGTH; i++) {
        sprintf (t, "%f", signal[i]);
        fputs(t, fp);
        fputs(" ", fp);
    } fputs("\n", fp);
    for (i = 0; i < SIGNAL_LENGTH; i++) {
        sprintf (t, "%f", signal_noise[i]);
        fputs(t, fp);
        fputs(" ", fp);
    } fputs("\n", fp);   
    for (i = 0; i < SIGNAL_LENGTH; i++) {
        sprintf (t, "%f", signal_noise_after_moving_average_filter_4[i]);
        fputs(t, fp);
        fputs(" ", fp);
    } fputs("\n", fp);
    for (i = 0; i < SIGNAL_LENGTH; i++) {
        sprintf (t, "%f", signal_noise_after_moving_average_filter_5[i]);
        fputs(t, fp);
        fputs(" ", fp);
    } fputs("\n", fp);
    for (i = 0; i < SIGNAL_LENGTH; i++) {
        sprintf (t, "%f", signal_noise_after_median_filter_3[i]);
        fputs(t, fp);
        fputs(" ", fp);
    } fputs("\n", fp);
    for (i = 0; i < SIGNAL_LENGTH; i++) {
        sprintf (t, "%f", signal_noise_after_median_filter_8[i]);
        fputs(t, fp);
        fputs(" ", fp);
    }
    fclose(fp);
    
    return 0;
}