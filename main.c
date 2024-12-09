#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// ฟังก์ชันคำนวณค่า Brightness
int computeBrightness(int **array, int rows, int cols) {
  int total = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      total += array[i][j];
    }
  }
  return total / (rows * cols);
}

// ฟังก์ชันคำนวณค่า Contrast
float computeContrast(int **array, int rows, int cols, int brightness) {
  float sumSquaredDiff = 0.0;
  int totalPixels = rows * cols;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      float diff = array[i][j] - brightness;
      sumSquaredDiff += diff * diff;
    }
  }
  return sqrt(sumSquaredDiff / totalPixels);
}

// ฟังก์ชันปรับค่าพิกเซลตาม Brightness และ Contrast
void adjustPixels(int **array, int rows, int cols, int brightness,
                  float contrast) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int adjusted = (int)(contrast * (array[i][j] - brightness) + brightness);
      array[i][j] = (adjusted < 0) ? 0 : (adjusted > 255) ? 255 : adjusted;
    }
  }
}

// ฟังก์ชันแสดงค่าพิกเซลใน array
void showPixels(int **array, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%d\t", array[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int rows, cols;

  // รับค่าจำนวนแถวและคอลัมน์
  printf("Enter the number of rows: ");
  scanf("%d", &rows);
  printf("Enter the number of columns: ");
  scanf("%d", &cols);

  // จองหน่วยความจำสำหรับ array
  int **pixels = malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++) {
    pixels[i] = malloc(cols * sizeof(int));
  }

  // รับค่าพิกเซล
  printf("Enter pixel values (0-255):\n");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("Pixel[%d][%d]: ", i, j);
      scanf("%d", &pixels[i][j]);
      while (pixels[i][j] < 0 || pixels[i][j] > 255) {
        printf("Invalid input. Re-enter Pixel[%d][%d]: ", i, j);
        scanf("%d", &pixels[i][j]);
      }
    }
  }

  // คำนวณ Brightness และ Contrast
  int brightness = computeBrightness(pixels, rows, cols);
  float contrast = computeContrast(pixels, rows, cols, brightness);

  // แสดงผล Original Array
  printf("\nOriginal Array:\n");
  showPixels(pixels, rows, cols);

  // แสดงค่าที่คำนวณได้
  printf("\nCalculated Brightness: %d\n", brightness);
  printf("Calculated Contrast: %.2f\n", contrast);

  // ปรับค่าใน array
  adjustPixels(pixels, rows, cols, brightness, contrast);

  // คืนหน่วยความจำ
  for (int i = 0; i < rows; i++) {
    free(pixels[i]);
  }
  free(pixels);

  return 0;
}
