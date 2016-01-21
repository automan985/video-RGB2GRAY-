// VideoCut.cpp : �������̨Ӧ�ó������ڵ㡣
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

// ��ʼ����������λ��
int g_slider_position = 0;
CvCapture* g_capture = NULL;
// ����ص��������ڲ��Ž��ȵĿ��� 
void onTrackbarSlide( int pos )
{
	cvSetCaptureProperty( g_capture, CV_CAP_PROP_POS_FRAMES, pos );
}

int main(int argc, char** argv )
{
    // ��׽��Ƶ�ļ�
	string VideoPath = "src.avi";
	g_capture = cvCreateFileCapture( VideoPath.c_str());
    // ��ȡ����ʾ��Ƶ�ļ���֡��
	int frames = (int) cvGetCaptureProperty( g_capture, CV_CAP_PROP_FRAME_COUNT );
	cout << "֡��frames = " << frames << endl;
    // ����������
	if( frames != 0 )
		cvCreateTrackbar("Position","Video Test",&g_slider_position,frames,onTrackbarSlide);
    // ��ȡ��Ƶ�ļ���Ϣ
	double fps = cvGetCaptureProperty( g_capture, CV_CAP_PROP_FPS );
	cout << "֡��fps = " << fps << endl;
	CvSize size = cvSize((int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_WIDTH),(int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_HEIGHT));
	 // ���� VideoWriter 
	char out[] = "dst.avi";
	CvVideoWriter* wrVideo = cvCreateVideoWriter(out,CV_FOURCC('X','V','I','D'), fps, size,1);
	 int frs = 0;
    // ��ʼ���Ų�������Ƶ
    IplImage* frame;
	IplImage* gray = cvCreateImage(size, IPL_DEPTH_8U, 1);
	frame = cvQueryFrame( g_capture );
		if( !frame ) return 0;
		// �������Ŵ��� flags = 0���ڴ�С�ɵ�
	cvNamedWindow( "Video Test", 0 );
	cvNamedWindow( "Video Gray", 0 );
	while(frame)
	{
		// ��ȡ����ʾԴ�ļ���֡����
		cvCvtColor(frame ,gray, CV_RGB2GRAY);
		cvShowImage( "Video Test", frame );
		// ���棺����ǰ֡д�뵽Ŀ����Ƶ�ļ�
		cvShowImage( "Video Gray", gray );
		cvWriteFrame( wrVideo, frame );
		// ������ ESC �������˳�����
		char c = cvWaitKey(33);
		if( c == 27 ) break;
		frame = cvQueryFrame( g_capture );
    }
	// �ͷ��ڴ棬�رմ���
	cvReleaseImage(&gray);
	cvReleaseCapture( &g_capture );
	cvReleaseVideoWriter( &wrVideo );
    cvDestroyWindow( "Video Test" );
	cvDestroyWindow( "Video Gray" );
	return 0;
} 