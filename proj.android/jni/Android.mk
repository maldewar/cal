LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
				../../Classes/AppDelegate.cpp \
				../../Classes/HelloWorldScene.cpp \
				../../Classes/LevelScene.cpp \
				../../Classes/util/jsoncpp.cpp \
				../../Classes/util/b2dJson.cpp \
				../../Classes/util/b2dJsonImage.cpp \
				../../Classes/util/Box2DDebugDraw.cpp \
				../../Classes/util/CMath.cpp \
				../../Classes/util/PathUtil.cpp \
				../../Classes/util/IdUtil.cpp  \
				../../Classes/engine/RayCastTool.cpp \
				../../Classes/component/ContactComponent.cpp \
				../../Classes/component/AIComponentCmd.cpp \
				../../Classes/component/AIComponentSeekCmd.cpp \
				../../Classes/component/AIComponent.cpp \
				../../Classes/model/ImageNode.cpp \
				../../Classes/model/ImageBody.cpp \
				../../Classes/model/Entity.cpp \
				../../Classes/model/Entry.cpp \
				../../Classes/model/Exit.cpp \
				../../Classes/model/Unit.cpp \
				../../Classes/model/Area.cpp \
				../../Classes/model/Gravitron.cpp \
				../../Classes/model/ctrl/WheelCtrl.cpp \
				../../Classes/model/LayerDef.cpp \
				../../Classes/model/WorldLayerDef.cpp \
				../../Classes/model/BgLayerDef.cpp \
				../../Classes/model/SceneDef.cpp \
				../../Classes/model/ActSceneDef.cpp \
				../../Classes/model/LevelSceneDef.cpp \
				../../Classes/model/Level.cpp \
				../../Classes/system/ContactSystem.cpp \
				../../Classes/layer/BaseLayer.cpp \
				../../Classes/layer/UILayer.cpp \
				../../Classes/layer/BasicUILayer.cpp \
				../../Classes/layer/MainMenuUILayer.cpp \
				../../Classes/layer/ActMenuLayer.cpp \
				../../Classes/layer/WorldActLayer.cpp \
				../../Classes/layer/BackgroundLayer.cpp \
				../../Classes/layer/BasicRUBELayer.cpp \
				../../Classes/layer/WorldLevelLayer.cpp \
				../../Classes/layer/WorldLevelCtrlLayer.cpp \
				../../Classes/layer/GravityCtrlLayer.cpp \
				../../Classes/layer/SelectCtrlLayer.cpp \
				../../Classes/layer/WorldLevelUILayer.cpp \
				../../Classes/layer/WorldLevelDebugLayer.cpp \
				../../Classes/layer/WorldLevelStatisticsLayer.cpp \
				../../Classes/scene/BaseScene.cpp \
				../../Classes/scene/MainMenuScene.cpp \
				../../Classes/scene/ActMenuScene.cpp \
				../../Classes/scene/ActScene.cpp \
				../../Classes/scene/WorldLevelScene.cpp \
				../../Classes/manager/StorageManager.cpp \
				../../Classes/manager/ConfigurationManager.cpp \
				../../Classes/manager/UnitManager.cpp \
				../../Classes/factory/BodyFactory.cpp \
				../../Classes/factory/EntityFactory.cpp \
				../../Classes/factory/SceneFactory.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)
$(call import-module,Box2D)
$(call import-module,editor-support/cocostudio)
$(call import-module,extensions)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)
