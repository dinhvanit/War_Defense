#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "CommonFunc.h"

class BaseObject
{
    public:
        BaseObject();
        ~BaseObject();
        void SetRect(const int& x, const int& y){rect_.x = x, rect_.y = y;}
        SDL_Rect GetRect() const {return rect_;}
        SDL_Texture* GetObject() const {return p_object_;}

        bool loadImg(string path, SDL_Renderer* screen);
        void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
        void Free();

    protected:
        SDL_Texture* p_object_;// bien luu tru hinh anh
        SDL_Rect rect_;// bien luu kich thuoc


    private:
};

#endif // BASEOBJECT_H
