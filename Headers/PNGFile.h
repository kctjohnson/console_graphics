#pragma once

struct ImageData {
    int width;
    int height;
    unsigned char colorType;
    unsigned char bitDepth;
    unsigned char** rows;
    char* filePath;
};

struct ASCIIImage {
    int width;
    int height;
    unsigned char** rows;

    ASCIIImage(int columns, int rows) {
        this->width = columns;
        this->height = rows;

        this->rows = new unsigned char*[this->height];
        for(int y = 0; y < this->height; y++) {
            this->rows[y] = new unsigned char[this->width];
        }
    }

    ~ASCIIImage() {
        if (this->rows) {
            for (int y = 0; y < this->height; y++) {
                delete[] this->rows[y];
            }
            delete[] this->rows;
        }
    }
};

class PNGFile {
private:

    void ReadPNGFile();

public:
    ImageData img;

    PNGFile(const char* pngPath);
    ~PNGFile();

    unsigned char** GetPixelData();
    ASCIIImage ConvertToASCII(int rows, int columns, bool simple);
};
