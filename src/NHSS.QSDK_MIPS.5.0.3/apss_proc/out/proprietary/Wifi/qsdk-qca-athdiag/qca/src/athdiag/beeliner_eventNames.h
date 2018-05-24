/*
 * Copyright (c) 2017 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */
#include "./beelinerEventId.h"

#define LOW32 0
#define HIGH32 1
#define TOTAL_EVENTS 302
//Module ID declaration
#define TOP_LEVEL_MODULE_ID 0x0
#define SCH_MODULE_ID 0x1
#define PDG_MODULE_ID 0x2
#define TXDMA_MODULE_ID 0x3
#define RXDMA_MODULE_ID 0x4
#define OLE_MODULE_ID 0x5
#define CRYPTO_MODULE_ID 0x6
#define TXPCU_MODULE_ID 0x7
#define RXPCU_MODULE_ID 0x8
#define SW_MODULE_ID 0x9

//Module register address mapping
#define TOP_LEVEL_REG_ADDR_LOW32 0x360cc
#define TOP_LEVEL_REG_ADDR_HIGH32 0x360d0
#define SCH_REG_ADDR_LOW32 0x3f77c
#define SCH_REG_ADDR_HIGH32 0x3f780
#define PDG_REG_ADDR_LOW32 0x30058
#define PDG_REG_ADDR_HIGH32 0x3005c
#define TXDMA_REG_ADDR_LOW32 0x30448
#define TXDMA_REG_ADDR_HIGH32 0x3044c
#define RXDMA_REG_ADDR_LOW32 0x308d4
#define RXDMA_REG_ADDR_HIGH32 0x308d4
#define OLE_REG_ADDR_LOW32 0x30d38
#define OLE_REG_ADDR_HIGH32 0x30d3c
#define CRYPTO_REG_ADDR_LOW32 0x3f0a0
#define CRYPTO_REG_ADDR_HIGH32 0x3f0a0
#define TXPCU_REG_ADDR_LOW32 0x360cc
#define TXPCU_REG_ADDR_HIGH32 0x360d0
#define RXPCU_REG_ADDR_LOW32 0x321dc
#define RXPCU_REG_ADDR_HIGH32 0x321e0
#define SW_REG_ADDR_LOW32 0x360cc
#define SW_REG_ADDR_HIGH32 0x360d0

//Module register default value declaration
#define TOP_LEVEL_REG_VALUE_LOW32 0
#define TOP_LEVEL_REG_VALUE_HIGH32 0
#define SCH_REG_VALUE_LOW32 0
#define SCH_REG_VALUE_HIGH32 0
#define PDG_REG_VALUE_LOW32 0
#define PDG_REG_VALUE_HIGH32 0
#define TXDMA_REG_VALUE_LOW32 0
#define TXDMA_REG_VALUE_HIGH32 0
#define RXDMA_REG_VALUE_LOW32 0
#define RXDMA_REG_VALUE_HIGH32 0
#define OLE_REG_VALUE_LOW32 0
#define OLE_REG_VALUE_HIGH32 0
#define CRYPTO_REG_VALUE_LOW32 0
#define CRYPTO_REG_VALUE_HIGH32 0
#define TXPCU_REG_VALUE_LOW32 0
#define TXPCU_REG_VALUE_HIGH32 0
#define RXPCU_REG_VALUE_LOW32 0
#define RXPCU_REG_VALUE_HIGH32 0
#define SW_REG_VALUE_LOW32 0
#define SW_REG_VALUE_HIGH32 0

//tracer config reg default value declaration
#define MAC_TRC_TS1_CAPTURE_CTRL_ADDRESS_VALUE 0x0
#define MAC_TRC_TS1_STATE_CTRL_ADDRESS_VALUE 0x0
#define MAC_TRC_TS1_TRIG_MASK_ADDRESS_VALUE 0x0
#define MAC_TRC_TS1_TRIG_ADDRESS_VALUE 0x0

#define MAC_TRC_TS2_CAPTURE_CTRL_ADDRESS_VALUE 0x0
#define MAC_TRC_TS2_STATE_CTRL_ADDRESS_VALUE 0x0
#define MAC_TRC_TS2_TRIG_MASK_ADDRESS_VALUE 0x0
#define MAC_TRC_TS2_TRIG_ADDRESS_VALUE 0x0

#define MAC_TRC_TS3_CAPTURE_CTRL_ADDRESS_VALUE 0x0
#define MAC_TRC_TS3_STATE_CTRL_ADDRESS_VALUE 0x0
#define MAC_TRC_TS3_TRIG_MASK_ADDRESS_VALUE 0x0
#define MAC_TRC_TS3_TRIG_ADDRESS_VALUE 0x0

