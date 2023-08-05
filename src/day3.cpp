

#include "aoc_2022.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

static std::vector<std::string> test_data = {
    "vJrwpWtwJgWrhcsFMMfFFhFp", "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
    "PmmdzqPrVvPwwTWBwg",       "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
    "ttgJtRGJQctTZtZT",         "CrZsJsPPZsGzwwsLwLmpwMDw",
};

static std::vector<std::string> data = {
    "CjhshBJCSrTTsLwqwqwb",
    "GtmnFHlDfcpHbLZjtTTRLWwb",
    "fDfNHHjVFNvvrvVBJJdS",
    "PPWvWQjPhrPQwlMWJJdMDGbJTdCJ",
    "rsqsStgNNggBNBZHSrJGdJdCFRRZCFbGbTdJ",
    "qgBqqHzzggBpzSnBNqNSSSgcfhrVlVmwPljQVLVwVvQmmzVl",
    "bBBGBfmGvBTnGtGJBtGpcJbZrrddjqrZhDldwdcqrjrjDr",
    "HWPSQMsPHFsMWPVVMVSHCwDCDwwZZvwjwQZZwjdd",
    "vVHPgHHFRLfpfJTLLtJL",
    "LWLZhDBHhWWHjBwHwBjCTrBnnrQTQCJTJpTQBQ",
    "vvdcqbRmvwSFmRqPFSqwdvtQnrpCQJpNNVnrptVCtCCP",
    "wRSffqlFgvvdgdlzhLWWDzLljZhhGL",
    "LNbTbPdTNgnShgSjmHcqtQGCtrctCPcQqc",
    "vzWZDZZBlDwlzvDRZfFBRzVBtMMGHCcpjrqBGMtQQppqHtCq",
    "DfRvFZjZRsRjlVWsjFlWVWvdSdbhsSmnSngTdTSTsJdSLm",
    "nnZRbfZRTZfRsbZTFPRfpbRJdqqQNPwNqvvwvvvSwdQqdS",
    "WjDzjMWMHpQwcSQWcJSS",
    "hrHhHDgpphmjtMrGLDmGgmnbsflbfZCsnsClltsVsfRR",
    "QFngsFnGdLGFGVRgLLqWPQPWvBrMDppCPrDB",
    "NfcHZZzbHthSZtNtNfhHWhClDvCqlrqBvrCpWMWB",
    "fSMSHjbTMVgVVngVgT",
    "llnMffwbvCnffHvJJPJpPBNVVZDJDmmS",
    "QssGGHhRgcqjRRTWGWRGDZcVFZBpNBmPFBDSmZNP",
    "hzsRHWQshzgRjjsgQRTsbwzCtnrrlnrwzMCtvMff",
    "HdddHHmtDMDTqHHSftmqdmfdssGzrsjVGtrllWlGZGsnlnnp",
    "BQNPNPgPhBBhCJQhbCgCnrrnbZnlWznzpGssllVW",
    "LFNZRvCPCFZmHmTLcwdwcq",
    "zQRDChCnVhqRllpzQlzqCVVzPvNHTTFFHlNPsPNvTBPBHBFT",
    "wcfdfDmfPHjdsHPs",
    "cwGMwMMbwbmwJZfDSMmfwcpRVWzQqnnnzGVVnhqRVCph",
    "CScCSPcPszFJWSMjGZHMpGMjvG",
    "TTQfQvBTVBfrDVRDVqGMmjZqnpnGmMpnnpZZ",
    "NDdbrQdVQDNNfvTVNdBfrDBJFcsLWcCJzWFCcFLbFcFJsc",
    "WWdzhpHcHHrtzGBJMwmjJGmBtP",
    "CqsgqNrVnlCBCvPjCBmPJm",
    "LDDDLnVsqsgTQsgFcQzbQdprbWHzdb",
    "nFpNPGLGrntlrFLpflfBTcJwSgwQvGwbgSvbvJvT",
    "DHZWmMDZZDHPMHsDJQbbgSJcvbQgjwJM",
    "CRdzzdDDVRHWWNlPfPzllnFLlL",
    "ZJVqGSVCJCSgdSvtjtvcjcjbNl",
    "pmDWFnDFMnDdFLDHffjcbjjtBNctBjBMbMcl",
    "dLnfmdLLmrWsgZqCThgssgsq",
    "CLsvLLQvrlrrpLpw",
    "tmTHnNtgmzgWmpjlpjnwrrlRjw",
    "WHgTdmNJmJTDDrtFWsVGQqBQqcCCbhdvCB",
    "jwCHwmWRTWRWJwfcgVgflvPqPBPH",
    "MpphdbZZpZMNZpsdpZLMgjBlBqDvLPjfLVPBgPfv",
    "ZdrZsjQbnMCGwrRwzmTr",
    "CMDsWppsfhjNNzzzcBrbPgnrrnVBQHBNrV",
    "ZmGdTdvtStFDtTvtBHgPHnPHgnrnHVmH",
    "ZtLZdwdGqtZqLTLtwvfjDWcRscqMCDsCfWjf",
    "QQPPfPjLNLfSShfNRSRrrGHzvHrvlvnHRDJJ",
    "WCMJJVBwbGCbnbCl",
    "gBJmTBBMchsSjgfS",
    "NvCQGNRQQrWRpWhhvQrNLgrJqTVzzLFZsJqJZFcJTqFMJJ",
    "ttdBllbCSdcsJVVVzVMb",
    "CnwfwwdlnPGQgpnPvv",
    "WQmnmBBmWRCgDpndbD",
    "SvjsqGGqTSTdbggS",
    "lZbFJqLjvHZrcZNHcc",
    "gcgQhclQlntnnvBMZlwffTBLwv",
    "JqzNpqbmpJCbbzCfNFFqfWpZvDVTqBMTrTLvrTMTrvrZTT",
    "NbJWCpRWSFWNWJCzmRNRdchcdHcchnfncnhntcdjng",
    "JvDwhPWPzvzPDggWlvCQgPtHgtGnHtNqLqTnHTHHnnVg",
    "jBsfcbpdQsRcsSpRcjZjHNGtnnVncVtqTVVNVNNT",
    "prBbsjQdSbZdSFwMzrhPMWwzwlvC",
    "SStQfWQmJQjjhphQ",
    "sMVTwvLTswLwwqMPnnhglbHgglPh",
    "RDrRVrVCsrssBFWffFCZthfNFN",
    "ZnpgzcqgmhHtfwSDwplwVV",
    "QCrBNLdLrrnSVSrl",
    "LQQLLLjTBjGWnNBBGLFZbGgMcsMsZzbgbZZgsZ",
    "ZnbzbhqPbMrnDGjtQGSRVVMGpf",
    "gFdTlNJFGVGChJCt",
    "HgswWLNdhwTTwWsNNvzPmbvbcZbrsbrmzP",
    "SHpDqcJvBmJgJJHgDphHmvhTddWlLsZTTdFWMMsWtthZ",
    "GPrRCPfRfjjwffjrrnPVPsTLZFwLWMzLdTsTFzzFWT",
    "QPfZVNfbfQnRVjCRrPJBvSJgpDSDBHNgBJpB",
    "mjpcZcHcrqjrNmNpNmptHNHWwvCwgwCgMmQgRQsRMgwMvnCg",
    "DfSfFSVtDSTJVfdGJMwPnMRwnRCPQgMR",
    "DDfzDVdbTbzVDDtrtqlHptqbjbql",
    "lsBgqLqhqqgBBvGLBwQJJHRpJCJDHMwhwz",
    "NCVfntPnVnfrZtfdbTntnnWDDMDwwRRJmJDWRWJmHRzpJD",
    "ZrZbtbSZfdNVfbtCrbPTndsFvFLFSqcGLBFgvgjsgcqj",
    "gwRCCDmlZtPDdtBBPM",
    "VLrjccJVcJTfTtLjscVBHjHPjPQQSPpBHMjBhP",
    "rfcJrzvvctrscvzRqGRCZvmqbmwqZw",
    "nffqBWfRfRnpBfznpWTpTlWNNbcrDcbGbPhrGVwGlllPGN",
    "MsJQsmQLjMMFsmjbPZNcNbrbmGVhZZ",
    "LCJsFSsJFMFpfrTBWSvqpB",
    "vSspfvprpTNTZNTj",
    "LlFQCtnwMqqSmCMPmMSwClCJhBDJZZJZZjBTjQNjJbdjTT",
    "PHtwMLPqCHsfVRGvSR",
    "HjLDQMjtRvTmfTfmtf",
    "BddChcvvhwhqgmqTfnSmdg",
    "NBVVZJhZVhZsJJzhJZNHrRMPbQvHrjPvPDRvRN",
    "GgwtwntLQmNjvRGJGv",
    "wwzWzrzrqWjRlhJrNlrj",
    "wBWSCMPMcdnHsTHPsn",
    "MggMDDJzdbvsjCJvWJnJ",
    "THBGGScfHwHqHGTGTBqfSWCsnWBCbvsbshjRnZWZCn",
    "HwltftNGtmHHGqNlGmfPrVDDgzpVplpzDpVPbP",
    "shMdsCMpQMCZMQsZQVDJnvvPpPLSvLSLLV",
    "RmgzGTGRmClLNCvzVn",
    "rCrRftmftWjbTttjcdFZBcjdsFqZQFjZ",
    "qLwvNLtLvPGqSltLLqvNSpflMfQfMpMnBBggslMpfB",
    "VDcVzzDRRVTDgMPBBgdfQD",
    "VVWrcHbVzrzVjHPNqSmtqJJwjLGN",
    "nBswlBBhntTttbFVnt",
    "JNjTHZvLHDLVVLtCCFFPLz",
    "THvNddgZWQNDNZgjZSfGwfsBrhmfGBhcWs",
    "cCSbPmJqwqJjgJtTzJZT",
    "BpBTFFTQZzQgNgZv",
    "sFRVpsfrfrLfslwTcTccwcnCcTRC",
    "DLjLwDPjVPnWWvVWVjcqzSCJTzSzMTtSrqRqJn",
    "bdNGgmbGHdZdHbSRqrTJzrMtTR",
    "dhGmFffGQsWjshcVpt",
    "TrGzZpzWhCHcPPpF",
    "sqsJqtlqDVDJVJttgNSbsQPfcjQcBQjhFFRSPQHFRc",
    "VgqbtllbdvNtDdLZrHWGmwdrLM",
    "DNrqBvvZZNDDHBFJmMNbLMRctztznRsbds",
    "hlSlPPWfQCChPtWWfjTwLzbdRcbMsbMjnRLsgzsz",
    "PCfWwlQpTTVmmtqmVGrvmt",
    "lLrlLRbgrjRbRjFlRrnRRdgPdWdCwdWqmWPwqScdPc",
    "tDZLNGHsNQZDNBGHTCVSddVCPwVqVtcdWV",
    "BhGLBNvhHDTZDjfRvbfjljbbJf",
    "McRctHfDctZGlZZWgpcW",
    "TTQLQqLSLqTqhdLqPzLqLwrpsGpWVGFZGrlgWZGhFllV",
    "QNdzbQgzSvqPzqNqvnnbtfbRfDntCfMRjn",
    "bHQvFvffjpVvPSTvVm",
    "RDLRRDLBnVbsDsqDSb",
    "MtGGtJJnwnLltblMFCHfQcthjNfjHCQN",
    "FQfFldFCSRRFQSQmLVfRGwGDDGZDhDGwmmhZtthZ",
    "cTpscpCcNzNNvCBgbPPwvZGZggbghb",
    "TNzznnccTjTspHWNzCTpNlRRQnlfdVFVfLLJFrFJQQ",
    "LsMMLCQQQMTJnJMnsJlGlZJNvbNVGNNSDJ",
    "fhcBqmfvmtRftcmfVVNNVbZSSDVGZmgG",
    "BztFRjFjBchWzhvWTHWTMCdwTdTQnH",
    "cpddMRdHTSNRtRztbG",
    "mWvrQnQFhFNtsSNV",
    "vrBnlLvWvlPCCnrrmBrnQQLmTMHwHHccMgggTNjdcDwjNgCw",
    "hlRhqRnQQHcbBHGVVgRLVmrRgrLR",
    "sCFMTMwtzFMzTwCsswWjCsdQJmJLGfrrgLfgPmPVVVmtLP",
    "TMDjCFMTHShBQSDB",
    "fcpssfGWpRDnvDRWvD",
    "LMvQlPLtLQZbQjBqZBFnCRFZRFzR",
    "jlQrvjlbjbLffpdpdrmGwr",
    "hbRTjRRZthvSDvDn",
    "LGrwPfrGfLjqvBsHzBrvstBv",
    "mpCLCqqqLcwcwCLmLmwwdWgWgVVMTbbWbRdQVNjC",
    "QLCqzhzQDqhHsCJjTcVdScccSVgs",
    "NMPBBfwbmwmmGnfpTJJJcTrRjRJJddpr",
    "mflmdfBBlnPBvBNGnwlGzhDqzHZzZtCLZqqltHtL",
    "GGsFmSmFHHGZsqhSTQjlNQNzpptD",
    "JfVJvvJfWMPPnVVJvhlNlltDldzpjpTzQn",
    "LgLcwJffMMLcwPVvPMvsmRqTmbGGssgGssRRqG",
    "ScnbPhwPHPTbwCGJBDtNZZPZDsttNB",
    "FjfQlVVWrQgfQrrWfddnWfQlqJqJMNJBZJqsZtsJjJsvDjJq",
    "lrVngVQpmmmrlnLGLLmTzchcwhHh",
    "QZtDJqWZtWGmhJJjvVBP",
    "crNMSpcdNNFcrdzlrsVGVnvhmnvHbjVjjrhV",
    "NTszNMSpwTNFzcsTlsLRQLtWwZDDfQgZhggQ",
    "mfmdLLLqsvZzjfPgPT",
    "hppLhBNpHGrhHnQQhGMDhPbPbWzvZzbMzZFPbvbvgz",
    "BNGGNLGcQpCcSstSRmct",
    "mnjsJBjBRsmFsSRqqrGfrqqtrfrN",
    "LZDHZZzdcdQzLbcgLwGtNVrlGrMVNfrllHrH",
    "DPcZZzdQpZPzQQDpDdcpbcPgmBBBsnWfTBmnJmCsjjsPSTjJ",
    "jwwHjCPvLVmhmRdJvr",
    "gTBnbFGTTQMgnTbdbhHhrplhJdlV",
    "DTScZTgSSnGTBFzjDwtLtDDHqwwL",
    "RZWhWWRSgBRrdMRdCmtcdtLncHndqF",
    "bssspTjbVDQGTVGTQsJpbvLtVmFLqqHgnLmCcFnmHC",
    "DpfQJJQpDsGzzfDNhPBlPlMBNhghPZlW",
    "VzJrJMBntJpMnBBJMDDGDQLLQwwDpQLGLG",
    "WSFCWNWWWhQRzvNqLTRD",
    "CbSlSlWHghChhWlcclgcWdHgfrmbmznnffMZMztrMbrJBBBJ",
    "gtjBNTvDQNBPlBFlPFZPdP",
    "mCmpfJCVmMzmfsHpCWdGPWCCWZGtSFtF",
    "zJnhJnJzbbMMpnspmmfsJpLNgqtrjQvrTbTgLgtqgqLj",
    "CLJnZZCJLJZJgZZZJMLSTgnRdFWpFdfFWBffpqDBfjFWQdRD",
    "slNzNzzwwPQrfWmDmqBFWlDm",
    "zwHhsVHwQcHJCgnngMZn",
    "wLRLLddJLdZZZjHdRwgJsjqDVsDVSVGSscsVVmDq",
    "tvMWfnhMvnvztzzVSVqqmcSSVsDGmW",
    "TmhhpnnFlfMzMMRZRPTJRHwdPJZB",
    "sLsQSLvcSrbQbFGlWlCD",
    "BhgPBqBhPwmmpPlGhZMVCFFlbZGF",
    "nCBBTPBHdHwmfCvTLStLJSctrJtt",
    "vwNjwvBSSNndtdBJMJsLvZsJhZpPLM",
    "TmCQDHGTVTLhPQhpZprq",
    "CbCmmTzfVGfFGGCNbctwNPtcSnbjww",
    "NWQQdHdTddhGrnJjqCRggvRmhzmm",
    "wLLVHcFFFfwtFfJzqRvmRqzRVgVz",
    "MlwFfflbLFfbwctDplwcwFMMNNWdWNTNSWDQQnsQNWWHsrQH",
    "QlfbQrBjBQvfDBjhlpwpqbMzwWppGWqGwG",
    "VJNcVCJgcntgRcsZWpPDPDqzPTqqnTpL",
    "ZCRNRNmcJZCcNNVRmVdmHfjdrlfhSrvBDSfH",
    "MzzPjGpjpGPPjdtHBfBNBQBrbtlclV",
    "FqCnZcgcnFsWqmVHVHlgfBrbQVVb",
    "STmCLFZWnTsWvdvSSdvPpGcP",
    "lNjczlDNCSRMSmlR",
    "VbhwhgwGQgwpvQpVDpSCbmfnCPfnMnmPmmBn",
    "VhvGTdhwQwVVVsQQshjcDZdHdqzcDdJrjjzH",
    "DhPffCSLCPCwfPPqqwqVjHFjzljppl",
    "TBWBRWTMRBTTBTBdbQqztzQtWqzQFqbV",
    "sgGTBGTGmNvrGfrz",
    "hJgqGzqQmGQMQzgGmJGhJQSvZPfppjjPnZNTTTTpjWJvWp",
    "lbwbRsRdbdmLdrllbbDcrHwwnjvjNfPWWZwWPjPjjZnTZZpf",
    "dDDrdlDBHbDtVFSqmBShMMVF",
    "ddvtMZJdJTtDvgtfZJfvtWZlHpGljLRcBcjplLwGRnnLGlGc",
    "SNbFbrCNhQbrVQCQSCVzbLjBGRGRGwTBVwpnRGcHcw",
    "bbhrTzrbrPrSQFrTTCmFQPCJmJqvJfZZWftZmZJqDvgfJv",
    "vWLsTNNscttvNTLTLHRgcdqBnVSZVZVWVZqdSdJwwd",
    "jDrFMhGPbGGFFPChDGpGBdngZMzVSSwZgJSqgMSV",
    "bjjPQjphCPprhFrCCjFPDCTmcLgLtsTlmsNsQTtscQHt",
    "PdhqLdNccGsrNLpScBnDznjnBnzppQwpHz",
    "ftFtMbtfRMMWTvfRgRWbWMTjjzngzCzjzmDPjjwQDCDQmm",
    "MRWVVfWfbFWWTbFWlvvRWPJGSLSLNJcPVsqJPcLSGr",
    "fdRbPbHmnqvrvHDz",
    "psTdcMgjjNpllVVgjJslMdpMhrttthznDttBWttBvWcnzBvh",
    "gJjgVNFppjgCCVNsTTCsZbFwmmmmQGZSZLfwSZZd",
    "csDFpcpJFbccqpFqpfggJJsljhvlTvQQtjwPTmjPPjRTtNvh",
    "ZBGLddVCSVwNThhCQjPj",
    "ZHLLLrSHGSBzWWzHWpgwcFbJsfcgJbsrgg",
    "QJljRQLGJSNjMjQBLLJllFznzVCFpBnnzgwngpDCnD",
    "mHWrTmWrdZHWvdrdWrdZttsFspFVcpzcwcggzpwzwVwDVp",
    "vfzWvqTWWtPffWHqrWTZvTNSjRjQGGPPRbJbllQbMlJS",
    "DFnFprBLpHcSlJHRBl",
    "dbdMMCdsVWmMPlHSSVPVJfcf",
    "sllvhgsdLThDnhQF",
    "BSFTWCJWFJmBJdbcgDHgfDzHbncC",
    "MjMPNjhlslPPLjPqPqVcDttzLBHcgDggDggDbB",
    "MZhjMsBNNMhPrNjBrMhMPZWRmFmQFRRFFFQmWFQGFQ",
    "NFgqSSrtlNbNffffffmFFZCf",
    "WPvTBPPnBWmdJjCsPmVd",
    "zBwhwwTRWwhvvzTvnhCTnCnSbbqlNStNbLltDRDHRHqtDR",
    "NgggqJTHTJscdjggNVDVRcNHGLQWqpffZQGQGqpQWpWwQZfW",
    "vvBPBhBFrzvnzSSrrSzPMtWZZcWGwmLnWQWpQlwGwpnl",
    "rzbSCtrSttMctvvFMvrvPvgNJDRNHDsHNJsjTjsJJsVb",
    "HbGVfpJbmbpHLBfHbdChRDDwDRhFlMlFVDFr",
    "QzNQqcNgtqcNMjgqtntsgswRDDRQlFDSFQPDFRDwhCFR",
    "ngscZtsqsznnnszqTnnqHfLWLWLWZmJpWMJGLBZb",
    "cTNmqSbTBFhBQZjq",
    "vswHWHWzHMMttvGGwgppttRfZFZjfBnQnfQZBhwQfhRB",
    "lglsvMHHWHsWjHMtsvHvjWvTmJbCmcCcbCTcJlTmSmPSPT",
    "JjSBbBLppbrvZGhhhvGwZNRtNMPCqCPqRgCFRNMgjP",
    "lWlmDsdDnszRRwdCcNcdwd",
    "TsDwwVTWsHTmTWVzQflQJbSGhZrZZQBhvBSrJZSr",
    "JcrncrnrcZcGtJzfrrrzqbTWTlvW",
    "SCRSDRPSLgRDCHdjjgmdDSHqQTzlmTNNVWbqfbvQzQlbfb",
    "gpvpHHPPLdLRCSgjpLPtpZZMtnBMZJZBZBtMZs",
    "lQSvJllvHBPPHPHWSPQQJtDtnhbwDDwwtwfhrrVw",
    "MgLLdsMsgpRpTLLMgFrbFnfhNbbrhtwDwDDr",
    "MqpTpqGRLpMgBzGPSvlhSBhW",
    "NqpNNNPzhwzzshPwRPHWRmRFQWHDQPHD",
    "VcbcnbjbbrrbbcnbZQDHmlRSVlvZWRFm",
    "MttmjTtMrhqwhLhtdN",
    "dMggwDwvMdqgqqtqwHnzVnmGmGtGRrFmsJrN",
    "SlBClclffBPfZlssrGnJnZZzzznF",
    "ljfTPplCpLcpBBPfTBfcCTbvbDMMFhqdvqWpMWHMDMpd",
    "llTNZlhSvqMGlZMGhGgGlttrbVVwNjDbNFJbtjjDtN",
    "fQWCBWQBBpBCsmzPmnmddQccwJtjdVbJDtDcrrjwjbFr",
    "QzpQCRspPPPmzfppmmBBWLhgTZZTMRwSTgLlqvMqGG",
    "HSfnNllsHThcchcJBjJhRL",
    "FQQdzFCrFMbdFbrJBcqprcBrcBDqcB",
    "mtmMFJJmnTfnsHvm",
    "nddbfrBHdvbdBBhhhnWmtLsBGQCCtpmmMGPMQP",
    "cwVVqVNggDgjZDFspptttQrsPgpttp",
    "wDjczVZqSFDZVlSvrfhHlJHThh",
    "CttLqSPLqLHhhCdGGTgdlZfclNlsfglbTg",
    "nzFJpQJWVQjFmnmpjFWzVvBbMBTBNNTfTgZlTgFMNNZb",
    "njDDWpVWQjQnzZzjJjnRRwCqPtLLrSqhSwCPCHqG",
    "BFmNvfFNJRrdpMLLLVldWm",
    "jPjGGwqsndHZqJqM",
    "GtTSbjbtJjGQsQSSbPSGbzNgCRcCTCFhvfFgFFTBhfRc",
    "rwBvGlDrBMSzMvGVSBwMSZgnJmmJqmcTTTmVCFJRcTgF",
    "bbjpzLhHnFTLngLJ",
    "zdHQdQQftWfNfNtsSvrsGBPGlswrlvDw",
    "hdnMhghHZzFnZhDCCVTTTbtVmHmWbT",
    "PQscSNcllJwzwbGmTmWVGm",
    "sjprJpJjJNPpJBlpdFdgMzDDDhhvhd",
    "SMwBWSBMPSfzqzPf",
    "gJDlrFFQlgbFgvjDjTgrQQTGlhNNLdlqLGhNPqwPNPNfGf",
    "jvwHQQjrjrJrppjvJpDFgDgHcsZZnnsVHsmMWCnsBsVVWZ",
    "cblRJczlcBtBRCqNfGgHfpHCVHGp",
    "WZWsLWmSPjMdWFGHTVNgLfvHqGDT",
    "ZdmsFmZPmnZMsWWNsNjdmmmcQlrBQnBtQJtclBrtJwBzJz",
    "wtMNCNwNqwtMMRnVcTlFtlcnFlsl",
    "vrvrjzjZDDDwmwwVFT",
    "jzrHjrrHjjLBPfQPjZBZzvpSMwCNRpRwSdRCNLqSShSR",
    "BDgnhMDCDDpjDhBDJDfMSsLSZzCFTTLzTFLzTFZS",
    "lrqrlmqbvtvWwVRtwlmrrqNvZlZSsLTTFTFZSPzZFzzTBFzz",
    "HRRRbVmmwqhHHHhGJBcD",
    "MvnmMvNjvvvmNnRcvzHgzMGtzhffHwHtwt",
    "ZBBsFPPrTgCpSSBwHrLtwbHbLLtzLf",
    "ZBZZssBdWRJgmgJdNn",
    "TTLChzhDnjQLTDhTQJrzSbbJHsGrGrGFGb",
    "BfvvpflfWVlVsFFvJHcFJFrJrt",
    "ZwMBwwZPWMMpffflqlZMRnRNQLCNhPhDDNssnRQD",
};
void println(const std::set<char>* mySet)
{
    for (char value : *mySet)
        printf("%c", value);
    printf("\n");
}

