/*============================================
* Author: chenjiabo
* E-mail: chen_wangyi666@163.com
* Date: 2024-5-5
* Description: This is draw.cpp file
* Copyright (c) 2024, All rights reserved
=============================================*/
#include "sdl_texture.h"

SDLTexture::SDLTexture(const std::string& name)
{
    //Initialize
    m_texture = nullptr;
    m_surface_pixels = nullptr;
    m_width = 0;
    m_height = 0;
    m_texture_name = name;
    INFOLOG("SDLTexture construct success, texture_name={}", m_texture_name);
}

SDLTexture::~SDLTexture()
{
    //Deallocate
    free();
    INFOLOG("~SDLTexture, release resource");
}

void SDLTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    //纹理颜色调制
    /*
    DL_SetTextureColorMod 接受 Uint8 作为颜色组件的参数。Uint8 只是一个无符号的 8 位整数。这意味着它的范围从 0 到 255。
    128 大约介于 0 和 255 之间，因此当您将绿色调制为 128 时，纹理上任何像素的绿色分量都会减半。
    红色和蓝色方格不会受到影响，因为它们没有绿色，但绿色的亮度会减半，白色则会变成浅洋红色（洋红色为红色 255、绿色 0、蓝色 255）。
    颜色调制只是将一种颜色乘以整个纹理的一种方法
    */
    SDL_SetTextureColorMod(m_texture, red, green, blue);
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool SDLTexture::loadFromRenderedText(SDL_Renderer* global_renderer, TTF_Font* gFont, std::string textureText, SDL_Color textColor)
{
    ////先取消原有纹理的渲染
    free();

    //Render text surface
    /*
    使用 TTF_RenderText_Solid 加载一个曲面。函数会根据给出的字体、文本和颜色创建一个纯色曲面。如果曲面创建成功，
    就会像之前从文件加载曲面一样创建纹理。创建纹理后，可以像渲染其他纹理一样对其进行渲染。
    */
    if(gFont == nullptr)
    {
        ERRORLOG("gFont nullptr");
        return false;
    }
    // linux下加载中文
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid(gFont, textureText.c_str(), textColor);
    // SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if(textSurface == nullptr)
    {
        ERRORLOG("Unable to render text surface! SDL_ttf Error={}", TTF_GetError());
        return false;
    }
    //Create texture from surface pixels
    m_texture = SDL_CreateTextureFromSurface(global_renderer, textSurface);
    if(m_texture == nullptr)
    {
        ERRORLOG("Unable to create texture from rendered text! SDL Error={}", SDL_GetError());
        return false;
    }
    //Get image dimensions
    m_width = textSurface->w;
    m_height = textSurface->h;
    //Get rid of old surface
    SDL_FreeSurface(textSurface);
    //Return success
    return m_texture != nullptr;
}
#endif

