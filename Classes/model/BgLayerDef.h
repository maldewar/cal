#ifndef __BG_LAYER_DEF_H__
#define __BG_LAYER_DEF_H__

#include <string>
#include "LayerDef.h"

class BgLayerDef : public LayerDef
{
protected:
  int m_bgType;

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
};

#endif // __BG_LAYER_DEF_H__
