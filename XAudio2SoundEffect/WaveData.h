#pragma once

#include "pch.h"

using namespace Platform;

private enum RiffType : uint32
{
	Riff = 'FFIR',
	List = 'TSIL',
	Wave = 'EVAW',
	Format = ' tmf',
	Data = 'atad'
};

private struct RiffChunk
{
	uint32 Tag;
	uint32 Length;
};

private struct ChunkInfo
{
	uint32 Tag;
	uint32 Length;
	byte* Data;
};

private struct WaveData
{
private:
	const Array<byte>^ _buffer;
	
	ChunkInfo FindChunk(const Array<byte>^ buffer, const RiffType& chunkType) const;
	void Read(const Array<byte>^ buffer);

public:
	WaveData(const Array<byte>^ buffer);

	const WAVEFORMATEX* Format;
	const byte* Data;
	uint32 Length;
};
