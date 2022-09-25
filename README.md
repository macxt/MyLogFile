# MyLogFile
write a log tools for output to console or log file instead of stdandard output deivce(std::cout/std::cerr)


若是要将日志输出到一个文件中：

则需要使用 INITIALIZ_LOGFILE(filename) 宏初始化日志文件；同时也会输出到控制台；

使用此日志输出如下：

eg:  MYLOG_INFO << "Hello world" << "!" << "I love C++ Language.";


若不需要输出到文件，则不必使用 INITIALIZ_LOGFILE(filename) 宏初始化日志文件；则会仅将日志输出到控制台。