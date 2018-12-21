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

//音视频编码接口类
class XMediaEncode
{
public:
	//输入参数
	int inWidth = 1280;
	int inHeight = 720;
	int inPixSize = 3;
	int channels = 2;
	int sampleRate = 44100;
	XSampleFMT inSampleFmt = X_S16;
	//输出参数
	int outWidth = 1280;
	int outHeight = 720;
	int bitrate = 4000000;//压缩后每一秒视频的bit位大小50KB
	int fps = 25;
	int nbSample = 1024;
	XSampleFMT outSampleFmt = X_FLAPT;

	//工厂的生产方法
	static XMediaEncode *Get(unsigned char index = 0);

	//初始化像素格式转换的上下文初始化
	virtual bool InitScale() = 0;

	//音频重采样上下文初始化
	virtual bool InitResample() = 0;

	//返回值无需调用者清理
	virtual XData Resample(XData d) = 0;

	//返回值无需调用者清理
	virtual XData RGBToYUV(XData rgb) = 0;

	//编码器初始化
	virtual bool InitVideoCodec() = 0;

	//音频编码初始化
	virtual bool InitAudioCodec() = 0;

	//视频编码 返回值无需用户清理
	virtual XData EncodeVideo(XData frame) = 0;

	//音频编码 返回值无需用户清理
	virtual XData EncodeAudio(XData frame) = 0;

	virtual ~XMediaEncode();
	AVCodecContext *vc = 0;//编码器上下文
	AVCodecContext *ac = 0;//音频编码器上下文
protected:
	XMediaEncode();
};

