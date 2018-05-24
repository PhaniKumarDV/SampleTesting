// This is an auto-generated file.
// DON'T manually modify the file but use cmdRspDictGenSrc.exe.

#if !defined(__CMD_RSP_AND_PARMS_DIC_H)
#define __CMD_RSP_AND_PARMS_DIC_H

// commands
typedef enum cmdCodeEnum {
    CMD_SYNC = 0,
        #define CMD_SYNC_RAND  584003679
    CMD_TPCCAL = 1,
        #define CMD_TPCCAL_RAND  1299040070
    CMD_TPCCALRSP = 2,
        #define CMD_TPCCALRSP_RAND  1699217351
    CMD_TPCCALPWR = 3,
        #define CMD_TPCCALPWR_RAND  1654919846
    CMD_TPCCALDATA = 4,
        #define CMD_TPCCALDATA_RAND  2027924831
    CMD_RXGAINCAL = 5,
        #define CMD_RXGAINCAL_RAND  1299041111
    CMD_RXGAINCALRSP = 6,
        #define CMD_RXGAINCALRSP_RAND  1699212222
    CMD_RXGAINCAL_SIGL_DONE = 7,
        #define CMD_RXGAINCAL_SIGL_DONE_RAND  1931385521
    CMD_RXGAINCALRSP_DONE = 8,
        #define CMD_RXGAINCALRSP_DONE_RAND  2027977812
    CMD_REGREAD = 9,
        #define CMD_REGREAD_RAND  3357
    CMD_REGREADRSP = 10,
        #define CMD_REGREADRSP_RAND  28045
    CMD_REGWRITE = 11,
        #define CMD_REGWRITE_RAND  3396
    CMD_REGWRITERSP = 12,
        #define CMD_REGWRITERSP_RAND  25954
    CMD_BASICRSP = 13,
        #define CMD_BASICRSP_RAND  684741659
    CMD_TX = 14,
        #define CMD_TX_RAND  788880175
    CMD_TXSTATUS = 15,
        #define CMD_TXSTATUS_RAND  1786600363
    CMD_TXSTATUSRSP = 16,
        #define CMD_TXSTATUSRSP_RAND  138420902
    CMD_RX = 17,
        #define CMD_RX_RAND  1360680161
    CMD_RXSTATUS = 18,
        #define CMD_RXSTATUS_RAND  68378807
    CMD_RXSTATUSRSP = 19,
        #define CMD_RXSTATUSRSP_RAND  810169362
    CMD_HWCAL = 20,
        #define CMD_HWCAL_RAND  1280063023
    CMD_RXRSP = 21,
        #define CMD_RXRSP_RAND  138356853
    CMD_XTALCALPROC = 22,
        #define CMD_XTALCALPROC_RAND  190849699
    CMD_XTALCALPROCRSP = 23,
        #define CMD_XTALCALPROCRSP_RAND  2058566353
    CMD_READCUSTOTPSPACE = 24,
        #define CMD_READCUSTOTPSPACE_RAND  1177604213
    CMD_READCUSTOTPSPACERSP = 25,
        #define CMD_READCUSTOTPSPACERSP_RAND  593844853
    CMD_WRITECUSTOTPSPACE = 26,
        #define CMD_WRITECUSTOTPSPACE_RAND  1177940841
    CMD_WRITECUSTOTPSPACERSP = 27,
        #define CMD_WRITECUSTOTPSPACERSP_RAND  2119255687
    CMD_GETCUSTOTPSIZE = 28,
        #define CMD_GETCUSTOTPSIZE_RAND  1547973684
    CMD_GETCUSTOTPSIZERSP = 29,
        #define CMD_GETCUSTOTPSIZERSP_RAND  1569440880
    CMD_GETDPDCOMPLETE = 30,
        #define CMD_GETDPDCOMPLETE_RAND  12643513
    CMD_GETDPDCOMPLETERSP = 31,
        #define CMD_GETDPDCOMPLETERSP_RAND  113961185
    CMD_GETTGTPWR = 32,
        #define CMD_GETTGTPWR_RAND  358252260
    CMD_GETTGTPWRRSP = 33,
        #define CMD_GETTGTPWRRSP_RAND  1940800329
    CMD_SETPCIECONFIGPARAMS = 34,
        #define CMD_SETPCIECONFIGPARAMS_RAND  854451531
    CMD_SETPCIECONFIGPARAMSRSP = 35,
        #define CMD_SETPCIECONFIGPARAMSRSP_RAND  1002969271
    CMD_COMMITOTPSTREAM = 36,
        #define CMD_COMMITOTPSTREAM_RAND  259798082
    CMD_COMMITOTPSTREAMRSP = 37,
        #define CMD_COMMITOTPSTREAMRSP_RAND  626266106
    CMD_SETREGDMN = 38,
        #define CMD_SETREGDMN_RAND  1272588943
    CMD_SETREGDMNRSP = 39,
        #define CMD_SETREGDMNRSP_RAND  840458865

    CMD_LAST,
    CMD_MAX  = CMD_LAST,
} CMD_CODE;

