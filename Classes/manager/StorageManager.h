#ifndef __STORAGE_MANAGER__
#define __STORAGE_MANAGER__

#include <vector>
#include <string>

#include "cocos2d.h"

class StorageManager : public cocos2d::Ref
{
protected:
  static std::string s_selected_slot;
  static std::string s_slot_pct;
  static std::string s_slot_act;
  static std::string s_slot_lvl;
  static std::string s_slot_time;

  std::string m_slot_prefix;

public:
  static StorageManager* getInstance();
  static void destroyInstance();
  virtual bool init();
  virtual float getPercentage();
  virtual int getAct();
  virtual int getLevel();
  virtual int getTime();
  virtual void setPercentage(float percentage);
  virtual void setAct(int act);
  virtual void setLevel(int level);
  virtual void setTime(int time);

private:
  StorageManager(void);
  ~StorageManager(void);
  void resetSlot();

};

#endif
