#ifndef PROG_LAB_4_FRAMEMASTER_H
#define PROG_LAB_4_FRAMEMASTER_H

#define LINESIZE 100
#define INITIAL7 2097152
#define INITIAL8 16777216

typedef struct {
    short unsynchronisation;
    short extended_header;
    short exp_indicator;
    short footer_present;
} flags_mp3;

typedef struct {
    char signature[4];
    short version;
    flags_mp3 flags;
    unsigned size;
} tag;

typedef struct {
    char header[5];
    char encoding;
    char info[LINESIZE];
    char flag[2];
    } frame;

void getBasicData(FILE *in, tag *tag_info);

frame *getNextFrame(FILE *in, tag *tag_info, frame *new_frame_list, unsigned *last_frame);

#endif //PROG_LAB_4_FRAMEMASTER_H
