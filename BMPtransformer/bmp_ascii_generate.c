#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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
void printUsage(const char* programName);

// ASCII艺术相关函数
char rgbToAscii(uint8_t r, uint8_t g, uint8_t b);
void printAsciiArt(RGBTRIPLE** pixels, int width, int height, int scale);
void printAsciiArtAdjusted(RGBTRIPLE** pixels, int width, int height, int scaleX, int scaleY);
void printAsciiArtAuto(RGBTRIPLE** pixels, int width, int height, int maxWidth);
void printAsciiArtHighQuality(RGBTRIPLE** pixels, int width, int height);
void printPixelData(RGBTRIPLE** pixels, int width, int height, int startX, int startY, int sampleWidth, int sampleHeight);
void generateHTML(RGBTRIPLE** pixels, int width, int height, const char* outputFile);
void generateTextReport(RGBTRIPLE** pixels, int width, int height, const char* reportFile);

// 显示使用说明
void printUsage(const char* programName) {
    printf("BMP文件分析工具\n");
    printf("用法: %s [选项] <输入文件.bmp>\n\n", programName);
    printf("选项:\n");
    printf("  -h, --help             显示此帮助信息\n");
    printf("  -i, --info             显示BMP文件信息\n");
    printf("  -a, --ascii            显示ASCII艺术（基础版）\n");
    printf("  -A, --ascii-adjusted   显示比例调整的ASCII艺术\n");
    printf("  -H, --ascii-high       显示高质量ASCII艺术\n");
    printf("  -p, --pixels [x,y,w,h] 显示指定区域的像素数据\n");
    printf("                         例如: -p 0,0,10,10\n");
    //printf("  -o, --output <文件>    生成HTML可视化文件\n");
    printf("  -r, --report <文件>    生成文本报告\n");
    printf("  -s, --scale <数值>     设置ASCII艺术采样比例（默认: 2）\n");
    printf("  -w, --width <数值>     设置ASCII艺术最大宽度（默认: 100）\n");
    printf("\n示例:\n");
    printf("  %s image.bmp -i -a           # 显示信息和ASCII艺术\n", programName);
    printf("  %s image.bmp -A -w 80        # 调整宽度的ASCII艺术\n", programName);
    printf("  %s image.bmp -p 0,0,5,5      # 显示左上角5x5像素\n", programName);
    //printf("  %s image.bmp -o output.html  # 生成HTML可视化\n", programName);
    //printf("  %s image.bmp --all           # 执行所有操作\n", programName);
}

// 解析像素区域参数
int parsePixelArea(const char* arg, int* x, int* y, int* w, int* h) {
    return sscanf(arg, "%d,%d,%d,%d", x, y, w, h) == 4;
}

// 检查是否包含某个参数
int hasArg(int argc, char* argv[], const char* shortOpt, const char* longOpt) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], shortOpt) == 0 || strcmp(argv[i], longOpt) == 0) {
            return 1;
        }
    }
    return 0;
}

// 获取参数值
const char* getArgValue(int argc, char* argv[], const char* shortOpt, const char* longOpt) {
    for (int i = 1; i < argc - 1; i++) {
        if (strcmp(argv[i], shortOpt) == 0 || strcmp(argv[i], longOpt) == 0) {
            return argv[i + 1];
        }
    }
    return NULL;
}

// 原有的函数实现（保持不变）
char rgbToAscii(uint8_t r, uint8_t g, uint8_t b) {
    int gray = (int)(0.299 * r + 0.587 * g + 0.114 * b);
    char asciiChars[] = " .:-=+*#%@";
    int index = gray * (sizeof(asciiChars) - 2) / 255;
    return asciiChars[index];
}

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

void printAsciiArtAdjusted(RGBTRIPLE** pixels, int width, int height, int scaleX, int scaleY) {
    printf("=== BMP ASCII艺术 (比例调整) ===\n");
    for (int i = 0; i < height; i += scaleY) {
        for (int j = 0; j < width; j += scaleX) {
            RGBTRIPLE pixel = pixels[i][j];
            printf("%c", rgbToAscii(pixel.red, pixel.green, pixel.blue));
        }
        printf("\n");
    }
}

void printAsciiArtAuto(RGBTRIPLE** pixels, int width, int height, int maxWidth) {
    printf("=== BMP ASCII艺术 (自动调整) ===\n");
    int scaleX = width / maxWidth;
    int scaleY = scaleX * 2;
    if (scaleX < 1) scaleX = 1;
    if (scaleY < 1) scaleY = 2;
    printf("使用比例: 水平每%d像素采样，垂直每%d像素采样\n", scaleX, scaleY);
    for (int i = 0; i < height; i += scaleY) {
        for (int j = 0; j < width; j += scaleX) {
            RGBTRIPLE pixel = pixels[i][j];
            printf("%c", rgbToAscii(pixel.red, pixel.green, pixel.blue));
        }
        printf("\n");
    }
}

char rgbToAsciiEnhanced(uint8_t r, uint8_t g, uint8_t b) {
    int gray = (int)(0.299 * r + 0.587 * g + 0.114 * b);
    char asciiChars[] = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
    int numChars = sizeof(asciiChars) - 2;
    int index = gray * numChars / 255;
    return asciiChars[index];
}

