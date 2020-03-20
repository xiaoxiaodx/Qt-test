/*******************************************************************
|  Copyright(c)  GaoZhi Technology Development Co.,Ltd
|  All rights reserved.
|
|  �汾: 1.0 
|  ����: ̷�� [tanfan0406@163.com]
|  ����: 2018��2��3��
|  ˵��:
|  �޸�:
|		1.2018/02/21 �������ñ������
******************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
//#include <sys/prctl.h>




#ifndef KEY_PROBE
#define KEY_PROBE				1
#endif

#ifndef KEY_TRUE
#define KEY_TRUE				0
#endif

#ifndef KEY_PULLMSG
#define KEY_PULLMSG				2
#endif

#ifndef KEY_SYNCHRONIZATION_POINT
#define KEY_SYNCHRONIZATION_POINT 3
#endif



#ifndef KEY_HELLO 
#define KEY_HELLO				4
#endif

#ifndef KEY_REBOOT
#define KEY_REBOOT				5
#endif

//һ�����
#ifndef KEY_FALSE
#define KEY_FALSE				-1
#endif

#ifndef B_FALSE
#define B_FALSE				(0)
#endif

#ifndef B_TRUE
#define B_TRUE				(1)
#endif

#ifndef KEY_TRUE
#define KEY_TRUE				0
#endif

#ifndef KEY_OUT					
#define KEY_OUT					-2
#endif


//ʱ��ת����appΪ����ʱ�䣬�豸¼��ΪUTCʱ��,����ڰ汾��ת��
#ifndef RECORD_LOCAL
//#define RECORD_LOCAL
#endif

//������:δ�ҵ����ñ�
#ifndef KEY_NOTFOUNDCONF		
#define KEY_NOTFOUNDCONF		-2
#endif

#ifndef KEY_NORESPONSE
#define KEY_NORESPONSE		-3
#endif


//������:������ȷ
#ifndef KEY_OK		
#define KEY_OK		200
#endif

//������:�������
#ifndef KEY_ERROR		
#define KEY_ERROR		400
#endif


//������:��Ȩʧ��
#ifndef KEY_UNAUTHORIZED		
#define KEY_UNAUTHORIZED		401
#endif

//������:�û��ظ���¼
#ifndef KEY_USERREPEATLOGIN
#define KEY_USERREPEATLOGIN		402
#endif

//������:��ֹ����
#ifndef KEY_FORBIDDEN		
#define KEY_FORBIDDEN		403
#endif

//������:�Ҳ�������
#ifndef KEY_NOTFOUND		
#define KEY_NOTFOUND		404
#endif

//������:û��Ȩ��
#ifndef KEY_METHODNOTALLOWED		
#define KEY_METHODNOTALLOWED		405
#endif

//�豸����
#ifndef KEY_DEVICEHADBIND		
#define KEY_DEVICEHADBIND		408
#endif

//�û��Ѿ�����
#ifndef KEY_USERREPEAT
#define KEY_USERREPEAT		407
#endif

//������������
#ifndef KEY_SERVEROFFLINE
#define KEY_SERVEROFFLINE   409
#endif

//�豸������
#ifndef KEY_DEVICEOFFLINE
#define KEY_DEVICEOFFLINE   500
#endif



//���ر�
#ifndef KEY_TEARDOWN
#define KEY_TEARDOWN	-2
#endif

#ifndef KEY_TIMEOUT
#define KEY_TIMEOUT		-3
#endif


#ifndef _OUT_
#define _OUT_
#endif 

#ifndef _IN_
#define _IN_
#endif 

#ifndef WIN32
#define  SleepMs(ms) usleep((ms)*1000)
#else
#define SleepMs(ms) Sleep(ms)
#endif

//�߳���
#ifndef MUTEX
#define MUTEX
#define MUTEX_LOCK(mutex)	pthread_mutex_lock(mutex)
#define MUTEX_UNLOCK(mutex)	pthread_mutex_unlock(mutex)
#define MUTEX_INIT(mutex)	pthread_mutex_init(mutex,NULL)
#define MUTEX_DESTROY(mutex)	pthread_mutex_destroy(mutex)
#endif	

#define DF_MAX_CHN 		 			8
#define DF_MAX_STREAM 		 		1
#define DF_MAX_URLSTRLEN 			128
#define DF_MAX_SUPPORTRESLUTION		32 
#define DF_MAX_ENCODETYPE	 		4
#define DF_MAX_NETETHNUM			10
#define DF_OSD_STRING_LEN           (32)
#define DF_MAX_SNAP_LEN 510*1024

#ifndef DF_MAX_USRNUM
#define DF_MAX_USRNUM				10
#endif

#ifndef DF_MAXLEN_USRNAME
#define DF_MAXLEN_USRNAME			127
#endif

#ifndef DF_MAXLEN_PASSWD
#define DF_MAXLEN_PASSWD			127
#endif

#ifndef DF_UUID_LEN
#define DF_UUID_LEN					64
#endif	

#ifndef DF_MAX_REC_NUM
#define DF_MAX_REC_NUM 				200
#endif

#ifndef MAX_DEV_NUM
#define MAX_DEV_NUM 				20		
#endif

typedef enum _ENUM_RUNSTATUS_E
{
	ENUM_ENABLED_INIT = 0x00,
	ENUM_ENABLED_CHANGE,
}ENUM_RUNSTATUS_E;

typedef enum _ENUM_ENABLED_E
{
	ENUM_ENABLED_FALSE = 0x00,
	ENUM_ENABLED_TRUE,
}ENUM_ENABLED_E;


typedef enum _E_ALARMTYPE
{
	ALARMTYPE_NULL = 0x00,
	ALARMTYPE_MOTION = 1 << 0,
	ALARMTYPE_BLIND = 1 << 1,//�ڵ��澯
	ALARMTYPE_IO1 = 1 << 2,
	ALARMTYPE_IO2 = 1 << 3,
	ALARMTYPE_SDCARD = 1 << 4,
}E_ALARMTYPE;

typedef struct _IntRange_T
{
	int max;
	int min;
}IntRange_T;

typedef struct _FloatRange_T
{
	float max;
	float min;
}FloatRange_T;

typedef struct _TimeYMD_T
{
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
}TimeYMD_T;

typedef struct _TimeSection_T
{
	ENUM_ENABLED_E enabled;
	TimeYMD_T starTime;
	TimeYMD_T endTime;
}TimeSection_T;

//SDK
typedef enum _VideoEncodeMode_E
{
	 VideoEncodMode__NULL  = 0,
	 VideoEncodMode__CBR  = 1 << 0,
	 VideoEncodMode__VBR  = 1 << 1, 
}VideoEncodeMode_E;

typedef enum _VideoEncoding_E
{
	 VideoEncoding__NULL  = 0,
	 VideoEncoding__JPEG  = 1 << 0,
	 VideoEncoding__MPEG4 = 1 << 1, 
	 VideoEncoding__H264 =  1 << 2,
	 VideoEncoding__H265 =  1 << 3,
	 VideoEncoding__MJPEG = 1 << 4, 
}VideoEncoding_E; 

typedef enum _H264Profile_E
{
	 H264Profile__NULL 		=	 0,
	 H264Profile__Baseline 	=	1 << 0,
	 H264Profile__Main 		=	1 << 1, 
	 H264Profile__Extended	=	1 << 2,
	 H264Profile__High 		= 	1 << 3,
}H264Profile_E; 

typedef enum _AudioEncoding_E
{
	 AudioEncoding__NULL,
	 AudioEncoding__G711A = 1,//G711A
	 AudioEncoding__G726,
	 AudioEncoding__AAC,
	 AudioEncoding__G711U,
	 AudioEncoding__PCM,
	 AudioEncoding__Max,
}AudioEncoding_E; 

typedef struct _VideoReslution_T
{
	int width;
	int height;
}VideoReslution_T;

typedef enum _Enum_FrameType
{
	API_FRAME_TYPE_P = 0x61,
	API_FRAME_TYPE_I = 0x65,
	API_FRAME_TYPE_SPS = 0x67,
	API_FRAME_TYPE_PPS = 0x68,
}Enum_FrameType;

typedef struct _AudioFramedataInfo_T
{
	int framesize;
	char* frame;
}AudioFramedataInfo_T;

//���ײ���
typedef struct _VideoPackInfo_T
{
 int frameEnd;    //������־
 int datalen;  	  //Ƭ����
 char *dataaddr;  //����
}VideoPackInfo_T;

typedef struct _VideoFramedataInfo_T
{
	int packcount;  //֡���ܰ���
	Enum_FrameType frametype;//֡����
	unsigned long long pts;
	VideoPackInfo_T *packInfo;//
}VideoFramedataInfo_T;


//���ײ���
//���:csq ����,H264/H265/MPEG Enum_FrameType���.
typedef struct _VideoInfo_T
{
	int chn;  	   //ͨ��
	int streamtype;//�������ͣ�����������������Ԥ��
	int fps;   //֡��
	int bitrate;
	int rcmode;//����������ѡ��0 CBR  1 VBR
	VideoEncoding_E   videoencode; //��������
	unsigned int  seq;  //֡���
	VideoReslution_T framesize;
	VideoFramedataInfo_T videoframeinfo;  //֡��Ϣ
}VideoInfo_T;

typedef enum _Enum_MsgCmd
{
	Msg_RecvGetDevicId = 0x01,
    Msg_GetPlay = 0x20,
    Msg_GetTearDown = 0x21,
	Msg_SendStreamPlayRes = 0x22,
}Enum_MsgCmd;



typedef enum _Enum_MediaType
{
	MediaType_H264 = 0x01,
	MediaType_H265,
	MediaType_JPEG = 0x11,
	MediaType_MPEG4,
	MediaType_MJPEG,
	MediaType_G711A = 0x21,
	MediaType_G711U,
	MediaType_G726,
	MediaType_AAC,
	MediaType_PCM,
	MediaType_MSG,
}Enum_MediaType;


typedef enum _MediaClarity_E{
	ENUM_MEDIA_CLEAR = 0x00,//����
	ENUM_MEDIA_STANDARD,//����
	ENUM_MEDIA_FLUENT,//����
	ENUM_MEDIA_BUTT=0xFFFF,//�Ƿ�״̬
}MediaClarity_E;

typedef struct _MediaVideoInfo_S{
	Enum_FrameType   frametype;
	int   chn;
	VideoReslution_T framesize;
	int bitrate;
	int rcmode;//����������ѡ��0 CBR  1 VBR
}MediaVideoInfo_S;

typedef struct _MediaAudioInfo_S{
	int samplerate;//��������
	int prenum;//������
	int bitwidth;//λ��
	int soundmode;   //��������
}MediaAudioInfo_S;

typedef struct _MediaFrame_T
{
	int fps;   //֡��
	unsigned int subChn;    //�������,��; ��Ƶ������ʶ,��Ƶ������ʶ  
	Enum_MediaType   mediaType; //��������
	int datalen;  //Ƭ����
	unsigned long long pts;
	unsigned char *dataaddr;  //����
	union
    {
    	MediaVideoInfo_S stvideoinfo;
    	MediaAudioInfo_S staudioinfo;
    };
}MediaFrame_T;

typedef struct  _SnapImageParam_T
{
	VideoReslution_T res;
	int quility;
}SnapImageParam_T;

typedef struct  _SnapImage_T{
	SnapImageParam_T info;
	unsigned long long pts;
	int datalen;  //Ƭ����
	char *dataaddr;  //����
}SnapImage_T;


//��Ƶ����
typedef struct _AUidoInfo_T
{
	int chn; 
	int fps;   //֡��
	int samplerate;//��������
	int prenum;//������
	int bitwidth;//λ��
	int soundmode;   //��������
	unsigned long long pts; //ʱ���
	AudioEncoding_E   audioencode;
	AudioFramedataInfo_T audioframeinfo;
}AudioInfo_T;

typedef struct _VideoEncode_T
{
	int					frameRate;
	int					bitrate;
	int					qulity;
	int					gop;
	int					cvbrMode;//0 CBR
	VideoEncoding_E		encoding;
	H264Profile_E		h264Profile;
	VideoReslution_T	reslution;		
}VideoEncode_T;
typedef struct _VideoSpsPpsInfo_T
{
	short spslen;
	short ppslen;
	char sps[64]; //base64����
	char pps[64]; //base64����
}VideoSpsPpsInfo_T;
typedef struct _VideoEncodeCab_T
{
	IntRange_T			frameRateRange;		//֡��
	IntRange_T			bitrateRange;		//����
	IntRange_T			qulityRange;		//����
	IntRange_T			gopRange;			//
	VideoEncoding_E		encodingCab;		//��������
	H264Profile_E		h264ProfileCab;		//���뷽ʽ
	VideoReslution_T	defaultReslution;	//
	VideoReslution_T	maxReslution;		//
	VideoReslution_T	resSupport[DF_MAX_SUPPORTRESLUTION];
	int					resSupportNum;
	VideoEncodeMode_E 	cvbrmodeCab;		//֧������ģʽ  0:ֻ֧��vbr 1:ֻ֧��cbr 2:��֧��
}VideoEncodeCab_T;


typedef struct _AudioEncode_T
{
	AudioEncoding_E encoding;
	int bitrate;
	int sampleRate;
	ENUM_ENABLED_E 	enabled;
}AudioEncode_T;

#define D_SYNCDATA_HEAD0 0x77
#define D_SYNCDATA_HEAD1 0x17

typedef struct _MeidaHead_T{
	unsigned char sysncHead0;
	unsigned char sysncHead1;
	unsigned char streamType;//��������
	unsigned char mediaType;//����Ƶ����
}MeidaHead_T;

typedef struct _QueueVideoInputInfo_T{
	unsigned char fps;   //֡��
	unsigned char rcmode;//����������ѡ��0 CBR  1 VBR
	unsigned char frametype;//֡����
	unsigned char staty0; //��������
	VideoReslution_T reslution;
	int bitrate;
	//unsigned long long  pts;//ms ����
	unsigned int highPts;
	unsigned int lowPts;//ms ����
}QueueVideoInputInfo_T;

typedef struct _MeidaVideo_T{
	MeidaHead_T head;
	QueueVideoInputInfo_T info;
	int datalen;  //Ƭ����
}MeidaVideo_T;

typedef struct _QueueAudioInputInfo_T{
	int samplerate;//��������
	int prenum;//������
	int bitwidth;//λ��
	int soundmode;   //��������
	//unsigned long long  pts; //ʱ���
	unsigned int highPts;
	unsigned int lowPts;//ms ����
}QueueAudioInputInfo_T;

typedef struct _MeidaAudio_T{
	MeidaHead_T head;
	QueueAudioInputInfo_T info;
	int datalen; //Ƭ����
}MeidaAudio_T;

typedef struct _OsdParam_T
{
	int posx;
	int posy;
	char text[DF_OSD_STRING_LEN];//�豸������ text��Ч,������deviceinfo�е�name;ʱ����TXT��Ч
	ENUM_ENABLED_E  enabled;	
}OsdParam_T;

typedef struct _OsdInfo_T
{
	OsdParam_T channelTitle;
	OsdParam_T time;
	OsdParam_T usrdef[10];
}OsdInfo_T;


typedef struct _ImagingCab_T
{
	IntRange_T			Brightness;
	IntRange_T			ColorSaturation;	
	IntRange_T			Contrast;	
	IntRange_T			Sharpness;
	IntRange_T			Hue;
}ImagingCab_T;

typedef struct _ImagingParam_T
{
	ENUM_ENABLED_E mirror;//ˮƽ��ת
	ENUM_ENABLED_E flip;//��ֱ��ת
	int			brightness;//����
	int			colorSaturation;//���Ͷ�	
	int			contrast;//�Աȶ�
	int			hue;//ɫ��
	int			sharpness;//��� �����ӿ�	
}ImagingParam_T;

typedef struct _Diskinfo_T
{
	unsigned char diskName[12]; 		//< ��������
	unsigned long long uiTotalSpace;	//< ��������MBΪ��λ
	unsigned long long uiRemainSpace;	//< ʣ��������MBΪ��λ
}Diskinfo_T;

typedef struct _DiskParam_T
{
	//int 	bIsCurrent;			//< �Ƿ�Ϊ��ǰ������			
	//int	iSerialNo;			//< �������к�
	//int	iPartNo;			//< ������
	int    	   count;			//���̸���
	Diskinfo_T Diskparam[MAX_DEV_NUM];
}DiskParam_T;

typedef int (*AlarmVoiceCb)();

#ifndef DF_DEBUG
#define DF_DEBUG(msg...) printf("[%s,%d]=> ",__FILE__,__LINE__);printf(msg);printf("\r\n");
#endif


#ifndef DF_ERROR
#define DF_ERROR(msg...) printf("[%s,%d]=>error: ",__FILE__,__LINE__);printf(msg);printf("\r\n");
#endif

#ifndef WIN32
#define  SleepMs(ms) usleep((ms)*1000)
#define _printd(fmt, ...)	printf ("[%s][%d]"fmt"\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define SleepMs(ms) Sleep(ms)
#define _printd(fmt, ...)	printf ("[%s][%d]" fmt"\n", (char *)(strrchr(__FILE__, '\\') + 1), __LINE__ - 2, ##__VA_ARGS__)
#endif

#endif
