///////////////////////////////////////////////////////////////////////////////
//
//      TargaImage.cpp                          Author:     Stephen Chenney
//                                              Modified:   Eric McDaniel
//                                              Date:       Fall 2004
//                                              Modified:   Feng Liu
//                                              Date:       Winter 2011
//                                              Why:        Change the library file 
//      Implementation of TargaImage methods.  You must implement the image
//  modification functions.
//
///////////////////////////////////////////////////////////////////////////////

#include "Globals.h"
#include "TargaImage.h"
#include "libtarga.h"
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

using namespace std;

// constants
const int           RED             = 0;                // red channel
const int           GREEN           = 1;                // green channel
const int           BLUE            = 2;                // blue channel
const int			ALPHA			= 3;				// alpha channel
const unsigned char BACKGROUND[3]   = { 0, 0, 0 };      // background color


// Computes n choose s, efficiently
double Binomial(int n, int s)
{
    double        res;

    res = 1;
    for (int i = 1 ; i <= s ; i++)
        res = (n - i + 1) * res / i ;

    return res;
}// Binomial


///////////////////////////////////////////////////////////////////////////////
//
//      Constructor.  Initialize member variables.
//
///////////////////////////////////////////////////////////////////////////////
TargaImage::TargaImage() : width(0), height(0), data(NULL)
{}// TargaImage

///////////////////////////////////////////////////////////////////////////////
//
//      Constructor.  Initialize member variables.
//
///////////////////////////////////////////////////////////////////////////////
TargaImage::TargaImage(int w, int h) : width(w), height(h)
{
   data = new unsigned char[width * height * 4];
   ClearToBlack();
}// TargaImage



///////////////////////////////////////////////////////////////////////////////
//
//      Constructor.  Initialize member variables to values given.
//
///////////////////////////////////////////////////////////////////////////////
TargaImage::TargaImage(int w, int h, unsigned char *d)
{
    int i;

    width = w;
    height = h;
    data = new unsigned char[width * height * 4];

    for (i = 0; i < width * height * 4; i++)
	    data[i] = d[i];
}// TargaImage

///////////////////////////////////////////////////////////////////////////////
//
//      Copy Constructor.  Initialize member to that of input
//
///////////////////////////////////////////////////////////////////////////////
TargaImage::TargaImage(const TargaImage& image) 
{
   width = image.width;
   height = image.height;
   data = NULL; 
   if (image.data != NULL) {
      data = new unsigned char[width * height * 4];
      memcpy(data, image.data, sizeof(unsigned char) * width * height * 4);
   }
}


///////////////////////////////////////////////////////////////////////////////
//
//      Destructor.  Free image memory.
//
///////////////////////////////////////////////////////////////////////////////
TargaImage::~TargaImage()
{
    if (data)
        delete[] data;
}// ~TargaImage


///////////////////////////////////////////////////////////////////////////////
//
//      Converts an image to RGB form, and returns the rgb pixel data - 24 
//  bits per pixel. The returned space should be deleted when no longer 
//  required.
//
///////////////////////////////////////////////////////////////////////////////
unsigned char* TargaImage::To_RGB(void)
{
    unsigned char   *rgb = new unsigned char[width * height * 3];
    int		    i, j;

    if (! data)
	    return NULL;

    // Divide out the alpha
    for (i = 0 ; i < height ; i++)
    {
	    int in_offset = i * width * 4;
	    int out_offset = i * width * 3;

	    for (j = 0 ; j < width ; j++)
        {
	        RGBA_To_RGB(data + (in_offset + j*4), rgb + (out_offset + j*3));
	    }
    }

    return rgb;
}// TargaImage


///////////////////////////////////////////////////////////////////////////////
//
//      Save the image to a targa file. Returns 1 on success, 0 on failure.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Save_Image(const char *filename)
{
    TargaImage	*out_image = Reverse_Rows();

    if (! out_image)
	    return false;

    if (!tga_write_raw(filename, width, height, out_image->data, TGA_TRUECOLOR_32))
    {
	    cout << "TGA Save Error: %s\n", tga_error_string(tga_get_last_error());
	    return false;
    }

    delete out_image;

    return true;
}// Save_Image


