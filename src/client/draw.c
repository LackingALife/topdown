// game
#include "draw.h"
#include "game.h"
#include "player.h"

// stdlib
#include <math.h>

// raylib
#include <raylib.h>
#include <raymath.h>



Vector2 convert_spaces(Vector2 vec, Vector2 spacefrom_size, Vector2 spaceto_size){
    Vector2 ret;
    ret.x = vec.x * (spaceto_size.x / spacefrom_size.x);
    ret.y = vec.y * (spaceto_size.y / spacefrom_size.y);
    return ret;
}


void draw_bullets(bullet *head, Vector2 world, Vector2 screen) {
    Vector2 bullet_screen_pos, bullet_screen_size;

    for (bullet *it = head; it; it = it->next) {
        bullet_screen_pos = convert_spaces(it->pos, world, screen);
        bullet_screen_size = convert_spaces(s2v2(it->size), world, screen);

        float angle = RAD2DEG * atanf(it->look_dir.y / it->look_dir.x);
        DrawRectanglePro((Rectangle) {
                .x = bullet_screen_pos.x, 
                .y = bullet_screen_pos.y,
                .width = bullet_screen_size.x,
                .height = bullet_screen_size.y
                },
                (Vector2) {bullet_screen_size.x/2, bullet_screen_size.y/2}, angle, it->color);
    }
}


void draw_player(Player player, Vector2 world, Vector2 screen) {
    Vector2 player_screen_pos, player_screen_size;
    Vector2 pointer_screen_pos, pointer_screen_size;

    pointer_screen_size = convert_spaces(s2v2(player.pointer_size), world, screen);
    player_screen_size = convert_spaces(s2v2(player.size), world, screen);

    pointer_screen_pos = Vector2Add(convert_spaces(player.pointer_pos, world, screen), Vector2Scale(pointer_screen_size, -.5));
    player_screen_pos = convert_spaces(player.pos, world, screen);

    float angle = RAD2DEG * atanf(player.look_dir.y / player.look_dir.x);

    DrawRectanglePro((Rectangle) {
                .x = player_screen_pos.x, 
                .y = player_screen_pos.y,
                .width = player_screen_size.x,
                .height = player_screen_size.y
            },
            (Vector2) {player_screen_size.x/2, player_screen_size.y/2}, angle, player.color);

    DrawRectangleV(pointer_screen_pos, pointer_screen_size, BLACK);
}


void draw_debug(Player player, Vector2 world, Vector2 screen) {
    Vector2 player_screen_pos = convert_spaces(player.pos, world, screen);
    Vector2 dir_norm_screen = Vector2Add(convert_spaces(Vector2Scale(Vector2Normalize(player.look_dir), player.size), world, screen), player_screen_pos);

    DrawLine(player_screen_pos.x, player_screen_pos.y, dir_norm_screen.x, dir_norm_screen.y, GREEN);
}
