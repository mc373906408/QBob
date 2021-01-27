#define LOG_TAG      "main"

#include "ThirdEasyLogger.h"
#include "3rd/EasyLogger/inc/elog.h"


ThirdEasyLogger* ThirdEasyLogger::m_instance = nullptr;
QMutex  ThirdEasyLogger::m_mutex;

ThirdEasyLogger* ThirdEasyLogger::getInstance()
{
    if (m_instance == Q_NULLPTR)
    {
        QMutexLocker locker(&m_mutex);
        if (m_instance == Q_NULLPTR)
        {
            m_instance = new ThirdEasyLogger();
        }
    }
    return m_instance;
}

ThirdEasyLogger::ThirdEasyLogger()
{

}

ThirdEasyLogger::~ThirdEasyLogger()
{
}

void ThirdEasyLogger::ThirdEasyLoggerSet(const QString& path)
{
    elog_init();
    /* set EasyLogger log format */
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    //elog_set_file_enabled(false);
    if(!path.isEmpty()){
        elog_set_file_path(path.toUtf8());
    }
    /* start EasyLogger */
    elog_start();
}

void ThirdEasyLogger::write_log(LOG_LEVEL type, const QString& file, const QString& func, const long line, const QString& strLog)
{
    switch (type) {
        case LOG_LVL_ASSERT:
            log_a_i(file.toUtf8(), func.toUtf8(), line, strLog.toUtf8());
            break;
        case LOG_LVL_ERROR:
            log_e_i(file.toUtf8(), func.toUtf8(), line, strLog.toUtf8());
            break;
        case LOG_LVL_WARN:
            log_w_i(file.toUtf8(), func.toUtf8(), line, strLog.toUtf8());
            break;
        case LOG_LVL_INFO:
            log_i_i(file.toUtf8(), func.toUtf8(), line, strLog.toUtf8());
            break;
        case LOG_LVL_DEBUG:
            log_d_i(file.toUtf8(), func.toUtf8(), line, strLog.toUtf8());
            break;
        case LOG_LVL_VERBOSE:
            log_v_i(file.toUtf8(), func.toUtf8(), line, strLog.toUtf8());
            break;
        default:
            log_i_i(file.toUtf8(), func.toUtf8(), line, strLog.toUtf8());
            break;
    }
}
