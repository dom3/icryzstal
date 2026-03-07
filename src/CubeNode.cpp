#include "CubeNode.hpp"

CubeNode::CubeNode()
{

}

bool CubeNode::init()
{
    m_btnSprite = CircleButtonSprite::createWithSprite("cube_30.png"_spr);
    m_btnSprite->getTopNode()->setScale(0.8f);
    m_btnSprite->setScale(0.8f);
    
    if (!CCMenuItemSpriteExtra::init(
        m_btnSprite, 
        nullptr, 
        this, 
        menu_selector(CubeNode::onBtnClick)
    )) {
        return false;
    }
    this->scheduleUpdate(); 
    return true;
}

void CubeNode::onBtnClick(CCObject *sender)
{
    if (!m_key.empty()) return;

    log::info("Opening npesta menu");

    auto glm = GameLevelManager::sharedState();
    auto searchObj = GJSearchObject::create(SearchType::Search, numToString(LEVEL_ID));
    auto key = std::string(searchObj->getKey());

    auto stored = glm->getStoredOnlineLevels(key.c_str());
    if (stored && stored->count() > 0)
    {
        auto level = static_cast<GJGameLevel *>(stored->objectAtIndex(0));
        if (level && level->m_levelID == LEVEL_ID)
        {
            this->openLevel(level);
            return;
        }
    }

    m_key = key;
    m_timeout = 10.0f;
    changeButton(false);

    glm->getOnlineLevels(searchObj);
}

void CubeNode::update(float dt)
{
    if (!m_key.empty())
    {
        auto glm = GameLevelManager::sharedState();
        auto stored = glm->getStoredOnlineLevels(m_key.c_str());
        if (stored && stored->count() > 0)
        {
            auto level = static_cast<GJGameLevel *>(stored->objectAtIndex(0));
            if (level && level->m_levelID == LEVEL_ID)
            {
                this->openLevel(level);
                m_key.clear();
                m_timeout = 0.0f;
                return;
            }
        }

        m_timeout -= dt;
        log::debug("timeout: {}s/10s", numToString(10-m_timeout));

        if (m_timeout <= 0.0)
        {
            // TODO: spinner

            Notification::create("Couldn't find ICryzstals challenge!!", NotificationIcon::Error)->show();
            m_key.clear();
            m_timeout = 0.0f;
            changeButton(true);
        }
    }
}

void CubeNode::changeButton(bool on)
{
    m_btnSprite = CircleButtonSprite::createWithSprite(
        "cube_30.png"_spr,
        1.0F,
        (on ? CircleBaseColor::Green : CircleBaseColor::Gray)
    );
    m_btnSprite->getTopNode()->setScale(0.8f);
    m_btnSprite->setScale(0.8f);
    
    this->setSprite(m_btnSprite);
    this->updateSprite();
}

void CubeNode::openLevel(GJGameLevel *level)
{
    changeButton(true);
    auto scene = LevelInfoLayer::scene(level, false);
    CCDirector::sharedDirector()->pushScene(
        CCTransitionFade::create(0.5f, scene));
}



CubeNode *CubeNode::create()
{
    auto ret = new CubeNode;
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}
