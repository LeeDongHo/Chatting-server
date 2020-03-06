#pragma once

#include "memoryPool.h"

class Sbuf
{
private:
	enum SbufPacket
	{
		defaultBuffer = 512,
		defaultHeader = 5,
		lanHeader = 2,
		// �� ������� ���� �� Ŭ���̾�Ʈ Ȥ�� ������ �ִ� ��Ŷ�� ���� ���絵 ����
		// �Ŀ� �������� ���ؼ� �� ������ �ʰ��ϴ� ��Ŷ����� ������ ��Ŷ ����� �����ϵ���? �غ� ����
	};

	void	init();				// �޸��Ҵ� �Լ� �Ժη� ȣ�� X
	void	release();		// �޸� ���� �Լ�

public:
	Sbuf();
	~Sbuf();

	void	clear();			// ���۸� ����. (���۸� �����ϴ°��� �ƴ�)
	void	lanClear();

	int		getBufSize();	// ������ �ִ� ����� ��´�. (���ۻ����� ��ȯ)
	int		getDataSize();// ���ۿ� ����� �������� ����� (�������)�� ��´�.
	int		getPacketSize(); // ��� ���� ������� ��´�.

	char* getBufPtr();	// ������ ������ ��ȯ
	char* getHeaderPtr(); // ��� ���ۺ��� ������ ��ȯ
	char* getDataPtr();
	char* getFrontPtr();

	int		moveFrontPos(int _pos);	// ������ front(����) ��ġ�� �����Ѵ�.
	int		moveRearPos(int _pos);	// ������ Rear(����) ��ġ�� �����Ѵ�.

	bool		setHeader(char *dest);	// 5����Ʈ ��� ����.
	bool		setHeaderCustom(char *dest, int _size);		// _size ũ�⸸ŭ�� ��� ����
	bool		setHeaderShort(void);		// unsigned short ũ�⸸ŭ ��� ����.

	void Encode(BYTE _code, BYTE _key1, BYTE _key2);
	void lanEncode(void);
	bool Decode(BYTE _code, BYTE _key1, BYTE _key2);
	bool lanDecode(void);

	LONG	addRef();
	
	int		push(char *dest, int _size);
	int		push(const char *dest, int _size);
	int		pop(char* dest, int _size);
	static Sbuf*Alloc();
	static Sbuf*lanAlloc();
	void		Free();

private:

	int		bufferSize;
	int		dataSize;
	int		header;
	int		headerSize;

	char*		frontPos;		// ����
	char*		rearPos;			// ����
	char*		dataPos;			// ������ ����

									
	volatile LONG _refCount;

	LONG encodeFlag;

public:
	char	*buffer;

public:
	static memoryPool<Sbuf> *pool;

public:
	// ����Ʈ������ �����ε� IN
	// 1byte
	Sbuf &operator << (BYTE _value);
	Sbuf &operator << (char _value);

	// 2byte
	Sbuf &operator << (short _value);
	Sbuf &operator << (WORD _value);
	Sbuf &operator << (bool _value);

	// 4byte
	Sbuf &operator << (int _value);
	Sbuf &operator << (DWORD _value);
	Sbuf &operator << (float _value);
	Sbuf &operator << (unsigned int _value);

	// 8byte
	Sbuf &operator << (__int64 _value);
	Sbuf &operator << (unsigned __int64 _value);
	Sbuf &operator << (double _value);

	// ����Ʈ ������ �����ε� OUT
	// 1byte
	Sbuf &operator >> (BYTE &_value);
	Sbuf &operator >> (char &_value);

	// 2byte
	Sbuf &operator >> (short &_value);
	Sbuf &operator >> (WORD &_value);
	Sbuf &operator >> (bool &_value);

	// 4byte
	Sbuf &operator >> (int &_value);
	Sbuf &operator >> (DWORD &_value);
	Sbuf &operator >> (float &_value);
	Sbuf &operator >> (unsigned int &_value);

	// 8byte
	Sbuf &operator >> (__int64 &_value);
	Sbuf &operator >> (unsigned __int64 &_value);
	Sbuf &operator >> (double &_value);
};
