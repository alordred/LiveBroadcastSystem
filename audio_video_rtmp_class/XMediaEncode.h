#pragma once
#include "XData.h"
class  AVCodecContext;
enum XSampleFMT
{
	X_S16 = 1,
	X_FLAPT = 8
};
//enum AVSampleFormat {
//	AV_SAMPLE_FMT_NONE = -1,
//	AV_SAMPLE_FMT_U8,          ///< unsigned 8 bits
//	AV_SAMPLE_FMT_S16,         ///< signed 16 bits
//	AV_SAMPLE_FMT_S32,         ///< signed 32 bits
//	AV_SAMPLE_FMT_FLT,         ///< float
//	AV_SAMPLE_FMT_DBL,         ///< double
//	AV_SAMPLE_FMT_U8P,         ///< unsigned 8 bits, planar
//	AV_SAMPLE_FMT_S16P,        ///< signed 16 bits, planar
//	AV_SAMPLE_FMT_S32P,        ///< signed 32 bits, planar
//	AV_SAMPLE_FMT_FLTP,        ///< float, planar
//	AV_SAMPLE_FMT_DBLP,        ///< double, planar
//	AV_SAMPLE_FMT_S64,         ///< signed 64 bits
//	AV_SAMPLE_FMT_S64P,        ///< signed 64 bits, planar
//	AV_SAMPLE_FMT_NB           ///< Number of sample formats. DO NOT USE if linking dynamically
//};

//����Ƶ����ӿ���
class XMediaEncode
{
public:
	//�������
	int inWidth = 1280;
	int inHeight = 720;
	int inPixSize = 3;
	int channels = 2;
	int sampleRate = 44100;
	XSampleFMT inSampleFmt = X_S16;
	//�������
	int outWidth = 1280;
	int outHeight = 720;
	int bitrate = 4000000;//ѹ����ÿһ����Ƶ��bitλ��С50KB
	int fps = 25;
	int nbSample = 1024;
	XSampleFMT outSampleFmt = X_FLAPT;

	//��������������
	static XMediaEncode *Get(unsigned char index = 0);

	//��ʼ�����ظ�ʽת���������ĳ�ʼ��
	virtual bool InitScale() = 0;

	//��Ƶ�ز��������ĳ�ʼ��
	virtual bool InitResample() = 0;

	//����ֵ�������������
	virtual XData Resample(XData d) = 0;

	//����ֵ�������������
	virtual XData RGBToYUV(XData rgb) = 0;

	//��������ʼ��
	virtual bool InitVideoCodec() = 0;

	//��Ƶ�����ʼ��
	virtual bool InitAudioCodec() = 0;

	//��Ƶ���� ����ֵ�����û�����
	virtual XData EncodeVideo(XData frame) = 0;

	//��Ƶ���� ����ֵ�����û�����
	virtual XData EncodeAudio(XData frame) = 0;

	virtual ~XMediaEncode();
	AVCodecContext *vc = 0;//������������
	AVCodecContext *ac = 0;//��Ƶ������������
protected:
	XMediaEncode();
};

