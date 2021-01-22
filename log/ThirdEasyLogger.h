#ifndef THIRDEASYLOGGERSET_H
#define THIRDEASYLOGGERSET_H

#include <QObject>

#define CU_DBG_LOG(fmt)                                \
{                                                           \
    ThirdEasyLogger::getInstance()->write_log(fmt); \
}

class ThirdEasyLogger : public QObject
{
    Q_OBJECT
public:
	static ThirdEasyLogger& getInstance();

private:
	ThirdEasyLogger();
    ~ThirdEasyLogger();
    //删掉定义，防止后门注入
    ThirdEasyLogger(const ThirdEasyLogger &sg) =delete ;
    ThirdEasyLogger &operator=(const ThirdEasyLogger &sg)=delete ;

public:
    void ThirdEasyLoggerSet();
    void write_log(const QString &str);

};

#endif
