#pragma once

#include "FileStream.h"

class Logger
{
public:
	enum Verbosity
	{
		Error,
		Warning,
	};

	static void Log(Verbosity Verbose, const char* Category, const char* Message)
	{
		if (Verbose == Error)
		{
			printf("%s: %s.\n", Category, Message);
			FileStream::WriteToFile("Log.txt", Message);
		}
		else if (Verbose == Warning)
		{
			FileStream::WriteToFile("Log.txt", Message);
		}
	}
};