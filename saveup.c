// int key_prss_call_back(int keycode,t_game *game)
// {
//     game->start_game_flag = 1;
//     if(keycode == ESC)
//     {
//         //fucking free (;
//         mlx_destroy_display(game->mlx);
//         exit(1);
//     }
//     else if(keycode == UP || keycode == 'w' || keycode == 'W')
//     {
//         game->player.y_pos = game->player.y_start_pos - SCALE;
//         game->player.frame_y = SCALE * 2;
//     }
//     else if(keycode == LEFT || keycode == 'a'|| keycode == 'A')
//     {
//         game->player.x_pos = game->player.x_start_pos - SCALE;
//         game->player.frame_y = SCALE * 3;
//     }
//     else if(keycode == RIGHT|| keycode == 'd'|| keycode == 'D')
//     {
//         game->player.x_pos = game->player.x_start_pos + SCALE;
//         game->player.frame_y = 0;
//     }
//     else if(keycode == DOWN || keycode == 's'|| keycode == 'S')
//     {
//         game->player.y_pos = game->player.y_start_pos + SCALE;
//         game->player.frame_y = SCALE;
//     }
//     return 0;
// }



// int put_next_frame(t_game *game)
// {
//     game->frame_counter++;
//     draw_next_frame(game);
//     mlx_put_image_to_window(game->mlx, game->win, game->image, 0, 0);
//     return (0);
// }
