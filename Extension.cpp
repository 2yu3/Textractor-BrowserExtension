#include "Extension.h"
#include <qobject.h>
#include <qstring.h>
#include <QtWebSockets/qwebsocket.h>
#include <QtWebSockets/qwebsocketserver.h>
#include <qvector.h>

const quint16 DEFAULT_PORT = 1234;

class WebSocketSrv : public QObject
{
public:
	WebSocketSrv(quint16 port) :
		_srv(new QWebSocketServer(QStringLiteral("Textractor Server"),
			QWebSocketServer::NonSecureMode, this))
	{
		if (this->_srv->listen(QHostAddress::Any, port)) {
			connect(this->_srv, &QWebSocketServer::newConnection,
				this, &WebSocketSrv::eventListenerNewConnection);
		}
	}

	WebSocketSrv::~WebSocketSrv()
	{
		this->_srv->close();
		qDeleteAll(this->_clients.begin(), this->_clients.end());
	}

	void send(const std::wstring& msg) const
	{
		QString s = QString::fromWCharArray(msg.c_str());
		for (auto& x : this->_clients)
		{
			x->sendTextMessage(s);
		}
	}

private:
	void eventListenerNewConnection()
	{
		QWebSocket* client = this->_srv->nextPendingConnection();

		connect(client, &QWebSocket::disconnected, this, &WebSocketSrv::eventListenerClientDisconnected);

		this->_clients << client;
		client->sendTextMessage(QString("Hello from Textractor!"));
	}

	void eventListenerClientDisconnected()
	{
		QWebSocket* client = qobject_cast<QWebSocket*>(sender());
		if (client) {
			this->_clients.removeAll(client);
			client->deleteLater();
		}
	}
private:
	QWebSocketServer* _srv;
	QVector<QWebSocket*> _clients;
} srv(DEFAULT_PORT);

bool ProcessSentence(std::wstring& sentence, SentenceInfo sentenceInfo)
{
	if (sentenceInfo["current select"])
		QMetaObject::invokeMethod(&srv, [sentence]{ srv.send(sentence); });

	return false;
}