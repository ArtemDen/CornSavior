#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <ctime>

#include "GameProcess.h"
#include "Object.h"
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  // Рандомизация случайных чисел
  srand(static_cast<unsigned int>(time(nullptr)));

  app.setDesktopFileName("BrandNewApp");
  app.setApplicationDisplayName("BrandNewApp");
  qmlRegisterUncreatableMetaObject(Const::staticMetaObject, "ConstData", 1, 0, "EnObjType", "Error: only enums");

  GameProcess oGameProcess;

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("GameProcess", &oGameProcess);
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
//-------------------------------------------------------------------------------------------------
