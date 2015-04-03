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
  bool m_translateEnabled;
  bool m_rotateEnabled;
  bool m_scaleEnabled;
  float m_cameraX;
  float m_cameraY;
  float m_cameraZoom;

public:
    /**
     * Class constructor.
     */
    SceneDef(void);
    /**
     * Class destructor.
     */
    virtual ~SceneDef(void);
    virtual std::string getId();
    virtual void setId(std::string id);
    virtual std::string getTitle();
    virtual void setTitle(std::string title);
    virtual std::vector<LayerDef*> getLayerDefs();
    virtual void addLayerDef(LayerDef* layerDef);
    virtual bool isTranslateEnabled();
    virtual void setTranslateEnabled(bool isTranslateEnabled);
    virtual bool isRotateEnabled();
    virtual void setRotateEnabled(bool isRotateEnabled);
    virtual bool isScaleEnabled();
    virtual void setScaleEnabled(bool isScaleEnabled);
    virtual float getCameraX();
    virtual void setCameraX(float cameraX);
    virtual float getCameraY();
    virtual void setCameraY(float cameraY);
    virtual float getCameraZoom();
    virtual void setCameraZoom(float cameraZoom);
};

#endif // __SCENE_DEF_H__