bool SDLTexture::loadPixelsFromFile(SDL_Window * global_window, const std::string& path)
{
    //Free preexisting assets
    free();

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr)
    {
        ERRORLOG("Unable to load image={}, SDL_image Error={}", path.c_str(), IMG_GetError());
    }
    else
    {
        // DEBUGLOG("loadPixelsFromFile loadedSurface success");
        //将现有的表面复制到指定格式的新的表面 第一个参数为源表面指针，第二个参数为像素格式，第三个参数设置为0即可
        m_surface_pixels = SDL_ConvertSurfaceFormat(loadedSurface, SDL_GetWindowPixelFormat(global_window), 0);
        if(m_surface_pixels == nullptr)
        {
            ERRORLOG("Unable to convert loaded surface to display format! SDL Error={}", IMG_GetError());
        }
        else
        {
            //Get image dimensions
            m_width = m_surface_pixels->w;
            m_height = m_surface_pixels->h;
            // DEBUGLOG("loadPixelsFromFile SDL_ConvertSurfaceFormat success||m_width={}||m_height={}", m_width, m_height);
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    // INFOLOG("loadPixelsFromFile m_surface_pixels success||m_width={}||m_height={}", m_width, m_height);
    return m_surface_pixels != nullptr;
}

// 加载纹理
bool SDLTexture::loadFromPixels(SDL_Renderer* global_renderer)
{
    //Only load if pixels exist
    if(m_surface_pixels == nullptr)
    {
        ERRORLOG("No pixels loaded!");
        return false;
    }
    //Color key image
    SDL_SetColorKey(m_surface_pixels, SDL_TRUE, SDL_MapRGB(m_surface_pixels->format, 0xff, 0xff, 0xff));

    //Create texture from surface pixels
    m_texture = SDL_CreateTextureFromSurface(global_renderer, m_surface_pixels);
    if(m_texture == nullptr)
    {
        ERRORLOG("Unable to create texture from loaded pixels! SDL Error={}", SDL_GetError());
        return false;
    }
    //Get image dimensions
    m_width = m_surface_pixels->w;
    m_height = m_surface_pixels->h;

    //Get rid of old loaded surface
    SDL_FreeSurface(m_surface_pixels);
    m_surface_pixels = nullptr;

    //Return success
    return m_texture != nullptr;
}

bool SDLTexture::loadFromFile(SDL_Window * global_window, SDL_Renderer* global_renderer, const std::string& path)
{
    INFOLOG("loadFromFile||path={}", path);

    //Load pixels
    if(!loadPixelsFromFile(global_window, path))
    {
        ERRORLOG("Failed to load pixels, path={}", path.c_str());
        return false;
    }
    //Load texture from pixels
    if(!loadFromPixels(global_renderer))
    {
        ERRORLOG("Failed to texture from pixels, path={}", path.c_str());
        return false;
    }
    return m_texture != nullptr;
}

Uint32* SDLTexture::getPixels32()
{
    Uint32* pixels = nullptr;

    if(m_surface_pixels != nullptr)
    {
        // pixels =  static_cast(m_surface_pixels->pixels);
        pixels =  static_cast<Uint32*>(m_surface_pixels->pixels);
    }

    return pixels;
}

Uint32 SDLTexture::getPitch32()
{
    Uint32 pitch = 0;

    if(m_surface_pixels != nullptr)
    {
        // 间距是以字节表示的，需要的是以像素为单位的间距，而每个像素有 32 位/4 字节，因此可以通过除以每个像素的 4 字节来得到每个间距的像素数
        pitch = m_surface_pixels->pitch / 4;
    }

    return pitch;
}

void SDLTexture::free()
{
    //Free texture if it exists
    if(m_texture != nullptr)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
        m_width = 0;
        m_height = 0;
    }

    //Free surface if it exists
    if(m_surface_pixels != nullptr)
    {
        SDL_FreeSurface(m_surface_pixels);
        m_surface_pixels = nullptr;
    }
    // INFOLOG("free success");
}

// TODO 优化倍率与目标区域
void SDLTexture::render(SDL_Renderer* global_renderer, int x, int y, float multiple, SDL_Rect* clip, SDL_Rect* renderQuad, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //设置渲染区域并渲染到屏幕
    SDL_Rect quad = {x, y, m_width, m_height};

    /* 在特定位置渲染纹理时，需要指定一个目标矩形，该矩形可设置 x/y 位置和宽度/高度。在不知道原始图像尺寸的情况下，无法指定宽度/高度。
    因此，当渲染纹理时，创建一个包含位置参数和成员宽度/高度的矩形，并将此矩形传递给 SDL_RenderCopy
    */

    // 源区域不为空，目标区域为空时，设置目标区域的高宽为源区域的高宽
    if(clip != nullptr && renderQuad == nullptr)
    {
        quad.w = clip->w;
        quad.h = clip->h;
    }

     // 检查缩放倍数是否为0
    if (multiple == 0)
    {
        ERRORLOG("render||multiple is zero||please check");
    }

    if(renderQuad == nullptr)
    {
        renderQuad = &quad;
    }

    // 使用倍数来缩放加载的图像,最好用于缩小，放大图片容易造成像素点过大
    if (multiple != 1.0)
    {
        renderQuad->w = (int)renderQuad->w * multiple;
        renderQuad->h = (int)renderQuad->h * multiple;
    }
    
    /*
    在剪辑时，如果使用的是剪辑矩形的尺寸而不是纹理的尺寸，我们将把目标矩形（此处称为 renderQuad）的宽度/高度设置为剪辑矩形的尺寸。
    我们要将剪辑矩形作为源矩形传递给 SDL_RenderCopy。源矩形定义了要渲染纹理的哪一部分。当源矩形为空时，将渲染整个纹理。
    */

    //Render to screen
    // SDL_RenderCopy(global_renderer, m_texture, clip, &renderQuad);
    //Render to screen 该函数的工作原理与原始的 SDL_RenderCopy 相同，但增加了用于旋转和翻转的参数
    SDL_RenderCopyEx(global_renderer, m_texture, clip, renderQuad, angle, center, flip);
}

