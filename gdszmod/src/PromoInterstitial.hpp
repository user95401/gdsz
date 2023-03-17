#ifndef __PromoInterstitial_H__
#define __PromoInterstitial_H__

#include <cocos2d.h>
#include <gd.h>
using namespace cocos2d;
using namespace gd;
using namespace cocos2d::extension;
#include "utils.hpp"

class PromoInterstitial : public gd::FLAlertLayer {
protected:
	virtual bool init();

	void onClose(cocos2d::CCObject*);
	void onPopup(cocos2d::CCObject*);

public:
	static PromoInterstitial* create();
};

#endif