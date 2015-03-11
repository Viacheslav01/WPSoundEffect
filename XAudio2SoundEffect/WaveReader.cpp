#include "pch.h"
#include "WaveReader.h"

WaveReader::WaveReader()
{
}

WaveData WaveReader::Read(const Array<byte>^ buffer) const
{
	if (!buffer)
	{
		throw ref new Platform::InvalidArgumentException("buffer is null");
	}

	auto chunk = FindChunk(buffer, RiffType::Riff);
	if (*reinterpret_cast<RiffType*>(chunk.Data) != RiffType::Wave)
	{
		throw ref new Platform::FailureException("unsupported file format");
	}

	chunk = FindChunk(buffer, RiffType::Format);
	if (chunk.Length < sizeof(WAVEFORMATEX))
	{
		throw ref new Platform::FailureException("unsupported sound format");
	}

	auto format = reinterpret_cast<WAVEFORMATEX*>(chunk.Data);
	if (format->wFormatTag != WAVE_FORMAT_PCM
		&& format->wFormatTag != WAVE_FORMAT_ADPCM)
	{
		throw ref new Platform::FailureException("unsupported wave format, must be PCM or ADPCM");
	}

	chunk = FindChunk(buffer, RiffType::Data);

	WaveData res = { format, chunk.Data, chunk.Length };
	return res;
}

ChunkInfo WaveReader::FindChunk(const Array<byte>^ buffer, const RiffType& chunkType) const
{
	if (buffer == nullptr)
	{
		throw ref new Platform::InvalidArgumentException("buffer is null");
	}

	auto current = buffer->Data;
	auto last = current + buffer->Length;

	while (last > (current + sizeof(RiffChunk)))
	{
		auto chunk = reinterpret_cast<RiffChunk*>(current);
		current += sizeof(RiffChunk);

		if (chunk->Tag == chunkType)
		{
			ChunkInfo res = { chunk->Tag, chunk->Length, current };
			return res;
		}

		if (chunk->Tag == RiffType::Riff
			|| chunk->Tag == RiffType::List)
		{
			current += sizeof(uint32);
		}
		else
		{
			current += chunk->Length;
		}
	}

	throw ref new Platform::FailureException("chunk don't found");
}
