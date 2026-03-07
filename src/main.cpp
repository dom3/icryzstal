#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include "CubeNode.hpp"

class $modify(MyLevelSearchLayer, LevelSearchLayer) {
    bool init(const int type) {
        if (!LevelSearchLayer::init(type)) {
            return false;
        }

        auto otherFilterMenu = this->getChildByID("other-filter-menu");

        auto btn = CubeNode::create();

        otherFilterMenu->addChild(btn);
        otherFilterMenu->updateLayout();

        return true;
    }
};

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
    struct Fields {
        bool is;
        CCLabelBMFont* m_title;
        float color;
    };

    static void onModify(auto& self) {
        // self.registerVirtual(&MyLevelInfoLayer::update);
    }

    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;
        
        if (level->m_levelID != 33759558) return true;
        m_fields->is = true;

        auto title = static_cast<CCLabelBMFont*>(this->getChildByID("title-label"));
        
        if (title) {
            float duration = 0.75f;

            auto toRed   = CCTintTo::create(duration, 255, 0, 0);
            auto toGreen = CCTintTo::create(duration, 0, 255, 0);
            auto toBlue  = CCTintTo::create(duration, 0, 0, 255);

            auto sequence = CCSequence::create(toRed, toGreen, toBlue, nullptr);
            
            auto repeat = CCRepeatForever::create(sequence);
            
            title->runAction(repeat);
        }

        return true;
    }
    
    // void update(float dt) {
    //     LevelInfoLayer::update(dt);

    //     if (!m_fields->is) return;

    //     if (!m_fields->m_title) return;
        
    //     m_fields->m_title->setColor()
    // }
};