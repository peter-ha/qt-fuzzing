#include <QtCore>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    QByteArray byteArrayData(reinterpret_cast<const char *>(Data), Size);
    QJsonDocument document = QJsonDocument::fromJson(byteArrayData);
    // ### test fromRawData as well
    if (document.isArray()) {
        QJsonArray array = document.array();
//        qDebug() << array.toVariantList();
    } else if (document.isObject()) {
        QJsonObject object = document.object();
//        qDebug() << object.toVariantMap();
    } else if (document.isEmpty()) {
//        qDebug() << "document is empty";
    } else if (document.isNull()) {
//        qDebug() << "document is null";
    }
    return 0;
}
