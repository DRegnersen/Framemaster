#include <stdio.h>
#include <stdlib.h>
#include "framemaster.h"

void getBasicData(FILE *in, tag *tag_info) {
    // ID3v2 signature reading

    (*tag_info).signature[0] = fgetc(in);
    (*tag_info).signature[1] = fgetc(in);
    (*tag_info).signature[2] = fgetc(in);
    (*tag_info).signature[3] = 0;

    // ID3v2 version reading
    (*tag_info).version = fgetc(in);

    fgetc(in);

    // flags reading
    short byte_for_flags = fgetc(in);

    for (int i = 0; i < 4; i++) {
        byte_for_flags /= 2;
    }

    (*tag_info).flags.footer_present = byte_for_flags % 2;
    byte_for_flags /= 2;

    (*tag_info).flags.exp_indicator = byte_for_flags % 2;
    byte_for_flags /= 2;

    (*tag_info).flags.extended_header = byte_for_flags % 2;
    byte_for_flags /= 2;

    (*tag_info).flags.unsynchronisation = byte_for_flags % 2;

    // size reading
    (*tag_info).size = 0;

    unsigned power = INITIAL7;

    for (int i = 0; i < 4; i++) {
        (*tag_info).size += fgetc(in) * power;
        power /= 128;
    }
}

frame *getNextFrame(FILE *in, tag *tag_info, frame *new_frame_list, unsigned *last_frame) {
    unsigned byte_num = ((*tag_info).version >= 3) ? 4 : 3;

    // new frame adding
    new_frame_list = (frame *) realloc(new_frame_list, ((*last_frame) + 1) * sizeof(frame));

    if (new_frame_list == NULL) {
        printf("Segmentation fault\n");
        return NULL;
    }

    // tag reading
    for (int i = 0; i < byte_num; i++) {
        new_frame_list[(*last_frame)].header[i] = fgetc(in);
    }

    new_frame_list[(*last_frame)].header[byte_num] = 0;

    // size reading
    unsigned frame_size = 0;
    unsigned power = INITIAL8;

    for (int i = 0; i < 4; i++) {
        frame_size += fgetc(in) * power;
        power /= 256;
    }

    // reading flags
    new_frame_list[(*last_frame)].flag[0] = fgetc(in);
    new_frame_list[(*last_frame)].flag[1] = fgetc(in);

    // information reading and skipping inappropriate bytes
    char cur_info_char;
    int idx = 0;

    for (int i = 0; i < frame_size; i++) {
        cur_info_char = fgetc(in);

        if (cur_info_char >= 32) {
            new_frame_list[(*last_frame)].info[idx] = cur_info_char;
            idx++;
        } else {
            // size updating
            (*tag_info).size--;
        }
    }

    new_frame_list[(*last_frame)].info[idx] = 0;

    (*last_frame)++;

    return new_frame_list;
}