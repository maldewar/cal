#ifndef __ACT_SCENE_DEF_H__
#define __ACT_SCENE_DEF_H__

#include <string>
#include <vector>

#include "SceneDef.h"

class ActSceneDef : public SceneDef
{
protected:
  std::string m_act;

public:
    /**
     * Class constructor.
     */
    ActSceneDef(void);
    virtual std::string getAct();
    virtual void setAct(std::string act);
};

#endif // __ACT_SCENE_DEF_H__
