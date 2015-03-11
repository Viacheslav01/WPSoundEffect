#pragma once

#include "pch.h"
#include "WaveData.h"

namespace XAudio2SoundEffect
{
	public ref class SoundEffect sealed
	{
	private:
		std::shared_ptr<WaveData> _waveData;

		Microsoft::WRL::ComPtr<IXAudio2> _audioEngine;
		IXAudio2MasteringVoice* _masteringVoice;
		IXAudio2SourceVoice* _sourceVoice;

	public:
		SoundEffect(const Array<byte>^ source);

		void Play();
		void Stop();
	};
}