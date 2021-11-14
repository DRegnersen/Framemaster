#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "framemaster.h"

void getBasicData(FILE *in, header *header_info) {
    // ID3v2 signature reading

    (*header_info).signature[0] = fgetc(in);
    (*header_info).signature[1] = fgetc(in);
    (*header_info).signature[2] = fgetc(in);
    (*header_info).signature[3] = 0;

    // ID3v2 version reading
    (*header_info).version = fgetc(in);

    fgetc(in);

    // flags reading
    short byte_for_flags = fgetc(in);

    for (int i = 0; i < 4; i++) {
        byte_for_flags /= 2;
    }

    (*header_info).flags.footer_present = byte_for_flags % 2;
    byte_for_flags /= 2;

    (*header_info).flags.exp_indicator = byte_for_flags % 2;
    byte_for_flags /= 2;

    (*header_info).flags.extended_header = byte_for_flags % 2;
    byte_for_flags /= 2;

    (*header_info).flags.unsynchronisation = byte_for_flags % 2;

    // size reading
    (*header_info).size = 0;

    unsigned power = INITIAL7;

    for (int i = 0; i < 4; i++) {
        (*header_info).size += fgetc(in) * power;
        power /= 128;
    }
}

frame *getNextFrame(FILE *in, header *header_info, frame *new_frame_list, unsigned *last_frame) {
    unsigned byte_num = ((*header_info).version >= 3) ? 4 : 3;

    // new frame adding
    new_frame_list = (frame *) realloc(new_frame_list, ((*last_frame) + 1) * sizeof(frame));

    if (new_frame_list == NULL) {
        printf("Segmentation fault\n");
        return NULL;
    }

    // tag reading
    for (int i = 0; i < byte_num; i++) {
        new_frame_list[(*last_frame)].tag[i] = fgetc(in);
    }

    new_frame_list[(*last_frame)].tag[byte_num] = 0;

    // size reading
    int frame_size = 0;
    unsigned power = INITIAL7;

    for (int i = 0; i < 4; i++) {
        frame_size += fgetc(in) * power;
        power /= 128;
    }

    frame_size--;

    // reading flags
    new_frame_list[(*last_frame)].flag[0] = fgetc(in);
    new_frame_list[(*last_frame)].flag[1] = fgetc(in);

    // information reading
    new_frame_list[(*last_frame)].encoding = fgetc(in);

    for (int i = 0; i < frame_size; i++) {
        new_frame_list[(*last_frame)].info[i] = fgetc(in);
    }

    if (!strcmp(new_frame_list[(*last_frame)].tag, "COMM")) {
        new_frame_list[(*last_frame)].info[3] = ' ';
    }

    new_frame_list[(*last_frame)].info[frame_size] = 0;

    (*last_frame)++;

    return new_frame_list;
}
