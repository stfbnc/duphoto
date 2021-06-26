#include "picture.h"

Picture::Picture(std::string pic_name)
{
    load(pic_name);
}

Picture::~Picture() {}

int64_t Picture::getPictureHash(hashType hash_type)
{
    int64_t hash = error_hash;
    
    switch(hash_type)
    {
    case AHASH:
        hash = ahash();
        break;
    case PHASH:
        hash = phash();
        break;
    case DHASH:
        hash = dhash();
        break;
    default:
        break;
    }

    return hash;
}

void Picture::load(std::string pic_name)
{
    struct stat buffer;   
    if(stat (pic_name.c_str(), &buffer) == 0)
    {
        picture = cv::imread(pic_name);
    }
}

int64_t Picture::ahash()
{
    if((picture.rows == 0) || (picture.cols == 0))
    {
        return error_hash;
    }
    
    try
    {
        // get only gray channel
        cv::Mat gray_pic;
        cv::cvtColor(picture, gray_pic, cv::COLOR_BGR2GRAY);
        
        // resize to 8x8
        cv::Mat resized_pic;
        cv::resize(gray_pic, resized_pic, cv::Size(8, 8));
        
        // get mean pixels value
        double pic_mean = cv::mean(resized_pic)[0];

        // set pixels to 0 or 1 if above or below the mean
        int64_t hash = 0;
        for(int i = 0; i < resized_pic.rows; ++i)
        {
            for(int j = 0; j < resized_pic.cols; ++j)
            {
                hash |= (int64_t)(resized_pic.at<uchar>(i, j) < pic_mean) << (i * resized_pic.cols + j);
            }
        }

        return hash;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return error_hash;
    }
}

int64_t Picture::phash()
{
    return error_hash;
}

int64_t Picture::dhash()
{
    return error_hash;
}

int64_t Picture::getErrorHashValue()
{
    return error_hash;
}
