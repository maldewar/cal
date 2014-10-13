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

SceneDef* SceneFactory::getSceneDef(const char* filename, std::string& errorMsg) {
  if (!filename)
    return nullptr;

  std::string fullpath = cocos2d::FileUtils::sharedFileUtils()->fullPathForFilename(filename);
  Json::Value root;
  Json::Reader reader;
  ssize_t fileSize = 0;
  unsigned char* fileData = cocos2d::FileUtils::sharedFileUtils()->getFileData(fullpath, "r", &fileSize);
  std::string jsonContent;
  jsonContent.assign(reinterpret_cast<const char*>(fileData), fileSize);

  if (!reader.parse(jsonContent, root)) {
    errorMsg = std::string("Failed to parse '") + std::string(filename) + std::string(" : ") + reader.getFormatedErrorMessages();
    return nullptr;
  }

  SceneDef* sceneDef = new SceneDef();
  sceneDef->setId(root.get("id", "").asString());
  sceneDef->setTitle(root.get("title", "").asString());
  sceneDef->setUnitsRequired(root.get("unitsRequired", 0).asInt());
  const Json::Value jarrLayerDefs = root["layers"];
  for (Json::ValueIterator itr = jarrLayerDefs.begin(); itr != jarrLayerDefs.end(); itr++) {
    const Json::Value jLayerDef = *itr;
    LayerDef* layerDef = buildLayerDef(jLayerDef);
    if (layerDef) {
      sceneDef->addLayerDef(layerDef);
    }
  }
  return sceneDef;
}

LayerDef* SceneFactory::buildLayerDef(Json::Value jValue) {
  std::string layerType = jValue.get("type", "").asString();
  if (layerType.compare("world") == 0) {
    WorldLayerDef* layerDef = new WorldLayerDef();
    layerDef->setPath(jValue.get("path", "").asString());
    layerDef->setIsMain(jValue.get("isMain", false).asBool());
    buildBaseLayerDef(layerDef, jValue);
    return layerDef;
  } else if (layerType.compare("bg") == 0) {
    BgLayerDef* layerDef = new BgLayerDef();
    layerDef->setBgType(jValue.get("bgType",0).asInt());
    buildBaseLayerDef(layerDef, jValue);
    return layerDef;
  }
  return nullptr;
}

void SceneFactory::buildBaseLayerDef(LayerDef* layerDef, Json::Value jValue) {
  layerDef->setId(jValue.get("id", "").asString());
  layerDef->setIndex(jValue.get("zIndex", 0).asInt());
  layerDef->setDistance(jValue.get("distance", 0).asDouble());
  layerDef->setIsEnabled(jValue.get("enabled", true).asBool());
}

WorldLevelLayer* SceneFactory::buildWorldLevelLayer(WorldLayerDef* worldLayerDef) {
  if (worldLayerDef) {
    WorldLevelLayer* worldLevelLayer = WorldLevelLayer::create(worldLayerDef->getPath());
    worldLevelLayer->setMain(worldLayerDef->isMain());
    return worldLevelLayer;
  }
  return nullptr;
}

BackgroundLayer* SceneFactory::buildBackgroundLayer(BgLayerDef* bgLayerDef) {
  if (bgLayerDef) {
    BackgroundLayer* backgroundLayer = BackgroundLayer::create(bgLayerDef->getBgType());
    return backgroundLayer;
  }
  return nullptr;
}
