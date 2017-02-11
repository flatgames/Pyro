LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := pyro_static

LOCAL_MODULE_FILENAME := libpyro

LOCAL_SRC_FILES := \
	Pyro\Animations\ActionBuilder.cpp \
	Pyro\Animations\AnimationUtils.cpp \
	Pyro\Animations\ResizeTo.cpp \
	Pyro\Components\InkButton.cpp \
	Pyro\Components\InkPaper.cpp \
	Pyro\Components\Paper.cpp \
	Pyro\Components\PaperDialog.cpp \
	Pyro\Components\PaperMenu.cpp \
	Pyro\Components\RaisedButton.cpp \
	Pyro\Components\Helpers\BatchedNinePatchSprite.cpp \
	Pyro\Components\Helpers\MoverButton.cpp \
	Pyro\Components\Helpers\NormalRectangle.cpp \
	Pyro\Components\Helpers\RoundedRectangle.cpp \
	Pyro\Shadow\Blur.cpp \
	Pyro\Shadow\ShadowLayer.cpp \
	Pyro\Shadow\ShadowSprite.cpp \
	Pyro\Common.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../cocos2d \
	$(LOCAL_PATH)/../cocos2d/cocos \
	$(LOCAL_PATH)/../cocos2d/cocos/platform/android \
	$(LOCAL_PATH)/../Floreto

include $(BUILD_STATIC_LIBRARY)

