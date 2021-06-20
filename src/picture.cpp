#include "picture.h"

Picture::Picture(std::string pic_name)
{
    load(pic_name);
}

Picture::~Picture()
{
    close();
}

std::string Picture::getPictureHash(std::string mode)
{
    return "";
}

void Picture::load(std::string pic_name)
{

}

void Picture::close()
{
    delete picture;
}
