#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <libpng16/png.h>

#include "../Headers/PNGFile.h"

const char * brightnessMapComplex = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
const char * brightnessMapSimple = " .,:ilwW";

char mapBrightness(int brightness, bool simple) {
    int brightnessMapLen = simple ? strlen(brightnessMapSimple) : strlen(brightnessMapComplex);

    double input_start = 0;
    double input_end = 255;
    double output_start = 0;
    double output_end = brightnessMapLen - 1;
    double input = brightness;

    int output = output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start);

    return simple ? brightnessMapSimple[output] : brightnessMapComplex[output];
}

PNGFile::PNGFile(const char* pngPath) {
    img.filePath = (char*)pngPath;
    ReadPNGFile();
}

PNGFile::~PNGFile() {
    if (this->img.rows) {
        for (int y = 0; y < img.height; y++) {
            delete[] img.rows[y];
        }
        delete[] img.rows;
    }
}

void PNGFile::ReadPNGFile() {
    FILE *fp = fopen(this->img.filePath, "rb");

    if(!fp) abort();
        png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png) abort();
        png_infop info = png_create_info_struct(png);
    if(!info) abort();
    if(setjmp(png_jmpbuf(png))) abort();

    png_init_io(png, fp);
    png_read_info(png, info);

    this->img.width = png_get_image_width(png, info);
    this->img.height     = png_get_image_height(png, info);
    this->img.colorType = png_get_color_type(png, info);
    this->img.bitDepth  = png_get_bit_depth(png, info);

    if(this->img.bitDepth == 16)
        png_set_strip_16(png);

    if(this->img.colorType == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    if(this->img.colorType == PNG_COLOR_TYPE_GRAY && this->img.bitDepth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if(png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    if(this->img.colorType == PNG_COLOR_TYPE_RGB ||
     this->img.colorType == PNG_COLOR_TYPE_GRAY ||
     this->img.colorType == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if(this->img.colorType == PNG_COLOR_TYPE_GRAY ||
     this->img.colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);
    png_read_update_info(png, info);

    this->img.rows = new unsigned char*[this->img.height];
    for(int y = 0; y < this->img.height; y++) {
        this->img.rows[y] = new unsigned char[png_get_rowbytes(png,info)];
    }

    png_read_image(png, this->img.rows);

    fclose(fp);
}

unsigned char** PNGFile::GetPixelData() {
    return img.rows;
}

ASCIIImage PNGFile::ConvertToASCII(int rows, int columns, bool simple) {
    // Convert the image to fit in the terminal correctly
    double r = (double)columns / this->img.width;
    double conImgCols = this->img.width * r;
    double conImgLines = this->img.height / 2 * r;

    if (conImgLines > rows) {
        r = (double)rows / this->img.height;
        conImgCols = this->img.width * r * 2;
        conImgLines = this->img.height / 2 * r * 2;
    }

    // The new columns and lines that this image ratio fits in
    int iGC = (int)conImgCols;
    int iGL = (int)conImgLines;

    ASCIIImage asciiImg = ASCIIImage(iGC, iGL);

    // The number of pixels each column and line will cover
    double imgColPixels = this->img.width / (double)iGC;
    double imgLinePixels = this->img.height / (double)iGL;

    for (int y = 0; y < iGL; y++) {
        for (int x = 0; x < iGC; x++) {
            int count = 0;
            int color[4] { 0, 0, 0, 0 };
            for (int pixelY = y * imgLinePixels; pixelY < y * imgLinePixels + imgLinePixels; pixelY++) {
                unsigned char* row = this->img.rows[pixelY];
                for (int pixelX = x * imgColPixels; pixelX < x * imgColPixels + imgColPixels; pixelX++) {
                    unsigned char* px = &(row[pixelX * 4]);
                    
                    color[0] += px[0];
                    color[1] += px[1];
                    color[2] += px[2];
                    color[3] += px[4];
                    count++;
                }
            }
            
            color[0] /= count;
            color[1] /= count;
            color[2] /= count;
            color[3] /= count;

            int bright = ((0.3 * color[0]) + (0.59 * color[1]) + (0.11 * color[2]));
            asciiImg.rows[y][x] = mapBrightness(bright, simple);
        }
    }

    return asciiImg;
}
