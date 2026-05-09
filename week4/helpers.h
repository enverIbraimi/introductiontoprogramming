#include <stdint.h>

// Represents a pixel
typedef struct
{
    uint8_t  rgbtBlue;
    uint8_t  rgbtGreen;
    uint8_t  rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;