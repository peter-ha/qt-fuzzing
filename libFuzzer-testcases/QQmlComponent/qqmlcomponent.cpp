#include <QtCore>
#include <QtQml>
#include <QtQuick>

QCoreApplication *globalApp;

extern "C" int LLVMFuzzerInitialize(int* argc, char*** argv) {
    globalApp = new QCoreApplication(*argc, *argv);
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    QByteArray byteArrayData(reinterpret_cast<const char *>(Data), Size);
    QQmlEngine engine;
    QQmlComponent component(&engine);
    component.setData(byteArrayData, QUrl());
    return 0;
}