void printAsciiArtHighQuality(RGBTRIPLE** pixels, int width, int height) {
    printf("=== BMP ASCII艺术 (高质量版) ===\n");
    int targetWidth = 120;
    int scaleX = (width + targetWidth - 1) / targetWidth;
    int scaleY = scaleX * 2;
    if (scaleX < 1) scaleX = 1;
    if (scaleY < 1) scaleY = 2;
    for (int i = 0; i < height; i += scaleY) {
        for (int j = 0; j < width; j += scaleX) {
            RGBTRIPLE pixel = pixels[i][j];
            printf("%c", rgbToAsciiEnhanced(pixel.red, pixel.green, pixel.blue));
        }
        printf("\n");
    }
}

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
/*
void generateHTML(RGBTRIPLE** pixels, int width, int height, const char* outputFile) {
    FILE* html = fopen(outputFile, "w");
    if (!html) {
        printf("无法创建HTML文件: %s\n", outputFile);
        return;
    }
    fprintf(html, "<!DOCTYPE html>\n<html>\n<head>\n<title>BMP像素数据可视化</title>\n");
    fprintf(html, "<style>.pixel { width: 2px; height: 2px; display: inline-block; }</style>\n");
    fprintf(html, "</head>\n<body>\n<h1>BMP像素数据可视化 (%dx%d)</h1>\n<div>\n", width, height);
    
    int scale = 2;
    for (int i = 0; i < height; i += scale) {
        for (int j = 0; j < width; j += scale) {
            RGBTRIPLE pixel = pixels[i][j];
            fprintf(html, "<div class='pixel' style='background: rgb(%d,%d,%d)'></div>\n",
                    pixel.red, pixel.green, pixel.blue);
        }
        fprintf(html, "<br>\n");
    }
    fprintf(html, "</div>\n</body>\n</html>\n");
    fclose(html);
    printf("已生成HTML可视化文件: %s\n", outputFile);
}
*/
void generateTextReport(RGBTRIPLE** pixels, int width, int height, const char* reportFile) {
    FILE* report = fopen(reportFile, "w");
    if (!report) {
        printf("无法创建报告文件: %s\n", reportFile);
        return;
    }
    fprintf(report, "BMP图像分析报告\n");
    fprintf(report, "================\n\n");
    fprintf(report, "图像尺寸: %d x %d 像素\n", width, height);
    fprintf(report, "总像素数: %d\n\n", width * height);
    fclose(report);
    printf("已生成文本报告: %s\n", reportFile);
}

// BMP读取
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

void freePixels(RGBTRIPLE*** pixels, int height) {
    if (*pixels) {
        for (int i = 0; i < height; i++) {
            free((*pixels)[i]);
        }
        free(*pixels);
        *pixels = NULL;
    }
}

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

// 主函数（支持命令行参数）
int main(int argc, char* argv[]) {
    if (argc < 2 || hasArg(argc, argv, "-h", "--help")) {
        printUsage(argv[0]);
        return 0;
    }

    // 获取输入文件名（第一个非选项参数）
    const char* filename = NULL;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            filename = argv[i];
            break;
        }
    }

    if (!filename) {
        printf("错误：未指定输入文件\n\n");
        printUsage(argv[0]);
        return -1;
    }

    // 检查文件是否存在
    FILE* test = fopen(filename, "rb");
    if (!test) {
        printf("错误：找不到文件 %s\n", filename);
        return -1;
    }
    fclose(test);

    // 读取BMP文件
    RGBTRIPLE** pixels;
    int width, height;
    
    if (readBMP(filename, &pixels, &width, &height) != 0) {
        printf("读取BMP文件失败\n");
        return -1;
    }

    printf("成功读取BMP文件: %s (%dx%d)\n", filename, width, height);

    // 处理各种选项
    int hasOperation = 0;

    // 显示文件信息
    if (hasArg(argc, argv, "-i", "--info")) {
        printBMPInfo(filename);
        hasOperation = 1;
    }

    // 获取参数值
    const char* scaleStr = getArgValue(argc, argv, "-s", "--scale");
    int scale = scaleStr ? atoi(scaleStr) : 2;
    
    const char* widthStr = getArgValue(argc, argv, "-w", "--width");
    int maxWidth = widthStr ? atoi(widthStr) : 100;

    // ASCII艺术显示
    if (hasArg(argc, argv, "-a", "--ascii")) {
        printAsciiArt(pixels, width, height, scale);
        hasOperation = 1;
    }

    if (hasArg(argc, argv, "-A", "--ascii-adjusted")) {
        printAsciiArtAdjusted(pixels, width, height, scale, scale * 2);
        hasOperation = 1;
    }

    if (hasArg(argc, argv, "-H", "--ascii-high")) {
        printAsciiArtHighQuality(pixels, width, height);
        hasOperation = 1;
    }

    // 像素数据显示
    const char* pixelArea = getArgValue(argc, argv, "-p", "--pixels");
    if (pixelArea) {
        int x, y, w, h;
        if (parsePixelArea(pixelArea, &x, &y, &w, &h)) {
            printPixelData(pixels, width, height, x, y, w, h);
            hasOperation = 1;
        } else {
            printf("错误：无效的像素区域格式，使用 x,y,width,height 格式\n");
        }
    }

    // 输出文件生成
    /*
    const char* htmlOutput = getArgValue(argc, argv, "-o", "--output");
    if (htmlOutput) {
        generateHTML(pixels, width, height, htmlOutput);
        hasOperation = 1;
    }
    */

    const char* reportOutput = getArgValue(argc, argv, "-r", "--report");
    if (reportOutput) {
        generateTextReport(pixels, width, height, reportOutput);
        hasOperation = 1;
    }

    // 如果没有指定任何操作，显示默认信息
    if (!hasOperation) {
        printf("未指定操作选项，使用 -h 查看帮助信息\n");
        printBMPInfo(filename);
        printf("\n使用示例:\n");
        printf("  %s %s -a -p 0,0,5,5\n", argv[0], filename);
    }

    // 清理内存
    freePixels(&pixels, height);
    printf("\n处理完成，内存已释放\n");

    return 0;
}
