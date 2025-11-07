#pragma once
#include <vector>
#include <string>

class GUIManager {
public:
    static int displayMainMenu();
    static void showRows(const std::vector<std::vector<std::string>>& rows,
                         const std::vector<std::string>& headers = {});
};

