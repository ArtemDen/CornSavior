#ifndef AIM_H
#define AIM_H
//-------------------------------------------------------------------------------------------------
#include "Object.h"
//-------------------------------------------------------------------------------------------------
/** Класс модели цели */
class Aim : public Object
{

public:

  /** Конструктор */
  Aim(int iID, double dStartX, double dStartY, int iWidth, int iHeight, double dV0, int iAmplidude);

  /** Задать признак сбития */
  void vSetHitSign(bool bIsHit) {
    _bIsHit = bIsHit;
    _dCurTime = 0.;
  }

  /** Получить признак сбития */
  bool bGetHitSign() const {
    return _bIsHit;
  }

protected slots:

  /** Расчет координат на текущий момент времени */
  void slotUpdateCoord() override;

private:

  /** Амплитуда */
  int _iAmplitude;

  /** Признак сбития */
  bool _bIsHit;

};
//-------------------------------------------------------------------------------------------------
#endif // AIM_H
