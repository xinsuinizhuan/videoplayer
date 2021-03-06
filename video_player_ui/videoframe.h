#ifndef _VIDEOFRAME_H
#define _VIDEOFRAME_H
#include <memory>
#include <iostream>
#include "video_player_core.h"

#ifdef FRAME_RGB
#define FRAME_LENGTH(x, y) x*y*3
#else
#define FRAME_LENGTH(x, y) x*y*3/2
#endif
class _video_frame_
{
public:
    _video_frame_(unsigned char* buffer, int w, int h)
        :framebuffer(nullptr)
    {
        this->w = w;
        this->h = h;
        auto len = FRAME_LENGTH(w,h);
        framebuffer = new unsigned char[len];
        memcpy(framebuffer, buffer, len);
    }

    ~_video_frame_()
    {
        if(framebuffer)
        {
            delete[] framebuffer;
            framebuffer = nullptr;
        }
    }

    unsigned char* Y()
    {
        return framebuffer;
    }

    unsigned char* U()
    {
        return framebuffer + w * h;
    }

    unsigned char* V()
    {
        return framebuffer + w * h * 5 / 4;
    }

    int size_y()
    {
        return w * h;
    }

    int size_u()
    {
        return w * h / 4;
    }

    int size_v()
    {
        return w * h / 4;
    }

    unsigned char* data(int index, int& width, int& height){
        unsigned char* data = nullptr;
        switch (index)
        {
        case 0:
            width = w;
            height = h;
            data = Y();
        break;
        case 1:
            width = w / 2;
            height = h / 2;
            data = U();
        break;
        case 2:
            width = w / 2;
            height = h / 2;
            data = V();
        break;
        }

        return data;
    }
    int w;
    int h;
    unsigned char* framebuffer;
};

typedef std::shared_ptr<_video_frame_> _VideoFramePtr;

#endif // _VIDEOFRAME_H