// parameters
typedef enum parmCodeEnum {
    PARM_RESERVED = 0,
        #define PARM_RESERVED_RAND  1767181237
    PARM_RADIOID = 1,
        #define PARM_RADIOID_RAND  1078202216
    PARM_NUMFREQ2G = 2,
        #define PARM_NUMFREQ2G_RAND  783992014
    PARM_FREQ2G = 3,
        #define PARM_FREQ2G_RAND  470730988
    PARM_NUMFREQ5G = 4,
        #define PARM_NUMFREQ5G_RAND  176973004
    PARM_FREQ5G = 5,
        #define PARM_FREQ5G_RAND  2010102476
    PARM_NUMCHAIN = 6,
        #define PARM_NUMCHAIN_RAND  639877336
    PARM_NUMCALPT2G = 7,
        #define PARM_NUMCALPT2G_RAND  332852346
    PARM_MEASUREDPWR = 8,
        #define PARM_MEASUREDPWR_RAND  716797366
    PARM_NUMMEASUREDPWR = 9,
        #define PARM_NUMMEASUREDPWR_RAND  165756936
    PARM_TPCCALDATA2G = 10,
        #define PARM_TPCCALDATA2G_RAND  25905134
    PARM_TPCCALDATA2GOFFSET = 11,
        #define PARM_TPCCALDATA2GOFFSET_RAND  908282359
    PARM_TPCCALDATA5G = 12,
        #define PARM_TPCCALDATA5G_RAND  1714114174
    PARM_TPCCALDATA5GOFFSET = 13,
        #define PARM_TPCCALDATA5GOFFSET_RAND  1359093690
    PARM_TPCCALDATA2GLENGTH = 14,
        #define PARM_TPCCALDATA2GLENGTH_RAND  642468564
    PARM_TPCCALDATA5GLENGTH = 15,
        #define PARM_TPCCALDATA5GLENGTH_RAND  1989017899
    PARM_CALPT2G = 16,
        #define PARM_CALPT2G_RAND  463935119
    PARM_NUMTXGAINS2G = 17,
        #define PARM_NUMTXGAINS2G_RAND  1856040979
    PARM_TXGAINS2G = 18,
        #define PARM_TXGAINS2G_RAND  1955125611
    PARM_NUMDACGAINS2G = 19,
        #define PARM_NUMDACGAINS2G_RAND  1076992776
    PARM_DACGAINS2G = 20,
        #define PARM_DACGAINS2G_RAND  267406232
    PARM_NUMPACFG2G = 21,
        #define PARM_NUMPACFG2G_RAND  751352277
    PARM_PACFG2G = 22,
        #define PARM_PACFG2G_RAND  1472306812
    PARM_CHAINMASKS = 23,
        #define PARM_CHAINMASKS_RAND  1876191032
    PARM_NUMCALPT5G = 24,
        #define PARM_NUMCALPT5G_RAND  1910772740
    PARM_CALPT5G = 25,
        #define PARM_CALPT5G_RAND  467317885
    PARM_NUMTXGAINS5G = 26,
        #define PARM_NUMTXGAINS5G_RAND  1817893134
    PARM_TXGAINS5G = 27,
        #define PARM_TXGAINS5G_RAND  711527951
    PARM_NUMDACGAINS5G = 28,
        #define PARM_NUMDACGAINS5G_RAND  230774027
    PARM_DACGAINS5G = 29,
        #define PARM_DACGAINS5G_RAND  1751729643
    PARM_NUMPACFG5G = 30,
        #define PARM_NUMPACFG5G_RAND  963837256
    PARM_PACFG5G = 31,
        #define PARM_PACFG5G_RAND  1083020536
    PARM_MISCFLAGS = 32,
        #define PARM_MISCFLAGS_RAND  351545944
    PARM_TGTPWR2G = 33,
        #define PARM_TGTPWR2G_RAND  167692342
    PARM_TGTPWR5G = 34,
        #define PARM_TGTPWR5G_RAND  807751391
    PARM_TPCCALDATA2G_CLPC = 35,
        #define PARM_TPCCALDATA2G_CLPC_RAND  572790975
    PARM_TPCCALDATA2GOFFSET_CLPC = 36,
        #define PARM_TPCCALDATA2GOFFSET_CLPC_RAND  1472433449
    PARM_TPCCALDATA5G_CLPC = 37,
        #define PARM_TPCCALDATA5G_CLPC_RAND  869450761
    PARM_TPCCALDATA5GOFFSET_CLPC = 38,
        #define PARM_TPCCALDATA5GOFFSET_CLPC_RAND  180798074
    PARM_TPCCALDATA2GLENGTH_CLPC = 39,
        #define PARM_TPCCALDATA2GLENGTH_CLPC_RAND  971133679
    PARM_TPCCALDATA5GLENGTH_CLPC = 40,
        #define PARM_TPCCALDATA5GLENGTH_CLPC_RAND  748974643
    PARM_STATUS = 41,
        #define PARM_STATUS_RAND  748977743
    PARM_BAND = 42,
        #define PARM_BAND_RAND  287998654
    PARM_REFISS = 43,
        #define PARM_REFISS_RAND  957473492
    PARM_RATE = 44,
        #define PARM_RATE_RAND  94874324
    PARM_BANDWIDTH = 45,
        #define PARM_BANDWIDTH_RAND  95926056
    PARM_CHANIDX = 46,
        #define PARM_CHANIDX_RAND  324374234
    PARM_CHAINIDX = 47,
        #define PARM_CHAINIDX_RAND  867448663
    PARM_NUMPACKETS = 48,
        #define PARM_NUMPACKETS_RAND  854372348
    PARM_CHAIN2CAL = 49,
        #define PARM_CHAIN2CAL_RAND  1046839514
    PARM_REGADDRESS = 50,
        #define PARM_REGADDRESS_RAND  20772
    PARM_REGVALUE = 51,
        #define PARM_REGVALUE_RAND  3242
    PARM_CMDID = 52,
        #define PARM_CMDID_RAND  1272413688
    PARM_TXMODE = 53,
        #define PARM_TXMODE_RAND  341460719
    PARM_FREQ = 54,
        #define PARM_FREQ_RAND  1421688400
    PARM_CHAINMASK = 55,
        #define PARM_CHAINMASK_RAND  1381774268
    PARM_WLANMODE = 56,
        #define PARM_WLANMODE_RAND  48372818
    PARM_GI = 57,
        #define PARM_GI_RAND  996941837
    PARM_ANTENNA = 58,
        #define PARM_ANTENNA_RAND  1565073502
    PARM_ENANI = 59,
        #define PARM_ENANI_RAND  1906667634
    PARM_SCRAMBLEROFF = 60,
        #define PARM_SCRAMBLEROFF_RAND  1938175155
    PARM_AIFSN = 61,
        #define PARM_AIFSN_RAND  1120553799
    PARM_BROADCAST = 62,
        #define PARM_BROADCAST_RAND  1342860700
    PARM_AGG = 63,
        #define PARM_AGG_RAND  1351056194
    PARM_SHORTGUARD = 64,
        #define PARM_SHORTGUARD_RAND  42868895
    PARM_DUTYCYCLE = 65,
        #define PARM_DUTYCYCLE_RAND  234446920
    PARM_FLAGS = 66,
        #define PARM_FLAGS_RAND  699759608
    PARM_IR = 67,
        #define PARM_IR_RAND  913400453
    PARM_PKTSZ = 68,
        #define PARM_PKTSZ_RAND  1072443974
    PARM_DATAPATTERN = 69,
        #define PARM_DATAPATTERN_RAND  561322939
    PARM_TXNUMPACKETS = 70,
        #define PARM_TXNUMPACKETS_RAND  798297731
    PARM_TXPATTERN = 71,
        #define PARM_TXPATTERN_RAND  403188442
    PARM_NPATTERN = 72,
        #define PARM_NPATTERN_RAND  1919288377
    PARM_TPCM = 73,
        #define PARM_TPCM_RAND  254567890
    PARM_GAINIDX = 74,
        #define PARM_GAINIDX_RAND  1074466803
    PARM_DACGAIN = 75,
        #define PARM_DACGAIN_RAND  1805933989
    PARM_DACGAINEND = 76,
        #define PARM_DACGAINEND_RAND  269712370
    PARM_DACGAINSTEP = 77,
        #define PARM_DACGAINSTEP_RAND  855533760
    PARM_PACONFIG = 78,
        #define PARM_PACONFIG_RAND  1929993506
    PARM_PACONFIGEND = 79,
        #define PARM_PACONFIGEND_RAND  1305552779
    PARM_PACONFIGSTEP = 80,
        #define PARM_PACONFIGSTEP_RAND  115432525
    PARM_PAD3 = 81,
        #define PARM_PAD3_RAND  1061435199
    PARM_RATEMASK = 82,
        #define PARM_RATEMASK_RAND  177676173
    PARM_RATEMASK11AC = 83,
        #define PARM_RATEMASK11AC_RAND  1976502008
    PARM_PWRGAINSTART = 84,
        #define PARM_PWRGAINSTART_RAND  1427269639
    PARM_PWRGAINEND = 85,
        #define PARM_PWRGAINEND_RAND  424018699
    PARM_PWRGAINSTEP = 86,
        #define PARM_PWRGAINSTEP_RAND  860764118
    PARM_PWRGAINSTART11AC = 87,
        #define PARM_PWRGAINSTART11AC_RAND  2048068249
    PARM_PWRGAINEND11AC = 88,
        #define PARM_PWRGAINEND11AC_RAND  1908020294
    PARM_PWRGAINSTEP11AC = 89,
        #define PARM_PWRGAINSTEP11AC_RAND  96625508
    PARM_BSSID = 90,
        #define PARM_BSSID_RAND  350173251
    PARM_TXSTATION = 91,
        #define PARM_TXSTATION_RAND  1690574818
    PARM_RXSTATION = 92,
        #define PARM_RXSTATION_RAND  88296209
    PARM_NUMOFREPORTS = 93,
        #define PARM_NUMOFREPORTS_RAND  463223138
    PARM_THERMCAL = 94,
        #define PARM_THERMCAL_RAND  534184381
    PARM_PDADC = 95,
        #define PARM_PDADC_RAND  1917267778
    PARM_PACFG = 96,
        #define PARM_PACFG_RAND  1106643480
    PARM_TOTALPACKETS = 97,
        #define PARM_TOTALPACKETS_RAND  1969387163
    PARM_GOODPACKETS = 98,
        #define PARM_GOODPACKETS_RAND  2135183001
    PARM_UNDERRUNS = 99,
        #define PARM_UNDERRUNS_RAND  579092863
    PARM_OTHERERROR = 100,
        #define PARM_OTHERERROR_RAND  1723554567
    PARM_EXCESSRETRIES = 101,
        #define PARM_EXCESSRETRIES_RAND  1241320473
    PARM_RATEBIT = 102,
        #define PARM_RATEBIT_RAND  1640050693
    PARM_SHORTRETRY = 103,
        #define PARM_SHORTRETRY_RAND  1813518400
    PARM_LONGRETRY = 104,
        #define PARM_LONGRETRY_RAND  462764869
    PARM_STARTTIME = 105,
        #define PARM_STARTTIME_RAND  2073904972
    PARM_ENDTIME = 106,
        #define PARM_ENDTIME_RAND  2012028921
    PARM_BYTECOUNT = 107,
        #define PARM_BYTECOUNT_RAND  697976361
    PARM_DONTCOUNT = 108,
        #define PARM_DONTCOUNT_RAND  1558078346
    PARM_RSSI = 109,
        #define PARM_RSSI_RAND  509820842
    PARM_RSSIC = 110,
        #define PARM_RSSIC_RAND  1408979597
    PARM_RSSIE = 111,
        #define PARM_RSSIE_RAND  1138231583
    PARM_RXMODE = 112,
        #define PARM_RXMODE_RAND  1925660275
    PARM_ACK = 113,
        #define PARM_ACK_RAND  1892170080
    PARM_LPL = 114,
        #define PARM_LPL_RAND  866207531
    PARM_ANTSWITCH1 = 115,
        #define PARM_ANTSWITCH1_RAND  189542157
    PARM_ANTSWITCH2 = 116,
        #define PARM_ANTSWITCH2_RAND  618207292
    PARM_PAD2 = 117,
        #define PARM_PAD2_RAND  2121816936
    PARM_SPECTRALSCAN = 118,
        #define PARM_SPECTRALSCAN_RAND  1416654144
    PARM_NOISEFLOOR = 119,
        #define PARM_NOISEFLOOR_RAND  385880570
    PARM_REGDMN = 120,
        #define PARM_REGDMN_RAND  944982574
    PARM_EXPECTEDPKTS = 121,
        #define PARM_EXPECTEDPKTS_RAND  1524444042
    PARM_OTPWRITEFLAG = 122,
        #define PARM_OTPWRITEFLAG_RAND  1809853483
    PARM_STAADDR = 123,
        #define PARM_STAADDR_RAND  1391484308
    PARM_BTADDR = 124,
        #define PARM_BTADDR_RAND  1722170531
    PARM_CRCPACKETS = 125,
        #define PARM_CRCPACKETS_RAND  187516853
    PARM_DECRYPERRORS = 126,
        #define PARM_DECRYPERRORS_RAND  1078090189
    PARM_BADRSSI = 127,
        #define PARM_BADRSSI_RAND  2089647505
    PARM_BADRSSIC = 128,
        #define PARM_BADRSSIC_RAND  1149501459
    PARM_BADRSSIE = 129,
        #define PARM_BADRSSIE_RAND  1256675541
    PARM_EVM = 130,
        #define PARM_EVM_RAND  1459891159
    PARM_BADEVM = 131,
        #define PARM_BADEVM_RAND  2121290035
    PARM_STOPTX = 132,
        #define PARM_STOPTX_RAND  1404993314
    PARM_NEEDREPORT = 133,
        #define PARM_NEEDREPORT_RAND  687894972
    PARM_STOPRX = 134,
        #define PARM_STOPRX_RAND  1380788600
    PARM_CALOP = 135,
        #define PARM_CALOP_RAND  200353319
    PARM_LOOPCNT = 136,
        #define PARM_LOOPCNT_RAND  797993136
    PARM_RSSIINDBM1 = 137,
        #define PARM_RSSIINDBM1_RAND  517422321
    PARM_SECERRPKT = 138,
        #define PARM_SECERRPKT_RAND  1316832418
    PARM_RATECNT = 139,
        #define PARM_RATECNT_RAND  1253205541
    PARM_RATECNT11AC = 140,
        #define PARM_RATECNT11AC_RAND  2135455981
    PARM_LOOPBACK = 141,
        #define PARM_LOOPBACK_RAND  1476462953
    PARM_SAVECAL = 142,
        #define PARM_SAVECAL_RAND  1788939705
    PARM_NOISEFLOORCAL = 143,
        #define PARM_NOISEFLOORCAL_RAND  1788939705
    PARM_CAPIN = 144,
        #define PARM_CAPIN_RAND  1536716510
    PARM_CAPOUT = 145,
        #define PARM_CAPOUT_RAND  1660177319
    PARM_CTRLFLAG = 146,
        #define PARM_CTRLFLAG_RAND  861931537
    PARM_CAPVALMIN = 147,
        #define PARM_CAPVALMIN_RAND  528223855
    PARM_CAPVALMAX = 148,
        #define PARM_CAPVALMAX_RAND  599005719
    PARM_PLLLOCKED = 149,
        #define PARM_PLLLOCKED_RAND  2068468356
    PARM_CUSTDATA = 150,
        #define PARM_CUSTDATA_RAND  213230345
    PARM_OFFSETADDR = 151,
        #define PARM_OFFSETADDR_RAND  1939829656
    PARM_CUSTDATASIZE = 152,
        #define PARM_CUSTDATASIZE_RAND  16323722
    PARM_WRITESTATUS = 153,
        #define PARM_WRITESTATUS_RAND  1098446922
    PARM_OTPCUSTSIZE = 154,
        #define PARM_OTPCUSTSIZE_RAND  1134286375
    PARM_DPDCOMPLETE = 155,
        #define PARM_DPDCOMPLETE_RAND  1612897212
    PARM_USERMODE = 156,
        #define PARM_USERMODE_RAND  1607587425
    PARM_TGTPWR = 157,
        #define PARM_TGTPWR_RAND  1970398708
    PARM_PCIEADDR = 158,
        #define PARM_PCIEADDR_RAND  1305722531
    PARM_PCIEVALUE = 159,
        #define PARM_PCIEVALUE_RAND  1609849136
    PARM_OPERATION = 160,
        #define PARM_OPERATION_RAND  1174835734
    PARM_SIZE = 161,
        #define PARM_SIZE_RAND  645813711

    PARM_LAST,
    PARM_MAX = PARM_LAST,
} PARM_CODE;

#endif //#if !defined(__CMD_RSP_AND_PARMS_DIC_H)
