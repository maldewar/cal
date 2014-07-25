#ifndef __SCENE_DEF_H__
#define __SCENE_DEF_H__

#include <string>
#include <vector>
#include "LayerDef.h"

class SceneDef
{
protected:
  std::string m_id;
  std::string m_title;
  std::vector<LayerDef*> m_layerDefs;

public:
    /**
     * Class constructor.
     */
    SceneDef(void);
    /**
     * Class destructor.
     */
    virtual ~SceneDef(void);
    /**
     * Returns an instance of this class.
     * @return SceneDef instance.
     */
    static SceneDef* create();
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init();
    virtual std::string getId();
    virtual void setId(std::string id);
    virtual std::string getTitle();
    virtual void setTitle(std::string title);
    virtual std::vector<LayerDef*> getLayerDefs();
    virtual void addLayerDef(LayerDef* layerDef);
};

#endif // __SCENE_DEF_H__
