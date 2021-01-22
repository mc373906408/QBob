#include "ThirdEasyLogger.h"
#include "3rd/EasyLogger/inc/elog.h"

ThirdEasyLogger &ThirdEasyLogger::getInstance()
{
    static ThirdEasyLogger instance;
    return instance;
}

ThirdEasyLogger::ThirdEasyLogger()
{

}

ThirdEasyLogger::~ThirdEasyLogger()
{
}

void ThirdEasyLogger::ThirdEasyLoggerSet()
{
    elog_init();
    /* set EasyLogger log format */
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    elog_set_file_path("F:/Git/qtPro/qtPro1/qtPro2/qtPro3");
    /* start EasyLogger */
    elog_start();
    //elog_set_output_enabled(false);
}

void ThirdEasyLogger::write_log(const QString &str)
{
    log_a(str.toUtf8());
    //log_a("Hello EasyLogger ASSERT!");
    //log_e("Hello EasyLogger ERROR!");
    //log_w("Hello EasyLogger WARN!");
    //log_i("Hello EasyLogger INFO!");
    //log_d("Hello EasyLogger DEBUG!");
    //log_v("Hello EasyLogger VERBOSE!");
}

