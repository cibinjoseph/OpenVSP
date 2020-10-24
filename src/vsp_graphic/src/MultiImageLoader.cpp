#include <MultiImageLoader.h>
#include "OpenGLHeaders.h"

#include "stb_image.h"

namespace VSPGraphic
{
MultiImageLoader::MultiImageLoader() : ImageLoader()
{
}
MultiImageLoader::~MultiImageLoader()
{
}

ImageData MultiImageLoader::load( std::string fileName )
{
    ImageData iData;

    int w, h, bpp;
    unsigned char *data = stbi_load( fileName.c_str(), &w, &h, &bpp, 0 );

    if ( data == NULL )
    {
        iData.valid = false;
        return iData;
    }

    iData.valid = true;
    iData.width = w;
    iData.height = h;

    if ( bpp == 4 )
    {
        iData.type = GL_RGBA;
    }
    else
    {
        iData.type = GL_RGB;
    }

    // Flip data top to bottom.
    iData.data = new unsigned char[ iData.width * iData.height * bpp];
    int scanLen = bpp * iData.width;

    for ( int i = 0 ; i < (int)iData.height; i++ )
    {
        unsigned char* srcLine = &data[ i * scanLen ];
        unsigned char* dstLine = &iData.data[ (iData.height - i - 1) * scanLen ];
        memcpy(  dstLine, srcLine, scanLen );
    }

    stbi_image_free(data);

    return iData;
}

bool MultiImageLoader::acceptExt( std::string e )
{
    return ( e == ".jpg" ) ||
           ( e == ".png" ) ||
           ( e == ".tga" ) ||
           ( e == ".bmp" ) ||
           ( e == ".gif" );
}
}
