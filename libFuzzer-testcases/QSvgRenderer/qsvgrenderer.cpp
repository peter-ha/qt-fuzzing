#include <QtCore>
#include <QtSvg>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    QByteArray byteArrayData(reinterpret_cast<const char *>(Data), Size);
    QSvgRenderer renderer(byteArrayData);
    qDebug() << "renderer is valid?" << renderer.isValid();
    // ### We should also call render() here
    return 0;
}
