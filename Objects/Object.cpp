#include "Object.h"

#include <math.h>
#include <QGuiApplication>
#include <QScreen>

// Коэффициент ускорения времени
const double cdTimeCoeff = 0.9;
//-------------------------------------------------------------------------------------------------
Object::Object(int iID, double dStartX, double dStartY, int iWidth, int iHeight, double dV0):
  _enType(Const::EnObject),
  _dCurTime(0.),
  _cdCoeffG(2.1 * QGuiApplication::primaryScreen()->geometry().width())
{
  _oStartCoord.first = dStartX;
  _oStartCoord.second = dStartY;
  _oCurCoord.first = dStartX;
  _oCurCoord.second = dStartY;

  _oSize.first = iWidth;
  _oSize.second = iHeight;

  _dV0 = dV0;
  _iID = iID;
  _oTimer.setInterval(5);
  _oTimer.start();

  connect(&_oTimer, SIGNAL(timeout()), this, SLOT(slotUpdateCoord()));
}
//-------------------------------------------------------------------------------------------------
Object::~Object()
{
  if (_oTimer.isActive()) {
    _oTimer.stop();
  }
}
//-------------------------------------------------------------------------------------------------
void Object::slotUpdateCoord()
{
  _dCurTime += cdTimeCoeff * (_oTimer.interval() / 1000.);
}
//-------------------------------------------------------------------------------------------------
