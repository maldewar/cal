#include "Entry.h"

Entry::Entry() : Entity() {
  m_state = 0;
  m_units = 0;
  m_capacity = 0;
  m_open = false;
  m_openTimer = 5000;
  m_forceMinDistance = 0.0f;
  m_forceMaxDistance = 0.0f;
  m_forceMaxAngle = 0.0f;
  m_forceMinAngularImpulse = 0.0f;
  m_forceMaxAngularImpulse = 0.0f;
  m_state = 0;
  m_armature = nullptr;
}

Entry::~Entry() {
}

Entry* Entry::create()
{
  Entry *entry = new (std::nothrow) Entry();
  if (entry && entry->init())
  {
    entry->autorelease();
    return entry;
  }
  CC_SAFE_DELETE(entry);
  return nullptr;
}

bool Entry::init(void)
{
  /*
  cocos2d::SpriteBatchNode* spritebatch = cocos2d::SpriteBatchNode::create("sprite/entry/entry.pvr");
  cocos2d::SpriteFrameCache* cache = cocos2d::SpriteFrameCache::getInstance();
  cache->addSpriteFramesWithFile("sprite/entry/entry.plist");
  m_sprite = cocos2d::Sprite::createWithSpriteFrameName("frame0000.png");
  spritebatch->addChild(m_sprite);
  if (m_sprite) {
    m_sprite->setScale(m_sprite->getContentSize().width/(0.2 * 840));
    addChild(spritebatch);
    return true;
  }
  */

  /*
  cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/bear.ExportJson");
  m_armature = cocostudio::Armature::create("bear");
  CCLOG("..Entry::init created armature");
  m_armature->getAnimation()->playWithIndex(0);
  if (m_armature) {
    addChild(m_armature);
    return true;
  }
  */

  m_armature = cocostudio::Armature::create("entry");
  CCLOG("..Entry::init created armature");
  //m_armature->getAnimation()->playWithIndex(0);
  if (m_armature) {
    m_armature->setScale(m_armature->getContentSize().width/(0.2 * 840));
    addChild(m_armature);
    return true;
  }
  return false;
}

/*
void Entry::onEnter() {
};
*/

/*
std::string Entry::getDescription() const
{
    return StringUtils::format("<Entry | Tag = %d>", _tag);
}
*/

void Entry::setCapacity(int capacity) {
    if (capacity >= 0)
        m_capacity = capacity;
}

int Entry::getCapacity() {
    return m_capacity;
}

int Entry::getUnits() {
    return m_units;
}

void Entry::open() {
    if (m_state == ENTRY_STATE_CLOSED)
        setState(ENTRY_STATE_OPENING);
    else
        setState(ENTRY_STATE_OPEN);
}

void Entry::close() {
    if (m_state == ENTRY_STATE_OPEN)
        setState(ENTRY_STATE_CLOSING);
}

void Entry::setOpen(bool isOpen) {
    if (isOpen)
        open();
    else
        close();
}

void Entry::setOpenTimer(int openTimer) {
    m_openTimer = openTimer;
}

void Entry::setInterval(int interval) {
    if (interval >= 0) {
        m_interval = interval;
        m_units = m_capacity;
    }
}

int Entry::getInterval() {
    return m_interval;
}

void Entry::setForceMinDistance(float distance) {
    m_forceMinDistance = distance;
}

float Entry::getForceMinDistance() {
    return m_forceMinDistance;
}

void Entry::setForceMaxDistance(float distance) {
    m_forceMaxDistance = distance;
}

float Entry::getForceMaxDistance() {
    return m_forceMaxDistance;
}

void Entry::setForceMaxAngle(float angle) {
    m_forceMaxAngle = angle;
}

float Entry::getForceMaxAngle() {
    return m_forceMaxAngle;
}

void Entry::setForceMinAngularImpulse(float angularImpulse) {
    m_forceMinAngularImpulse = angularImpulse;
}

float Entry::getForceMinAngularImpulse() {
    return m_forceMinAngularImpulse;
}

void Entry::setForceMaxAngularImpulse(float angularImpulse) {
    m_forceMaxAngularImpulse = angularImpulse;
}

float Entry::getForceMaxAngularImpulse() {
    return m_forceMaxAngularImpulse;
}

/*
b2Vec2 Entry::getRandomForce() {
    b2Vec2 force;
    float angle = m_rotation + m_rotationOffset;
    if (m_forceMaxAngle > 0 || m_forceMaxDistance > 0) {
        float randomAngle = CMath::Random(0.0f, m_forceMaxAngle);
        angle = angle - m_forceMaxAngle/2 + randomAngle;
        float randomDistance = CMath::Random(m_forceMinDistance, m_forceMaxDistance);
        force.x = cos(angle) * randomDistance;
        force.y = sin(angle) * randomDistance;
    } else {
        force.x = 0;
        force.y = 0;
    }
    return force;
}
*/

void Entry::setState(int state) {
    /*
    m_state = state;
    if (m_state == ENTRY_STATE_OPENING) {
        SetAnimation(ENTRY_ANIM_OPENING);
    } else if(m_state == ENTRY_STATE_CLOSING) {
        SetAnimation(ENTRY_ANIM_CLOSING);
    }
    */
}

/*
void Entry::OnLoop() {
    if (m_state == ENTRY_STATE_CLOSED) {
        if (m_timerRef < 0 || m_timerRef + m_openTimer > SDL_GetTicks())
            return;
        m_timerRef = -1;
        Open();
    } else if (m_state == ENTRY_STATE_OPEN) {
        if (m_units > 0) {
            if (m_timerRef + m_interval < SDL_GetTicks()) {
                m_timerRef = SDL_GetTicks();
                Unit* unit = new Unit(this->GetLayer());
                unit->SetX(this->GetX());
                unit->SetY(this->GetY());
                unit->SetBody();
                ((WorldLayer*)this->GetLayer())->AddUnit(unit);
                unit->GetBody()->ApplyLinearImpulse( GetRandomForce(), unit->GetBody()->GetWorldCenter() );
                float angularImpulse = CMath::Random(m_forceMinAngularImpulse, m_forceMaxAngularImpulse);
                angularImpulse = m_forceMinAngularImpulse - m_forceMaxAngularImpulse/2 + angularImpulse;
                unit->GetBody()->ApplyAngularImpulse(angularImpulse);
                m_units--;
            }
        }
    } else if (m_state == ENTRY_STATE_OPENING) {
        if (!IsPlaying())
          Open();
    }
    LayeredElem::OnLoop();
};
*/
