

enum kwn_tftp_filetype
{
    KWN_CONFIG = 1,
    KWN_IMAGE = 2,
    KWN_EVENTLOG_FILE= 3,
    KWN_TEMPLOG_FILE=4
};

enum kwn_tftp_operation_status
{
    KWN_IDLE = 1,
    KWN_DOWNLOAD_IN_PROGRESS = 2,
    KWN_DOWNLOAD_SUCCESS = 3,
    KWN_DOWNLOAD_FAILURE = 4,
    KWN_UPLOAD_IN_PROGRESS = 5,
    KWN_UPLOAD_SUCCESS = 6,
    KWN_UPLOAD_FAILURE = 7
};

enum kwn_tftp_operation_type
{
    KWN_UPLOAD = 1,
    KWN_DOWNLOAD = 2
};

typedef struct
{
    unsigned char filename[32];
    unsigned char filetype;
    unsigned char serverip[4];
    unsigned char opt_status;
    unsigned char opt_type;
}__attribute__((packed)) kwn_tftp_config;
