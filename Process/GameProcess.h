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

  /** Удалить объект орудия */
  Q_INVOKABLE void vDeleteObject(int iID);

  /** Возвращает признак пересечения объектов */
  bool bIsCrossing(const std::shared_ptr<Object>& croFirstObject, const std::shared_ptr<Object>& croSecondObject) const;

signals:

  /** Отправить координаты объекта в QML */
  void sigSendCoordToQML(int ID, double X, double Y);

  /** Сигнал об уничтожении объекта еды */
  void sigFoodIsEaten(int ID);

public slots:

  /** Проверка пересечения объектов */
  void slotCheckingCross(int ID,  double X, double Y);

private:

  /** Вектор объектов */
  std::vector<std::shared_ptr<Object>> _vecObjects;

};
//-------------------------------------------------------------------------------------------------
#endif // GAMEPROCESS_H
