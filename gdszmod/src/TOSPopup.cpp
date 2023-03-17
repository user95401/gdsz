#include "TOSPopup.hpp"

bool TOSPopup::init() {
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	if (!this->initWithColor({ 0, 0, 0, 75 })) return false;
	m_pLayer = CCLayer::create();
	this->addChild(m_pLayer);

	auto bg = CCScale9Sprite::create("GJ_square01.png", { 0.0f, 0.0f, 80.0f, 80.0f });
	bg->setContentSize({ 350.0f, 195.0f });
	bg->setPosition(winSize.width / 2, winSize.height / 2);
	m_pLayer->addChild(bg);

	m_pButtonMenu = CCMenu::create();
	m_pLayer->addChild(m_pButtonMenu,5);

	auto title = CCLabelBMFont::create("Notice", "goldFont.fnt");
	title->setScale(0.9f);
	title->setPosition(winSize.width / 2, winSize.height / 2 + 80.0f);
	m_pLayer->addChild(title);

	auto textBg = CCScale9Sprite::create("square02_001.png", { 0.0f, 0.0f, 80.0f, 80.0f });
	textBg->setPosition(winSize.width / 2, winSize.height / 2);
	textBg->setContentSize({ 320.0f, 100.0f });
	textBg->setOpacity(60);
	m_pLayer->addChild(textBg);

	auto text = CCLabelBMFont::create("By tapping \"ok\", you accept the\nTerms of Use and confirm that\nYou have read the Privacy Policy.", "bigFont.fnt", 320, kCCTextAlignmentCenter);
	m_pLayer->addChild(text);
	text->setScale(0.5f);
	text->setPosition(winSize.width / 2, winSize.height / 2);

	auto blueText1bruh = CCLabelBMFont::create("Terms of Use", "bigFont.fnt", kCCLabelAutomaticWidth, kCCTextAlignmentCenter);
	m_pButtonMenu->addChild(blueText1bruh);
	blueText1bruh->setPosition(-78.000f, 0);
	blueText1bruh->setColor({ 93, 170, 239 });
	blueText1bruh->setScale(0.5f);
	auto blueText1Btn = CCMenuItem::create(this, menu_selector(TOSPopup::onTermsOfUse));
	blueText1Btn->setContentSize({ blueText1bruh->getContentSize().width / 2, blueText1bruh->getContentSize().height / 2 });
	blueText1Btn->setPosition(blueText1bruh->getPositionX(), blueText1bruh->getPositionY());
	m_pButtonMenu->addChild(blueText1Btn);

	auto blueText2bruh = CCLabelBMFont::create("Privacy Policy", "bigFont.fnt", kCCLabelAutomaticWidth, kCCTextAlignmentCenter);
	m_pButtonMenu->addChild(blueText2bruh);
	blueText2bruh->setPosition(81.000f, -16.000f);
	blueText2bruh->setColor({ 93, 170, 239 });
	blueText2bruh->setScale(0.5f);
	auto blueText2Btn = CCMenuItem::create(this,menu_selector(TOSPopup::onPrivacyPolicy));
	blueText2Btn->setContentSize({ blueText2bruh->getContentSize().width/2, blueText2bruh->getContentSize().height / 2 });
	blueText2Btn->setPosition(blueText2bruh->getPositionX(), blueText2bruh->getPositionY());
	m_pButtonMenu->addChild(blueText2Btn);

	auto closeBtn = gd::CCMenuItemSpriteExtra::create(
		gd::ButtonSprite::create("OK", 30, true, "goldFont.fnt", "GJ_button_01.png", 0.0f, 1.0f),
		this,
		menu_selector(TOSPopup::onOk)
	);
	m_pButtonMenu->addChild(closeBtn);
	closeBtn->setPosition({ 0, -74.000f });

	//this->setKeypadEnabled(true);
	this->setTouchEnabled(true);

	return true;
}

void TOSPopup::onOk(cocos2d::CCObject*) {
	GameManager::sharedState()->setUGV("30", true);
	this->removeFromParentAndCleanup(true);
}

void TOSPopup::onTermsOfUse(cocos2d::CCObject*) {CCApplication::sharedApplication()->openURL("http://www.robtopgames.com/tos.html");}
void TOSPopup::onPrivacyPolicy(cocos2d::CCObject*) { CCApplication::sharedApplication()->openURL("http://www.robtopgames.com/privacy.html"); }

TOSPopup* TOSPopup::create() {
	TOSPopup* pRet = new TOSPopup();
	if (pRet && pRet->init()) {
		pRet->autorelease();
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}