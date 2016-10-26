#include <QtCore>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    QByteArray byteArrayData(reinterpret_cast<const char *>(Data), Size);
    QXmlStreamReader reader(byteArrayData);
    while (!reader.atEnd()) {
        reader.readNext();
        qDebug() << reader.tokenString();
    }
    return 0;
}
