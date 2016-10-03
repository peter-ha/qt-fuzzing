#include <QtCore>
#include <QtNetwork>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    int argc = 1;
    char *argv[] = {"dummy"};
    QCoreApplication app(argc, argv);
    // ### We should rather run one global server and not create one for each run
    QTcpServer server;
    QHostAddress address(QHostAddress::LocalHost);
    server.listen(address);
    QUrl serverUrl(QStringLiteral("http://") + server.serverAddress().toString() + QStringLiteral(":") + QString::number(server.serverPort()) + QStringLiteral("/"));
    QObject::connect(&server, &QTcpServer::newConnection, [&server, Data, Size]() {
        while (server.hasPendingConnections()) {
            QTcpSocket *socket = server.nextPendingConnection();
            socket->waitForReadyRead();
            socket->write(reinterpret_cast<const char *>(Data), Size);
            socket->waitForBytesWritten();
            socket->disconnectFromHost();
            QObject::connect(socket, &QTcpSocket::disconnected, &QTcpSocket::deleteLater);
        }
    });
    QNetworkRequest request(serverUrl);
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(request);
    QObject::connect(reply, &QNetworkReply::finished, &app, &QCoreApplication::quit);
    app.exec();
    qDebug() << "reply error:" << reply->errorString();
    delete reply;
    return 0;
}
