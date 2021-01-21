#include "ScreenCapture.h"
#include <QGuiApplication>
#include <QPainter>
#include <QScreen>
#include <QJsonObject>
#include <QJsonDocument>

#include "Tools/Tools.h"




ScreenCapture &ScreenCapture::getInstance()
{
    static ScreenCapture instance;
    return instance;
}

void ScreenCapture::startScreenshot()
{
    /*截取所有屏幕*/
    QPixmap screenshot=allScreenshot();
    screenshot.save("test.png","png",100);
    /*打开新窗口*/
    openScreenshotWindow(screenshot);
    /*设置图片*/
    m_pixmapProvider->setScreenshot(screenshot);
    emit sgRefeshPixmap();
}

ScreenCapture::ScreenCapture()
{
    m_pixmapProvider=new PixmapProvider();

    /*很奇怪有时候会获取空白的界面*/
//    dxgiInit();
}

ScreenCapture::~ScreenCapture()
{
    closeScreenshotWindow();

    /*很奇怪有时候会获取空白的界面*/
//    m_d3dDevice->Release();
//    m_d3dContext->Release();
}

QPixmap ScreenCapture::allScreenshot()
{
        auto screens = QGuiApplication::screens();
        if(screens.isEmpty()){
            return QPixmap();
        }

//        QList<QPixmap> scrs;
//        int w = 0, h = 0, p = 0;
//        foreach (auto scr, screens) {
//            /*获取窗口起点位置，左上窗口的左上角就是起点*/
//            if(scr->geometry().topLeft().x()<m_startPoint.x()){
//                m_startPoint=scr->geometry().topLeft();
//            }else if(scr->geometry().topLeft().y()<m_startPoint.y()){
//                m_startPoint=scr->geometry().topLeft();
//            }
//            QPixmap pix = scr->grabWindow(0);
//            w += static_cast<int>(pix.width()/pix.devicePixelRatio());
//            h += static_cast<int>(pix.height()/pix.devicePixelRatio());
//            /*TODO 这里需要做排序，目前这里有问题*/
//            scrs << pix;
//        }
//        m_screenshot=QPixmap(w, h);
//        QPainter painter(&m_screenshot);
//        m_screenshot.fill(Qt::black);
//        foreach (auto scr, scrs) {
//            painter.drawPixmap(QPoint(p, 0), scr);
//            p += static_cast<int>(scr.width()/scr.devicePixelRatio());
//        }
//        return;

        m_startPoint=screens[1]->geometry().topLeft();
        return screens[1]->grabWindow(0);



      /*很奇怪有时候会获取空白的界面*/

//    IDXGIResource *desktopRes;
//    DXGI_OUTDUPL_FRAME_INFO frameInfo;
//    m_duplication->ReleaseFrame();
//    HRESULT hr = m_duplication->AcquireNextFrame(10000, &frameInfo, &desktopRes);
//    if (FAILED(hr)) {
//         qDebug()<< "Failed to AcquireNextFrame ErrorCode = " + QString::number(uint(hr), 16);
//        return QPixmap();
//    }

//    return copyToImage(desktopRes);
}

QPixmap ScreenCapture::copyToImage(IDXGIResource *res)
{
    D3D11_TEXTURE2D_DESC desc;
    ID3D11Texture2D *textrueRes = nullptr;
    HRESULT hr = res->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void **>(&textrueRes));
    if (FAILED(hr)) {
       qDebug() << "Failed to ID3D11Texture2D result =" << uint(hr);
       return QPixmap();
    }
    textrueRes->GetDesc(&desc);

    D3D11_TEXTURE2D_DESC texDesc;
    ZeroMemory(&texDesc, sizeof(texDesc));
    texDesc.Width = desc.Width;
    texDesc.Height = desc.Height;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.SampleDesc.Count = 1;
    texDesc.SampleDesc.Quality = 0;
    texDesc.Usage = D3D11_USAGE_STAGING;
    texDesc.Format = desc.Format;
    texDesc.BindFlags = 0;
    texDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    texDesc.MiscFlags = 0;
    ID3D11Texture2D *texture=nullptr;
    m_d3dDevice->CreateTexture2D(&texDesc, nullptr, &texture);
    m_d3dContext->CopyResource(texture, textrueRes);

    IDXGISurface1 *surface = nullptr;
    hr = texture->QueryInterface(__uuidof(IDXGISurface1), reinterpret_cast<void **>(&surface));
    if (FAILED(hr)) {
       qDebug() << "Failed to QueryInterface IDXGISurface1 ErrorCode =" << uint(hr);
       return QPixmap();
    }

    DXGI_MAPPED_RECT map;
    surface->Map(&map, DXGI_MAP_READ);
    QPixmap pixmap = QPixmap::fromImage(QImage(static_cast<uchar *>(map.pBits),
                                       int(desc.Width), int(desc.Height), QImage::Format_ARGB32));
    surface->Unmap();
    surface->Release();
    texture->Release();

    return pixmap;
}

