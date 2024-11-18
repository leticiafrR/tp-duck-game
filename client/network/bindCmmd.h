#ifndef BIND_CMMD_H
#define BIND_CMMD_H
#include "data/id.h"

enum class BindCmmdCode : uint8_t { CREATE_MATCH, SELECT_MATCH, REFRESH_MATCHES };

struct BindCmmd {
    BindCmmdCode code;
    MatchID_t selection;

    explicit BindCmmd(MatchID_t matchSelection):
            code(BindCmmdCode::SELECT_MATCH), selection(matchSelection) {}

    explicit BindCmmd(BindCmmdCode _code): code(_code), selection(0) {}

    BindCmmd() = default;
};

#endif
