/* Copyright (c) 2022 Hygon Corporation
 * Copyright (c) 2020-2022 Alibaba Cloud
 * Copyright (c) 2022 Ant Group
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef UAL_VERIFICATION_PLATFORMS_CSV_CSV_H_
#define UAL_VERIFICATION_PLATFORMS_CSV_CSV_H_

#include <string>

#ifdef __cplusplus
extern "C" {
#endif

#define HYGON_CERT_SIZE 832
#define HYGON_CSV_CERT_SIZE 2084
#define HYGON_HSK_CEK_CERT_SIZE (HYGON_CERT_SIZE + HYGON_CSV_CERT_SIZE)

/* CSV attestation report */
#define HASH_BLOCK_SIZE 32
typedef struct {
  uint8_t block[HASH_BLOCK_SIZE];
} hash_block_t;

#define CSV_VM_ID_SIZE 16
#define CSV_VM_VERSION_SIZE 16
#define CSV_ATTESTATION_USER_DATA_SIZE 64
#define CSV_ATTESTATION_MNONCE_SIZE 16
#define CSV_ATTESTATION_CHIP_SN_SIZE 64
typedef struct __attribute__((__packed__)) csv_attestation_report_t {
  hash_block_t user_pubkey_digest;
  uint8_t vm_id[CSV_VM_ID_SIZE];
  uint8_t vm_version[CSV_VM_VERSION_SIZE];
  uint8_t user_data[CSV_ATTESTATION_USER_DATA_SIZE];
  uint8_t mnonce[CSV_ATTESTATION_MNONCE_SIZE];
  hash_block_t measure;
  uint32_t policy;
  uint32_t sig_usage;
  uint32_t sig_algo;
  uint32_t anonce;
  union {
    uint8_t sig1[72 * 2];
    struct {
      uint8_t r[72];
      uint8_t s[72];
    } ecc_sig1;
  };
  uint8_t pek_cert[HYGON_CSV_CERT_SIZE];
  uint8_t chip_id[CSV_ATTESTATION_CHIP_SN_SIZE];
  uint8_t reserved1[32];
  hash_block_t hmac;
  uint8_t reserved2[1548];  // Padding to a page size
} csv_attestation_report;

#include <stddef.h>
#define CSV_ATTESTATION_REPORT_SIGN_DATA_OFFSET \
  offsetof(csv_attestation_report, user_pubkey_digest)
#define CSV_ATTESTATION_REPORT_SIGN_DATA_SIZE    \
  (offsetof(csv_attestation_report, sig_usage) - \
   offsetof(csv_attestation_report, user_pubkey_digest))
#define CSV_ATTESTATION_REPORT_HMAC_DATA_OFFSET \
  offsetof(csv_attestation_report, pek_cert)
#define CSV_ATTESTATION_REPORT_HMAC_DATA_SIZE \
  (offsetof(csv_attestation_report, hmac) -   \
   offsetof(csv_attestation_report, pek_cert))

#ifdef __cplusplus
}
#endif

#endif  // UAL_VERIFICATION_PLATFORMS_CSV_CSV_H_
