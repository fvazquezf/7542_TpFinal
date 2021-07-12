#include "TtWinRoundUpdate.h"

TtWinRoundUpdate::TtWinRoundUpdate() {
}

void TtWinRoundUpdate::serialize(std::function<void(std::vector<unsigned char>)> &callback) {
    protocol.handleByte(TT_WIN_ROUND, callback);
}

TtWinRoundUpdate::~TtWinRoundUpdate() {
}
