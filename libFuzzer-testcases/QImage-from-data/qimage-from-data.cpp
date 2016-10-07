#include <QtCore>
#include <QtGui>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    QImage image = QImage::fromData(Data, Size);
    qDebug() << "image is null?" << image.isNull();
    return 0;
}
