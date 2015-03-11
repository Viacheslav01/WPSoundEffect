#pragma once

#include "pch.h"
#include "WaveData.h"

private class WaveReader
{
private:
	ChunkInfo FindChunk(const Array<byte>^ buffer, const RiffType& chunkType) const;
public:
	WaveReader();
	WaveData Read(const Array<byte>^ buffer) const;
};
