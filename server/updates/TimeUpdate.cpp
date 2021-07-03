#include "TimeUpdate.h"

TimeUpdate::TimeUpdate(uint8_t time)
: time(time){
}

void TimeUpdate::serialize(std::function<void(std::vector<unsigned char>)>& callback) {
    // protocol.updatePlayerTime(Time, id, callback);
}

TimeUpdate::~TimeUpdate() {
}
