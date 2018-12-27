#pragma once

#include <stdio.h>
#include "Logger.h"

class FileStream
{
public:
	static void WriteToFile(const char* Filename, const char* Message)
	{
		FILE* f;
		f = fopen(Filename, "w");
		if (f == NULL)
		{
			Logger::Log(Logger::Error, "File", "Error opening file\n.");
		}

		fprintf(f, Message);
	}
};