void ScreenCapture::openScreenshotWindow(const QPixmap &screenshot)
{
    closeScreenshotWindow();
    QJsonObject json;
    json["objectName"]=m_screenshotWindow;
    QRect rect=screenshot.rect();
    json["x"]=m_startPoint.x();
    json["y"]=m_startPoint.y();
    json["minimumWidth"]=rect.width()/Tools::getInstance().getZoomFactor();
    json["minimumHeight"]=rect.height()/Tools::getInstance().getZoomFactor();
    emit sgOpenWindow(nullptr,QJsonDocument(json).toJson());
    m_isOpenWindow=true;
}

void ScreenCapture::closeScreenshotWindow()
{
    if(m_isOpenWindow){
        emit sgCloseWindow(m_screenshotWindow);
        m_isOpenWindow=false;
    }
}

bool ScreenCapture::dxgiInit()
{
    D3D_FEATURE_LEVEL feat = D3D_FEATURE_LEVEL_11_0;
    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &m_d3dDevice, &feat, &m_d3dContext);
    if (FAILED(hr)) {
        qDebug()<< "Failed to D3D11CreateDevice ErrorCode = " + QString::number(uint(hr), 16);
        return false;
    }

    IDXGIDevice *dxgiDevice = nullptr;
    hr = m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
    if(FAILED(hr)) {
        qDebug()<< "Failed to QueryInterface IDXGIOutput6 ErrorCode = " + QString::number(uint(hr), 16);
        return false;
    }

    IDXGIAdapter *dxgiAdapter = nullptr;
    hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter));
    dxgiDevice->Release();
    if (FAILED(hr)) {
        qDebug()<<"Failed to Get IDXGIAdapter ErrorCode = " + QString::number(uint(hr), 16);
        return false;
    }

    IDXGIOutput *dxgiOutput = nullptr;
    QVector<IDXGIOutput *> outputs;
    for(uint i = 0; dxgiAdapter->EnumOutputs(i, &dxgiOutput) != DXGI_ERROR_NOT_FOUND; ++i) {
        outputs.push_back(dxgiOutput);
    }
    dxgiAdapter->Release();
    if (outputs.size() > 0) dxgiOutput = outputs.at(0);
    else {
        qDebug()<< "Failed to IDXGIOutput is Empty!";
        return false;
    }

    IDXGIOutput6 *dxgiOutput6 = nullptr;
    hr = dxgiOutput->QueryInterface(__uuidof(IDXGIOutput6), reinterpret_cast<void**>(&dxgiOutput6));
    dxgiOutput->Release();
    if (FAILED(hr)) {
        qDebug()<<"Failed to QueryInterface IDXGIOutput6 ErrorCode = " + QString::number(uint(hr), 16);
        return false;
    }

    hr = dxgiOutput6->DuplicateOutput(m_d3dDevice, &m_duplication);
    dxgiOutput6->Release();
    if (FAILED(hr)) {
        qDebug()<<"Failed to DuplicateOutput ErrorCode = " + QString::number(uint(hr), 16);
        return false;
    }

    DXGI_OUTDUPL_DESC desc;
    m_duplication->GetDesc(&desc);
    if (desc.DesktopImageInSystemMemory) {
        qDebug() << "Desc: CPU shared with GPU";
    } else {
        qDebug() << "Desc: CPU not shared with GPU";
    }

    return true;
}

PixmapProvider *ScreenCapture::getPixmapProvider()
{
    return m_pixmapProvider;
}

PixmapProvider::PixmapProvider():QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

void PixmapProvider::setScreenshot(const QPixmap &screenshot)
{
    m_screenshot=screenshot;
}

QPixmap PixmapProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id)
    Q_UNUSED(size)
    Q_UNUSED(requestedSize)
    return m_screenshot;
}
