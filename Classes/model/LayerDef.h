#ifndef __LAYER_DEF_H__
#define __LAYER_DEF_H__

#include <string>
#include <vector>

const int LAYER_TYPE_WORLD = 0;
const int LAYER_TYPE_BG = 1;
const int LAYER_TYPE_FG = 2;

class LayerDef
{
protected:
  std::string m_id;
  bool m_isMain;
  int m_index;
  float m_width;
  float m_height;
  bool m_enabled;

public:
    /**
     * Class constructor.
     */
    LayerDef(void);
    /**
     * Class destructor.
     */
    virtual ~LayerDef(void);
    /**
     * Returns an instance of this class.
     * @return LayerDef instance.
     */
    static LayerDef* create();
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init();
    virtual std::string getId();
    virtual void setId(std::string id);
    virtual int getType();
    virtual bool isMain();
    virtual void setIsMain(bool isMain);
    virtual int getIndex();
    virtual void setIndex(int index);
    virtual float getWidth();
    virtual void setWidth(float width);
    virtual float getHeight();
    virtual void setHeight(float height);
    virtual bool isEnabled();
    virtual void setIsEnabled(bool enabled);
};

#endif // __LAYER_DEF_H__
