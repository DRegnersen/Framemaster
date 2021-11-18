#ifndef PROG_LAB_4_FRAMEMASTER_H
#define PROG_LAB_4_FRAMEMASTER_H

#define LINESIZE 1000
#define LISTCAPASITY 9
#define INITIAL7 2097152

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
} header;

typedef struct {
    char tag[5];
    char encoding;
    char info[LINESIZE];
    char flag[2];
} frame;

typedef struct {
    int size;
    int capacity;
    frame *values;
} FrameList;

void getBasicData(FILE *in, header *header_info);

FrameList *declare_list();

FrameList *push_back(FrameList *dest, frame new_value);

FrameList *getNextFrame(FILE *in, header *header_info, FrameList *frames);

#endif //PROG_LAB_4_FRAMEMASTER_H
