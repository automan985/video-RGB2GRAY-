// VideoCut.cpp : 定义控制台应用程序的入口点。
//
#pragma once
#include "stdafx.h"
#include <iostream>
#include <cxcore.h>
#include <highgui.h>
#include "cxcore.h"
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
using namespace cv;
using namespace std;

// 初始化进度条的位置
int g_slider_position = 0;
CvCapture* g_capture = NULL;
// 定义回调函数用于播放进度的控制 
void onTrackbarSlide( int pos )
{
	cvSetCaptureProperty( g_capture, CV_CAP_PROP_POS_FRAMES, pos );
}

int main(int argc, char** argv )
{
    // 捕捉视频文件
	string VideoPath = "src.avi";
	g_capture = cvCreateFileCapture( VideoPath.c_str());
    // 读取、显示视频文件的帧数
	int frames = (int) cvGetCaptureProperty( g_capture, CV_CAP_PROP_FRAME_COUNT );
	cout << "帧数frames = " << frames << endl;
    // 建立进度条
	if( frames != 0 )
		cvCreateTrackbar("Position","Video Test",&g_slider_position,frames,onTrackbarSlide);
    // 读取视频文件信息
	double fps = cvGetCaptureProperty( g_capture, CV_CAP_PROP_FPS );
	cout << "帧率fps = " << fps << endl;
	CvSize size = cvSize((int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_WIDTH),(int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_HEIGHT));
	 // 创建 VideoWriter 
	char out[] = "dst.avi";
	CvVideoWriter* wrVideo = cvCreateVideoWriter(out,CV_FOURCC('X','V','I','D'), fps, size,1);
	 int frs = 0;
    // 开始播放并保存视频
    IplImage* frame;
	IplImage* gray = cvCreateImage(size, IPL_DEPTH_8U, 1);
	frame = cvQueryFrame( g_capture );
		if( !frame ) return 0;
		// 建立播放窗口 flags = 0窗口大小可调
	cvNamedWindow( "Video Test", 0 );
	cvNamedWindow( "Video Gray", 0 );
	while(frame)
	{
		// 获取、显示源文件的帧画面
		cvCvtColor(frame ,gray, CV_RGB2GRAY);
		cvShowImage( "Video Test", frame );
		// 保存：将当前帧写入到目标视频文件
		cvShowImage( "Video Gray", gray );
		cvWriteFrame( wrVideo, frame );
		// 若按下 ESC 键，则退出程序
		char c = cvWaitKey(33);
		if( c == 27 ) break;
		frame = cvQueryFrame( g_capture );
    }
	// 释放内存，关闭窗口
	cvReleaseImage(&gray);
	cvReleaseCapture( &g_capture );
	cvReleaseVideoWriter( &wrVideo );
    cvDestroyWindow( "Video Test" );
	cvDestroyWindow( "Video Gray" );
	return 0;
} 