#define MAC_TRC_TS4_CAPTURE_CTRL_ADDRESS_VALUE 0x0
#define MAC_TRC_TS4_STATE_CTRL_ADDRESS_VALUE 0x0
#define MAC_TRC_TS4_TRIG_MASK_ADDRESS_VALUE 0x0
#define MAC_TRC_TS4_TRIG_ADDRESS_VALUE 0x0

#define MAC_TRC_TS5_CAPTURE_CTRL_ADDRESS_VALUE 0x0
#define MAC_TRC_TS5_STATE_CTRL_ADDRESS_VALUE 0x0
#define MAC_TRC_TS5_TRIG_MASK_ADDRESS_VALUE 0x0
#define MAC_TRC_TS5_TRIG_ADDRESS_VALUE 0x0

#define MAC_TRC_WFT_CAPTURE_CTRL_ADDRESS_VALUE 0x0
#define MAC_TRC_WFT_STATE_CTRL_ADDRESS_VALUE 0x0

typedef struct{
	A_UINT32 regAddr;
	A_UINT32 regValue;
}regInfo;
//tracer config registers start
	regInfo mac_trc_ts[5][4] = {
									{//element 0---TS1
											{MAC_TRC_TS1_CAPTURE_CTRL_ADDRESS,MAC_TRC_TS1_CAPTURE_CTRL_ADDRESS_VALUE},
											{MAC_TRC_TS1_STATE_CTRL_ADDRESS,MAC_TRC_TS1_STATE_CTRL_ADDRESS_VALUE},
											{MAC_TRC_TS1_TRIG_MASK_ADDRESS,MAC_TRC_TS1_TRIG_MASK_ADDRESS_VALUE},
											{MAC_TRC_TS1_TRIG_ADDRESS,MAC_TRC_TS1_TRIG_ADDRESS_VALUE}
									},
									{//element 1---TS2
											{MAC_TRC_TS2_CAPTURE_CTRL_ADDRESS,MAC_TRC_TS2_CAPTURE_CTRL_ADDRESS_VALUE},
											{MAC_TRC_TS2_STATE_CTRL_ADDRESS,MAC_TRC_TS2_STATE_CTRL_ADDRESS_VALUE},
											{MAC_TRC_TS2_TRIG_MASK_ADDRESS,MAC_TRC_TS2_TRIG_MASK_ADDRESS_VALUE},
											{MAC_TRC_TS2_TRIG_ADDRESS,MAC_TRC_TS2_TRIG_ADDRESS_VALUE}
									},
									{//element 2---TS3
											{MAC_TRC_TS3_CAPTURE_CTRL_ADDRESS,MAC_TRC_TS3_CAPTURE_CTRL_ADDRESS_VALUE},
											{MAC_TRC_TS3_STATE_CTRL_ADDRESS,MAC_TRC_TS3_STATE_CTRL_ADDRESS_VALUE},
											{MAC_TRC_TS3_TRIG_MASK_ADDRESS,MAC_TRC_TS3_TRIG_MASK_ADDRESS_VALUE},
											{MAC_TRC_TS3_TRIG_ADDRESS,MAC_TRC_TS3_TRIG_ADDRESS_VALUE}
									},
									{//element 3---TS4
											{MAC_TRC_TS4_CAPTURE_CTRL_ADDRESS,MAC_TRC_TS4_CAPTURE_CTRL_ADDRESS_VALUE},
											{MAC_TRC_TS4_STATE_CTRL_ADDRESS,MAC_TRC_TS4_STATE_CTRL_ADDRESS_VALUE},
											{MAC_TRC_TS4_TRIG_MASK_ADDRESS,MAC_TRC_TS4_TRIG_MASK_ADDRESS_VALUE},
											{MAC_TRC_TS4_TRIG_ADDRESS,MAC_TRC_TS4_TRIG_ADDRESS_VALUE}
									},
									{//element 4---TS5
											{MAC_TRC_TS5_CAPTURE_CTRL_ADDRESS,MAC_TRC_TS5_CAPTURE_CTRL_ADDRESS_VALUE},
											{MAC_TRC_TS5_STATE_CTRL_ADDRESS,MAC_TRC_TS5_STATE_CTRL_ADDRESS_VALUE},
											{MAC_TRC_TS5_TRIG_MASK_ADDRESS,MAC_TRC_TS5_TRIG_MASK_ADDRESS_VALUE},
											{MAC_TRC_TS5_TRIG_ADDRESS,MAC_TRC_TS5_TRIG_ADDRESS_VALUE}
									}
								};
	
	regInfo mac_trc_wft[2] = {
									{MAC_TRC_WFT_CAPTURE_CTRL_ADDRESS,MAC_TRC_WFT_CAPTURE_CTRL_ADDRESS_VALUE},
									{MAC_TRC_WFT_STATE_CTRL_ADDRESS,MAC_TRC_WFT_STATE_CTRL_ADDRESS_VALUE}
							 };
