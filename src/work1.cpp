//
// Created by larker on 2026/11/8.
//
#include "../inc/common.hpp"
#include "../inc/work1.hpp"

namespace work1 {
	int PictureViewer(const cv::String ImgPath) {
		/**
		1．从零创建一个图片查看程序
			新建一个 C++ 项目，使用 CMake 编译，实现：
			• 读取一张彩色图片并显示。
			• 输出图片的宽、高、通道数、像素总数、每个像素占用的字节数。
			• 将图片转为灰度图，再输出同样的信息。
		**/

		cv::Mat gray;
		cv::Mat img = cv::imread(ImgPath); // 当前为BGR格式
		if (img.empty()) {
			std::cout << "读取图片失败" << std::endl;
			return 0;
		}
		cv::imshow("PictureViewer | Press q to exit.", img);
		cv::waitKey(0);
		std::cout << "[Work1] 高：" << img.rows << std::endl;
		std::cout << "[Work1] 宽：" << img.cols << std::endl;
		std::cout << "[Work1] 通道数：" << img.channels() << std::endl;
		std::cout << "[Work1] 元素个数：" << img.total() << std::endl;
		std::cout << "[Work1] 元素大小：" << img.elemSize() << std::endl;
		cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
		cout << "[Work1] 灰度后: " << endl;
		std::cout << "[Work1] 高：" << gray.rows << std::endl;
		std::cout << "[Work1] 宽：" << gray.cols << std::endl;
		std::cout << "[Work1] 通道数：" << gray.channels() << std::endl;
		std::cout << "[Work1] 元素个数：" << gray.total() << std::endl;
		std::cout << "[Work1] 元素大小：" << gray.elemSize() << std::endl;
		return 1;
	}

	void FlagGenerator(string SaveFileName) {
		/**
		2．自己生成一张三色旗
			不读取外部图片，创建一张宽 600、高 300 的彩色图像：
			• 左侧 200 列为蓝色，中间 200 列为绿色，右侧 200 列为红色。
			• 将图像坐标 (250, 80) 处的像素改为白色。
			• 打印修改前、修改后的该像素 BGR 值。
			• 显示结果。
			要求： 三个色块用 ROI 和 setTo() 完成，指定像素用 at<>() 修改。
		**/

		cv::Mat flagimg(300, 600, CV_8UC3, cv::Scalar(0, 0, 0));

		cv::Rect rect_blue(0, 0, 200, 300);
		cv::Rect rect_green(200, 0, 200, 300);
		cv::Rect rect_red(400, 0, 200, 300);

		cv::Mat roi_blue = flagimg(rect_blue);
		roi_blue.setTo(cv::Scalar(255, 0, 0));

		cv::Mat roi_green = flagimg(rect_green);
		roi_green.setTo(cv::Scalar(0, 255, 0));

		cv::Mat roi_red = flagimg(rect_red);
		roi_red.setTo(cv::Scalar(0, 0, 255));

		cout << "[Work1](FlagGenerator) The BGR Code before change : " << flagimg.at<cv::Vec3b>(80, 250) << endl;
		flagimg.at<cv::Vec3b>(80, 250) = cv::Vec3b(0, 0, 0);
		cout << "[Work1](FlagGenerator) The BGR Code after change : " << flagimg.at<cv::Vec3b>(80, 250) << endl;

		while (1) {
			cv::imshow("FlagGenerator | Press q to exit.", flagimg);
			if (cv::waitKey(1) == 'q')
				break;
		}

		cv::imwrite(SaveFileName, flagimg);
	}

	int Cutting(cv::String ImgPath) {
		/**
		3. 裁剪图片，验证共享和复制
			读取一张宽、高均不小于 300 的图片，选取左上角为 (50, 80)、宽 120、高 100 的区域，分别进行两次独立实验：
			• 实验 A：直接取 ROI，将其填充为黑色，观察原图。
			• 实验 B：重新读取原图，对同一区域使用 clone()，再把裁剪结果填充为黑色，观察原图。
		**/

		cv::Mat imgA = cv::imread(ImgPath);
		cv::Mat imgB = cv::imread(ImgPath);
		if (imgA.empty() || imgB.empty()) {
			std::cout << "[Work1](Cutting) 读取图片失败" << std::endl;
			return 0;
		}

		cv::Rect rect_A(50, 80, 120, 100);
		cv::Rect rect_B(50, 80, 120, 100);

		cv::Mat roi_A = imgA(rect_A);
		roi_A.setTo(cv::Scalar(0, 0, 0));
		while (1) {
			cv::imshow("Cutting (1) | Press q to exit.", imgA);
			if (cv::waitKey(1) == 'q')
				break;
		}
		cv::Mat roi_B = imgB(rect_B).clone();
		roi_B.setTo(cv::Scalar(0, 0, 0));
		while (1) {
			cv::imshow("Cutting (2) | Press q to exit.", imgB);
			if (cv::waitKey(1) == 'q')
				break;
		}
		return 1;
	}

