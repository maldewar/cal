#include "AIComponentCmd.h"
#include "cocos2d.h"
#include "../util/CMath.h"

AIComponentCmd::AIComponentCmd() {
  m_type = AI_CMD_STAY;
}

AIComponentCmd::~AIComponentCmd() {
}

int AIComponentCmd::GetType() {
  return m_type;
}

void AIComponentCmd::Update(float dt, b2Body *body) {
}