//tracer config registers end
	regInfo moduleRegInfo[10][2] = {
										{//element 0
											{TOP_LEVEL_REG_ADDR_LOW32,TOP_LEVEL_REG_VALUE_LOW32},
											{TOP_LEVEL_REG_ADDR_HIGH32,TOP_LEVEL_REG_VALUE_HIGH32}
										},
										{//element 1
											{SCH_REG_ADDR_LOW32,SCH_REG_VALUE_LOW32},
											{SCH_REG_ADDR_HIGH32,SCH_REG_VALUE_HIGH32}
										},
										{//element 2
											{PDG_REG_ADDR_LOW32,PDG_REG_VALUE_LOW32},
											{PDG_REG_ADDR_HIGH32,PDG_REG_VALUE_HIGH32}
										},
										{//element 3
											{TXDMA_REG_ADDR_LOW32,TXDMA_REG_VALUE_LOW32},
											{TXDMA_REG_ADDR_HIGH32,TXDMA_REG_VALUE_HIGH32}
										},
										{//element 4
											{RXDMA_REG_ADDR_LOW32,RXDMA_REG_VALUE_LOW32},
											{RXDMA_REG_ADDR_HIGH32,RXDMA_REG_VALUE_HIGH32}
										},
										{//element 5
											{OLE_REG_ADDR_LOW32,OLE_REG_VALUE_LOW32},
											{OLE_REG_ADDR_HIGH32,OLE_REG_VALUE_HIGH32}
										},
										{//element 6
											{CRYPTO_REG_ADDR_LOW32,CRYPTO_REG_VALUE_LOW32},
											{CRYPTO_REG_ADDR_HIGH32,CRYPTO_REG_VALUE_HIGH32}
										},
										{//element 7
											{TXPCU_REG_ADDR_LOW32,TXPCU_REG_VALUE_LOW32},
											{TXPCU_REG_ADDR_HIGH32,TXPCU_REG_VALUE_HIGH32}
										},
										{//element 8
											{RXPCU_REG_ADDR_LOW32,RXPCU_REG_VALUE_LOW32},
											{RXPCU_REG_ADDR_HIGH32,RXPCU_REG_VALUE_HIGH32}
										},
										{//element 9
											{SW_REG_ADDR_LOW32,SW_REG_VALUE_LOW32},
											{SW_REG_ADDR_HIGH32,SW_REG_VALUE_HIGH32}
										}
									};
	
	A_UINT32 eventIdInfo[] = { 	TOP_LEVEL_HW_ERR_AND_EVENT_COLLISION_EVENT_ID,
TOP_LEVEL_EVENT_COLLISION_EVENT_ID,
TOP_LEVEL_HW_ERR_EVENT_ID,
SCH_HW_ERR_AND_EVENT_COLLISION_EVENT_ID,
SCH_EVENT_COLLISION_EVENT_ID,
SCH_HWSCH_CMD_LOAD_EVENT_ID,
SCH_HWSCH_CMD_START_EVENT_ID,
SCH_HWSCH_FES_START_EVENT_ID,
SCH_HWSCH_FES_FETCH_PHASE_EVENT_ID,
SCH_HWSCH_FES_PREBKOFF_FLUSH_EVENT_ID,
SCH_HWSCH_FES_TLVO_DONE_EVENT_ID,
SCH_HWSCH_FES_START_TX_EVENT_ID,
SCH_HWSCH_FES_BURST_CMD_PREFETCH_EVENT_ID,
SCH_HWSCH_FES_BURST_SCHTLV_DONE_EVENT_ID,
SCH_HWSCH_FES_STATUS_RCVD_EVENT_ID,
SCH_HWSCH_FES_FSTATS_UPDATE_EVENT_ID,
SCH_HWSCH_FES_CSTATS_UPDATE_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING15_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING14_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING13_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING12_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING11_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING10_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING9_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING8_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING7_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING6_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING5_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING4_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING3_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING2_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING1_EVENT_ID,
SCH_HWSCH_FES_TERMINATION_RING0_EVENT_ID,
SCH_HWSCH_FES_TXOP_EVENT_ID,
SCH_HWSCH_FES_TLVIF_START_EVENT_ID,
SCH_HWSCH_FES_TLVIF_COMPLETE_EVENT_ID,
SCH_HWSCH_FES_TLVIF_FLUSH_EVENT_ID,
SCH_HWSCH_FES_ABORT_EVENT_ID,
SCH_HWSCH_MTU_CCA_EVENT_ID,
SCH_HWSCH_ASSERTION_EVENT_EVENT_ID,
PDG_HW_ERR_AND_EVENT_COLLISION_EVENT_ID,
PDG_EVENT_COLLISION_EVENT_ID,
PDG_HW_ERR_EVENT_ID,
PDG_WATCHDOG_TIMEOUT_EVENT_ID,
PDG_GOTO_IDLE_EVENT_ID,
PDG_FLUSH_OR_TX_FES_SETUP_EVENT_ID,
PDG_VALID_TX_FES_SETUP_EVENT_ID,
PDG_VALID_PDG_REPONSE_EVENT_ID,
PDG_VALID_PDG_FES_SETUP_EVENT_ID,
PDG_NEW_AMPDU_LENGTH_EVENT_ID,
PDG_MPDU_CALC_USER0_END0_EVENT_ID,
PDG_MPDU_CALC_USER0_END1_EVENT_ID,
PDG_MPDU_CALC_USER1_END0_EVENT_ID,
PDG_MPDU_CALC_USER1_END1_EVENT_ID,
PDG_MPDU_CALC_USER2_END0_EVENT_ID,
PDG_MPDU_CALC_USER2_END1_EVENT_ID,
PDG_MPDU_CALC_USER0_TXOP_EXCEED_END_EVENT_ID,
PDG_MPDU_CALC_USER1_TXOP_EXCEED_END_EVENT_ID,
PDG_MPDU_CALC_USER2_TXOP_EXCEED_END_EVENT_ID,
PDG_MPDU_CALC_CHECK_SOME_MPDU_EVENT_ID,
PDG_MPDU_CALC_CHECK_SOME_MPDU_TXOP_EXCEED_EVENT_ID,
PDG_MAIN_STATE_CHANGE_EVENT_ID,
PDG_COMP_ENG_STATE_CHANGE_EVENT_ID,
PDG_COMP_ENG_START_EVENT_ID,
PDG_COMP_ENG_DONE_EVENT_ID,
PDG_RESERVED0_EVENT_ID,
PDG_RESERVED1_EVENT_ID,
PDG_RESERVED2_EVENT_ID,
PDG_TXDMA_TO_PDG_IFTLV_EVENT_ID,
PDG_PDG_TO_HWSCH_IFTLV_EVENT_ID,
PDG_TXDMA_TO_PDG_IF_TERMINATED_TLV_EVENT_ID,
PDG_PDG_TO_HWSCH_IF_TERMINATED_TLV_EVENT_ID,
PDG_HWSCH_TO_PDG_IF_TLV_EVENT_ID,
PDG_PDG_TO_TXDMA_IF_TLV_EVENT_ID,
PDG_HWSCH_TO_PDG_IF_TERMINATED_TLV_EVENT_ID,
PDG_HWSCH_TO_TXPCU_IF_SW_TLV_EVENT_ID,
PDG_HWSCH_TO_TXPCU_IF_TLV_EVENT_ID,
TXDMA_HW_ERR_AND_EVENT_COLLISION_EVENT_ID,
TXDMA_EVENT_COLLISION_EVENT_ID,
TXDMA_HW_ERR_EVENT_ID,
TXDMA_EVENT_FES_SETUP_RCVD_EVENT_ID,
TXDMA_EVENT_BUFFERS_SETUP_RCVD_EVENT_ID,
TXDMA_EVENT_ALL_REQD_TLVS_RCVD_EVENT_ID,
TXDMA_EVENT_FLUSH_RCVD_EVENT_ID,
TXDMA_EVENT_FLUSH_REQ_RCVD_EVENT_ID,
TXDMA_EVENT_MPDU_LIMIT_STATUS_RCVD_EVENT_ID,
TXDMA_EVENT_OLE_BUF_STATUS_RCVD_EVENT_ID,
TXDMA_EVENT_PCU_BUF_STATUS_RCVD_EVENT_ID,
TXDMA_EVENT_EXCESS_MPDU_USR0_EVENT_ID,
TXDMA_EVENT_EXCESS_MPDU_USR1_EVENT_ID,
TXDMA_EVENT_EXCESS_MPDU_USR2_EVENT_ID,
TXDMA_EVENT_TXDATA_AXI_REQ_MADE_EVENT_ID,
TXDMA_EVENT_CVDATA_AXI_REQ_MADE_EVENT_ID,
TXDMA_EVENT_CV_PHASE_DONE_EVENT_ID,
TXDMA_EVENT_CV_START_SENT_EVENT_ID,
TXDMA_EVENT_MPDU_START_SENT_EVENT_ID,
TXDMA_EVENT_MSDU_START_SENT_EVENT_ID,
TXDMA_EVENT_DATA_TAG_SENT_EVENT_ID,
TXDMA_EVENT_MSDU_END_SENT_EVENT_ID,
TXDMA_EVENT_MPDU_END_SENT_EVENT_ID,
TXDMA_EVENT_CTRL_STATE_CHANGE_EVENT_ID,
TXDMA_EVENT_DMA_PHASE_DONE_EVENT_ID,
TXDMA_EVENT_TXDMA_IDLE_EVENT_ID,
RXDMA_HW_ERR_AND_EVENT_COLLISION_EVENT_ID,
RXDMA_EVENT_COLLISION_EVENT_ID,
RXDMA_HW_ERR_EVENT_ID,
RXDMA_WATCHDOG_TIMEOUT_EVENT_ID,
RXDMA_TLV_IS_TYPE_UNKNOWN_EVENT_ID,
RXDMA_TLV_IS_PPDU_START_EVENT_ID,
RXDMA_TLV_IS_PPDU_END_EVENT_ID,
RXDMA_TLV_IS_MPDU_START_EVENT_ID,
RXDMA_TLV_IS_MPDU_END_EVENT_ID,
RXDMA_TLV_IS_MSDU_START_EVENT_ID,
RXDMA_TLV_IS_MSDU_END_EVENT_ID,
RXDMA_TLV_IS_RX_ATTENTION_EVENT_ID,
RXDMA_TLV_IS_RX_HEADER_EVENT_ID,
RXDMA_TLV_IS_RX_PACKET_EVENT_ID,
RXDMA_TLV_IS_FRAGINFO_EVENT_ID,
RXDMA_STATE_TLV_START_EVENT_ID,
RXDMA_RING_HW_IDX_OVERWRITE_EVENT_ID,
RXDMA_INTR_RING_LWM_EVENT_ID,
RXDMA_RING_STOP_ACK_EVENT_ID,
OLE_HW_ERR_AND_EVENT_COLLISION_EVENT_ID,
OLE_EVENT_COLLISION_EVENT_ID,
OLE_EVENT_ERROR_EVENT_ID,
OLE_TX_BAD_FRAME_RECVD_EVENT_ID,
OLE_TX_FES_SETUP_RECVD_EVENT_ID,
OLE_TX_QUEUE_EXT_RECVD_EVENT_ID,
OLE_TX_PEER_ENTRY_RECVD_EVENT_ID,
OLE_TX_MPDU_START_RECVD_EVENT_ID,
OLE_TX_MSDU_START_RECVD_EVENT_ID,
OLE_TX_MSDU_DATA_RECVD_EVENT_ID,
OLE_TX_MSDU_END_RECVD_EVENT_ID,
OLE_TX_MPDU_END_RECVD_EVENT_ID,
OLE_TX_BUFFER_CHAIN_MODE_EVENT_ID,
OLE_TX_L2_HEADER_PARSING_DONE_EVENT_ID,
OLE_TX_ENCAPSULATION_DONE_EVENT_ID,
OLE_TX_DATA_FRAME_WRITTEN_TO_FIFO_EVENT_ID,
OLE_TX_MPDU_HDR_LEN_OVERWRITTEN_EVENT_ID,
OLE_TX_IP_CHECKSUM_OVERWRITTEN_EVENT_ID,
OLE_TX_IP_TOT_LEN_OVERWRITTEN_EVENT_ID,
OLE_TX_IP_IDENTIFICATION_OVERWRITTEN_EVENT_ID,
OLE_TX_TCP_SEQ_NUM_WORD1_OVERWRITTEN_EVENT_ID,
OLE_TX_TCP_SEQ_NUM_WORD2_OVERWRITTEN_EVENT_ID,
OLE_TX_TCP_FLAGS_OVERWRITTEN_EVENT_ID,
OLE_TX_L4_CHECKSUM_OVERWRITTEN_EVENT_ID,
OLE_TX_COMMAND_FIFO_WRITTEN_EVENT_ID,
OLE_TX_SHORT_FRAME_RECVD_EVENT_ID,
OLE_RXOLE_EVENT_WMAC_PARSER_ERR_EVENT_ID,
OLE_RXOLE_EVENT_ETH_PARSER_ERR_EVENT_ID,
OLE_RXOLE_EVENT_MSDU_LEN_ERR_EVENT_ID,
OLE_RXOLE_EVENT_PPDU_START_RCVD_EVENT_ID,
OLE_RXOLE_EVENT_MPDU_PCU_START_RCVD_EVENT_ID,
OLE_RXOLE_EVENT_MPDU_PKT_RCVD_EVENT_ID,
OLE_RXOLE_EVENT_ATTENTION_WR_BUF1_DONE_EVENT_ID,
OLE_RXOLE_EVENT_L4_HDR_DONE_EVENT_ID,
OLE_RXOLE_EVENT_WMAC_PARSER_DONE_EVENT_ID,
OLE_RXOLE_EVENT_DYN_DECAP_TURNED_OFF_EVENT_ID,
OLE_RXOLE_EVENT_ETH_PARSER_DONE_EVENT_ID,
OLE_RXOLE_EVENT_HDR_WR_BUF0_DONE_EVENT_ID,
OLE_RXOLE_EVENT_PPDU_START_WR_BUF1_DONE_EVENT_ID,
OLE_RXOLE_EVENT_HDR_WR_BUF1_DONE_EVENT_ID,
OLE_RXOLE_EVENT_MPDU_START_WR_BUF1_DONE_EVENT_ID,
OLE_RXOLE_EVENT_MSDU_START_WR_BUF1_DONE_EVENT_ID,
OLE_RXOLE_EVENT_DECAP_TO_ETH_HDR_WR_BUF1_DONE_EVENT_ID,
OLE_RXOLE_EVENT_DECAP_TO_NWIFI_HDR_WR_BUF1_DONE_EVENT_ID,
OLE_RXOLE_EVENT_MSDU_PACKET_WR_BUF1_DONE_EVENT_ID,
OLE_RXOLE_EVENT_MSDU_END_WR_BUF1_DONE_EVENT_ID,
OLE_RXOLE_EVENT_TLV_TERM_RCVD_EVENT_ID,
OLE_RXOLE_EVENT_MPDU_END_WR_BUF1_DONE_EVENT_ID,
OLE_RXOLE_EVENT_PPDU_END_WR_BUF1_DONE_EVENT_ID,
OLE_RXOLE_EVENT_SA_SEARCH_DONE_EVENT_ID,
OLE_RXOLE_EVENT_DA_SEARCH_DONE_EVENT_ID,
OLE_RXOLE_EVENT_FRAG_INFO_WR_BUF1_DONE_EVENT_ID,
CRYPTO_HW_ERR_AND_EVENT_COLLISION_EVENT_ID,
CRYPTO_EVENT_COLLISION_EVENT_ID,
CRYPTO_HW_ERR_EVENT_ID,
CRYPTO_TX_FES_SETUP_TLV_START_EVENT_ID,
CRYPTO_TX_DATA_USR0_TLV_START_EVENT_ID,
CRYPTO_TX_DATA_USR1_TLV_START_EVENT_ID,
CRYPTO_TX_DATA_USR2_TLV_START_EVENT_ID,
CRYPTO_RX_MPDU_START_TLV_START_EVENT_ID,
CRYPTO_RX_PACKET_TLV_START_EVENT_ID,
CRYPTO_TX_FLUSH_TLV_REC_EVENT_ID,
CRYPTO_MIC_LENGTH_CHK_FAIL_EVENT_ID,
CRYPTO_TX_TLV_OUT_OF_SEQUENCE_EVENT_ID,
CRYPTO_RX_TLV_OUT_OF_SEQUENCE_EVENT_ID,
CRYPTO_RX_MIC_ERROR_EVENT_ID,
CRYPTO_TX_ABORT_EVENT_ID,
CRYPTO_RX_ABORT_EVENT_ID,
CRYPTO_TX_FLUSH_REQ_GEN_EVENT_ID,
CRYPTO_ENCR_START_USR0_EVENT_ID,
CRYPTO_ENCR_START_USR1_EVENT_ID,
CRYPTO_ENCR_START_USR2_EVENT_ID,
CRYPTO_ENCR_END_USR0_EVENT_ID,
CRYPTO_ENCR_END_USR1_EVENT_ID,
CRYPTO_ENCR_END_USR2_EVENT_ID,
CRYPTO_DECR_START_EVENT_ID,
CRYPTO_DECR_END_EVENT_ID,
TXPCU_HW_ERR_AND_EVENT_COLLISION_EVENT_ID,
TXPCU_EVENT_COLLISION_EVENT_ID,
TXPCU_TXPCU_EVENT_ERROR_INTERRUPT_EVENT_ID,
TXPCU_TXPCU_EVENT_RCV_FRAME_EVENT_ID,
TXPCU_TXPCU_EVENT_CV_FRAME_INVALID_EVENT_ID,
TXPCU_TXPCU_EVENT_RESP_FRAME_LEN_TIMEOUT_EVENT_ID,
TXPCU_TXPCU_EVENT_RESP_FRAME_SENDING_PDG_REQ_EVENT_ID,
TXPCU_TXPCU_EVENT_RESP_FRAME_SIFS_ELAPSED_EVENT_ID,
TXPCU_TXPCU_EVENT_RESP_FRAME_TX_PHY_DESC_INVALID_EVENT_ID,
TXPCU_TXPCU_EVENT_RESP_FRAME_START_EVENT_ID,
TXPCU_TXPCU_EVENT_RESP_FRAME_PREAMBLE_TIMEOUT_EVENT_ID,
TXPCU_TXPCU_EVENT_RESP_FRAME_STATUS_NOT_OK_EVENT_ID,
TXPCU_TXPCU_EVENT_RESP_FRAME_WAIT_CCA_CLEAR_EVENT_ID,
TXPCU_TXPCU_EVENT_RESP_FRAME_RCVD_TX_PKT_END_EVENT_ID,
TXPCU_TXPCU_EVENT_RESP_FRAME_END_ERROR_EVENT_ID,
TXPCU_TXPCU_EVENT_RESP_FRAME_END_SUCCESSFUL_EVENT_ID,
TXPCU_TXPCU_EVENT_FES_SETUP_RCVD_EVENT_ID,
TXPCU_TXPCU_EVENT_START_TX_RCVD_EVENT_ID,
TXPCU_TXPCU_EVENT_GEN_FLUSH_RE_EVENT_ID,
TXPCU_TXPCU_EVENT_PROT_FRAME_START_EVENT_ID,
TXPCU_TXPCU_EVENT_DATA_FRAME_START_EVENT_ID,
TXPCU_TXPCU_EVENT_PROT_FRAME_PREAMBLE_TIMEOUT_EVENT_ID,
TXPCU_TXPCU_EVENT_PROT_FRAME_STATUS_NOT_OK_EVENT_ID,
TXPCU_TXPCU_EVENT_PROT_FRAME_WAIT_CCA_CLEAR_EVENT_ID,
TXPCU_TXPCU_EVENT_PROT_FRAME_RCVD_TX_PKT_END_EVENT_ID,
TXPCU_TXPCU_EVENT_PROT_FRAME_END_EVENT_ID,
TXPCU_TXPCU_EVENT_CTS_RESP_TIMEOUT_EVENT_ID,
TXPCU_TXPCU_EVENT_CTS_RESP_RCVD_WITH_ERROR_EVENT_ID,
TXPCU_TXPCU_EVENT_CTS_RESP_RCVD_BW_NOT_AVAIL_EVENT_ID,
TXPCU_TXPCU_EVENT_CTS_RESP_RCVD_EVENT_ID,
TXPCU_TXPCU_EVENT_DATA_FRAME_PREAMBLE_TIMEOUT_EVENT_ID,
TXPCU_TXPCU_EVENT_DATA_FRAME_STATUS_NOT_OK_EVENT_ID,
TXPCU_TXPCU_EVENT_DATA_FRAME_WAIT_CCA_CLEAR_NDP_EVENT_ID,
TXPCU_TXPCU_EVENT_DATA_FRAME_DATA_XFER_START_EVENT_ID,
TXPCU_TXPCU_EVENT_DATA_FRAME_WAIT_MAX_DATA_TIME_EVENT_ID,
TXPCU_TXPCU_EVENT_DATA_FRAME_RCVD_TX_PKT_END_EVENT_ID,
TXPCU_TXPCU_EVENT_DATA_FRAME_WAIT_CBF_EVENT_ID,
TXPCU_TXPCU_EVENT_DATA_FRAME_WAIT_CCA_CLEAR_DATA_EVENT_ID,
TXPCU_TXPCU_EVENT_DATA_FRAME_STATUS_UPDATE_START_EVENT_ID,
TXPCU_TXPCU_EVENT_DATA_FRAME_WAIT_ACK_EVENT_ID,
TXPCU_TXPCU_EVENT_DATA_FRAME_END_EVENT_ID,
TXPCU_TXPCU_EVENT_DATA_FRAME_RCVD_FLUSH_EVENT_ID,
TXPCU_TXPCU_EVENT_SENT_MSG_TLV_EVENT_ID,
TXPCU_TXPCU_EVENT_SEND_MPDU_LIMIT_STATUS_EVENT_ID,
TXPCU_TXPCU_EVENT_CV_START_RCVD_EVENT_ID,
TXPCU_TXPCU_EVENT_CV_DATA_XFER_START_EVENT_ID,
TXPCU_TXPCU_EVENT_CV_DATA_XFER_END_EVENT_ID,
TXPCU_TXPCU_EVENT_SENT_BF_PARAMS_EVENT_ID,
TXPCU_TXPCU_EVENT_SVD_READY_RCVD_EVENT_ID,
TXPCU_TXPCU_EVENT_STATE_CHANGE_EVENT_ID,
RXPCU_HW_ERR_AND_EVENT_COLLISION_EVENT_ID,
RXPCU_EVENT_COLLISION_EVENT_ID,
RXPCU_HW_ERR_EVENT_ID,
RXPCU_EVENT_RXSM_STATE_EVENT_ID,
RXPCU_EVENT_RXSM_WCF_A_WR_EVENT_ID,
RXPCU_EVENT_RXSM_WCF_B_WR_EVENT_ID,
RXPCU_EVENT_RXSM_WCF_C_WR_EVENT_ID,
RXPCU_EVENT_RXSM_IS_DELIMITER_EVENT_ID,
RXPCU_EVENT_RXSM_FRAME_DONE_EVENT_ID,
RXPCU_EVENT_RXSM_RESP_REQ_MPDU_EVENT_ID,
RXPCU_EVENT_RXSM_RESP_REQ_EVENT_ID,
RXPCU_EVENT_RXSM_RESP_RCV_EVENT_ID,
RXPCU_EVENT_RXSM_SEND_RX_FRAME_INFO_EVENT_ID,
RXPCU_EVENT_RXSM_RX_PKT_END_DONE_EVENT_ID,
RXPCU_EVENT_RXSM_OVERFLOW_INT_EVENT_ID,
RXPCU_EVENT_DPSM_LAT_CMD_A_EVENT_ID,
RXPCU_EVENT_DPSM_ASE_ARB_EVENT_ID,
RXPCU_EVENT_DPSM_AST_DONE_EVENT_ID,
RXPCU_EVENT_DPSM_PTE_DONE_EVENT_ID,
RXPCU_EVENT_DPSM_UPDATE_PPDU_START_VALID_EVENT_ID,
RXPCU_EVENT_DPSM_UPDATE_MPDU_START_DONE_EVENT_ID,
RXPCU_EVENT_DPSM_UPDATE_PTE_DONE_EVENT_ID,
RXPCU_EVENT_DPSM_POP_CMD_B_EVENT_ID,
RXPCU_EVENT_DPSM_POP_CMD_AC_EVENT_ID,
RXPCU_EVENT_DPSM_CHECK_TLV_TERMINATE_EVENT_ID,
RXPCU_EVENT_DPSM_UPDATE_MPDU_END_DONE_EVENT_ID,
RXPCU_EVENT_DPSM_UPDATE_PPDU_END_DONE_EVENT_ID,
RXPCU_EVENT_TRIC_READ_PPDU_START_VALID_EVENT_ID,
RXPCU_EVENT_TRIC_XFER_MPDU_START_EVENT_ID,
RXPCU_EVENT_TRIC_XFER_PTE_EVENT_ID,
RXPCU_EVENT_TRIC_XFER_DATA_TLV_EVENT_ID,
RXPCU_EVENT_TRIC_XFER_MPDU_END_EVENT_ID,
RXPCU_EVENT_TRIC_XFER_PPDU_END_EVENT_ID,
RXPCU_EVENT_TRIC_XFER_TERMINATE_EVENT_ID,
RXPCU_EVENT_TRIC_ALL_DONE_EVENT_ID,
RXPCU_EVENT_SEND_RX_FRAME_RESP_CBF_EVENT_ID,
RXPCU_EVENT_SEND_RX_MESSAGE_PHY_ON_OFF_NAP_EVENT_ID,
RXPCU_EVENT_SEND_RX_MESSAGE_TXBF_EVENT_ID,
RXPCU_EVENT_SEND_RX_MESSAGE_RTT_IMPBF_EVENT_ID,
RXPCU_EVENT_SEND_RX_FRAME_RESP_DONE_EVENT_ID,
RXPCU_EVENT_TLVIN_RSSI_LEGACY_EVENT_ID,
RXPCU_EVENT_TLVIN_L_SIG_A_EVENT_ID,
RXPCU_EVENT_TLVIN_L_SIG_B_EVENT_ID,
RXPCU_EVENT_TLVIN_HT_SIG_EVENT_ID,
RXPCU_EVENT_TLVIN_VHT_SIG_A_EVENT_ID,
RXPCU_EVENT_TLVIN_VHT_SIG_B_EVENT_ID,
RXPCU_EVENT_TLVIN_SERVICE_EVENT_ID,
RXPCU_EVENT_TLVIN_RX_PKT_END_EVENT_ID,
RXPCU_EVENT_TLVIN_RX_PHY_PPDU_END_EVENT_ID,
RXPCU_EVENT_TLVIN_TLV_TERMINATE_EVENT_ID,
SW_HW_ERR_AND_EVENT_COLLISION_EVENT_ID,
SW_EVENT_COLLISION_EVENT_ID,
SW_HW_ERR_EVENT_ID
							  };

