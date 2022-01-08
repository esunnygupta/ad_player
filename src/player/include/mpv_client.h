/*
 * mpv_client.h
 *
 *  Created on: 01-Oct-2018
 *      Author: sunny
 */

#ifndef SRC_PLAYER_INCLUDE_MPV_CLIENT_H_
#define SRC_PLAYER_INCLUDE_MPV_CLIENT_H_

#include <client.h>
#include <render_gl.h>

int mpv_main(char *message, mpv_handle *mpv, mpv_render_context *mpv_gl);

#endif /* SRC_PLAYER_INCLUDE_MPV_CLIENT_H_ */
