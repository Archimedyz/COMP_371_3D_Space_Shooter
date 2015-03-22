#include "header.h"

// ----------------------------------------------------------------------------------------------------------------------------

#define BUFFER_SIZE_INCREMENT 1048576

// ----------------------------------------------------------------------------------------------------------------------------

class CBuffer
{
private:
	BYTE *Buffer;
	int BufferSize, Position;

public:
	CBuffer();
	~CBuffer();

	void AddData(void *Data, int DataSize);
	void Empty();
	void FreeUnusedMemory();
	BYTE *GetData();
	int GetDataSize();

private:
	void SetDefaults();
};