	int CoveredWithBlackAndWhite(cv::String ImgPath) {
		/*
		4．实现一个简单的黑白化程序
			读取图片，转成灰度图，再进行二值化：
			• 分别使用阈值 60、120、180，显示三种结果。
			• 自己写双层循环实现阈值为 120 的二值化，规则为：大于 120 设为 255，否则设为 0。
			• 统计二值图中白色像素的数量及其占总像素的百分比。
		*/
		cv::Mat gray, gray60, gray120, gray180;
		cv::Mat img = cv::imread(ImgPath);
		if (img.empty()) {
			std::cout << "[Work1](Covered) 读取图片失败" << std::endl;
			return 0;
		}
		cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
		cv::threshold(gray, gray60, 60, 255, cv::THRESH_BINARY);
		cv::threshold(gray, gray120, 120, 255, cv::THRESH_BINARY);
		cv::threshold(gray, gray180, 180, 255, cv::THRESH_BINARY);

		cv::imshow("gray60", gray60);
		cv::imshow("gray120", gray120);
		cv::imshow("gray180", gray180);

		cv::Mat gray120New;
		cv::cvtColor(img, gray120New, cv::COLOR_BGR2GRAY);
		// 遍历灰度图的所有像素
		for (int i = 0; i < gray120New.rows; i++) {
			uint8_t *ptr = gray120New.ptr<uint8_t>(i);
			for (int j = 0; j < gray.cols; j++) {
				uint8_t &g = ptr[j];
				if (g > 120) {
					g = 255;
				} else {
					g = 0;
				}
			}
		}
		cv::imshow("gray120New", gray120New);

		int WhiteCount = 0, BlackCount = 0, ErrorCount = 0;
		// 遍历灰度图的所有像素
		for (int i = 0; i < gray120New.rows; i++) {
			uint8_t *ptr = gray120New.ptr<uint8_t>(i);
			for (int j = 0; j < gray120New.cols; j++) {
				uint8_t &g = ptr[j];
				if (g == 255) {
					WhiteCount++;
				} else if (g == 0) {
					BlackCount++;
				} else {
					ErrorCount++;
				}
			}
		}
		cout << "[Work1](Covered) White Count : " << WhiteCount << " | " << fixed << setprecision(3) << (
					static_cast<float>(BlackCount) / static_cast<float>(gray120New.cols * gray120New.rows)) * 100.000 << "%"
				<<
				std::endl;

		cv::waitKey(0);

		return 1;
	}

	int Progression(cv::String ImgPath) {
		// 		5．给同一张图做处理对比
		//			使用同一张有纹理、文字或物体轮廓的图片，完成：
		//			• 分别进行均值滤波、高斯滤波、中值滤波，窗口大小均为 3。
		//			• 对原始灰度图，以及高斯滤波后的灰度图，分别做 Canny 边缘检测。
		//			• 将 Canny 阈值分别设为 (50, 100) 和 (100, 200)，观察变化。

		cv::Mat img = cv::imread(ImgPath), avg_img, gauss_img, median_img;
		cv::Mat gray, gray2, canny_edge, canny_edge2;
		if (img.empty()) {
			std::cout << "[Work1](Progression) 读取图片失败" << std::endl;
			return 0;
		}

		cv::blur(img, avg_img, cv::Size(3, 3)); // 均值滤波
		cv::GaussianBlur(img, gauss_img, cv::Size(3, 3), 0); // 高斯滤波
		cv::medianBlur(img, median_img, 3); // 中值滤波

		// cv::imshow("avg_img", avg_img);
		// cv::imshow("gauss_img", gauss_img);
		// cv::imshow("median_img", median_img);
		// cv::waitKey(0);

		cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
		cv::cvtColor(gauss_img, gray2, cv::COLOR_BGR2GRAY);

		cv::Canny(gray, canny_edge, 100, 200);
		cv::Canny(gray2, canny_edge2, 100, 200);

		cv::imshow("canny_edge without gauss", canny_edge);
		cv::imshow("canny_edge with gauss", canny_edge2);
		cv::waitKey(0);

		return 1;
	}

	int RealtimeCamera(int CameraID) {
		// 6．做一个摄像头实时处理小程序
		// 打开摄像头，默认显示原始画面，通过按键切换处理模式：
		// 	• 1：原始彩色画面。
		// 	• 2：灰度画面。
		// 	• 3：二值化画面。
		// 	• 4：Canny 边缘画面。
		// 	• q：退出程序。

		int mode = 0, thresh = 60;
		cv::VideoCapture cap(CameraID); // VideoCapture用于捕获视频流
		cv::Mat frame, gray, endgray, canny_edge;
		while (1) {
			cap >> frame;
			if (frame.empty()) {
				return 0;
				break;
			}
			if (mode == 0) {
				cv::imshow("frame", frame);
			} else if (mode == 1) {
				cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
				cv::imshow("frame", gray);
			} else if (mode == 2) {
				cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
				cv::threshold(gray, endgray, thresh, 255, cv::THRESH_BINARY);
				cv::imshow("frame", endgray);
			} else if (mode == 3) {
				cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
				cv::Canny(gray, canny_edge, 100, 200);
				cv::imshow("frame", canny_edge);
			}

			int key = cv::waitKey(1) & 0xFF;

			if (key == 'q') {
				break;
			} else if (key == '1') {
				mode = 0;
			} else if (key == '2') {
				mode = 1;
			} else if (key == '+') {
				if (thresh < 255) {
					thresh++;
				}
			} else if (key == '-') {
				if (thresh > 0) {
					thresh--;
				}
			} else if (key == '3') {
				mode = 2;
			} else if (key == '4') {
				mode = 3;
			}

		}
		return 1;
	}
}
