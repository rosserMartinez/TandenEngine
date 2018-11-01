//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#include "EventSystem.h"

std::queue<Event*> EventSystem::mEvents;
std::vector<EventListener*> EventSystem::mListeners;

EventSystem::EventSystem() {

}

bool EventSystem::RegisterListener(EventListener* newListener) {
    mListeners.emplace_back(newListener);
    return false;
}

bool EventSystem::DeregisterListener(EventListener*) {
    return false;
}

void EventSystem::ProcessEvents() {
    std::cout<<"Going through events\n";

    Event* thisEvent = nullptr ;
    while(!mEvents.empty()) {
        thisEvent = mEvents.front(); //point to the next event
        for (auto &listener : mListeners) { //Tell all listeners that this event happened
            listener->ProcessEvent(thisEvent);
        }

        mEvents.pop(); //Remove the processed Event
    }
}

void EventSystem::AddEvent(Event* newEvent) {
    mEvents.push(newEvent);
}