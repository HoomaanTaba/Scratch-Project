//
// Created by Fazel on 2/18/2026.
//

#ifndef SCRATCH_RENDER_H
#define SCRATCH_RENDER_H
#include "UI_Objects.h"

void renderStage(SDL_Renderer* renderer, Stage& stage) {
    // first backdrop
    if (!stage.backdrops.empty()) {
        SDL_RenderCopy(renderer,
            stage.backdrops[stage.currentBackdrop],
            NULL,
            NULL);
    }

    //second sprites, in therms of grade of layers
    for (auto s : stage.sprites) {
        s->render(renderer);
    }
}
#endif //SCRATCH_RENDER_H