int SDLTexture::getWidth()
{
    return m_width;
}

int SDLTexture::getHeight()
{
    return m_height;
}

void SDLTexture::setBlendMode(SDL_BlendMode blending)
{
    //Set blending function
    // SDL_SetTextureBlendMode 允许启用混合模式
    SDL_SetTextureBlendMode(m_texture, blending);
}
        
void SDLTexture::setAlpha(Uint8 alpha)
{
    //Modulate texture alpha
    // SDL_SetTextureAlphaMod 则允许设置整个纹理的 Alpha 值
    SDL_SetTextureAlphaMod(m_texture, alpha);
}

// 获取特定位置像素
Uint32 SDLTexture::getPixel32(Uint32 x, Uint32 y)
{
    //Convert the pixels to 32 bit
    Uint32* pixels = static_cast<Uint32*>(m_surface_pixels->pixels);

    //一个二维纹理图像 像素是以一个维度存储的
    return pixels[ (y * getPitch32()) + x ];
}

//创建一个 32 位 RGBA 纹理并进行流访问。创建纹理时必须确保的一点是，纹理像素的格式要与流式传输的像素格式一致
bool SDLTexture::createBlank(SDL_Renderer* global_renderer, int width, int height)
{
    //Get rid of preexisting texture
    free();

    //Create uninitialized texture
    m_texture = SDL_CreateTexture(global_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if(m_texture == nullptr)
    {
        ERRORLOG("Unable to create streamable blank texture! SDL Error={}", SDL_GetError());
    }
    else
    {
        m_width = width;
        m_height = height;
    }

    return m_texture != nullptr;
}

bool SDLTexture::createBlank(SDL_Renderer* global_renderer, int width, int height, SDL_TextureAccess access)
{
    //Get rid of preexisting texture
    free();

    //Create uninitialized texture
    m_texture = SDL_CreateTexture(global_renderer, SDL_PIXELFORMAT_RGBA8888, access, width, height);
    if(m_texture == nullptr)
    {
        ERRORLOG("Unable to create streamable blank texture! SDL Error={}", SDL_GetError());
    }
    else
    {
        m_width = width;
        m_height = height;
    }

    return m_texture != nullptr;
}

// 对纹理进行渲染，将其设置为渲染目标
void SDLTexture::setAsRenderTarget(SDL_Renderer* global_renderer)
{
    //Make self render target
    SDL_SetRenderTarget(global_renderer, m_texture);
}

/*
SDL_LockTexture() 会抓取一个像素数据指针和纹理的间距。注意：该指针不会包含原始纹理的数据。如果创建了一个纹理，然后将其锁定，则不要指望它拥有您创建纹理时使用的原始像素数据。
用SDL_LockTexture()提供一个新的像素指针，以便向纹理发送新数据。SDL_LockTexture() 还会以字节为单位抓取纹理间距。
*/
bool SDLTexture::lockTexture()
{
    bool success = true;

    //Texture is already locked
    if(m_raw_pixels != nullptr)
    {
        ERRORLOG("Texture is already locked!");
        success = false;
    }
    //Lock texture
    else
    {   
        // 函数功能：锁定纹理，第一个参数 纹理指针。第二个参数 锁定区域，NULL 为整个纹理，第三个参数 像素，第四个参数 程度

        if(SDL_LockTexture(m_texture, nullptr, &m_raw_pixels, &m_raw_pitch) != 0)
        {
            ERRORLOG("Unable to lock texture, err={} ", SDL_GetError());
            success = false;
        }
    }

    return success;
}

// 用所需的数据完成了对像素指针的操作，解锁它就会将像素数据发送到 GPU。
bool SDLTexture::unlockTexture()
{
    bool success = true;

    //Texture is not locked
    if(m_raw_pixels == nullptr)
    {
        ERRORLOG("Texture is not locked!");
        success = false;
    }
    //Unlock texture
    else
    {
        SDL_UnlockTexture(m_texture);
        m_raw_pixels = nullptr;
        m_raw_pitch = 0;
    }

    return success;
}

// 用于将数据流中的像素复制到锁定的纹理像素指针中。该函数假定像素来自与纹理大小相同的图像
void SDLTexture::copyRawPixels32(void* pixels)
{
    //Texture is locked
    if(m_raw_pixels != nullptr)
    {
        //Copy to locked pixels
        memcpy(m_raw_pixels, pixels, m_raw_pitch * m_height);
    }
}