///////////////////////////////////////////////////////////////////////////////
//
//      Load a targa image from a file.  Return a new TargaImage object which 
//  must be deleted by caller.  Return NULL on failure.
//
///////////////////////////////////////////////////////////////////////////////
TargaImage* TargaImage::Load_Image(char *filename)
{
    unsigned char   *temp_data;
    TargaImage	    *temp_image;
    TargaImage	    *result;
    int		        width, height;

    if (!filename)
    {
        cout << "No filename given." << endl;
        return NULL;
    }// if

    temp_data = (unsigned char*)tga_load(filename, &width, &height, TGA_TRUECOLOR_32);
    if (!temp_data)
    {
        cout << "TGA Error: %s\n", tga_error_string(tga_get_last_error());
	    width = height = 0;
	    return NULL;
    }
    temp_image = new TargaImage(width, height, temp_data);
    free(temp_data);

    result = temp_image->Reverse_Rows();

    delete temp_image;

    return result;
}// Load_Image

///////////////////////////////////////////////////////////////////////////////
//
//    helper functions
//
/////////////////////////////////////////////////////////////////////////////
inline void Set_rgba_px_black(unsigned char * px)
{
	*(uint32_t*)(px) &= 0xFF000000;
}
inline void Set_rgba_px_white(unsigned char * px)
{
	*(uint32_t*)(px) |= ~0xFF000000;
}
inline void Set_rgba_px_gray(unsigned char * px, unsigned char gray)
{
	(px)[RED]=(px)[GREEN]=(px)[BLUE]=gray;
}
inline unsigned char clampToU8(float val)
{
	if (val > 255.0f) return 0xFF;
	if (val < 0.0f) return 0;
	return (unsigned char)val;
}

///////////////////////////////////////////////////////////////////////////////
//
//      Convert image to grayscale.  Red, green, and blue channels should all 
//  contain grayscale value.  Alpha channel shoould be left unchanged.  Return
//  success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::To_Grayscale()
{
	for (int i = 0 ; i < height ; i++)
    {
		int offset = i * width * 4;
	    for (int j = 0 ; j < width ; j++)
        {
			unsigned char* pixel = data + offset + (j*4);
	        RGBA_To_RGB(pixel, pixel);
			unsigned char gray = (unsigned char)((0.299 * pixel[RED]) + (0.587 * pixel[GREEN]) + (0.114 * pixel[BLUE]));
			Set_rgba_px_gray(pixel, gray);
	    }
    }
    return true;
}// To_Grayscale


///////////////////////////////////////////////////////////////////////////////
//
//  Convert the image to an 8 bit image using uniform quantization.  Return 
//  success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Quant_Uniform()
{
	for (int i = 0 ; i < height ; i++)
    {
		int offset = i * width * 4;
	    for (int j = 0 ; j < width ; j++)
        {
			unsigned char* pixel = data + offset + (j*4);
	        RGBA_To_RGB(pixel, pixel);
			pixel[RED]   = ROUND_DOWN(pixel[RED], 32);
			pixel[GREEN] = ROUND_DOWN(pixel[GREEN], 32);
			pixel[BLUE]  = ROUND_DOWN(pixel[BLUE], 64);
	    }
    }
    return true;
}// Quant_Uniform


///////////////////////////////////////////////////////////////////////////////
//
//      Convert the image to an 8 bit image using populosity quantization.  
//  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Quant_Populosity()
{
    ClearToBlack();
    return false;
	/*
	std::vector<int> histogram;
	histogram.reserve(32*32*32);
	std::fill(histogram.begin(), histogram.end(), 0);
		//;32*32*32;
	// First covert colors to 32 levels of coor
	for (int i = 0 ; i < height ; i++)
    {
		int offset = i * width * 4;
	    for (int j = 0 ; j < width ; j++)
        {
			unsigned char rgb[3];
			unsigned char* pixel = data + offset + (j*4);
	        RGBA_To_RGB(pixel, rgb);			
			ROUND_DOWN(rgb[RED], 4);
			//rgb[RED] = ((rgb[RED]) / 4);
			//rgb[RED]*=4;
			ROUND_DOWN(rgb[GREEN], 4);
			//rgb[GREEN] = (rgb[GREEN]) / 4;
			//rgb[GREEN]*=4;
			ROUND_DOWN(rgb[BLUE], 4);
			//rgb[BLUE] = (rgb[BLUE]) / 4;
			//rgb[BLUE]*=4;
			++histogram.at( (((rgb[RED]>>2))<<10)  | (((rgb[GREEN]>>2))<<5) |(rgb[BLUE]>>2) );
	    }
    }
	std::priority_queue<histPair, vector<histPair>, std::less<histPair>> top;
	for (int i = 0; i < 32*32*32; ++i)
	{
		top.push(histPair(i, histogram[i]));
	}

	for (int i = 0; i < 256; ++i)
	{
		cout  << top.top()._val;
		top.pop();
	}
    return true;*/
}// Quant_Populosity

