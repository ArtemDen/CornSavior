#include "Object.h"

#include <math.h>
#include <QGuiApplication>
#include <QScreen>

// Коэффициент замедления времени
const double cdTimeCoeff = 0.8;
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
}
//-------------------------------------------------------------------------------------------------
Object::~Object()
{
}
//-------------------------------------------------------------------------------------------------
void Object::vUpdateCoord()
{
  _dCurTime += cdTimeCoeff * (ciInterval / 1000.);
}
//-------------------------------------------------------------------------------------------------