/*
#define TXPCU_TXPCU_EVENT_SENT_BF_PARAMS_EVENT_MASK 0x8000
#define TXPCU_TXPCU_EVENT_SENT_MSG_TLV_EVENT_MASK 0X2000
#define TXPCU_TXPCU_EVENT_START_TX_RCVD_EVENT_MASK 0X20000
#define TXPCU_TXPCU_EVENT_STATE_CHANGE_EVENT_MASK 0X20000
#define TXPCU_TXPCU_EVENT_SVD_READY_RCVD_EVENT_MASK 0X10000

#define TXPCU_TXPCU_EVENT_SENT_BF_PARAMS_EVENT_SELECT 0
#define TXPCU_TXPCU_EVENT_SENT_MSG_TLV_EVENT_SELECT 0
#define TXPCU_TXPCU_EVENT_START_TX_RCVD_EVENT_SELECT 0
#define TXPCU_TXPCU_EVENT_STATE_CHANGE_EVENT_SELECT 0
#define TXPCU_TXPCU_EVENT_SVD_READY_RCVD_EVENT_SELECT 0
#define SCH_HW_ERR_AND_EVENT_COLLISION_EVENT 0
#define SCH_HWSCH_FES_CSTATS_UPDATE_EVENST_SELECT 0
#define TOP_LEVEL_HW_ERR_EVENT_SELECT 0
*/
