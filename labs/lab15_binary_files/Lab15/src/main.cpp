#include <iostream>

// Lab 15

void collor_filter(){
    FILE *fin = fopen("input.bmp", "rb");
    if (!fin) {
        printf("Error: Cannot open %s\n", "input.bmp");
        return;
    }
    FILE *fout = fopen("otput.bmp", "wb");

    unsigned char header[54];
    if (fread(header, sizeof(unsigned char), 54, fin) != 54) {
        printf("Error: Invalid BMP file.\n");
        fclose(fin); fclose(fout); return;
    }

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int abs_height = std::abs(height);

    short bitCount = *(short*)&header[28];
    if (bitCount != 24) {
        printf("Error! Only 24-bit BMP supported \n");
        fclose(fin); fclose(fout); return;
    }

    fwrite(header, sizeof(unsigned char), 54, fout);

    int x1, x2, y1, y2;
    float coeff_R, coeff_G, coeff_B;
    printf("Image size: %d x %d\nEnter coordinates (x1,y1) and (x2,y2): ", width, height);
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    printf("Enter how you want to change Red Green Blue (coef): ");
    scanf("%f %f %f", &coeff_R, &coeff_G, &coeff_B);

    int padding = (4 - (width * 3) % 4) % 4;

    int row_size = width * 3 + padding;
    unsigned char *row = new unsigned char[row_size];

    for (int y = 0; y < abs_height; y++){
        fread(row, sizeof(unsigned char), row_size, fin);

        int actual_y = (height > 0) ? (abs_height - 1 - y) : y;
        if (actual_y >= y1 && actual_y <= y2) {
            for (int x = 0; x < width; x++){
                if (x >= x1 && x <= x2){
                    int b_idx = x * 3, g_idx = x * 3 + 1, r_idx = x * 3 + 2;
                    
                    float new_b = row[b_idx] * coeff_B;
                    float new_g = row[g_idx] * coeff_G;
                    float new_r = row[r_idx] * coeff_R;
                }
            }
        }
        fwrite(row, sizeof(unsigned char), row_size, fout);
    }
    /*int c;
    while ((c = fgetc(fin)) != EOF) {
        fputc(c, fout);
    }*/
    delete[] row;
    fclose(fin); fclose(fout);
}
int main() {
    collor_filter();
    return 0;
}
