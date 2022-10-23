#ifndef OBJECT_H
#define OBJECT_H
//-------------------------------------------------------------------------------------------------
#include <QGuiApplication>
#include <QScreen>
#include <QTimer>
#include <QPair>

typedef double x;
typedef double y;
typedef int height;
typedef int width;

// Интервал таймера
const int ciInterval = 15;

/** Пространство имен основных констант */
namespace Const {

  Q_NAMESPACE

  /** Типы объектов */
  enum EnObjType {
    EnObject = 0,
    EnWeapon = 1,
    EnAim    = 2,
    EnFood   = 3
  };
  Q_ENUM_NS(EnObjType)
}
//-------------------------------------------------------------------------------------------------
/** Класс модели абстрактного объекта */
class Object : public QObject
{
  Q_OBJECT

public:

  /** Конструктор */
  Object(int iID, double dStartX, double dStartY, int iWidth, int iHeight, double dV0);

  /** Деструктор */
  virtual ~Object();

  /** Получить идентификатор */
  int iGetID() const {
    return _iID;
  }

  /** Получить тип */
  Const::EnObjType enGetType() const {
    return _enType;
  }

  /** Получить размеры */
  const QPair<width, height>& croGetSize() const {
    return _oSize;
  }

  /** Получить текущие координаты */
  const QPair<x,y>& croGetCoord() const {
    return _oCurCoord;
  }

  /** Получить начальную скорость */
  double dGetV0() const {
    return _dV0;
  }

signals:

  /** Отправить текущее значение координат */
  void sigSendCurrentCoord(int ID, double X, double Y);

  /** Сигнал, требующий уничтожение объекта */
  void sigToDelete(int ID);

public slots:

  /** Расчет координат на текущий момент времени */
  virtual void slotUpdateCoord();

protected:

  /** Тип объекта */
  Const::EnObjType _enType;

  /** Уникальный идентификатор */
  int _iID;

  /** Текущее время, с */
  double _dCurTime;

  /** Начальная скорость, м/с */
  double _dV0;

  /** Текущие координаты, м */
  QPair<x,y> _oCurCoord;

  /** Координаты точки старта, м */
  QPair<x,y> _oStartCoord;

  /** Размеры */
  QPair<width, height> _oSize;

  /** Коэффициент ускорения свободного падения */
  const double _cdCoeffG;

};
//-------------------------------------------------------------------------------------------------
#endif // OBJECT_H
