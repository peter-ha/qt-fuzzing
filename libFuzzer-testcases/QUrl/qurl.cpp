#include <QtCore>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    // We are implicitly testing QString here as well
    QString string = QString::fromUtf8(reinterpret_cast<const char *>(Data), Size);
    QUrl url(string);
    qDebug() << "URL is valid?" << url.isValid();
    return 0;
}
