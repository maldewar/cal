#ifndef __LEVEL_NODE_H__
#define __LEVEL_NODE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Entity.h"

const int LEVEL_STATE_INACTIVE = 0;
const int LEVEL_STATE_ACTIVE   = 1;
const int LEVEL_STATE_LOCKED   = 2;

const int LEVEL_ANIM_INACTIVE = 0;
const int LEVEL_ANIM_ACTIVE   = 1;

class Level : public Entity
{
protected:
    int m_state;
    int m_level;
    std::string m_title;
    cocostudio::Armature* m_armature;

public:
    /**
     * Class constructor.
     */
    Level(void);
    /**
     * Class destructor.
     */
    virtual ~Level(void);
    /**
     * Get the identifier for this class.
     * @return Type identifier.
     */
    virtual int getType();
    static Level* create(std::string armature);
    /**
     * Returns an instance of this class.
     * @return Level instance.
     */
    static Level* create(std::string armature, bool active);
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init(std::string armature, bool active);
    int getLevel();
    void setLevel(int level);
    std::string getTitle();
    void setTitle(std::string title);
    void activate();
    void deactivate();
    bool isActive();
    virtual void update(float dt);
    virtual void select();
};

#endif // __LEVEL_NODE_H__
