#include "CtWinRoundUpdate.h"

CtWinRoundUpdate::CtWinRoundUpdate() {
}

void CtWinRoundUpdate::serialize(std::function<void(std::vector<unsigned char>)> &callback) {
    protocol.handleByte(CT_WIN_ROUND, callback);
}

CtWinRoundUpdate::~CtWinRoundUpdate() {
}
