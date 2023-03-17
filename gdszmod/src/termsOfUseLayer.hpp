#ifndef __termsOfUseLayer_H__
#define __termsOfUseLayer_H__

#include <cocos2d.h>
#include <gd.h>
using namespace cocos2d;
using namespace gd;
using namespace cocos2d::extension;

class termsOfUseLayer : public gd::FLAlertLayer {
protected:
	virtual bool init();

	void onOk(cocos2d::CCObject*);
	void onTermsOfUse(cocos2d::CCObject*);
	void onPrivacyPolicy(cocos2d::CCObject*);

public:
	static termsOfUseLayer* create();
};

#endif