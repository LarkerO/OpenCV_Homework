#include "inc/common.hpp"
#include "inc/work1.hpp"

int main()
{
	cv::Mat m(3,4,CV_8UC1,cv::Scalar(100));  // 创建一个3行4列，数据类型为uint8,1通道的矩阵，并初始化所有像素值为100
	std::cout << "m 行数：" << m.rows << std::endl;
	std::cout << "m 列数：" << m.cols << std::endl;
	std::cout << "m 数据类型：" << m.type() << std::endl;  // 输出数据类型 opencv定义了#define CV_8U   0
	std::cout << "m 通道数：" << m.channels() << std::endl;
	std::cout << "m 元素个数：" << m.total() << std::endl;
	std::cout << "m 元素大小：" << m.elemSize() << std::endl;  // 单位为字节
	std::cout << "尺寸：" << m.size() << std::endl;

	// work1::PictureViewer("../testphoto.png");
	// work1::FlagGenerator("../FlagImg.jpg");
	// work1::Cutting("../FlagImg.jpg");
	// work1::CoveredWithBlackAndWhite("../testphoto.png");
	// work1::Progression("../testphoto.png");
	work1::RealtimeCamera(0);

}
