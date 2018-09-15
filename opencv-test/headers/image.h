#include "../headers/common.h"

/*******************************
 * Class which contains images - GPU or CPU buffers
 * ****************************/
ALGOS_CV_2D_BEGIN

enum class DataDevice : uint32_t
{
    GPU,
    CPU
};

class Image {


/* Public interface */

    ~Image();

    Image() = delete;

    Image(DataDevice dataDevice, size_t width, size_t height, uint32_t type /* opencv Types : CV_8U, CV8UC3, CV_32F...*/, cv::cuda::Stream& st = cv::cuda::Stream::Null());
    
    /**
     * @details
     * A fuction which returns the step size of the buffer
     * 
     * @return
    */
    uint32_t GetStepSize();
    
    uint32_t GetWidth();
    
    uint32_t GetHeight();
    
    cv::Size GetSize();

    uint32_t OnGpu();

/* Private variables and buffers */
private:
    typedef struct Buffer
    {
        /**
         * Indicator which signals which buffer is the most updated - the one on the GPU device or the on on the RAM (CPU) 
         * */
        enum UpdatedBuffer
        {
            CPU = 0,
            GPU
        }m_updatedBuffer;

        cv::cuda::Stream m_st = cv::cuda::Stream::Null();
        cv::cuda::GpuMat m_gpuImage; 
	    cv::cuda::HostMem m_cpuImage;

        /**
         * @details
         * updates the relevant buffer such that both buffers holds the same data
         * */
        inline uint32_t update(uint32_t& OnGpu)
        {
            switch (m_updatedBuffer)
            {
                case CPU:
                    m_gpuImage.download(m_cpuImage);
                    return true;
                case GPU:
                    m_gpuImage.upload(m_cpuImage);
                    return true;
                default:
                    break;
            }
        }

        template<typename T>
        inline void init(T inImage, DataDevice& dataDevice, cv::cuda::Stream& st = cv::cuda::Stream::Null())
        {

            m_st = st;

            switch (dataDevice)
            {
                case DataDevice::CPU :
                    m_cpuImage(inImage);
                    m_updatedBuffer = UpdatedBuffer::CPU;
                    break;
                case DataDevice::GPU :
                    inImage.copyTo(m_gpuImage, st);
                    m_updatedBuffer = UpdatedBuffer::GPU;     
            }
        }

    }m_buffer;

    uint32_t m_width = 0, m_height = 0;




    

};

ALGOS_CV_2D_END