#include "SceneFactory.h"
#include <istream>
#include <fstream>
#include "cocos2d.h"

static SceneFactory* s_sharedSceneFactory = nullptr;

SceneFactory* SceneFactory::getInstance() {
  if (s_sharedSceneFactory == nullptr) {
    s_sharedSceneFactory = new SceneFactory();
    if (!s_sharedSceneFactory || !s_sharedSceneFactory->init()) {
      CC_SAFE_DELETE(s_sharedSceneFactory);
    }
  }
  return s_sharedSceneFactory;
}

void SceneFactory::destroyInstance() {
  CC_SAFE_RELEASE_NULL(s_sharedSceneFactory);
}

SceneFactory::SceneFactory(void) {
}

SceneFactory::~SceneFactory(void) {
}

bool SceneFactory::init() {
  return true;
}

SceneDef* SceneFactory::getSceneDef(const char* filename) {
  SceneDef *sceneDef = new SceneDef();
  if (!buildSceneDef(sceneDef, filename)) {
    return nullptr;
  }
  return sceneDef;
}

ActSceneDef* SceneFactory::getActSceneDef(const char* filename) {
  ActSceneDef *actSceneDef = new ActSceneDef();
  if (!buildSceneDef(actSceneDef, filename)) {
    return nullptr;
  }
  if (!buildActSceneDef(actSceneDef, filename)) {
    return nullptr;
  }
  return actSceneDef;
}

LevelSceneDef* SceneFactory::getLevelSceneDef(const char* filename) {
  LevelSceneDef *levelSceneDef = new LevelSceneDef();
  if (!buildSceneDef(levelSceneDef, filename)) {
    return nullptr;
  }
  if (!buildLevelSceneDef(levelSceneDef, filename)) {
    return nullptr;
  }
  return levelSceneDef;
}

LayerDef* SceneFactory::getLayerDef(Json::Value& jLayerDef) {
  LayerDef *layerDef = new LayerDef();
  if (!buildLayerDef(layerDef, jLayerDef)) {
    return nullptr;
  }
  return layerDef;
}

WorldLayerDef* SceneFactory::getWorldLayerDef(Json::Value& jLayerDef) {
  WorldLayerDef* worldLayerDef = new WorldLayerDef();
  if (!buildLayerDef(worldLayerDef, jLayerDef)) {
    return nullptr;
  }
  if (!buildWorldLayerDef(worldLayerDef, jLayerDef)) {
    return nullptr;
  }
  return worldLayerDef;
}

BgLayerDef* SceneFactory::getBgLayerDef(Json::Value& jLayerDef) {
  BgLayerDef* bgLayerDef = new BgLayerDef();
  if (!buildLayerDef(bgLayerDef, jLayerDef)) {
    return nullptr;
  }
  if (!buildBgLayerDef(bgLayerDef, jLayerDef)) {
    return nullptr;
  }
  return bgLayerDef;
}

WorldLevelLayer* SceneFactory::getWorldLevelLayer(WorldLayerDef* worldLayerDef) {
  if (worldLayerDef) {
    WorldLevelLayer* worldLevelLayer = WorldLevelLayer::create(worldLayerDef->getPath());
    worldLevelLayer->setMain(worldLayerDef->isMain());
    return worldLevelLayer;
  }
  return nullptr;
}

WorldActLayer* SceneFactory::getWorldActLayer(int act, WorldLayerDef* worldLayerDef) {
  if (worldLayerDef) {
    WorldActLayer* worldActLayer = WorldActLayer::create(act, worldLayerDef->getPath());
    return worldActLayer;
  }
  return nullptr;
}

BackgroundLayer* SceneFactory::getBackgroundLayer(BgLayerDef* bgLayerDef) {
  if (bgLayerDef) {
    BackgroundLayer* backgroundLayer = BackgroundLayer::create(bgLayerDef->getBgType());
    return backgroundLayer;
  }
  return nullptr;
}

bool SceneFactory::buildSceneDef(SceneDef* sceneDef,
                                 const char* filename) {
  Json::Value root;
  std::string errorMsg;

  if (!readFile(filename, errorMsg, root)) {
    return false;
  }

  // Set base properties
  sceneDef->setId(root.get("id", "").asString());
  sceneDef->setTitle(root.get("title", "").asString());
  // Set layers
  const Json::Value jarrLayerDefs = root["layers"];
  for (Json::ValueIterator itr = jarrLayerDefs.begin(); itr != jarrLayerDefs.end(); itr++) {
    Json::Value jLayerDef = *itr;
    std::string layerType = jLayerDef.get("type", "").asString();
    if (layerType.compare("world") == 0) {
      WorldLayerDef* worldLayerDef = getWorldLayerDef(jLayerDef);
      if (worldLayerDef != nullptr)
        sceneDef->addLayerDef(worldLayerDef);
    } else if (layerType.compare("bg") == 0) {
      BgLayerDef* bgLayerDef = getBgLayerDef(jLayerDef);
      if (bgLayerDef != nullptr)
        sceneDef->addLayerDef(bgLayerDef);
    }
  }
  return true;
}

bool SceneFactory::buildActSceneDef(ActSceneDef* actSceneDef,
                                    const char* filename) {
  Json::Value root;
  std::string errorMsg;

  if (!readFile(filename, errorMsg, root)) {
    return false;
  }

  // Set base properties
  actSceneDef->setAct(root.get("act","").asString());
  return true;
}

bool SceneFactory::buildLevelSceneDef(LevelSceneDef* actSceneDef,
                                      const char* filename) { 
  Json::Value root;
  std::string errorMsg;

  if (!readFile(filename, errorMsg, root)) { 
    return false;
  } 

  // Set base properties
  return true;
}

bool SceneFactory::buildLayerDef(LayerDef* layerDef,
                                 Json::Value& jLayerDef) {
  layerDef->setId(jLayerDef.get("id", "").asString());
  layerDef->setIsMain(jLayerDef.get("isMain", false).asBool());
  layerDef->setWidth(jLayerDef.get("width", 0.0f).asDouble());
  layerDef->setHeight(jLayerDef.get("height", 0.0f).asDouble());
  layerDef->setIndex(jLayerDef.get("zIndex", 0).asInt());
  layerDef->setIsEnabled(jLayerDef.get("enabled", true).asBool());
  return true;
}

bool SceneFactory::buildWorldLayerDef(WorldLayerDef* worldLayerDef,
                                      Json::Value& jLayerDef) {
  worldLayerDef->setPath(jLayerDef.get("path", "").asString());
  worldLayerDef->setIsMain(jLayerDef.get("isMain", false).asBool());
  return true;
}

bool SceneFactory::buildBgLayerDef(BgLayerDef* bgLayerDef,
                                   Json::Value& jLayerDef) {
  bgLayerDef->setBgType(jLayerDef.get("bgType", 0).asInt());
  return true;
}

bool SceneFactory::readFile(const char* filename,
                            std::string& errorMsg,
                            Json::Value& root) {
  if (!filename)
    return false;
  std::string fullpath = cocos2d::FileUtils::getInstance()->fullPathForFilename(filename);
  Json::Reader reader;
  ssize_t fileSize = 0;
  unsigned char* fileData = cocos2d::FileUtils::getInstance()->getFileData(fullpath, "r", &fileSize);
  std::string jsonContent;
  jsonContent.assign(reinterpret_cast<const char*>(fileData), fileSize);
  
  if (!reader.parse(jsonContent, root)) {
    errorMsg = std::string("Failed to parse '") + std::string(filename) + std::string(" : ") + reader.getFormatedErrorMessages();
    return false;
  }
  return true;
}
