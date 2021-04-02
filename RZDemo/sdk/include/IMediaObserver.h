#pragma once

#include <cstdint>

namespace rz {

enum VIDEO_FRAME_TYPE
{ VIDEO_FRAME_I420 };

struct VideoFrame {
  VIDEO_FRAME_TYPE type = VIDEO_FRAME_I420;
  int width = 0;
  int height = 0;
  int yStride = 0;
  int uStride = 0;
  int vStride = 0;
  void* yBuffer = nullptr;
  void* uBuffer = nullptr;
  void* vBuffer = nullptr;
  int32_t timeStamp = 0;
  ~VideoFrame() {
    delete[] yBuffer;
    delete[] uBuffer;
    delete[] vBuffer;
  }
};

class VideoObserver {
 public:
  //��ȡ��Ƶ��Զ����Ƶ����ǰ������
  virtual bool onRenderVideoFrame(const char* channelId, const char* uid, const char* streamName, VideoFrame& videoFrame) = 0;

  //��òɼ�����Ƶ
  virtual bool onCaptureVideoFrame(const char* streamName, VideoFrame& videoFrame) = 0;

  //�����Ƶ����ǰ������
  virtual bool onPreEncodeVideoFrame(const char* streamName, VideoFrame& videoFrame) = 0;
};

enum VIDEO_OBSERVER_POSITION
{
  POSITION_POST_CAPTURER = 1 << 0,  //��Ƶ�ɼ����λ��
  POSITION_PRE_ENCODER = 1 << 1,    //��Ƶ����ǰ��λ��
  POSITION_PRE_RENDERER = 1 << 2    //Զ����Ƶ����ǰ��λ��
};

struct VideoObserverInfo {
  VideoObserver* observer = nullptr;
  uint8_t observerPosition = 0;  //��ֵ������ΪOBSERVER_POSITION����ö��ֵͨ�� & ����ͬʱ���ö���۲��
};

enum AUDIO_FRAME_TYPE
{ AUDIO_FRAME_PCM16 };

struct AudioFrame {
  AUDIO_FRAME_TYPE type = AUDIO_FRAME_PCM16;  //��Ƶ��������
  int samples = 320;                          //��֡��Ƶ���ݲ�����
  int bytesPerSample = 2;                     //ÿ������ռ�е�byte����
  int channels = 1;                           //������
  int samplesRate = 16000;                    //������
  void* buffer = nullptr;                     //����
  uint32_t timeStamp = 0;                     //��Ƶ֡ʱ���
  ~AudioFrame() { delete[] buffer; }
};

class AudioObserver {
 public:
  //��ȡ��Ƶ������ǰ����Ƶ�������ݡ�
  virtual bool onPlaybackAudioFrameBeforeMixing(const char* channelId, const char* uid, AudioFrame& audioFrame) = 0;

  //��òɼ�����Ƶ��
  virtual bool onRecordAudioFrame(AudioFrame& audioFrame) = 0;

  //��ò��ŵ�������
  virtual bool onPlaybackAudioFrame(AudioFrame& audioFrame) = 0;
};

enum AUDIO_OBSERVER_POSITION
{
  AUDIO_OBSERVER_RECORD = 1 << 0,    //��Ƶ�ɼ����λ��
  AUDIO_OBSERVER_PLAYBACK = 1 << 1,  //��Ƶ����ǰ��λ��
  AUDIO_OBSERVER_MIXBEFORE = 1 << 2  //��Ƶ����ǰ��λ��
};

struct AudioObserverInfo {
  AudioObserver* observer = nullptr;
  uint8_t observerPosition = 0;  //��ֵ������ΪOBSERVER_POSITION����ö��ֵͨ�� & ����ͬʱ���ö���۲��
};
}  // namespace rz
