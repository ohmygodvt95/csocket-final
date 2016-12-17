//
// Created by lengkeng on 14/12/2016.
//

#ifndef SHARE_FILE_TRANSFER_H
#define SHARE_FILE_TRANSFER_H


class transfer {
public:
    static void *transfer_thread(void *us);

    static char *get_filename(char buff[]);
};


#endif //SHARE_FILE_TRANSFER_H
