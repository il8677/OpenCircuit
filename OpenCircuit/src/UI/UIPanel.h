#pragma once
#include "../Rendering/Window/EventManager.h"

#include <memory>
#include <vector>

class UIPanel {
public:
    void render();
    void registerEventHandler(EventCode eventCode, EventCallback callback);
protected:
    UIPanel()=default;

    void handleEvents();
    void dispatchEvent(Event* e) { m_eventManager.handleEvent(e); }

    template <class T, typename... Args>
    T& emplaceChild(Args... args){
        return *m_children.emplace_back(std::make_unique<T>(std::forward(args...)));
    }
    
private:
    virtual void onImGuiDraw()=0;
    EventManager m_eventManager;

    std::vector<std::unique_ptr<UIPanel>> m_children;
};