#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#ifdef _MSC_VER
#ifdef MYLOGFILE_EXPORTS
#define LOG_DLL		__declspec(dllexport)
#else
#define LOG_DLL		__declspec(dllimport)
#endif
#else
#define LOG_DLL
#endif

class LOG_DLL LogPrint
{
public:

	static LogPrint GetInstance() {
		static LogPrint logPrint;
		return logPrint;
	}

	~LogPrint() {};

	void OutLogToConsole(const std::string &sBaseMessage, const std::string &sUserMessage);

	void OutLogToFile(const std::string &sBaseMessage, const std::string &sUserMessage, const std::string &sLogFile);

private:
	LogPrint() {};
	LogPrint(const LogPrint &objOther) {};
	LogPrint& operator = (const LogPrint &objOther) { return *this; };

};

class LOG_DLL LogFile
{
public:
	enum MyLogLevel {
		MYLOG_INFO_LEVEL,
		MYLOG_ERROR_LEVEL,
		MYLOG_WARN_LEVEL
	};

public:
	LogFile(std::string const& fileInfo, int lineInfo, std::string const& funcInfo, MyLogLevel logLevel);

	static void InitLogFile(std::string const& logFileName) {
		if (!logFileName.empty()) {
			sLogFileName = logFileName;
			bIsOutLogFile = true;
		}
	}
	~LogFile();

	template<typename OutType>
	LogFile& operator << (const OutType &outmessage) {
		std::stringstream ss;
		ss << outmessage;
		sUserLogMeg += ss.str();
		return *this;
	}

private:

	void SetBaseLogMessage();
	std::string GetLocalCurrentTime(std::string const& formats = "%Y-%m-%d %H:%M:%S", std::string const& millformats = ".%03d");

	static bool IsOutLogFile() { return bIsOutLogFile; }

	std::string sFileInfo;
	std::string sFuncInfo;
	std::string sCurrNowTime;
	std::string sBaseLogMsg;
	std::string sUserLogMeg;

	static std::string sLogFileName;	//static variable must be externally defined(meaning allocate memory) and then use, here is declaration.
	static bool bIsOutLogFile;

	int nLineInfo = -1;
	MyLogLevel ml_logLevel;

};


#define INITIALIZ_LOGFILE(filename)		LogFile::InitLogFile(filename)

#define	MYLOG_INFO						LogFile(__FILE__, __LINE__, __FUNCTION__, LogFile::MYLOG_INFO_LEVEL)
#define MYLOG_ERROR						LogFile(__FILE__, __LINE__, __FUNCTION__, LogFile::MYLOG_ERROR_LEVEL)
#define MYLOG_WARN						LogFile(__FILE__, __LINE__, __FUNCTION__, LogFile::MYLOG_WARN_LEVEL)

