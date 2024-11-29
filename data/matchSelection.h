#ifndef MATCH_SELECTION_
#define MATCH_SELECTION_

#include <cstdint>

struct MatchSelection {
    uint16_t matchSelection;
    uint8_t playersPerConection;
    MatchSelection(uint16_t _matchSelection, uint8_t _playersPerConection):
            matchSelection(_matchSelection), playersPerConection(_playersPerConection) {}
    MatchSelection(): matchSelection(0), playersPerConection(0) {}
};


#endif