int getCharacterPriority(char& value)
{
    if (97 <= value && value <= 122)
        return value - 96;
    else
        return (value - 64) + 26;
}

void part1(int& score)
{
    for (auto line : data)
    {
        std::set<char> lhs;
        std::set<char> rhs;
        for (int i = 0; i < line.length() / 2; i++)
        {
            const char* c_str = line.c_str();
            lhs.insert(c_str[i]);
            rhs.insert(c_str[(line.length() - 1) - i]);
        }

        std::set<char> result;
        std::set_intersection(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), std::inserter(result, result.begin()));
        char value = *result.rbegin();
        score += getCharacterPriority(value);
    }
}

void part2(int& score)
{
    std::set<char> groupSet;
    int counter = 0;
    for (auto line : data)
    {
        if (counter % 3 == 0 && counter)
        {
            auto value = *groupSet.rbegin();
            score += getCharacterPriority(value);
            groupSet.clear();
        }

        if (groupSet.size() == 0)
        {
            for (auto c : line)
                groupSet.insert(c);
        }
        else
        {
            std::set<char> groupSetCopy(groupSet.begin(), groupSet.end());
            groupSet.clear();

            std::set<char> lineSet;
            for (auto c : line)
                lineSet.insert(c);

            std::set_intersection(lineSet.begin(), lineSet.end(), groupSetCopy.begin(), groupSetCopy.end(),
                                  std::inserter(groupSet, groupSet.begin()));
        }

        counter++;
    }

    auto value = *groupSet.rbegin();
    score += getCharacterPriority(value);
}

void runDay3()
{
    int score = 0;
    part1(score);
    std::cout << "Part 1: " << score << std::endl;

    score = 0;
    part2(score);
    std::cout << "Part 2: " << score << std::endl;
}