inline void TargaImage::Dither_Threshold(float threshold)
{	
	for (int i = 0; i < height ; i++)
	{
		int offset = i * width * 4;

		for (int j = 0; j < width; j++)
		{
			unsigned char* pixel = data + offset + (j*4);

			if (((float)pixel[RED] / 255.0f) < threshold)
			{
				Set_rgba_px_black(pixel);
			}
			else
			{
				Set_rgba_px_white(pixel);
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
//
//      Dither the image using a threshold of 1/2.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Dither_Threshold()
{
	if (To_Grayscale())
	{
		Dither_Threshold(0.5f);
		return true;
	}
	return false;
}// Dither_Threshold


///////////////////////////////////////////////////////////////////////////////
//
//      Dither image using random dithering.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Dither_Random()
{

	if (To_Grayscale())
	{
		srand((unsigned int)time(NULL));
		float brightness = 0;
		for (int i = 0 ; i < height ; i++)
		{
			int offset = i * width * 4;
			for (int j = 0 ; j < width ; j++)
			{
				unsigned char* pixel = data + offset + (j*4);

				// generate number between 0 and 2000
				// subtract 1000 to have a new number between -1000 and 1000
				// divide by 5000.0f to scale to a number between [-.2,.2]
				float newPixel = (((rand()%2001)-1000)/5000.0f);
				newPixel += ((float)pixel[RED] / 256.0f);
				
		
				Set_rgba_px_gray(pixel, (unsigned char)(newPixel*256.0f));
			}
		}
		return Dither_Bright();
	}
    return false;
}// Dither_Random


///////////////////////////////////////////////////////////////////////////////
//
//      Perform Floyd-Steinberg dithering on the image.  Return success of 
//  operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Dither_FS()
{
	const float threshold = 0.50f;
	unsigned char * nextpix;
	unsigned char gray;
	if (To_Grayscale())
	{

		float *image = new float[width * height];
		for (int h = 0; h < height; ++h)
		{
			int offset = h*width;
			for (int w = 0; w < width; ++w)
			{
				int px = offset+w;
				image[px] = data[px*4]/255.0f;
			}
		}

		for (int i = 0 ; i < height ; i++)
		{
			int offset = i * width;
			if ((i & 1) == 1)
			{
				for (int j = width-1; j >= 0; --j)
				{
					float e = image[offset + j];

					if (e < threshold)
					{
						image[offset + j] = 0;
					}
					else
					{
						image[offset + j] = 1;
						e = e-1;
					}
					
					//Propagate error
					if (j > 0)
					{
						// next
						image[offset + j-1] += (e*7.0f/16.0f);
					}

					if (i < height-1)
					{	
						image[offset + j + width] += (e*5.0f/16.0f);
						
						if (j > 0)
						{
							//
							image[offset + j-1 + width] += (e*1.0f/16.0f);
						}

						if ( j < (width - 1))
						{
							image[offset + j+1+width] += (e*3.0f/16.0f);
						}
					}
				}
			}
			else
			{
				for (int j = 0 ; j < width ; j++)
				{
					float e = image[offset + j];					

					if (e < threshold)
					{
						image[offset + j] = 0;
					}
					else
					{
						image[offset + j] = 1.0f;
						e = e-1;
					}

					//Propagate error
					if (j < width-1)
					{
						// next
						image[offset + j+1] += (e*7.0f/16.0f);
					}

					if (i < height-1)
					{	
						image[offset + j+width] += (e*5.0f/16.0f);
						
						if ( j > 0)
						{
							image[offset + j - 1 + width] += (e*3.0f/16.0f);
						}
						if (j < width-1)
						{
							image[offset + j + 1 + width] += (e*1.0f/16.0f);
						}
					}
				}
			}
		}
		
		for (int h = 0; h < height; ++h)
		{
			int offset = h*height;
			for (int w = 0; w < width; ++w)
			{
				int px = offset+w;
				//cout << image[px];
				Set_rgba_px_gray(data+(px*4), image[px] ? 0xFF : 0);
			}
			//cout << endl;
		}
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//
//      Dither the image while conserving the average brightness.  Return 
//  success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Dither_Bright()
{
    if (To_Grayscale())
	{
		float brightness = 0;
		for (int i = 0 ; i < height ; i++)
		{
			int offset = i * width * 4;
			for (int j = 0 ; j < width ; j++)
			{
				unsigned char* pixel = data + offset + (j*4);

				brightness += ((float)pixel[RED] / 255.0f);
			}
		}
		brightness /= (width*height);
		float thresh = (float)brightness;
		Dither_Threshold(thresh);
		return true;
	}
    return false;
}// Dither_Bright


///////////////////////////////////////////////////////////////////////////////
//
//      Perform clustered differing of the image.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Dither_Cluster()
{
	float thresh[4][4] = {{ 0.7500f, 0.3750f, 0.6250f, 0.2500f},
						{ 0.0625f, 1.0000f, 0.8750f, 0.4375f},
						{ 0.5000f, 0.8125f, 0.9375f, 0.1250f},
						{ 0.1875f, 0.5625f, 0.3125f, 0.6875f}};

    if (To_Grayscale())
	{
		for (int i = 0 ; i < height ; i++)
		{
			int offset = i * width * 4;
			for (int j = 0 ; j < width ; j++)
			{
				unsigned char* pixel = data + offset + (j*4);

				if (((float)pixel[RED] / 255.0f) < thresh[i&3][j&3])
				{
					Set_rgba_px_black(pixel);
				}
				else
				{
					Set_rgba_px_white(pixel);
				}
			}
		}
		return true;
	}
	return false;
}// Dither_Cluster


///////////////////////////////////////////////////////////////////////////////
//
//  Convert the image to an 8 bit image using Floyd-Steinberg dithering over
//  a uniform quantization - the same quantization as in Quant_Uniform.
//  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Dither_Color()
{
    ClearToBlack();
    return false;
}// Dither_Color


///////////////////////////////////////////////////////////////////////////////
//
//      Composite the current image over the given image.  Return success of 
//  operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Comp_Over(TargaImage* pImage)
{
    if (width != pImage->width || height != pImage->height)
    {
        cout <<  "Comp_Over: Images not the same size\n";
        return false;
    }

	for (int i = 0 ; i < height ; i++)
	{
		int offset = i * width * 4;
		for (int j = 0 ; j < width ; j++)
		{
			unsigned char* pixelF = data + offset + (j*4);
			unsigned char* pixelG= pImage->data + offset + (j*4);

			unsigned char alpha_f = pixelF[ALPHA];
			unsigned char alpha_g = pixelG[ALPHA];
			
			float F = 1;
			float G = 1- alpha_f/255.0f;
			
			pixelF[RED]   = (unsigned char) (pixelF[RED]   * F + pixelG[RED]   * G);
			pixelF[GREEN] = (unsigned char) (pixelF[GREEN] * F + pixelG[GREEN] * G);
			pixelF[BLUE]  = (unsigned char) (pixelF[BLUE]  * F + pixelG[BLUE]  * G);
			pixelF[ALPHA] = (unsigned char) (pixelF[ALPHA] * F + pixelG[ALPHA] * G); 
			
		}
	}
	return true;
}// Comp_Over


///////////////////////////////////////////////////////////////////////////////
//
//      Composite this image "in" the given image.  See lecture notes for 
//  details.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Comp_In(TargaImage* pImage)
{
    if (width != pImage->width || height != pImage->height)
    {
        cout << "Comp_In: Images not the same size\n";
        return false;
    }
	
	for (int i = 0 ; i < height ; i++)
	{
		int offset = i * width * 4;
		for (int j = 0 ; j < width ; j++)
		{
			unsigned char* pixelF = data + offset + (j*4);
			unsigned char* pixelG= pImage->data + offset + (j*4);
			
			//unsigned char alpha_f = pixelF[ALPHA];
			unsigned char alpha_g = pixelG[ALPHA];
			
			float F = alpha_g/255.0f;
			//float G = 0;
			
			pixelF[RED]   = (unsigned char)(pixelF[RED]   * F); // + pixelG[RED]   * G;
			pixelF[GREEN] = (unsigned char)(pixelF[GREEN] * F); // + pixelG[GREEN] * G;
			pixelF[BLUE]  = (unsigned char)(pixelF[BLUE]  * F); // + pixelG[BLUE]  * G;
			pixelF[ALPHA] = (unsigned char)(pixelF[ALPHA] * F); // + pixelG[ALPHA] * G; 
			
		}
	}
	return true;
}// Comp_In


///////////////////////////////////////////////////////////////////////////////
//
//      Composite this image "out" the given image.  See lecture notes for 
//  details.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Comp_Out(TargaImage* pImage)
{
    if (width != pImage->width || height != pImage->height)
    {
        cout << "Comp_Out: Images not the same size\n";
        return false;
    }
	
	for (int i = 0 ; i < height ; i++)
	{
		int offset = i * width * 4;
		for (int j = 0 ; j < width ; j++)
		{
			unsigned char* pixelF = data + offset + (j*4);
			unsigned char* pixelG= pImage->data + offset + (j*4);
			
			//unsigned char alpha_f = pixelF[ALPHA];
			unsigned char alpha_g = pixelG[ALPHA];
			
			float F = 1- alpha_g/255.0f;
			//float G = 0;
			
			pixelF[RED]   = (unsigned char) (pixelF[RED]   * F); // + pixelG[RED]   * G;
			pixelF[GREEN] = (unsigned char) (pixelF[GREEN] * F); // + pixelG[GREEN] * G;
			pixelF[BLUE]  = (unsigned char) (pixelF[BLUE]  * F); // + pixelG[BLUE]  * G;
			pixelF[ALPHA] = (unsigned char) (pixelF[ALPHA] * F); // + pixelG[ALPHA] * G; 
		}
	}
	return true;
}// Comp_Out


///////////////////////////////////////////////////////////////////////////////
//
//      Composite current image "atop" given image.  Return success of 
//  operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Comp_Atop(TargaImage* pImage)
{
    if (width != pImage->width || height != pImage->height)
    {
        cout << "Comp_Atop: Images not the same size\n";
        return false;
    }
	
	for (int i = 0 ; i < height ; i++)
	{
		int offset = i * width * 4;
		for (int j = 0 ; j < width ; j++)
		{
			unsigned char* pixelF = data + offset + (j*4);
			unsigned char* pixelG= pImage->data + offset + (j*4);
			unsigned char alpha_f = pixelF[ALPHA];
			unsigned char alpha_g = pixelG[ALPHA];
			
			float F = alpha_g/255.0f;
			float G = 1 - alpha_f/255.0f;
			
			pixelF[RED]   = (unsigned char) (pixelF[RED]   * F + pixelG[RED]   * G);
			pixelF[GREEN] = (unsigned char) (pixelF[GREEN] * F + pixelG[GREEN] * G);
			pixelF[BLUE]  = (unsigned char) (pixelF[BLUE]  * F + pixelG[BLUE]  * G);
			pixelF[ALPHA] = (unsigned char) (pixelF[ALPHA] * F + pixelG[ALPHA] * G);			
		}
	}
	return true;
}// Comp_Atop


///////////////////////////////////////////////////////////////////////////////
//
//      Composite this image with given image using exclusive or (XOR).  Return
//  success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Comp_Xor(TargaImage* pImage)
{
    if (width != pImage->width || height != pImage->height)
    {
        cout << "Comp_Xor: Images not the same size\n";
        return false;
    }

	for (int i = 0 ; i < height ; i++)
	{
		int offset = i * width * 4;
		for (int j = 0 ; j < width ; j++)
		{
			unsigned char* pixelF = data + offset + (j*4);
			unsigned char* pixelG= pImage->data + offset + (j*4);

			unsigned char alpha_f = pixelF[ALPHA];
			unsigned char alpha_g = pixelG[ALPHA];
			
			float F = 1 - alpha_g/255.0f;
			float G = 1 - alpha_f/255.0f;
			
			pixelF[RED]   = (unsigned char) (pixelF[RED]   * F + pixelG[RED]   * G);
			pixelF[GREEN] = (unsigned char) (pixelF[GREEN] * F + pixelG[GREEN] * G);
			pixelF[BLUE]  = (unsigned char) (pixelF[BLUE]  * F + pixelG[BLUE]  * G);
			pixelF[ALPHA] = (unsigned char) (pixelF[ALPHA] * F + pixelG[ALPHA] * G); 
			
		}
	}
	return true;
}// Comp_Xor


///////////////////////////////////////////////////////////////////////////////
//
//      Calculate the difference bewteen this imag and the given one.  Image 
//  dimensions must be equal.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Difference(TargaImage* pImage)
{
    if (!pImage)
        return false;

    if (width != pImage->width || height != pImage->height)
    {
        cout << "Difference: Images not the same size\n";
        return false;
    }// if

    for (int i = 0 ; i < width * height * 4 ; i += 4)
    {
        unsigned char        rgb1[3];
        unsigned char        rgb2[3];

        RGBA_To_RGB(data + i, rgb1);
        RGBA_To_RGB(pImage->data + i, rgb2);

        data[i] = abs(rgb1[0] - rgb2[0]);
        data[i+1] = abs(rgb1[1] - rgb2[1]);
        data[i+2] = abs(rgb1[2] - rgb2[2]);
        data[i+3] = 255;
    }

    return true;
}// Difference

bool TargaImage::Run_2DFilter(int filter_size, float* kernel)
{
	if ((filter_size & 1) == 0) return false;
	unsigned char * newImage = new unsigned char[width*height*4];

	float total_weight = 0.0f;
	int radius = filter_size/2;
	for (int i = 0; i < filter_size*filter_size; ++i)
	{
		total_weight += kernel[i];
	}
	
	// avoid division by 0
	if (total_weight == 0.0f) total_weight = 1.0f;

	for (int i = 0; i < height; ++i)
	{
		int offset = i * width * 4;
		for (int j = 0; j < width; ++j)
		{
			float accum[3] = {0,0,0};
			unsigned char* pixel = newImage + offset + (j*4);
			
			for (int i2 = -radius; i2 <= radius; ++i2)
			{
				for (int j2 = -radius; j2 <= radius; ++j2)
				{
					float k = kernel[j2+radius + (i2+radius)*radius];
					int w = j - j2;
					int h = i - i2;
#if REPLICATE
					if (w < 0)
					{
						w = 0;
					}
					if (w >= width)
					{
						w = (width-1);
					}
					if (h < 0)
					{
						h = 0;
					}
					if (h >= height)
					{
						h = height-1;
					}
#elif MIRROR
					if (w < 0)
					{
						w = -w;
					}
					if (w >= width)
					{
						w = 2*(width-1)-w;
					}
					if (h < 0)
					{
						h = -h;
					}
					if (h >= height)
					{
						h = -h + (height-1)*2;
					}
#endif
					unsigned char * px = (data + (w + (h*width))*4);
					accum[RED] += (px[RED]*k);
					accum[GREEN] += (px[GREEN]*k);
					accum[BLUE] += (px[BLUE]*k);
				}
			}
			pixel[RED]   = clampToU8(accum[RED]   / total_weight);
			pixel[GREEN] = clampToU8(accum[GREEN] / total_weight);
			pixel[BLUE]  = clampToU8(accum[BLUE]  / total_weight);
			pixel[ALPHA] = 0xFF;
		}
	}
	delete [] data;
	data = newImage;
	return true;
}


///////////////////////////////////////////////////////////////////////////////
//
//      Perform 5x5 box filter on this image.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Filter_Box()
{
	const int filter_size = 5;
	float kernel[25] = {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1};

	if (Run_2DFilter(filter_size, kernel))
		return true;

	ClearToBlack();
	return false;
}// Filter_Box


///////////////////////////////////////////////////////////////////////////////
//
//      Perform 5x5 Bartlett filter on this image.  Return success of 
//  operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Filter_Bartlett()
{
	const int filter_size = 5;
	float kernel[25] = {1,2,3,2,1,
						2,4,6,4,2,
						3,6,9,6,3,
						2,4,6,4,2,
						1,2,3,2,1};


	if (Run_2DFilter(filter_size, kernel))
		return true;


    ClearToBlack();
    return false;
}// Filter_Bartlett


///////////////////////////////////////////////////////////////////////////////
//
//      Perform 5x5 Gaussian filter on this image.  Return success of 
//  operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Filter_Gaussian()
{
	const int filter_size = 5;
/*	float kernel[25] = {1,4,6,4,1,
						4,16,24,16,4,
						6,24,36,24,6,
						4,16,24,16,4,
						1,4,6,4,1};*/
	float kernel[25] = {1,4,7,4,1,
						4,16,26,16,4,
						7,26,41,26,7,
						4,16,26,16,4,
						1,4,7,4,1};

	if (Run_2DFilter(filter_size, kernel))
		return true;

    ClearToBlack();
    return false;
}// Filter_Gaussian

///////////////////////////////////////////////////////////////////////////////
//
//      Perform NxN Gaussian filter on this image.  Return success of 
//  operation.
//
///////////////////////////////////////////////////////////////////////////////

bool TargaImage::Filter_Gaussian_N( unsigned int N )
{
	unsigned int filter_size = N;
	float *kernel = new float[N*N];
	for (unsigned int i = 0; i < N; ++i)
	{
		kernel[i] = kernel[i*N]
				  = kernel[N-1+i*N]
				  = kernel[(N-1)*(N)+i]
				  = Binomial(N-1, i);
	}

	for (unsigned int i = 1; i < N-1; ++i)
	{
		for (unsigned int j = 1; j < N-1; ++j)
		{
			kernel[i*N + j] = kernel[i]*kernel[j*N];
		}
	}
#if 0
	for (unsigned int i = 0; i < N; ++i)
	{
		for (unsigned int j = 0; j < N; ++j)
		{
			cout << kernel[i*N + j] << " ";
		}
		cout << endl;
	}
#endif
	if (Run_2DFilter(filter_size, kernel))
		return true;
    ClearToBlack();
   return false;
}// Filter_Gaussian_N


///////////////////////////////////////////////////////////////////////////////
//
//      Perform 5x5 edge detect (high pass) filter on this image.  Return 
//  success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Filter_Edge()
{
    ClearToBlack();
    return false;
}// Filter_Edge


///////////////////////////////////////////////////////////////////////////////
//
//      Perform a 5x5 enhancement filter to this image.  Return success of 
//  operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Filter_Enhance()
{
    ClearToBlack();
    return false;
}// Filter_Enhance


///////////////////////////////////////////////////////////////////////////////
//
//      Run simplified version of Hertzmann's painterly image filter.
//      You probably will want to use the Draw_Stroke funciton and the
//      Stroke class to help.
// Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::NPR_Paint()
{
    ClearToBlack();
    return false;
}



///////////////////////////////////////////////////////////////////////////////
//
//      Halve the dimensions of this image.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Half_Size()
{
    ClearToBlack();
    return false;
}// Half_Size


///////////////////////////////////////////////////////////////////////////////
//
//      Double the dimensions of this image.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Double_Size()
{
    ClearToBlack();
    return false;
}// Double_Size


///////////////////////////////////////////////////////////////////////////////
//
//      Scale the image dimensions by the given factor.  The given factor is 
//  assumed to be greater than one.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Resize(float scale)
{
    ClearToBlack();
    return false;
}// Resize


//////////////////////////////////////////////////////////////////////////////
//
//      Rotate the image clockwise by the given angle.  Do not resize the 
//  image.  Return success of operation.
//
///////////////////////////////////////////////////////////////////////////////
bool TargaImage::Rotate(float angleDegrees)
{
	float angleRad = angleDegrees*M_PI/180.0f;
	float sin_Theta = sin(angleRad);
	float cos_Theta = cos(angleRad);
	int a = width/2;
	int b = height/2;
	unsigned char * oldImage = data;
	data = new unsigned char[width*height*4];
    ClearToBlack();
	//ClearToAlpha();
	for (int i = 0 ; i < height ; i++)
    {
	    for (int j = 0 ; j < width ; j++)
        {
			int x_prime = a + ((j-a) * cos_Theta) - ((i-b) * sin_Theta);
			int y_prime = b + ((j-a) * sin_Theta) + ((i-b) * cos_Theta);

			if ((0 <= x_prime && x_prime < width) && (0 <= y_prime && y_prime < height))
			{
				*(uint32_t*)(data+(((y_prime * width) + x_prime)*4))
					= *(uint32_t*)(oldImage + (((i * width) + j)*4));
			}
		}
	}
	Filter_Bartlett();
	//ClearFullAlphaToBlack();
	return true;
    ClearToBlack();
    return false;
}// Rotate


//////////////////////////////////////////////////////////////////////////////
//
//      Given a single RGBA pixel return, via the second argument, the RGB
//      equivalent composited with a black background.
//
///////////////////////////////////////////////////////////////////////////////
void TargaImage::RGBA_To_RGB(unsigned char *rgba, unsigned char *rgb)
{
    const unsigned char	BACKGROUND[3] = { 0, 0, 0 };

    unsigned char  alpha = rgba[3];

    if (alpha == 0)
    {
        rgb[0] = BACKGROUND[0];
        rgb[1] = BACKGROUND[1];
        rgb[2] = BACKGROUND[2];
    }
    else
    {
	    float	alpha_scale = (float)255 / (float)alpha;
	    int	val;
	    int	i;

	    for (i = 0 ; i < 3 ; i++)
	    {
	        val = (int)floor(rgba[i] * alpha_scale);
	        if (val < 0)
		    rgb[i] = 0;
	        else if (val > 255)
		    rgb[i] = 255;
	        else
		    rgb[i] = val;
	    }
    }
}// RGA_To_RGB


///////////////////////////////////////////////////////////////////////////////
//
//      Copy this into a new image, reversing the rows as it goes. A pointer
//  to the new image is returned.
//
///////////////////////////////////////////////////////////////////////////////
TargaImage* TargaImage::Reverse_Rows(void)
{
    unsigned char   *dest = new unsigned char[width * height * 4];
    TargaImage	    *result;
    int 	        i, j;

    if (! data)
    	return NULL;

    for (i = 0 ; i < height ; i++)
    {
	    int in_offset = (height - i - 1) * width * 4;
	    int out_offset = i * width * 4;

	    for (j = 0 ; j < width ; j++)
        {
	        dest[out_offset + j * 4] = data[in_offset + j * 4];
	        dest[out_offset + j * 4 + 1] = data[in_offset + j * 4 + 1];
	        dest[out_offset + j * 4 + 2] = data[in_offset + j * 4 + 2];
	        dest[out_offset + j * 4 + 3] = data[in_offset + j * 4 + 3];
        }
    }

    result = new TargaImage(width, height, dest);
    delete[] dest;
    return result;
}// Reverse_Rows


///////////////////////////////////////////////////////////////////////////////
//
//      Clear the image to all black.
//
///////////////////////////////////////////////////////////////////////////////
void TargaImage::ClearToBlack()
{
    memset(data, 0, width * height * 4);
}// ClearToBlack


///////////////////////////////////////////////////////////////////////////////
//
//      Helper function for the painterly filter; paint a stroke at
// the given location
//
///////////////////////////////////////////////////////////////////////////////
void TargaImage::Paint_Stroke(const Stroke& s) {
   int radius_squared = (int)s.radius * (int)s.radius;
   for (int x_off = -((int)s.radius); x_off <= (int)s.radius; x_off++) {
      for (int y_off = -((int)s.radius); y_off <= (int)s.radius; y_off++) {
         int x_loc = (int)s.x + x_off;
         int y_loc = (int)s.y + y_off;
         // are we inside the circle, and inside the image?
         if ((x_loc >= 0 && x_loc < width && y_loc >= 0 && y_loc < height)) {
            int dist_squared = x_off * x_off + y_off * y_off;
            if (dist_squared <= radius_squared) {
               data[(y_loc * width + x_loc) * 4 + 0] = s.r;
               data[(y_loc * width + x_loc) * 4 + 1] = s.g;
               data[(y_loc * width + x_loc) * 4 + 2] = s.b;
               data[(y_loc * width + x_loc) * 4 + 3] = s.a;
            } else if (dist_squared == radius_squared + 1) {
               data[(y_loc * width + x_loc) * 4 + 0] = 
                  (data[(y_loc * width + x_loc) * 4 + 0] + s.r) / 2;
               data[(y_loc * width + x_loc) * 4 + 1] = 
                  (data[(y_loc * width + x_loc) * 4 + 1] + s.g) / 2;
               data[(y_loc * width + x_loc) * 4 + 2] = 
                  (data[(y_loc * width + x_loc) * 4 + 2] + s.b) / 2;
               data[(y_loc * width + x_loc) * 4 + 3] = 
                  (data[(y_loc * width + x_loc) * 4 + 3] + s.a) / 2;
            }
         }
      }
   }
}


///////////////////////////////////////////////////////////////////////////////
//
//      Build a Stroke
//
///////////////////////////////////////////////////////////////////////////////
Stroke::Stroke() {}

///////////////////////////////////////////////////////////////////////////////
//
//      Build a Stroke
//
///////////////////////////////////////////////////////////////////////////////
Stroke::Stroke(unsigned int iradius, unsigned int ix, unsigned int iy,
               unsigned char ir, unsigned char ig, unsigned char ib, unsigned char ia) :
   radius(iradius),x(ix),y(iy),r(ir),g(ig),b(ib),a(ia)
{
}

