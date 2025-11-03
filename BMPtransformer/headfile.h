#include <stdio.h>
#include <stdlib.h>

// 将RGB转换为灰度，然后映射到ASCII字符
char rgbToAscii(uint8_t r, uint8_t g, uint8_t b) {
    // 计算灰度值
    int gray = (int)(0.299 * r + 0.587 * g + 0.114 * b);
    
    // ASCII字符序列（从暗到亮）
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

// 输出统计信息
void printPixelStats(RGBTRIPLE** pixels, int width, int height) {
    int totalPixels = width * height;
    uint64_t totalR = 0, totalG = 0, totalB = 0;
    uint8_t minR = 255, minG = 255, minB = 255;
    uint8_t maxR = 0, maxG = 0, maxB = 0;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            RGBTRIPLE pixel = pixels[i][j];
            
            totalR += pixel.red;
            totalG += pixel.green;
            totalB += pixel.blue;
            
            if (pixel.red < minR) minR = pixel.red;
            if (pixel.green < minG) minG = pixel.green;
            if (pixel.blue < minB) minB = pixel.blue;
            
            if (pixel.red > maxR) maxR = pixel.red;
            if (pixel.green > maxG) maxG = pixel.green;
            if (pixel.blue > maxB) maxB = pixel.blue;
        }
    }
    
    printf("=== 像素统计信息 ===\n");
    printf("总像素数: %d\n", totalPixels);
    printf("平均颜色: R=%.1f, G=%.1f, B=%.1f\n", 
           (double)totalR/totalPixels, (double)totalG/totalPixels, (double)totalB/totalPixels);
    printf("颜色范围: R[%d-%d], G[%d-%d], B[%d-%d]\n", minR, maxR, minG, maxG, minB, maxB);
}


// 生成HTML文件来显示像素数据
void generateHTML(RGBTRIPLE** pixels, int width, int height, const char* outputFile) {
    FILE* html = fopen(outputFile, "w");
    if (!html) {
        printf("无法创建HTML文件\n");
        return;
    }
    
    fprintf(html, "<!DOCTYPE html>\n");
    fprintf(html, "<html>\n<head>\n<title>BMP像素数据可视化</title>\n");
    fprintf(html, "<style>\n");
    fprintf(html, ".pixel { width: 4px; height: 4px; display: inline-block; }\n");
    fprintf(html, ".container { line-height: 1px; font-size: 0; }\n");
    fprintf(html, ".pixel-info { position: fixed; background: white; border: 1px solid #000; padding: 5px; }\n");
    fprintf(html, "</style>\n</head>\n<body>\n");
    
    fprintf(html, "<h1>BMP像素数据可视化 (%dx%d)</h1>\n", width, height);
    fprintf(html, "<div class='container'>\n");
    
    // 生成像素网格（缩小显示）
    int scale = 2; // 缩放因子
    for (int i = 0; i < height; i += scale) {
        for (int j = 0; j < width; j += scale) {
            RGBTRIPLE pixel = pixels[i][j];
            fprintf(html, "<div class='pixel' style='background: rgb(%d,%d,%d)' title='(%d,%d) RGB(%d,%d,%d)'></div>\n",
                    pixel.red, pixel.green, pixel.blue, j, i, pixel.red, pixel.green, pixel.blue);
        }
        fprintf(html, "<br>\n");
    }
    
    fprintf(html, "</div>\n");
    fprintf(html, "<script>\n");
    fprintf(html, "document.addEventListener('mousemove', function(e) {\n");
    fprintf(html, "  var pixel = e.target;\n");
    fprintf(html, "  if (pixel.classList.contains('pixel')) {\n");
    fprintf(html, "    console.log(pixel.title);\n");
    fprintf(html, "  }\n");
    fprintf(html, "});\n");
    fprintf(html, "</script>\n");
    fprintf(html, "</body>\n</html>\n");
    fclose(html);
    printf("已生成HTML可视化文件: %s\n", outputFile);
}




// 生成详细的文本报告
void generateTextReport(RGBTRIPLE** pixels, int width, int height, const char* reportFile) {
    FILE* report = fopen(reportFile, "w");
    if (!report) return;
    
    fprintf(report, "BMP图像分析报告\n");
    fprintf(report, "================\n\n");
    fprintf(report, "图像尺寸: %d x %d 像素\n", width, height);
    fprintf(report, "总像素数: %d\n\n", width * height);
    
    // 颜色分布统计
    int colorDist[256] = {0}; // 简化：只统计灰度分布
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            RGBTRIPLE pixel = pixels[i][j];
            int gray = (pixel.red + pixel.green + pixel.blue) / 3;
            colorDist[gray]++;
        }
    }
    
    fprintf(report, "灰度分布:\n");
    for (int i = 0; i < 256; i += 16) {
        if (colorDist[i] > 0) {
            fprintf(report, "灰度%3d: %6d像素\n", i, colorDist[i]);
        }
    }
    
    fclose(report);
    printf("已生成文本报告: %s\n", reportFile);
}


