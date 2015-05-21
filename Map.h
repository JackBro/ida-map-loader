#pragma once

#include <windows.h>
#include <vector>

#define USE_DANGEROUS_FUNCTIONS

#pragma warning(push, 2)

#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <name.hpp>
#include <demangle.hpp>
#include <bytes.hpp>
//#include <pe/pe.h>

#pragma warning(pop)

struct MapFileSegment
{
	char		Name[64];
	char		Class[16];
	int			Id;
	ULONGLONG	Start;
	ULONGLONG	Length;
};

struct MapFileSymbol
{
	char		Name[256];
	int			Id;
	ULONGLONG	Offset;
};

class MapFile
{
public:

private:
	HANDLE	m_FileHandle;
	char	*m_FileDataBase;
	char	*m_FileData;

	std::vector<MapFileSegment> m_Segments;
	std::vector<MapFileSymbol>	m_Symbols;

public:
	MapFile();
	~MapFile();

	bool Load(const char *Path);

	std::vector<MapFileSegment>&	GetSegments();
	std::vector<MapFileSymbol>&		GetSymbols();

private:
	bool EnumerateLines(char *Start, int Type);

	bool LoadSegments();
	bool LoadSegment(char *Line);

	bool LoadSymbols();
	bool LoadSymbol(char *Line);
};