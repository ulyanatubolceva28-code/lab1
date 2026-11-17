#include "region_validator.h"

#include <unordered_set>

namespace lab2 {

bool RegionValidator::isSupportedRegion(const std::string& region) {
    static const std::unordered_set<std::string> regions = {
        "Москва",
        "Санкт-Петербург",
        "Казань",
        "Новосибирск",
        "Екатеринбург",
        "Владивосток"
    };

    return regions.find(region) != regions.end();
}

}