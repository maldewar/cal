#ifndef __WORLD_LEVEL_LAYER__
#define __WORLD_LEVEL_LAYER__

#include "BasicRUBELayer.h"
#include "cocostudio/CocoStudio.h"
#include "../scene/WorldLevelScene.h"

class WorldLevelScene;

class WorldLevelLayer : public BasicRUBELayer
{
protected:
    bool m_isMain;
    WorldLevelScene* m_worldScene;
    cocos2d::Layer* m_unitLayer;
    cocos2d::Layer* m_areaLayer;
    cocos2d::Layer* m_assetLayer;
    bool m_manageTouch;

public:
    WorldLevelLayer();
    static WorldLevelLayer* create();
    virtual bool init();
    virtual std::string getFilename();
    virtual void setMain(bool isMain);
    virtual cocos2d::Point initialWorldOffset();
    virtual float initialWorldScale();
    virtual void afterLoadProcessing(b2dJson* json);
    virtual void addChild(cocos2d::Node* node);
    virtual void setWorldLevelScene(WorldLevelScene* worldScene);
    virtual WorldLevelScene* getWorldLevelScene();
    virtual void clear();
    virtual void update(float dt);
    void removeBodyFromWorld(b2Body* body);
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);

};

#endif /* __WORLD_LEVEL_LAYER__ */
