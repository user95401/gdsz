#include "PromoInterstitial.hpp"

bool PromoInterstitial::init() {
	if (!this->initWithColor({ 0, 0, 0, 75 })) return false;
	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);
	
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	m_pLayer = CCLayer::create();
	this->addChild(m_pLayer);
	m_pButtonMenu = CCMenu::create();
	m_pLayer->addChild(m_pButtonMenu, 5);
	m_pButtonMenu->setTouchMode(kCCTouchesAllAtOnce);

	CCSprite* normalPopup = ModUtils::createSpriteOrPlaceholder("GJ_popup.png");
	CCSprite* selPopup = ModUtils::createSpriteOrPlaceholder("GJ_popup.png");
	selPopup->setColor({ 200,200,200 });
	CCMenuItemSprite* popupItem = CCMenuItemSprite::create(normalPopup, selPopup, this, menu_selector(PromoInterstitial::onPopup));
	//fucks m_pButtonMenu
	popupItem->setContentSize({ popupItem->getContentSize().width, popupItem->getContentSize().height - 30 });
	popupItem->setPositionY(-15.0f);
	m_pButtonMenu->addChild(popupItem);

	CCMenuItemSpriteExtra* closeBtnItem = CCMenuItemSpriteExtra::create(ModUtils::createWithSpriteFrameNameOrPlaceholder("GJ_closeBtn_001.png"), this, menu_selector(PromoInterstitial::onClose));
	closeBtnItem->setPosition({ -206.0f, 133.0f });
	m_pButtonMenu->addChild(closeBtnItem);

	return true;
}

void PromoInterstitial::onClose(cocos2d::CCObject*) {
	this->removeFromParentAndCleanup(true);
}
void PromoInterstitial::onPopup(cocos2d::CCObject*) {CCApplication::sharedApplication()->openURL("https://store.steampowered.com/app/322170/Geometry_Dash/");}

PromoInterstitial* PromoInterstitial::create() {
	PromoInterstitial* pRet = new PromoInterstitial();
	if (pRet && pRet->init()) {
		pRet->autorelease();
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}