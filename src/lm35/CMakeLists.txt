upm_mixed_module_init (NAME lm35
    DESCRIPTION "Analog Temperature Sensor"
    C_HDR lm35.h
    C_SRC lm35.c
    IFACE_HDR iTemperature.hpp
    CPP_HDR lm35.hpp
    CPP_SRC lm35.cxx
    FTI_SRC lm35_fti.c
    CPP_WRAPS_C
    REQUIRES mraa)
