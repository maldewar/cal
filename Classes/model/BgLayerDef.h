#ifndef __BG_LAYER_DEF_H__
#define __BG_LAYER_DEF_H__

#include <string>
#include "LayerDef.h"

class BgLayerDef : public LayerDef
{
protected:
  int m_bgType;
  std::string m_color;
  std::string m_imgPath;
  bool m_imgStretch;
  float m_imgAlpha;

public:
    /**
     * Class constructor.
     */
    BgLayerDef(void);
    /**
     * Class destructor.
     */
    virtual ~BgLayerDef(void);
    /**
     * Returns an instance of this class.
     * @return BgLayerDef instance.
     */
    static BgLayerDef* create();
    /**
     * Initialization method.
     * @return True if the object is correctly initialized.
     */
    virtual bool init();
    virtual int getType();
    virtual int getBgType();
    virtual void setBgType(int bgType);
    std::string getColor();
    void setColor(std::string color);
    std::string getImgPath();
    void setImgPath(std::string path);
    bool isImgStretch();
    void setIsImgStretch(bool isImgStretch);
    float getImgAlpha();
    void setImgAlpha(float imgAlpha);
};

#endif // __BG_LAYER_DEF_H__
