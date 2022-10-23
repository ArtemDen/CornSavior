#include "GameProcess.h"
#include "Weapon.h"
#include "Aim.h"
#include "Food.h"
//-------------------------------------------------------------------------------------------------
GameProcess::GameProcess()
{
  startTimer(ciInterval);
  connect(this, SIGNAL(sigDeleteObject(int)), this, SLOT(slotDeleteObject(int)), Qt::QueuedConnection);
}
//-------------------------------------------------------------------------------------------------
GameProcess::~GameProcess()
{
  _mapObjects.clear();
}
//-------------------------------------------------------------------------------------------------
void GameProcess::vCreateObject(int iObjType, int iID, double dStartX, double dStartY, int iWidth, int iHeight, double dV0, double dParam)
{
  std::shared_ptr<Object> poObject;
  Const::EnObjType enObjType = static_cast<Const::EnObjType>(iObjType);

  switch(enObjType) {

    case Const::EnWeapon: {
      poObject = std::make_shared<Weapon>(iID, dStartX, dStartY, iWidth, iHeight, dV0, dParam);
      break;
    }

    case Const::EnAim: {
      poObject = std::make_shared<Aim>(iID, dStartX, dStartY, iWidth, iHeight, dV0, static_cast<int>(dParam));
      break;
    }

    case Const::EnFood: {
      poObject = std::make_shared<Food>(iID, dStartX, dStartY, iWidth, iHeight, dV0);
      break;
    }

    default:
      break;
  }

  if (poObject) {
    _mapObjects[iID] = poObject;
    connect(_mapObjects[iID].get(), SIGNAL(sigSendCurrentCoord(int,double,double)), this, SIGNAL(sigSendCoordToQML(int,double,double)));
  }
}
//-------------------------------------------------------------------------------------------------
void GameProcess::slotDeleteObject(int iID)
{
  auto it = _mapObjects.find(iID);
  if (it != _mapObjects.end()) {
    disconnect(it->second.get(), SIGNAL(sigSendCurrentCoord(int, double, double)), this, SIGNAL(sigSendCoordToQML(int, double, double)));
    qDebug() << "Удаление: " << iID;
    _mapObjects.erase(it);
  }
}
//-------------------------------------------------------------------------------------------------
void GameProcess::vCheckingCross(int ID,  double X, double Y)
{
  Q_UNUSED(X)
  Q_UNUSED(Y)

  auto it = _mapObjects.find(ID);
  if (it != _mapObjects.end() && it->second.get()->enGetType() == Const::EnAim) {
    std::shared_ptr<Aim> poAim = std::dynamic_pointer_cast<Aim>(it->second);
    if (poAim && !poAim->bGetHitSign()) {
      for (const std::pair<const int, std::shared_ptr<Object>>& croPair : _mapObjects) {
        if (croPair.second->enGetType() == Const::EnWeapon && bIsCrossing(it->second, croPair.second)) { // Орудие попало в цель
          poAim->vSetHitSign(true);
          break;
        }
        else if (croPair.second->enGetType() == Const::EnFood && bIsCrossing(it->second, croPair.second)) { // Цель съела еду
          emit sigFoodIsEaten(croPair.second->iGetID());
          break;
        }
      }
    }
  }
}
//-------------------------------------------------------------------------------------------------
bool GameProcess::bIsCrossing(const std::shared_ptr<Object>& croFirstObject, const std::shared_ptr<Object>& croSecondObject) const
{
  // Разность координат
  double dDiffX = croFirstObject.get()->croGetCoord().first - croSecondObject.get()->croGetCoord().first;
  double dDiffY = croFirstObject.get()->croGetCoord().second - croSecondObject.get()->croGetCoord().second;

  // Коэффициент учета неквадртаной формы
  const double cdCrossCoeff = 1.25;

  // Пересечение
  bool bIsCrossingLeft = (dDiffX < croSecondObject.get()->croGetSize().first / cdCrossCoeff);
  bool bIsCrossingRight = (dDiffX > -croFirstObject.get()->croGetSize().first / cdCrossCoeff);
  bool bIsCrossingUp = (dDiffY < croSecondObject.get()->croGetSize().second / cdCrossCoeff);
  bool bIsCrossingDown = (dDiffY > -croFirstObject.get()->croGetSize().second / cdCrossCoeff);

  return bIsCrossingLeft && bIsCrossingRight && bIsCrossingUp && bIsCrossingDown;
}
//-------------------------------------------------------------------------------------------------
void GameProcess::timerEvent(QTimerEvent *event)
{
  Q_UNUSED(event)
  qDebug() << "Таймер:" << _mapObjects.size();
  for (const std::pair<const int, std::shared_ptr<Object>>& croPair : _mapObjects) {
    qDebug() << "Обновление координат:" << croPair.second.get()->iGetID();
    croPair.second.get()->slotUpdateCoord();
    vCheckingCross(croPair.second.get()->iGetID(), croPair.second.get()->croGetCoord().first, croPair.second.get()->croGetCoord().second);
  }
}
//--------------------------------------------------------------------------------------------------
