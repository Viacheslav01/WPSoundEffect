// XAudio2SoundEffect.cpp
#include "pch.h"
#include "XAudio2SoundEffect.h"

using namespace XAudio2SoundEffect;
using namespace Platform;

SoundEffect::SoundEffect(const Array<byte>^ source)
{
	_waveData = std::make_shared<WaveData>(source);

	auto hr = XAudio2Create(&_audioEngine);
	if (FAILED(hr))
	{
		throw ref new Platform::Exception(hr);
	}
	
	hr = _audioEngine->CreateMasteringVoice(&_masteringVoice);
	if (FAILED(hr))
	{
		throw ref new Platform::Exception(hr);
	}

	hr = _audioEngine->CreateSourceVoice(&_sourceVoice, _waveData->Format);
	if (FAILED(hr))
	{
		throw ref new Platform::Exception(hr);
	}
	
	hr = _audioEngine->StartEngine();
	if (FAILED(hr))
	{
		throw ref new Platform::Exception(hr);
	}
}

void SoundEffect::Play()
{
	Stop();

	XAUDIO2_BUFFER playBuffer = { 0 };
	playBuffer.AudioBytes = _waveData->Length;
	playBuffer.pAudioData = _waveData->Data;
	playBuffer.Flags = XAUDIO2_END_OF_STREAM;

	auto hr = _sourceVoice->SubmitSourceBuffer(&playBuffer);
	if (SUCCEEDED(hr))
	{
		hr = _sourceVoice->Start(0, XAUDIO2_COMMIT_NOW);
	}
}

void SoundEffect::Stop()
{
	auto hr = _sourceVoice->Stop();
	if (SUCCEEDED(hr))
	{
		_sourceVoice->FlushSourceBuffers();
	}
}