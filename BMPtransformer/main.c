#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// BMP相关结构体定义
#pragma pack(push, 1)

typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BITMAPINFOHEADER;

#pragma pack(pop)

typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} RGBTRIPLE;

// 函数声明
int readBMP(const char* filename, RGBTRIPLE*** pixels, int* width, int* height);
void freePixels(RGBTRIPLE*** pixels, int height);
void printBMPInfo(const char* filename);

// 将RGB转换为ASCII字符
char rgbToAscii(uint8_t r, uint8_t g, uint8_t b) {
    int gray = (int)(0.299 * r + 0.587 * g + 0.114 * b);
    char asciiChars[] = " .:-=+*#%@";
    int index = gray * (sizeof(asciiChars) - 2) / 255;
    return asciiChars[index];
}

// 在控制台输出ASCII艺术
void printAsciiArt(RGBTRIPLE** pixels, int width, int height, int scale) {
    printf("=== BMP ASCII艺术 ===\n");
    
    for (int i = 0; i < height; i += scale) {
        for (int j = 0; j < width; j += scale) {
            RGBTRIPLE pixel = pixels[i][j];
            printf("%c", rgbToAscii(pixel.red, pixel.green, pixel.blue));
        }
        printf("\n");
    }
}

// 输出详细的像素信息
void printPixelData(RGBTRIPLE** pixels, int width, int height, 
                   int startX, int startY, int sampleWidth, int sampleHeight) {
    printf("=== 像素数据采样（位置(%d,%d)，尺寸%dx%d） ===\n", 
           startX, startY, sampleWidth, sampleHeight);
    
    for (int i = startY; i < startY + sampleHeight && i < height; i++) {
        printf("第%4d行: ", i);
        for (int j = startX; j < startX + sampleWidth && j < width; j++) {
            RGBTRIPLE pixel = pixels[i][j];
            printf("(%3d,%3d,%3d) ", pixel.red, pixel.green, pixel.blue);
        }
        printf("\n");
    }
}

// 读取BMP文件的完整实现
int readBMP(const char* filename, RGBTRIPLE*** pixels, int* width, int* height) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("无法打开文件: %s\n", filename);
        return -1;
    }

    BITMAPFILEHEADER fileHeader;
    if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, file) != 1) {
        printf("读取文件头失败\n");
        fclose(file);
        return -1;
    }

    if (fileHeader.bfType != 0x4D42) {
        printf("不是有效的BMP文件\n");
        fclose(file);
        return -1;
    }

    BITMAPINFOHEADER infoHeader;
    if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file) != 1) {
        printf("读取信息头失败\n");
        fclose(file);
        return -1;
    }

    if (infoHeader.biBitCount != 24 || infoHeader.biCompression != 0) {
        printf("只支持24位非压缩BMP文件\n");
        fclose(file);
        return -1;
    }

    *width = infoHeader.biWidth;
    *height = abs(infoHeader.biHeight);
    int isTopDown = infoHeader.biHeight < 0;

    int padding = (4 - ((*width) * 3) % 4) % 4;

    *pixels = (RGBTRIPLE**)malloc(*height * sizeof(RGBTRIPLE*));
    for (int i = 0; i < *height; i++) {
        (*pixels)[i] = (RGBTRIPLE*)malloc(*width * sizeof(RGBTRIPLE));
    }

    fseek(file, fileHeader.bfOffBits, SEEK_SET);

    for (int i = 0; i < *height; i++) {
        int row = isTopDown ? i : (*height - 1 - i);
        
        for (int j = 0; j < *width; j++) {
            if (fread(&(*pixels)[row][j], sizeof(RGBTRIPLE), 1, file) != 1) {
                printf("读取像素数据失败\n");
                fclose(file);
                return -1;
            }
        }
        
        fseek(file, padding, SEEK_CUR);
    }

    fclose(file);
    return 0;
}

// 释放像素数据内存
void freePixels(RGBTRIPLE*** pixels, int height) {
    if (*pixels) {
        for (int i = 0; i < height; i++) {
            free((*pixels)[i]);
        }
        free(*pixels);
        *pixels = NULL;
    }
}

// 打印BMP文件信息
void printBMPInfo(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("无法打开文件: %s\n", filename);
        return;
    }

    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, file);
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

    printf("=== BMP文件信息 ===\n");
    printf("文件大小: %u 字节\n", fileHeader.bfSize);
    printf("图像宽度: %d 像素\n", infoHeader.biWidth);
    printf("图像高度: %d 像素\n", infoHeader.biHeight);
    printf("每像素位数: %d\n", infoHeader.biBitCount);
    printf("压缩类型: %u\n", infoHeader.biCompression);
    printf("图像数据大小: %u 字节\n", infoHeader.biSizeImage);

    fclose(file);
}

// 主程序
int main() {
    const char* filename = "ayachi_nene.bmp";
    
    // 先检查文件是否存在
    FILE* test = fopen(filename, "rb");
    if (!test) {
        printf("错误：找不到文件 %s\n", filename);
        printf("请确保test.bmp文件存在于当前目录\n");
        return -1;
    }
    fclose(test);
    
    // 打印文件信息
    printBMPInfo(filename);
    
    // 读取BMP文件
    RGBTRIPLE** pixels;
    int width, height;
    
    if (readBMP(filename, &pixels, &width, &height) == 0) {
        printf("成功读取BMP文件: %dx%d\n", width, height);
        
        // 输出ASCII艺术
        printf("\n1. ASCII艺术表示:\n");
        printAsciiArt(pixels, width, height, 10);
        
        // 输出部分像素数据
        printf("\n2. 左上角5x5像素数据:\n");
        printPixelData(pixels, width, height, 0, 0, 5, 5);
        
        // 释放内存
        freePixels(&pixels, height);
        printf("\n内存已释放\n");
    } else {
        printf("读取BMP文件失败\n");
    }
    
    return 0;
}
