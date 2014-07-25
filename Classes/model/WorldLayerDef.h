#ifndef __WORLD_LAYER_DEF_H__
#define __WORLD_LAYER_DEF_H__

#include <string>
#include "LayerDef.h"

class WorldLayerDef : public LayerDef
{
protected:
  std::string m_path;
  bool m_isMain;

public:
    /**
     * Class constructor.
     */
    WorldLayerDef(void);
    /**
     * Class destructor.
     */
    virtual ~WorldLayerDef(void);
    /**
     * Returns an instance of this class.
     * @return WorldLayerDef instance.
     */
    static WorldLayerDef* create();
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init();
    virtual int getType();
    virtual bool isMain();
    virtual void setIsMain(bool isMain);
    virtual std::string getPath();
    virtual void setPath(std::string path);
};

#endif // __WORLD_LAYER_DEF_H__
