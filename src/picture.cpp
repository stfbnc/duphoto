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
    if((picture.rows == 0) || (picture.cols == 0))
    {
        return error_hash;
    }
    
    try
    {
        // get only gray channel
        cv::Mat gray_pic;
        cv::cvtColor(picture, gray_pic, cv::COLOR_BGR2GRAY);
        
        // resize to 32x32
        cv::Mat resized_pic;
        cv::resize(gray_pic, resized_pic, cv::Size(32, 32));

        // dct
        cv::Mat dct_pic;
        cv::dct(resized_pic, dct_pic);

        // get 8x8 top left of dct
        cv::Mat dct_pic_resized = dct_pic(cv::Range(0, 7), cv::Range(0, 7));

        // get mean pixels value
        int pic_mean_cnt = 0;
        for(int i = 0; i < dct_pic_resized.rows; ++i)
        {
            for(int j = 0; j < dct_pic_resized.cols; ++j)
            {
                if((i != 0) || (j != 0))
                {
                    pic_mean_cnt += dct_pic_resized.at<uchar>(i, j);
                }
            }
        }
        double pic_mean = pic_mean_cnt / static_cast<double>(dct_pic_resized.rows * dct_pic_resized.cols - 1);

        // set pixels to 0 or 1 if above or below the mean
        int64_t hash = 0;
        for(int i = 0; i < dct_pic_resized.rows; ++i)
        {
            for(int j = 0; j < dct_pic_resized.cols; ++j)
            {
                hash |= (int64_t)(dct_pic_resized.at<uchar>(i, j) < pic_mean) << (i * dct_pic_resized.cols + j);
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

int64_t Picture::dhash()
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
        
        // resize to 8x9
        cv::Mat resized_pic;
        cv::resize(gray_pic, resized_pic, cv::Size(8, 9));

        // difference between adjacent row pixels
        cv::Mat sub_pic_1 = resized_pic(cv::Range(0, resized_pic.rows - 1), cv::Range(0, resized_pic.cols - 2));
        cv::Mat sub_pic_2 = resized_pic(cv::Range(0, resized_pic.rows - 1), cv::Range(1, resized_pic.cols - 1));

        // set pixels to 0 or 1 if brighter or darker than the next pixel
        int64_t hash = 0;
        for(int i = 0; i < sub_pic_1.rows; ++i)
        {
            for(int j = 0; j < sub_pic_1.cols; ++j)
            {
                hash |= (int64_t)(sub_pic_1.at<uchar>(i, j) < sub_pic_2.at<uchar>(i, j)) << (i * sub_pic_1.cols + j);
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

int64_t Picture::getErrorHashValue()
{
    return error_hash;
}
