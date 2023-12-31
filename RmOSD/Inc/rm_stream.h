#define FILE_DEVICE_RM_KS              0x00008200U

#define IOCTL_KS_PROPERTY              CTL_CODE(FILE_DEVICE_RM_KS, 0x000, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_KS_ENABLE_EVENT          CTL_CODE(FILE_DEVICE_RM_KS, 0x001, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_KS_DISABLE_EVENT         CTL_CODE(FILE_DEVICE_RM_KS, 0x002, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_KS_METHOD                CTL_CODE(FILE_DEVICE_RM_KS, 0x003, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_KS_WRITE_STREAM          CTL_CODE(FILE_DEVICE_RM_KS, 0x004, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_KS_READ_STREAM           CTL_CODE(FILE_DEVICE_RM_KS, 0x005, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_KS_RESET_STATE           CTL_CODE(FILE_DEVICE_RM_KS, 0x006, METHOD_BUFFERED, FILE_ANY_ACCESS)

