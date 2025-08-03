#include "AppState.hpp"

AppState* AppState::instance = nullptr;

AppState* GetAppState()
{
    return AppState::instance;
}