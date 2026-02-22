//
// Created by Fazel on 2/15/2026.
//

#ifndef SCRATCH_MOTION_H
#define SCRATCH_MOTION_H


#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "SDLInclude.h"
#include "UI_Objects.h"
using namespace std;

#define BLOCK_MOVE 1000
#define BLOCK_TURN_RIGHT 1001
#define BLOCK_TURN_LEFT 1002
#define BLOCK_GO_TO_XY 1003
#define BLOCK_CHANGE_X 1005
#define BLOCK_CHANGE_Y 1006
#define BLOCK_POINT_DIRECTION 1007
#define BLOCK_SET_X 1008
#define BLOCK_SET_Y 1009
#define BLOCK_BOUNCE 1010
#define BLOCK_GO_TO_RANDOM 1011
#define BLOCK_GO_TO_MOUSE 1012
#define BLOCK_POINT_TOWARDS 1013
#define BLOCK_SET_ROTATION_STYLE 1014

static int globalMotionBlockID = 5000;
SideButton motionBtn = {
    1,
    "Motion",
    {76, 151, 255, 255},
    {0, 90, 70, 65},
    true
};

void initMotion(SDL_Renderer *renderer) {
    SDL_Texture *moveTex = IMG_LoadTexture(renderer, "move.png");
    SDL_Texture *turnRightTex = IMG_LoadTexture(renderer, "turnRight.png");
    SDL_Texture *turnLeftTex = IMG_LoadTexture(renderer, "turnLeft.png");
    SDL_Texture *goToXYTex = IMG_LoadTexture(renderer, "goToXY.png");
    SDL_Texture *goToRandomTex = IMG_LoadTexture(renderer, "go to random position.png");
    SDL_Texture *goToMousePointerTex = IMG_LoadTexture(renderer, "go to mouse-pointer.png");
    SDL_Texture *glideTex = IMG_LoadTexture(renderer, "glide.png");
    SDL_Texture *pointDirTex = IMG_LoadTexture(renderer, "pointDir.png");
    SDL_Texture *pointTowardsTex = IMG_LoadTexture(renderer, "pointTowards.png");
    SDL_Texture *changeXTex = IMG_LoadTexture(renderer, "changeX.png");
    SDL_Texture *setXTex = IMG_LoadTexture(renderer, "setX.png");
    SDL_Texture *changeYTex = IMG_LoadTexture(renderer, "changeY.png");
    SDL_Texture *setYTex = IMG_LoadTexture(renderer, "setY.png");
    SDL_Texture *bounceTex = IMG_LoadTexture(renderer, "bounce.png");
    SDL_Texture *rotationTex = IMG_LoadTexture(renderer, "rotation.png");

    int startY = 100, gap = 35;

    // Move block
    DraggableBlock moveBlock = {
        moveTex,
        {80, startY, 130, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    };
    moveBlock.blockType = BLOCK_MOVE;
    moveBlock.hasNumberInput = true;
    moveBlock.inputValue = 10;

    MotionMenuBlocks.push_back(moveBlock);

    // turn right
    DraggableBlock turnRightBlock = {
        turnRightTex,
        {80, startY + gap, 150, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    };
    turnRightBlock.blockType = BLOCK_TURN_RIGHT;
    turnRightBlock.hasNumberInput = true;
    turnRightBlock.inputValue = 15;
    MotionMenuBlocks.push_back(turnRightBlock);
    // turn left
    DraggableBlock turnLeftBlock = {
        turnLeftTex,
        {80, startY + gap * 2, 150, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    };
    turnLeftBlock.blockType = BLOCK_TURN_LEFT;
    turnLeftBlock.hasNumberInput = true;
    turnLeftBlock.inputValue = 15;
    MotionMenuBlocks.push_back(turnLeftBlock);
    // go to xy
    DraggableBlock goToXYBlock = {
        goToXYTex,
        {80, startY + gap * 3, 200, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    };
    goToXYBlock.blockType = BLOCK_GO_TO_XY;
    goToXYBlock.hasNumberInput = true;
    goToXYBlock.inputValue = 0;
    goToXYBlock.hasSecondNumberInput = true;
    goToXYBlock.inputValue2 = 0;

    MotionMenuBlocks.push_back(goToXYBlock);

    // go to (dropdown)
    DraggableBlock goToRandomBlock = {
        goToRandomTex,
        {80, startY + gap * 4, 160, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    };
    goToRandomBlock.blockType = BLOCK_GO_TO_RANDOM;
    MotionMenuBlocks.push_back(goToRandomBlock);

    DraggableBlock goToMouseBlock = {
        goToMousePointerTex,
        {80, startY + gap * 5, 160, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    };
    goToMouseBlock.blockType = BLOCK_GO_TO_MOUSE;
    MotionMenuBlocks.push_back(goToMouseBlock);

    // point in direction
    DraggableBlock pointDirBlock = {
        pointDirTex,
        {80, startY + gap * 6, 150, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    };
    pointDirBlock.blockType = BLOCK_POINT_DIRECTION;
    pointDirBlock.hasNumberInput = true;
    pointDirBlock.inputValue = 90;
    MotionMenuBlocks.push_back(pointDirBlock);

    DraggableBlock pointTowardsBlock = {
        pointTowardsTex,
        {80, startY + gap * 7, 200, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    };
    pointTowardsBlock.blockType = BLOCK_POINT_TOWARDS;
    pointTowardsBlock.hasDropdown = true;
    pointTowardsBlock.dropdownOptions = {"mouse-pointer", "sprite1"};
    pointTowardsBlock.dropdownRect = {0, 0, 100, 22};
    MotionMenuBlocks.push_back(pointTowardsBlock);

    // change x
    DraggableBlock changeXBlock = {
        changeXTex,
        {80, startY + gap * 8, 110, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    };
    changeXBlock.blockType = BLOCK_CHANGE_X;
    changeXBlock.hasNumberInput = true;
    changeXBlock.inputValue = 10;
    MotionMenuBlocks.push_back(changeXBlock);
    // set x
    DraggableBlock setXBlock = {
        setXTex,
        {80, startY + gap * 9, 110, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    };
    setXBlock.blockType = BLOCK_SET_X;
    setXBlock.hasNumberInput = true;
    setXBlock.inputValue = 0;
    MotionMenuBlocks.push_back(setXBlock);
    // change y
    DraggableBlock changeYBlock = {
        changeYTex,
        {80, startY + gap * 10, 110, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    };
    changeYBlock.blockType = BLOCK_CHANGE_Y;
    changeYBlock.hasNumberInput = true;
    changeYBlock.inputValue = 10;
    MotionMenuBlocks.push_back(changeYBlock);

    // set y
    DraggableBlock setYBlock = {
        setYTex,
        {80, startY + gap * 11, 110, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    };
    setYBlock.blockType = BLOCK_SET_Y;
    setYBlock.hasNumberInput = true;
    setYBlock.inputValue = 0;
    MotionMenuBlocks.push_back(setYBlock);

    // bounce
    DraggableBlock bounceBlock = {
        bounceTex,
        {80, startY + gap * 12, 130, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    };
    bounceBlock.blockType = BLOCK_BOUNCE;
    MotionMenuBlocks.push_back(bounceBlock);

    // set rotation style (dropdown)
    DraggableBlock rotationBlock = {
        rotationTex,
        {80, startY + gap * 13, 200, 45},
        false, 0, 0,
        false,
        -1,
        globalMotionBlockID++
    };
    rotationBlock.blockType = BLOCK_SET_ROTATION_STYLE;
    rotationBlock.hasDropdown = true;
    rotationBlock.dropdownOptions = {"all around", "left-right", "don't rotate"};
    rotationBlock.dropdownRect = {0, 0, 120, 22};
    MotionMenuBlocks.push_back(rotationBlock);
}

void handleMotionBlock(SDL_Event &e, bool codeTabActive, bool motionBtnActive) {
    if (!codeTabActive || !motionBtnActive)
        return;
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        for (auto &wb: workspaceBlocks) {
            if (wb.hasNumberInput && isInside(mx, my, wb.inputRect1)) {
                wb.editingInput1 = true;
                wb.editingInput2 = false;
                SDL_StartTextInput();
                return;
            }

            if (wb.hasSecondNumberInput && isInside(mx, my, wb.inputRect2)) {
                wb.editingInput1 = false;
                wb.editingInput2 = true;
                SDL_StartTextInput();
                return;
            }
        }
        bool caught = false;
        for (int i = workspaceBlocks.size() - 1; i >= 0; i--) {
            if (isInside(mx, my, workspaceBlocks[i].rect)) {
                workspaceBlocks[i].dragging = true;
                workspaceBlocks[i].parentID = -1;
                workspaceBlocks[i].offsetX = mx - workspaceBlocks[i].rect.x;
                workspaceBlocks[i].offsetY = my - workspaceBlocks[i].rect.y;

                DraggableBlock temp = workspaceBlocks[i];
                workspaceBlocks.erase(workspaceBlocks.begin() + i);
                workspaceBlocks.push_back(temp);
                caught = true;
                break;
            }
        }

        if (!caught && codeTabActive && motionBtnActive) {
            for (auto &mb: MotionMenuBlocks) {
                if (isInside(mx, my, mb.rect)) {
                    DraggableBlock newNode = mb;

                    newNode.inputText1 = "";
                    newNode.inputText2 = "";
                    newNode.editingInput1 = false;
                    newNode.editingInput2 = false;

                    newNode.parentID = -1;
                    newNode.dragging = true;

                    newNode.rect.x = mx - mb.rect.w / 2;
                    newNode.rect.y = my - mb.rect.h / 2;

                    newNode.offsetX = mb.rect.w / 2;
                    newNode.offsetY = mb.rect.h / 2;
                    workspaceBlocks.push_back(newNode);
                    break;
                }
            }
        }
    }

    if (e.type == SDL_MOUSEBUTTONUP) {
        for (auto &b: workspaceBlocks) {
            if (b.dragging) {
                b.dragging = false;
                if (b.rect.x < 250) {
                    for (int k = 0; k < workspaceBlocks.size(); k++) {
                        if (&workspaceBlocks[k] == &b) {
                            workspaceBlocks.erase(workspaceBlocks.begin() + k);
                            break;
                            return;
                        }
                    }
                }
                // Sticking part

                for (auto &target: workspaceBlocks) {
                    if (&b == &target)
                        continue;

                    int centerBX = b.rect.x + b.rect.w / 2;
                    int centerTX = target.rect.x + target.rect.w / 2;

                    int snapX = abs(centerBX - centerTX);
                    int snapY = abs(b.rect.y - (target.rect.y + target.rect.h));

                    if (snapX < 30 && snapY < 30) {
                        if (b.isHat && target.parentID != -1)
                            continue;
                        b.rect.x = target.rect.x;
                        b.rect.y = target.rect.y + target.rect.h - 6; //Overlapping pixels
                        b.parentID = target.id;
                        break; // when fined good block, break;
                    }
                }
            }
        }
    }
    if (e.type == SDL_MOUSEMOTION) {
        for (int i = 0; i < workspaceBlocks.size(); i++) {
            if (workspaceBlocks[i].dragging) {
                int oldX = workspaceBlocks[i].rect.x;
                int oldY = workspaceBlocks[i].rect.y;

                // Dragging the main block
                workspaceBlocks[i].rect.x = mx - workspaceBlocks[i].offsetX;
                workspaceBlocks[i].rect.y = my - workspaceBlocks[i].offsetY;

                int diffX = workspaceBlocks[i].rect.x - oldX;
                int diffY = workspaceBlocks[i].rect.y - oldY;

                // Dragging all blocks under each other
                bool changed = true;
                vector<int> movedIndices;
                movedIndices.push_back(i);
                while (changed) {
                    changed = false;
                    for (int j = 0; j < workspaceBlocks.size(); j++) {
                        bool alreadyMoved = false;
                        for (int idx: movedIndices)
                            if (idx == j)
                                alreadyMoved = true;
                        if (!alreadyMoved && j != i && !workspaceBlocks[j].dragging) {
                            for (int idx: movedIndices) {
                                // checking if idx is under a block
                                if (workspaceBlocks[j].parentID == workspaceBlocks[idx].id && workspaceBlocks[j].
                                    parentID != -1) {
                                    workspaceBlocks[j].rect.x += diffX;
                                    workspaceBlocks[j].rect.y += diffY;
                                    movedIndices.push_back(j);
                                    changed = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void renderMotionBlocks(SDL_Renderer *renderer, TTF_Font *font, bool codeTabActive, bool motionBtnActive) {
    if (!codeTabActive || !motionBtnActive)
        return;
    if (codeTabActive && motionBtnActive) {
        for (auto &mb: MotionMenuBlocks) {
            SDL_RenderCopy(renderer, mb.texture, NULL, &mb.rect);
        }
    }
}


Sprite s;

double step = 1;

void normalizeDirection(Sprite &s) {
    while (s.direction >= 360)
        s.direction -= 360;
    while (s.direction < 0)
        s.direction += 360;
}

void move_n_steps(Sprite &s, double n) {
    double rad = (s.direction - 90) * M_PI / 180;
    s.x += n * cos(rad);
    s.y += n * sin(rad);
}

void turn_angle_right(Sprite &s, double angle) {
    s.direction += angle;
    normalizeDirection(s);
}

void turn_angle_left(Sprite &s, double angle) {
    s.direction -= angle;
    normalizeDirection(s);
}

void go_to_randomposition(Sprite &s) {
    double randX = rand() % W + 1;
    double randY = rand() % H + 1;
    s.x = randX;
    s.y = randY;
}

void go_to_x_and_y(Sprite &s, double x, double y) {
    s.x = x;
    s.y = y;
}

void change_x_by(Sprite &s, double dx) {
    s.x += dx;
    if (s.x == 0 || s.x == W)
        s.direction *= -1;
    normalizeDirection(s);
}

void change_y_by(Sprite &s, double dy) {
    s.y += dy;
    if (s.y == 0 || s.y == H)
        s.direction *= -1;
    normalizeDirection(s);
}

void point_in_direction(Sprite &s, double angle) {
    s.direction = angle;
    normalizeDirection(s);
}

void go_to_mouseposition(Sprite &s) {
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    s.x = mx;
    s.y = my;
    if (s.x == 0 || s.x == W || s.y == 0 || s.y == H) {
        s.direction *= -1;
    }
    normalizeDirection(s);
}

void set_x_to(Sprite &s, double x) {
    s.x = x;
}

void set_y_to(Sprite &s, double y) {
    s.y = y;
}

#endif //SCRATCH_MOTION_H
