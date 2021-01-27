#ifndef THIRDEASYLOGGERSET_H
#define THIRDEASYLOGGERSET_H

#include <QObject>
#include <QMutex>

typedef enum {
    LOG_LVL_ASSERT  = 0,
    LOG_LVL_ERROR   = 1,
    LOG_LVL_WARN    = 2,
    LOG_LVL_INFO    = 3,
    LOG_LVL_DEBUG   = 4,
    LOG_LVL_VERBOSE = 5
} LOG_LEVEL;

#define WRITE_LOG_A(strLog)                                                                                 \
{                                                                                                           \
    ThirdEasyLogger::getInstance()->write_log(LOG_LVL_ASSERT, __FILE__, __FUNCTION__, __LINE__, strLog);	\
}
#define WRITE_LOG_E(strLog)                                                                                 \
{                                                                                                           \
    ThirdEasyLogger::getInstance()->write_log(LOG_LVL_ERROR, __FILE__, __FUNCTION__, __LINE__, strLog);     \
}
#define WRITE_LOG_W(strLog)                                                                                 \
{                                                                                                           \
    ThirdEasyLogger::getInstance()->write_log(LOG_LVL_WARN, __FILE__, __FUNCTION__, __LINE__, strLog);      \
}
#define WRITE_LOG_I(strLog)                                                                                 \
{                                                                                                           \
    ThirdEasyLogger::getInstance()->write_log(LOG_LVL_INFO, __FILE__, __FUNCTION__, __LINE__, strLog);      \
}
#define WRITE_LOG_D(strLog)                                                                                 \
{                                                                                                           \
    ThirdEasyLogger::getInstance()->write_log(LOG_LVL_DEBUG, __FILE__, __FUNCTION__, __LINE__, strLog);     \
}
#define WRITE_LOG_V(strLog)                                                                                 \
{                                                                                                           \
    ThirdEasyLogger::getInstance()->write_log(LOG_LVL_VERBOSE, __FILE__, __FUNCTION__, __LINE__, strLog);	\
}

class ThirdEasyLogger : public QObject
{
    Q_OBJECT
public:
    static ThirdEasyLogger* getInstance();

private:
    ThirdEasyLogger();
    ~ThirdEasyLogger();
    //删掉定义，防止后门注入
    ThirdEasyLogger(const ThirdEasyLogger &sg) =delete ;
    ThirdEasyLogger &operator=(const ThirdEasyLogger &sg)=delete ;

public:
    void ThirdEasyLoggerSet(const QString& path = "");
    void write_log(LOG_LEVEL type, const QString& file, const QString& func, const long line, const QString& strLog);

private:
    static ThirdEasyLogger *m_instance;
    static QMutex  m_mutex;
};

#endif
