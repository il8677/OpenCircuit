#pragma once
#include "../Rendering/Window/EventManager.h"

#include <memory>
#include <vector>

class UIPanel {
public:
    void destroy() { m_destroy = true; }
    void render();
    void registerEventHandler(EventCode eventCode, EventCallback callback);

    virtual ~UIPanel()=default;
protected:
    UIPanel()=default;

    void handleEvents();
    void dispatchEvent(Event* e); 

    template <class T, typename... Args>
    T& emplaceChild(Args... args){
        return reinterpret_cast<T&>(*m_children.emplace_back(std::make_unique<T>(std::forward<Args>(args)...)));
    }

    
private:
    void removeChild(UIPanel* child);
    virtual void onImGuiDraw()=0;
    EventManager m_eventManager;

    bool m_destroy = false;

    std::vector<std::unique_ptr<UIPanel>> m_children;
};