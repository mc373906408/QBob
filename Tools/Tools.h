#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>

class Tools : public QObject
{
    Q_OBJECT
public:
    static Tools& getInstance();

    /**
     * @brief imageToBase64  图片转base64
     * @param image
     * @return
     */
    QByteArray imageToBase64(const QImage& image);

private:
    Tools();

    //删掉定义，防止后门注入
    Tools(const Tools &sg) =delete ;
    Tools &operator=(const Tools &sg)=delete ;
signals:

};

#endif // TOOLS_H
