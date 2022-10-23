#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H
//-------------------------------------------------------------------------------------------------
#include <QObject>
#include <memory>

#include "Object.h"
//-------------------------------------------------------------------------------------------------
/** Класс процесса */
class GameProcess : public QObject
{
  Q_OBJECT

public:

  /** Конструктор */
  GameProcess();

  /** Деструктор */
  ~GameProcess();

  /** Создать объект орудия */
  Q_INVOKABLE void vCreateObject(int iObjType, int iID, double dStartX, double dStartY, int iWidth, int iHeight, double dV0, double dParam);

  /** Возвращает признак пересечения объектов */
  bool bIsCrossing(const std::shared_ptr<Object>& croFirstObject, const std::shared_ptr<Object>& croSecondObject) const;

signals:

  /** Отправить координаты объекта в QML */
  void sigSendCoordToQML(int ID, double X, double Y);

  /** Сигнал об уничтожении объекта еды */
  void sigFoodIsEaten(int ID);

  /** Сигнал об удалении с QML */
  Q_INVOKABLE void sigDeleteObject(int ID);

public slots:

  /** Удалить объект орудия */
  Q_INVOKABLE void slotDeleteObject(int iID);

private slots:

  /** Событие таймера */
  void timerEvent(QTimerEvent *event);

private:

  /** Проверка пересечения объектов */
  void vCheckingCross(int ID,  double X, double Y);

  /** Вектор объектов */
  std::map<int, std::shared_ptr<Object>> _mapObjects;

};
//-------------------------------------------------------------------------------------------------
#endif // GAMEPROCESS_H
